#include "GameEngine.h"

namespace engine
{
	GameEngine::GameEngine()
		: mbInit(false)
		, mInput()
		, mTimer()
	{}

	GameEngine::~GameEngine()
	{
	}

	bool GameEngine::Init(const HINSTANCE hInstance, const HWND hWnd)
	{
		// 이미 초기화 되었다면 진행하지 않는다.
		if (mbInit)
		{
			return false;
		}

		if (!mInput.Init(hInstance, hWnd))
		{
			return false;
		}

		mTimer.Init();


		mbInit = true;
		return true;
	}

	InputManager& GameEngine::GetInput()
	{
		return mInput;
	}

	Timer& GameEngine::GetTimer()
	{
		return mTimer;
	}
}