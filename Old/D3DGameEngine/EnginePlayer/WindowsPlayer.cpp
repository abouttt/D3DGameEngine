#include "WindowsPlayer.h"

namespace wndplayer
{
	HINSTANCE Var::Instance = nullptr;
	HWND Var::WndHandler = nullptr;

	const TCHAR* Var::ClassName = _T("D3D_GAME_ENGINE");
	TCHAR Var::Title[64] = _T("D3D GAME ENGINE");
	TCHAR Var::PlayTitle[128];

	int Var::Width = 800;
	int Var::Height = 640;

	LRESULT CALLBACK WndProc(const HWND inHWND, const UINT32 inMSG, const WPARAM inWPARAM, const LPARAM inLPARAM)
	{
		switch (inMSG)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_KEYDOWN:
			if (inWPARAM == VK_ESCAPE)
			{
				DestroyWindow(inHWND);
			}
			break;
		}

		return ::DefWindowProc(inHWND, inMSG, inWPARAM, inLPARAM);
	}

	bool InitWindowsApp(const HINSTANCE inHINSTANCE, const int inWidth, const int inHeight)
	{
		Var::Instance = inHINSTANCE;

		WNDCLASS wc;
		::ZeroMemory(&wc, sizeof(wc));

		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = Var::Instance;
		wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = ::LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = Var::ClassName;

		if (!::RegisterClass(&wc))
		{
			::MessageBox(nullptr, _T("RegisterClass() - FAILED"), 0, 0);
			return false;
		}

		RECT rect{ 0, 0, inWidth, inHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
		int windowWidth = rect.right - rect.left;
		int windowHeight = rect.bottom - rect.top;

		Var::WndHandler = ::CreateWindow(Var::ClassName, Var::Title,
			WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
			0, 0, windowWidth, windowHeight,
			NULL /*parent hwnd*/, NULL /* menu */, Var::Instance, NULL /*extra*/);

		if (!Var::WndHandler)
		{
			::MessageBox(nullptr, _T("CreateWindow() - FAILED"), 0, 0);
			return false;
		}

		return true;
	}

	bool Tick()
	{
		MSG msg;
		::ZeroMemory(&msg, sizeof(msg));

		while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			::DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				return false;
			}
		}

		return true;
	}

	void Destroy()
	{
		DestroyWindow(Var::WndHandler);
	}
}