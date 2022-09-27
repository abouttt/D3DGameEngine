#include "GameObject.h"
#include "Behavior.h"

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
		// 컴포넌트 종류마다 알맞은 컴포넌트 컨테이너에서 제거한다.
		for (auto& component : mComponents)
		{
			component->removeFromEventContainer();
		}

		mTransformPtr = nullptr;
		mEnginePtr = nullptr;
	}

	bool GameObject::IsActive() const
	{
		return mbActive;
	}

	void GameObject::SetActive(const bool bActive)
	{
		// 현재 상태와 매개변수 상태가 같다면 진행하지 않는다.
		if (mbActive == bActive)
		{
			return;
		}

		for (auto& component : mComponents)
		{
			auto behavior = dynamic_cast<Behavior*>(component.get());
			if (behavior)
			{
				if (!behavior->IsActive())
				{
					continue;
				}

				if (bActive)
				{
					GetEngine()->GetBehaviorOnEnableQueue().emplace(behavior);
				}
				else
				{
					GetEngine()->GetBehaviorOnDisableQueue().emplace(behavior);
				}
			}
		}

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