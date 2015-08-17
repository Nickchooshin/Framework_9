#include "Input.h"

#include "EventSender.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "MouseButton.h"

namespace framework9
{
	macro_singleton2(Input);

	Input::Input()
		: m_directInput(nullptr)
		, m_windowHandle(nullptr)
		, m_directInputKeyboard(nullptr)
		, m_dwItemsKeyboard(0)
		, m_directInputMouse(nullptr)
		, m_dwItemsMouse(0)
	{
	}
	Input::~Input()
	{
		if (!m_directInput)
		{
			m_directInput->Release();
			m_directInput = nullptr;
		}

		// Keyboard
		if (!m_directInputKeyboard)
		{
			m_directInputKeyboard->Unacquire();
			m_directInputKeyboard->Release();
			m_directInputKeyboard = nullptr;
		}

		// Mouse
		if (!m_directInputMouse)
		{
			m_directInputMouse->Unacquire();
			m_directInputMouse->Release();
			m_directInputMouse = nullptr;
		}
	}

	bool Input::Init(HWND windowHandle)
	{
		if (!m_directInput)
		{
			HINSTANCE instanceHandle = GetModuleHandle(nullptr);

			if (FAILED(DirectInput8Create(instanceHandle, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, nullptr)))
			{
				MessageBox(NULL, L"DirectInput8Create Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}
		}

		if (m_windowHandle != windowHandle)
		{
			m_windowHandle = windowHandle;

			if (!InitKeyboard())
				return false;

			if (!InitMouse())
				return false;
		}

		return true;
	}

	void Input::Acquiring()
	{
		AcquiringKeyboard();
		AcquiringMouse();
	}

	// Keyboard
	bool Input::InitKeyboard()
	{
		if (!m_directInputKeyboard)
		{
			if (FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &m_directInputKeyboard, nullptr)))
			{
				MessageBox(NULL, L"Keyboard CreateDevice Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			DIPROPDWORD dipDW;
			ZeroMemory(&dipDW, sizeof(DIPROPDWORD));
			dipDW.diph.dwSize = sizeof(DIPROPDWORD);
			dipDW.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipDW.diph.dwObj = 0;
			dipDW.diph.dwHow = DIPH_DEVICE;
			dipDW.dwData = DINPUT_KEYBOARD_BUFFERSIZE;

			if (FAILED(m_directInputKeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipDW.diph)))
			{
				MessageBox(NULL, L"Keyboard SetProperty Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			if (FAILED(m_directInputKeyboard->SetDataFormat(&c_dfDIKeyboard)))
			{
				MessageBox(NULL, L"Keyboard SetDataFormat Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}
		}

		if (FAILED(m_directInputKeyboard->SetCooperativeLevel(m_windowHandle, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			MessageBox(NULL, L"Keyboard SetCooperativeLevel Fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		m_directInputKeyboard->Acquire();

		return true;
	}

	HRESULT Input::AcquiringKeyboard()
	{
		m_dwItemsKeyboard = DINPUT_KEYBOARD_BUFFERSIZE;

		if (FAILED(m_directInputKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didKeyboardBuffer, &m_dwItemsKeyboard, 0)))
		{
			m_directInputKeyboard->Acquire();
			return E_FAIL;
		}

		if (m_dwItemsKeyboard)
		{
			for (DWORD dwCurBuffer = 0; dwCurBuffer < m_dwItemsKeyboard; dwCurBuffer++)
			{
				bool isPressed = (m_didKeyboardBuffer[dwCurBuffer].dwData & 0x80) != 0;
				KeyCode keycode = (KeyCode)m_didKeyboardBuffer[dwCurBuffer].dwOfs;

				CEventKeyboard event(keycode, isPressed);
				EventSender::GetInstance()->Send(&event);
			}
		}

		return S_OK;
	}

	// Mouse
	bool Input::InitMouse()
	{
		if (!m_directInputMouse)
		{
			if (FAILED(m_directInput->CreateDevice(GUID_SysMouse, &m_directInputMouse, nullptr)))
			{
				MessageBox(NULL, L"Mouse CreateDevice Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			DIPROPDWORD dipDW;
			ZeroMemory(&dipDW, sizeof(DIPROPDWORD));
			dipDW.diph.dwSize = sizeof(DIPROPDWORD);
			dipDW.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipDW.diph.dwObj = 0;
			dipDW.diph.dwHow = DIPH_DEVICE;
			dipDW.dwData = DINPUT_MOUSE_BUFFERSIZE;

			if (FAILED(m_directInputMouse->SetProperty(DIPROP_BUFFERSIZE, &dipDW.diph)))
			{
				MessageBox(NULL, L"Mouse SetProperty Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}

			if (FAILED(m_directInputMouse->SetDataFormat(&c_dfDIMouse)))
			{
				MessageBox(NULL, L"Mouse SetDataFormat Fail", L"Error", MB_OK | MB_ICONERROR);
				return false;
			}
		}

		if (FAILED(m_directInputMouse->SetCooperativeLevel(m_windowHandle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) // DISCL_EXCLUSIVE, DISCL_NONEXCLUSIVE
		{
			MessageBox(NULL, L"Mouse SetCooperativeLevel Fail", L"Error", MB_OK | MB_ICONERROR);
			return false;
		}

		m_directInputMouse->Acquire();

		return true;
	}

	HRESULT Input::AcquiringMouse()
	{
		m_dwItemsMouse = DINPUT_MOUSE_BUFFERSIZE;

		if (FAILED(m_directInputMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_didMouseBuffer, &m_dwItemsMouse, 0)))
		{
			m_directInputMouse->Acquire();
			return E_FAIL;
		}

		bool isMouseMoved = false;
		int mouseButtonNum = 0;

		int mouseDeltaX = 0, mouseDeltaY = 0, mouseDeltaZ = 0;
		std::pair<MouseButton, bool> mouseButtonBuffer[DINPUT_MOUSE_BUFFERSIZE];

		if (m_dwItemsMouse)
		{
			for (DWORD dwCurBuffer = 0; dwCurBuffer < m_dwItemsMouse; dwCurBuffer++)
			{
				bool isPressed = (m_didMouseBuffer[dwCurBuffer].dwData & 0x80) != 0;
				int mouseDelta = (int)m_didMouseBuffer[dwCurBuffer].dwData;

				switch (m_didMouseBuffer[dwCurBuffer].dwOfs)
				{
				case DIMOFS_BUTTON0:
					mouseButtonBuffer[mouseButtonNum++] = std::make_pair(MouseButton::LEFT_BUTTON, isPressed);
					break;
				case DIMOFS_BUTTON1:
					mouseButtonBuffer[mouseButtonNum++] = std::make_pair(MouseButton::RIGHT_BUTTON, isPressed);
					break;
				case DIMOFS_BUTTON2:
					mouseButtonBuffer[mouseButtonNum++] = std::make_pair(MouseButton::MIDDLE_BUTTON, isPressed);
					break;
				case DIMOFS_X:
					mouseDeltaX += mouseDelta;
					isMouseMoved = true;
					break;
				case DIMOFS_Y:
					mouseDeltaY += mouseDelta;
					isMouseMoved = true;
					break;
				case DIMOFS_Z:
					mouseDeltaZ += mouseDelta;
					isMouseMoved = true;
					break;
				}
			}

			if (isMouseMoved)
			{
				CEventMouseMove event((float)mouseDeltaX, (float)mouseDeltaY, (float)mouseDeltaZ);
				EventSender::GetInstance()->Send(&event);
			}

			for (int i = 0; i < mouseButtonNum; i++)
			{
				CEventMouseButton event(mouseButtonBuffer[i].first, mouseButtonBuffer[i].second);
				EventSender::GetInstance()->Send(&event);
			}
		}

		return S_OK;
	}

	// Joystick
}