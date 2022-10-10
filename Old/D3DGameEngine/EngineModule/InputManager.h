#pragma once

#include <assert.h>
#include <dinput.h>
#include <wrl.h>

#include "D3DUtil.h"

namespace engine
{
	struct KeyInfo
	{
		bool IsPressed = false;
		bool IsPressing = false;
		bool IsUp = false;
	};

	class InputManager
	{
	public:
		InputManager();

	public:
		bool Init(
			const HINSTANCE inHINSTANCE,
			const HWND inHWND);
		bool Update();

		// 키보드.
		bool GetKey(const unsigned int inKey);
		bool GetKeyDown(const unsigned int inKey);
		bool GetKeyUp(const unsigned int inKey);

		// 마우스.
		bool GetMouseButtonDown(const int inButton);
		bool GetMouseButton(const int inButton);
		bool GetMouseButtonUp(const int inButton);

		LONG GetAxisMouseX();
		LONG GetAxisMouseY();

		void GetMousePosition(int* const outMouseX, int* const outMouseY);

	private:
		bool readKeyboard();
		bool readMouse();

	private:
		bool mbInit;

		Microsoft::WRL::ComPtr<IDirectInput> mInput;
		Microsoft::WRL::ComPtr<IDirectInputDevice> mKeyboard;
		Microsoft::WRL::ComPtr<IDirectInputDevice> mMouse;

		unsigned char mKeyboardState[256];
		KeyInfo mKeyboardInfo[256];

		DIMOUSESTATE mMouseState;
		KeyInfo mMouseInfo[4];
	};
}

