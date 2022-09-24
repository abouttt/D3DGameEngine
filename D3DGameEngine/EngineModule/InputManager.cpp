#include "InputManager.h"

namespace engine
{
	InputManager::InputManager()
		: mbInit(false)
		, mInput(nullptr)
		, mKeyboard(nullptr)
		, mMouse(nullptr)
		, mKeyboardState()
		, mKeyboardInfo()
		, mMouseState()
		, mMouseInfo()
	{}

	bool InputManager::Init(
		const HINSTANCE hInstance,
		const HWND hWnd)
	{
		// 이미 초기화 되었다면 진행하지 않는다.
		if (mbInit)
		{
			return false;
		}

		// Direct Input 초기화.
		if (FAILED(DirectInput8Create(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&mInput,
			nullptr)))
		{
			::MessageBox(nullptr, "InputManager - Init() - DirectInput8Create() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 키보드 생성.
		if (FAILED(mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, nullptr)))
		{
			::MessageBox(nullptr, "InputManager - Init() - CreateDevice() : Keyboard FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 키보드 데이터 형식 설정.
		if (FAILED(mKeyboard->SetDataFormat(&c_dfDIKeyboard)))
		{
			::MessageBox(nullptr, "InputManager - Init() - SetDataFormat() : Keyboard FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 키보드 협조레벨 설정.
		/*if (FAILED(mKeyboard->SetCooperativeLevel(
			inHWND,
			DISCL_FOREGROUND |
			DISCL_EXCLUSIVE)))
		{
			::MessageBox(nullptr, _T("Keyboard SetCooperativeLevel() - FAILED"), 0, 0);
			return false;
		}*/

		// 키보드 할당.
		if (FAILED(mKeyboard->Acquire()))
		{
			::MessageBox(nullptr, "InputManager - Init() - Acquire() : Keyboard FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 마우스 생성.
		if (FAILED(mInput->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
		{
			::MessageBox(nullptr, "InputManager - Init() - CreateDevice() : Mouse FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 마우스 데이터 형식 설정.
		if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
		{
			::MessageBox(nullptr, "InputManager - Init() - SetDataFormat() : Mouse FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// 마우스 협조레벨 설정.
		/*if (FAILED(mMouse->SetCooperativeLevel(
			inHWND,
			DISCL_NONEXCLUSIVE |
			DISCL_FOREGROUND)))
		{
			::MessageBox(nullptr, _T("Mouse SetCooperativeLevel() - FAILED"), 0, 0);
			return false;
		}*/

		// 마우스 할당.
		if (FAILED(mMouse->Acquire()))
		{
			::MessageBox(nullptr, "InputManager - Init() - Acquire() : Mouse FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		mbInit = true;
		return true;
	}

	bool InputManager::Update()
	{
		if (!readKeyboard())
		{
			return false;
		}

		for (int i = 0; i < 256; i++)
		{
			if (mKeyboardState[i] & 0x80)
			{
				mKeyboardInfo[i].IsPressed = !mKeyboardInfo[i].IsPressing ? true : false;
				mKeyboardInfo[i].IsPressing = true;
				mKeyboardInfo[i].IsUp = false;
			}
			else
			{
				mKeyboardInfo[i].IsUp = mKeyboardInfo[i].IsPressing ? true : false;
				mKeyboardInfo[i].IsPressed = false;
				mKeyboardInfo[i].IsPressing = false;
			}
		}

		// 마우스 처리.
		if (!readMouse())
		{
			return false;
		}

		for (int i = 0; i < 4; i++)
		{
			if (mMouseState.rgbButtons[i] & 0x80)
			{
				mMouseInfo[i].IsPressed = !mMouseInfo[i].IsPressing ? true : false;
				mMouseInfo[i].IsPressing = true;
				mMouseInfo[i].IsUp = false;
			}
			else
			{
				mMouseInfo[i].IsUp = mMouseInfo[i].IsPressing ? true : false;
				mMouseInfo[i].IsPressed = false;
				mMouseInfo[i].IsPressing = false;
			}
		}

		return true;
	}

	bool InputManager::GetKey(unsigned int key)
	{
		return mKeyboardInfo[key].IsPressing;
	}

	bool InputManager::GetKeyDown(unsigned int key)
	{
		return mKeyboardInfo[key].IsPressed;
	}

	bool InputManager::GetKeyUp(unsigned int key)
	{
		return mKeyboardInfo[key].IsUp;
	}

	bool InputManager::GetMouseButtonDown(int button)
	{
		return mMouseInfo[button].IsPressed;
	}

	bool InputManager::GetMouseButton(int button)
	{
		return mMouseInfo[button].IsPressing;
	}

	bool InputManager::GetMouseButtonUp(int button)
	{
		return mMouseInfo[button].IsUp;
	}

	LONG InputManager::GetAxisMouseX()
	{
		return mMouseState.lX;
	}

	LONG InputManager::GetAxisMouseY()
	{
		return mMouseState.lY;
	}

	void InputManager::GetMousePosition(int* const outMouseX, int* const outMouseY)
	{
		assert(outMouseX);
		assert(outMouseY);

		*outMouseX = mMouseState.lX;
		*outMouseY = mMouseState.lY;
	}

	bool InputManager::readKeyboard()
	{
		// 키보드 디바이스를 얻는다.
		HRESULT result = mKeyboard->GetDeviceState(sizeof(mKeyboardState), (LPVOID)&mKeyboardState);
		if (FAILED(result))
		{
			// 키보드가 포커스를 잃었거나 흭득되지 않은 경우 컨트롤을 다시 가져온다.
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				mKeyboard->Acquire();
			}
			else
			{
				return false;
			}
		}

		return true;
	}

	bool InputManager::readMouse()
	{
		// 마우스 디바이스를 얻는다.
		HRESULT result = mMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mMouseState);
		if (FAILED(result))
		{
			// 마우스가 포커스를 잃었거나 흭득되지 않은 경우 컨트롤을 다시 가져온다.
			if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			{
				mMouse->Acquire();
			}
			else
			{
				return false;
			}
		}

		return true;
	}
}