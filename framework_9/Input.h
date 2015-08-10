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

		LPDIRECTINPUTDEVICE8 m_directInputKeyboard;
		DIDEVICEOBJECTDATA m_didKeyboardBuffer[10];
		DWORD m_dwItemsKeyboard;

	public:
		bool Init(HWND windowHandle);

		void Acquiring();
	private:
		Input();
		Input(const Input&);
		~Input();

		bool InitKeyboard(HWND windowHandle);

		HRESULT AcquiringKeyboard();

		macro_singleton(Input);
	};
}

#endif