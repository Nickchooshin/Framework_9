#include <stdio.h>

#include "WindowsApp.h"
#include "SampleState.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define CRTDBG_MAP_ALLOC
#define new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(219) ;
#endif
	framework9::CWindowsApp app;

	if (app.Init(L"Sample Window"))
	{
		app.Run(new SampleState);
	}

	return 0;
}