#include "Behavior.h"
#include "Camera.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "Light.h"
#include "Transform.h"
#include "Text.h"

namespace engine
{
	GameEngine::GameEngine()
		: mbInit(false)
		, mLightCount(-1)
		, mInput()
		, mTimer()
		, mMainCameraPtr(nullptr)
		, mScene()
		, mBehaviorsPtr()
		, mLightsPtr()
		, mUIsPtr()
		, mBehaviorStartQueue()
		, mBehaviorOnDestroyQueue()
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

	Light* GameEngine::CreateLight(const std::string& name, D3DLIGHTTYPE lightType)
	{
		auto newGameObject = CreateGameObject(name);
		auto light = newGameObject->AddComponent<Light>();
		light->SetLightType(lightType);
		light->SetIndex(++mLightCount);
		return light;
	}

	Text* GameEngine::CreateText(const std::string& name)
	{
		auto newGameObject = CreateGameObject(name);
		auto text = newGameObject->AddComponent<Text>();
		return text;
	}

	GameObject* GameEngine::FindGameObject(const std::string& name)
	{
		auto it = findGameObjectIter(name);
		return it != mScene.end() ? (*it).get() : nullptr;
	}

	bool GameEngine::RemoveGameObject(const std::string& name)
	{
		auto it = findGameObjectIter(name);
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

	void GameEngine::SetMainCamera(Camera* camera)
	{
		mMainCameraPtr = camera;
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

	std::vector<Light*>& GameEngine::GetLights()
	{
		return mLightsPtr;
	}

	std::vector<UI*>& GameEngine::GetUIs()
	{
		return mUIsPtr;
	}

	std::queue<Behavior*>& GameEngine::GetBehaviorStartQueue()
	{
		return mBehaviorStartQueue;
	}

	std::queue<std::shared_ptr<Behavior>>& GameEngine::GetBehaviorOnDestroyQueue()
	{
		return mBehaviorOnDestroyQueue;
	}

	std::vector<Behavior*>::iterator GameEngine::BehaviorBegin()
	{
		return mBehaviorsPtr.begin();
	}

	std::vector<Behavior*>::iterator GameEngine::BehaviorEnd()
	{
		return mBehaviorsPtr.end();
	}

	std::vector<Light*>::iterator GameEngine::LightBegin()
	{
		return mLightsPtr.begin();
	}

	std::vector<Light*>::iterator GameEngine::LightEnd()
	{
		return mLightsPtr.end();
	}

	std::vector<UI*>::iterator GameEngine::UIBegin()
	{
		return mUIsPtr.begin();
	}

	std::vector<UI*>::iterator GameEngine::UIEnd()
	{
		return mUIsPtr.end();
	}

	std::vector<std::unique_ptr<GameObject>>::iterator GameEngine::findGameObjectIter(const std::string& name)
	{
		return std::find_if(mScene.begin(), mScene.end(),
			[&](auto& gameObject)
			{
				return gameObject.get()->GetName() == name;
			});
	}
}