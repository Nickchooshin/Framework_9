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

			if (!InitKeyboard(windowHandle))
				return false;

			if (!InitMouse(windowHandle))
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
	bool Input::InitKeyboard(HWND windowHandle)
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

		if (FAILED(m_directInputKeyboard->SetCooperativeLevel(windowHandle, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
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
				if (m_didKeyboardBuffer[dwCurBuffer].dwData & 0x80)
				{
					CEventKeyboard event((KeyCode)m_didKeyboardBuffer[dwCurBuffer].dwOfs, true);
					EventSender::GetInstance()->Send(&event);
				}
				else
				{
					CEventKeyboard event((KeyCode)m_didKeyboardBuffer[dwCurBuffer].dwOfs, false);
					EventSender::GetInstance()->Send(&event);
				}
			}
		}

		return S_OK;
	}

	// Mouse
	bool Input::InitMouse(HWND windowHandle)
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

		if (FAILED(m_directInputMouse->SetCooperativeLevel(windowHandle, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) // DISCL_EXCLUSIVE, DISCL_NONEXCLUSIVE
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

		int mouseDelta_X = 0;
		int mouseDelta_Y = 0;
		int mouseDelta_Z = 0;
		int buttonCount = 0;
		std::pair<MouseButton, bool> mouseButton[3];

		if (m_dwItemsMouse)
		{
			for (DWORD dwCurBuffer = 0; dwCurBuffer < m_dwItemsMouse; dwCurBuffer++)
			{
				switch (m_didMouseBuffer[dwCurBuffer].dwOfs)
				{
				case DIMOFS_BUTTON0:
					mouseButton[buttonCount++] = std::make_pair(MouseButton::LEFT_BUTTON, (m_didMouseBuffer[dwCurBuffer].dwData & 0x80) != 0);
					break;
				case DIMOFS_BUTTON1:
					mouseButton[buttonCount++] = std::make_pair(MouseButton::RIGHT_BUTTON, (m_didMouseBuffer[dwCurBuffer].dwData & 0x80) != 0);
					break;
				case DIMOFS_BUTTON2:
					mouseButton[buttonCount++] = std::make_pair(MouseButton::MIDDLE_BUTTON, (m_didMouseBuffer[dwCurBuffer].dwData & 0x80) != 0);
					break;
				case DIMOFS_X:
					mouseDelta_X += (int)m_didMouseBuffer[dwCurBuffer].dwData;
					break;
				case DIMOFS_Y:
					mouseDelta_Y += (int)m_didMouseBuffer[dwCurBuffer].dwData;
					break;
				case DIMOFS_Z:
					mouseDelta_Z += (int)m_didMouseBuffer[dwCurBuffer].dwData;
					break;
				}
			}

			if (mouseDelta_X || mouseDelta_Y || mouseDelta_Z)
			{
				CEventMouseMove event((float)mouseDelta_X, (float)mouseDelta_Y, (float)mouseDelta_Z);
				EventSender::GetInstance()->Send(&event);
			}

			for (int i = 0; i < buttonCount; i++)
			{
				CEventMouseButton event(mouseButton[i].first, mouseButton[i].second);
				EventSender::GetInstance()->Send(&event);
			}
		}

		return S_OK;
	}

	// Joystick
}