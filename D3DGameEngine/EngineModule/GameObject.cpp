#include "GameObject.h"

namespace engine
{
	GameObject::GameObject()
		: mbActive(true)
		, mName("GameObject")
		, mComponents()
		, mTransformPtr(nullptr)
		, mEnginePtr(nullptr)
	{}

	GameObject::GameObject(const std::string& name)
		: mbActive(true)
		, mName(name)
		, mComponents()
		, mTransformPtr(nullptr)
		, mEnginePtr(nullptr)
	{}

	GameObject::~GameObject()
	{
		mTransformPtr = nullptr;
		mEnginePtr = nullptr;
	}

	bool GameObject::IsActive() const
	{
		return mbActive;
	}

	void GameObject::SetActive(const bool bActive)
	{
		mbActive = bActive;
	}

	const std::string& GameObject::GetName() const
	{
		return mName;
	}

	void GameObject::SetName(const std::string& name)
	{
		mName = name;
	}

	Transform* GameObject::GetTransform()
	{
		return mTransformPtr;
	}

	const Transform* GameObject::GetTransform() const
	{
		return mTransformPtr;
	}

	GameEngine* GameObject::GetEngine()
	{
		return mEnginePtr;
	}

	const GameEngine* GameObject::GetEngine() const
	{
		return mEnginePtr;
	}
}