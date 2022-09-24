#include "WindowsPlayer.h"
#include "WindowsUtil.h"

int CALLBACK WinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PSTR lpCmdLine, const int nCmdShow)
{
	if (!wndplayer::InitWindowsApp(
		hInstance,
		wndplayer::gWidth, wndplayer::gHeight))
	{
		::MessageBox(nullptr, "WinMain() - InitWindowsApp() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	while (wndplayer::Tick())
	{
		//enginePlayer.OnTick();
	}

	wndplayer::Destroy();
	return 0;
}