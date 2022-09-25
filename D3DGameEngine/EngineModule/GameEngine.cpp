#include "Behavior.h"
#include "Camera.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Transform.h"
#include "Text.h"

namespace engine
{
	GameEngine::GameEngine()
		: mbInit(false)
		, mInput()
		, mTimer()
		, mScene()
		, mBehaviorsPtr()
		, mUIComponentsPtr()
		, mMainCameraPtr(nullptr)
	{}

	GameEngine::~GameEngine()
	{
		mMainCameraPtr = nullptr;
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

	GameObject* GameEngine::CreateGameObject(const std::string& name)
	{
		auto newGameObject = std::make_unique<GameObject>(name);
		newGameObject.get()->mTransformPtr = newGameObject.get()->AddComponent<Transform>();
		newGameObject.get()->mEnginePtr = this;
		mScene.emplace_back(std::move(newGameObject));
		return mScene.back().get();
	}

	Camera* GameEngine::CreateCamera(const std::string& name)
	{
		auto newGameObject = CreateGameObject(name);
		auto camera = newGameObject->AddComponent<Camera>();
		if (!mMainCameraPtr)
		{
			mMainCameraPtr = camera;
		}

		return camera;
	}

	Text* GameEngine::CreateText(const std::string& name)
	{
		auto newGameObject = CreateGameObject(name);
		auto text = newGameObject->AddComponent<Text>();
		return text;
	}

	GameObject* GameEngine::GetGameObject(const std::string& name)
	{
		auto it = getGameObjectIter(name);
		return it != mScene.end() ? (*it).get() : nullptr;
	}

	bool GameEngine::RemoveGameObject(const std::string& name)
	{
		auto it = getGameObjectIter(name);
		if (it != mScene.end())
		{
			mScene.erase(it);
			return true;
		}

		return false;
	}

	Camera* GameEngine::GetMainCamera()
	{
		return mMainCameraPtr;
	}

	InputManager& GameEngine::GetInput()
	{
		return mInput;
	}

	Timer& GameEngine::GetTimer()
	{
		return mTimer;
	}

	std::vector<Behavior*>& GameEngine::GetBehaviors()
	{
		return mBehaviorsPtr;
	}

	std::vector<UI*>& GameEngine::GetUIComponents()
	{
		return mUIComponentsPtr;
	}

	std::queue<Behavior*>& GameEngine::GetBehaviorStartQueue()
	{
		return mBehaviorStartQueue;
	}

	std::vector<Behavior*>::iterator GameEngine::BehaviorBegine()
	{
		return mBehaviorsPtr.begin();
	}

	std::vector<Behavior*>::iterator GameEngine::BehaviorEnd()
	{
		return mBehaviorsPtr.end();
	}

	std::vector<UI*>::iterator GameEngine::UIBegine()
	{
		return mUIComponentsPtr.begin();
	}

	std::vector<UI*>::iterator GameEngine::UIEnd()
	{
		return mUIComponentsPtr.end();
	}

	std::vector<std::unique_ptr<GameObject>>::iterator GameEngine::getGameObjectIter(const std::string& name)
	{
		return std::find_if(mScene.begin(), mScene.end(),
			[&](auto& gameObject)
			{
				return gameObject.get()->GetName() == name;
			});
	}
}