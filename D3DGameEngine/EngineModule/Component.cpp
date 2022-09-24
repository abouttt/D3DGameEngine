#include "Component.h"
#include "GameEngine.h"
#include "GameObject.h"

namespace engine
{
	Component::Component()
		: mGameEnginePtr(nullptr)
		, mGameObjectPtr(nullptr)
		, mTransformPtr(nullptr)
	{}

	Component::~Component()
	{
		mGameEnginePtr = nullptr;
		mGameObjectPtr = nullptr;
		mTransformPtr = nullptr;
	}

	GameEngine* Component::GetGameEngine()
	{
		return mGameEnginePtr;
	}

	const GameEngine* Component::GetGameEngine() const
	{
		return mGameEnginePtr;
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
