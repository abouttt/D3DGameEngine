#pragma once

#include <assert.h>
#include <memory>
#include <vector>
#include <string>

#include "D3DUtil.h"
#include "InputManager.h"
#include "Timer.h"

namespace engine 
{
	class Camera;
	class GameObject;

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

	public:
		bool Init(const HINSTANCE hInstance, const HWND hWnd);

	public: // 게임 오브젝트.
		GameObject* CreateGameObject(const std::string& name);

		GameObject* CreateCamera(const std::string& name);

		GameObject* GetGameObject(const std::string& name);
		bool RemoveGameObject(const std::string& name);

		Camera* GetMainCamera();

	public:
		InputManager& GetInput();
		Timer& GetTimer();

	private:
		std::vector<std::unique_ptr<GameObject>>::iterator getGameObjectIter(const std::string& name);

	private:
		bool mbInit;

		InputManager mInput;
		Timer mTimer;

		std::vector<std::unique_ptr<GameObject>> mScene;
		Camera* mMainCameraPtr;
	};
}
