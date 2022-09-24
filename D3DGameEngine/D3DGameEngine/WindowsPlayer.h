#pragma once

#include <Windows.h>

namespace wndplayer
{
	extern HINSTANCE gInstance;
	extern HWND gWndHandler;

	extern const TCHAR* gClassName;
	extern TCHAR gTitle[64];
	extern TCHAR gPlayTitle[128];

	extern int gWidth;
	extern int gHeight;

	LRESULT CALLBACK WndProc(const HWND hWnd, const UINT32 msg, const WPARAM wParam, const LPARAM lParam);
	bool InitWindowsApp(const HINSTANCE hInstance, const int width, const int height);
	bool Tick();
	void Destroy();
}