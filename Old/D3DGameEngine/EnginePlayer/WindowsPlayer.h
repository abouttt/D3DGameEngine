#pragma once

#include <tchar.h>
#include <Windows.h>

namespace wndplayer
{
	struct Var
	{
		static HINSTANCE Instance;
		static HWND WndHandler;

		static const TCHAR* ClassName;
		static TCHAR Title[64];
		static TCHAR PlayTitle[128];

		static int Width;
		static int Height;
	};

	LRESULT CALLBACK WndProc(const HWND inHWND, const UINT32 inMSG, const WPARAM inWPARAM, const LPARAM inLPARAM);
	bool InitWindowsApp(const HINSTANCE inHINSTANCE, const int inWidth, const int inHeight);
	bool Tick();
	void Destroy();
}

