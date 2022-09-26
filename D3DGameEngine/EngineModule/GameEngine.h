#pragma once

#include <assert.h>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <queue>

#include "D3DUtil.h"
#include "InputManager.h"
#include "Timer.h"

namespace engine
{
	class Behavior;
	class Camera;
	class GameObject;
	class Light;
	class UI;
	class Text;

	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

	public:
		bool Init(const HINSTANCE hInstance, const HWND hWnd);

	public: // 게임 오브젝트.
		GameObject* CreateGameObject(const std::string& name);
		Camera* CreateCamera(const std::string& name);
		Light* CreateLight(const std::string& name, D3DLIGHTTYPE lightType = D3DLIGHT_DIRECTIONAL);
		Text* CreateText(const std::string& name);

		GameObject* GetGameObject(const std::string& name);
		bool RemoveGameObject(const std::string& name);

		Camera* GetMainCamera();

	public: // 유틸.
		InputManager& GetInput();
		Timer& GetTimer();

	public: // 동적 생성된 컴포넌트.
		std::vector<Behavior*>& GetBehaviors();
		std::vector<Light*>& GetLights();
		std::vector<UI*>& GetUIs();

		std::queue<Behavior*>& GetBehaviorStartQueue();
		std::queue<std::shared_ptr<Behavior>>& GetBehaviorOnDestroyQueue();

		std::vector<Behavior*>::iterator BehaviorBegin();
		std::vector<Behavior*>::iterator BehaviorEnd();

		std::vector<Light*>::iterator LightBegin();
		std::vector<Light*>::iterator LightEnd();

		std::vector<UI*>::iterator UIBegin();
		std::vector<UI*>::iterator UIEnd();

	private:
		std::vector<std::unique_ptr<GameObject>>::iterator getGameObjectIter(const std::string& name);

	private:
		bool mbInit;
		DWORD mLightCount;

		InputManager mInput;
		Timer mTimer;

		std::vector<std::unique_ptr<GameObject>> mScene;
		std::vector<Behavior*> mBehaviorsPtr;
		std::vector<Light*> mLightsPtr;
		std::vector<UI*> mUIsPtr;

		std::queue<Behavior*> mBehaviorStartQueue;
		std::queue<std::shared_ptr<Behavior>> mBehaviorOnDestroyQueue;

		Camera* mMainCameraPtr;
	};
}
