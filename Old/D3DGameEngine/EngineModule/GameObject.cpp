#include "GameObject.h"
#include "GameEngine.h"

namespace engine
{
	GameObject::GameObject()
		: mbActive(true)
		, mName("GameObject")
		, mComponents()
		, mTransformPtr(nullptr)
		, mGameEnginePtr(nullptr)
	{}

	GameObject::GameObject(const std::string& inName)
		: mbActive(true)
		, mName(inName)
		, mComponents()
		, mTransformPtr(nullptr)
		, mGameEnginePtr(nullptr)
	{}

	GameObject::~GameObject()
	{
		mTransformPtr = nullptr;
		mGameEnginePtr = nullptr;
	}

	bool GameObject::IsActive() const
	{
		return mbActive;
	}

	void GameObject::SetActive(const bool inbActive)
	{
		mbActive = inbActive;
	}

	const std::string& GameObject::GetName() const
	{
		return mName;
	}

	void GameObject::SetName(const std::string& inName)
	{
		mName = inName;
	}

	Transform* GameObject::GetTransform()
	{
		return mTransformPtr;
	}

	const Transform* GameObject::GetTransform() const
	{
		return mTransformPtr;
	}

	GameEngine* GameObject::GetGameEngine()
	{
		return mGameEnginePtr;
	}

	const GameEngine* GameObject::GetGameEngine() const
	{
		return mGameEnginePtr;
	}
}
