#pragma once

#include <memory>
#include <type_traits>
#include <vector>
#include <string>

#include "Component.h"

namespace engine
{
	class Transform;
	class GameEngine;

	class GameObject
	{
	public:
		friend class GameEngine;

	public:
		GameObject();
		GameObject(const std::string& name);
		~GameObject();

	public:
		bool IsActive() const;
		void SetActive(const bool bActive);

		const std::string& GetName() const;
		void SetName(const std::string& name);

		Transform* GetTransform();
		const Transform* GetTransform() const;

		GameEngine* GetEngine();
		const GameEngine* GetEngine() const;

	public:
		template<typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<Component, T>::value);

			for (auto& c : mComponents)
			{
				auto t = dynamic_cast<T*>(c.get());
				if (t)
				{
					return t;
				}
			}

			return nullptr;
		}

		template<typename T, typename ...Args>
		T* AddComponent(Args&&...args)
		{
			static_assert(std::is_base_of<Component, T>::value);

			auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
			newComponent.get()->mGameObjectPtr = this;
			if (mTransformPtr)
			{
				newComponent.get()->mTransformPtr = mTransformPtr;
			}
			if (mEnginePtr)
			{
				newComponent.get()->mEnginePtr = mEnginePtr;
			}

			mComponents.emplace_back(std::move(newComponent));
			return static_cast<T*>(mComponents.back().get());
		}

		template<typename T>
		bool RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value);

			// 트랜스폼 컴포넌트는 제거 불가능.
			if (std::is_same<Transform, T>::value)
			{
				return false;
			}

			// 삭제할 컴포넌트를 찾는다.
			auto it = std::find_if(mComponents.begin(), mComponents.end(),
				[](auto& component)
				{
					return dynamic_cast<T*>(component.get());
				});

			if (it != mComponents.end())
			{
				mComponents.erase(it);
				return true;
			}

			return false;
		}

	private:
		bool mbActive;
		std::string mName;
		std::vector<std::unique_ptr<Component>> mComponents;
		Transform* mTransformPtr;
		GameEngine* mEnginePtr;
	};
}

