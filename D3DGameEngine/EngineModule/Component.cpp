#include "Component.h"
#include "GameEngine.h"
#include "GameObject.h"

namespace engine
{
	Component::Component()
		: mEnginePtr(nullptr)
		, mGameObjectPtr(nullptr)
		, mTransformPtr(nullptr)
	{}

	Component::~Component()
	{
		mEnginePtr = nullptr;
		mGameObjectPtr = nullptr;
		mTransformPtr = nullptr;
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
