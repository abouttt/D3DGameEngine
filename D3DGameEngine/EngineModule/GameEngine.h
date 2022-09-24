#pragma once

#include "InputManager.h"
#include "Timer.h"

namespace engine 
{
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

	public:
		bool Init(const HINSTANCE hInstance, const HWND hWnd);

	public:
		InputManager& GetInput();
		Timer& GetTimer();

	private:
		bool mbInit;

		InputManager mInput;
		Timer mTimer;
	};
}
