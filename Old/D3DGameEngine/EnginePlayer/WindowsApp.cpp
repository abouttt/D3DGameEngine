#include "D3DUtil.h"
#include "EnginePlayer.h"
#include "WindowsPlayer.h"
#include "WindowsUtil.h"

int CALLBACK WinMain(const HINSTANCE inHINSTANCE, const HINSTANCE inPrevHINSTANCE, const PSTR inCmdLine, const int inShowCmd)
{
	if (!wndplayer::InitWindowsApp(
		inHINSTANCE,
		wndplayer::Var::Width, wndplayer::Var::Height))
	{
		::MessageBox(nullptr, _T("InitWindowsApp() - FAILED"), 0, 0);
		return 0;
	}

	if (!d3d::InitD3D(
		inHINSTANCE,
		wndplayer::Var::WndHandler,
		wndplayer::Var::Width, wndplayer::Var::Height,
		true,
		D3DDEVTYPE_HAL,
		&d3d::Var::Device))
	{
		::MessageBox(nullptr, _T("InitD3D() - FAILED"), 0, 0);
		return 0;
	}

	EnginePlayer enginePlayer;
	enginePlayer.Init();

	wndutil::Show(wndplayer::Var::WndHandler);
	wndutil::SetCenterWindow(wndplayer::Var::WndHandler);

	while (wndplayer::Tick())
	{
		enginePlayer.OnTick();
	}

	d3d::Destroy();
	wndplayer::Destroy();
	return 0;
}