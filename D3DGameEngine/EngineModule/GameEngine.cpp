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
		// �̹� �ʱ�ȭ �Ǿ��ٸ� �������� �ʴ´�.
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