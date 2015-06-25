#include <stdio.h>

#include "WindowsApp.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	framework9::CWindowsApp app(hInstance);

	app.Init();

	app.Create(L"Sample Window");
	app.Loop();
	app.Destroy();

	return 0;
}