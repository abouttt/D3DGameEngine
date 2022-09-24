#include "D3DUtil.h"
#include "EnginePlayer.h"
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

	if (!d3d::InitD3D(
		hInstance,
		wndplayer::gWndHandler,
		wndplayer::gWidth, wndplayer::gHeight,
		true,
		D3DDEVTYPE_HAL,
		&d3d::gDevice))
	{
		::MessageBox(nullptr, "WinMain() - InitD3D() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	EnginePlayer enginePlayer;
	enginePlayer.Init();

	wndutil::Show(wndplayer::gWndHandler);
	wndutil::SetCenterWindow(wndplayer::gWndHandler);

	while (wndplayer::Tick())
	{
		enginePlayer.OnTick();
	}

	d3d::Destroy();
	wndplayer::Destroy();
	return 0;
}