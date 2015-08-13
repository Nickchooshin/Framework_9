#ifndef _INPUT_H_
#define _INPUT_H_

#include "Singleton.h"

#include <dinput.h>

namespace framework9
{
	const int DINPUT_KEYBOARD_BUFFERSIZE = 10;
	const int DINPUT_MOUSE_BUFFERSIZE = 16;

	class Input
	{
	private:
		LPDIRECTINPUT8 m_directInput;


		// Keyboard
		LPDIRECTINPUTDEVICE8 m_directInputKeyboard;
		DIDEVICEOBJECTDATA m_didKeyboardBuffer[DINPUT_KEYBOARD_BUFFERSIZE];
		DWORD m_dwItemsKeyboard;

		// Mouse
		LPDIRECTINPUTDEVICE8 m_directInputMouse;
		DIDEVICEOBJECTDATA m_didMouseBuffer[DINPUT_MOUSE_BUFFERSIZE];
		DWORD m_dwItemsMouse;

		// Joystick

	public:
		bool Init(HWND windowHandle);

		void Acquiring();
	private:
		Input();
		Input(const Input&);
		~Input();

		// Keyboard
		bool InitKeyboard(HWND windowHandle);
		HRESULT AcquiringKeyboard();

		// Mouse
		bool InitMouse(HWND windowHandle);
		HRESULT AcquiringMouse();

		// Joystick
		bool InitJoystick(HWND windowHandle);
		HRESULT AcquiringJoystick();

		macro_singleton(Input);
	};
}

#endif