#include "Component.h"
#include "GameEngine.h"
#include "GameObject.h"

namespace engine
{
	Component::Component()
		: mbActive(true)
		, mEnginePtr(nullptr)
		, mGameObjectPtr(nullptr)
		, mTransformPtr(nullptr)
	{}

	Component::~Component()
	{
		mEnginePtr = nullptr;
		mGameObjectPtr = nullptr;
		mTransformPtr = nullptr;
	}

	bool Component::IsActive() const
	{
		return mbActive;
	}

	void Component::SetActive(bool bActive)
	{
		// 현재 상태와 매개변수 상태가 같다면 진행하지 않는다.
		if (mbActive == bActive)
		{
			return;
		}

		mbActive = bActive;
	}

	GameEngine* Component::GetEngine()
	{
		return mEnginePtr;
	}

	const GameEngine* Component::GetEngine() const
	{
		return mEnginePtr;
	}

	GameObject* Component::GetGameObject()
	{
		return mGameObjectPtr;
	}

	const GameObject* Component::GetGameObject() const
	{
		return mGameObjectPtr;
	}

	Transform* Component::GetTransform()
	{
		return mTransformPtr;
	}

	const Transform* Component::GetTransform() const
	{
		return mTransformPtr;
	}
}
