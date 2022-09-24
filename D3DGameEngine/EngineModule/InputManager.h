#pragma once

#include <assert.h>
#include <dinput.h>

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
			const HINSTANCE hInstance,
			const HWND hWnd);
		bool Update();

		// 키보드.
		bool GetKey(const unsigned int key);
		bool GetKeyDown(const unsigned int key);
		bool GetKeyUp(const unsigned int key);

		// 마우스.
		bool GetMouseButtonDown(const int button);
		bool GetMouseButton(const int button);
		bool GetMouseButtonUp(const int button);

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

