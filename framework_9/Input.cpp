#include "Input.h"

#include "EventSender.h"
#include "EventKeyboard.h"

namespace framework9
{
	macro_singleton2(Input);

	Input::Input()
		: m_directInput(nullptr)
		, m_directInputKeyboard(nullptr)
		, m_didKeyboardBuffer()
		, m_dwItemsKeyboard(0)
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
		}

		if (!InitKeyboard(windowHandle))
			return false;
	}

	void Input::Acquiring()
	{
		AcquiringKeyboard();
	}

	bool Input::InitKeyboard(HWND windowHandle)
	{
		if (FAILED(m_directInput->CreateDevice(GUID_SysKeyboard, &m_directInputKeyboard, NULL)))
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
}