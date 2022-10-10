#pragma once

#include <assert.h>
#include <Windows.h>

namespace wndutil
{
	void GetWindowSize(const HWND inHWND, float* const outWidth, float* const outHeight)
	{
		assert(outWidth);
		assert(outHeight);

		RECT rect;
		GetClientRect(inHWND, &rect);
		*outWidth = static_cast<float>(rect.right - rect.left);
		*outHeight = static_cast<float>(rect.bottom - rect.top);
	}

	void Show(const HWND inHWND)
	{
		ShowWindow(inHWND, SW_SHOW);
		SetForegroundWindow(inHWND);
		SetFocus(inHWND);
	}

	void SetCenterWindow(const HWND inHWND)
	{
		// 부모 또는 화면 가운데에 놓는다.
		RECT rc, rcOwner, rcWindow;
		HWND ownerHandle = GetDesktopWindow();
		GetWindowRect(ownerHandle, &rcOwner);
		GetWindowRect(inHWND, &rcWindow);
		CopyRect(&rc, &rcOwner);

		OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top);
		OffsetRect(&rc, -rc.left, -rc.top);
		OffsetRect(&rc, -rcWindow.right, -rcWindow.bottom);

		SetWindowPos(inHWND, HWND_TOP,
			rcOwner.left + (rc.right / 2),
			rcOwner.top + (rc.bottom / 2),
			0, 0,
			SWP_NOSIZE);
	}
}