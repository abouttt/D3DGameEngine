#pragma once

#include <memory>
#include <type_traits>
#include <vector>
#include <string>

#include "Component.h"
#include "GameEngine.h"

namespace engine
{
	class Transform;
	class Light;
	class UI;

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

			// ������Ʈ �������� �˸��� ������Ʈ �����̳ʿ� �߰��Ѵ�.
			if (std::is_base_of<Behavior, T>::value)
			{
				mEnginePtr->GetBehaviors().emplace_back((Behavior*)newComponent.get());
				mEnginePtr->GetBehaviorStartQueue().emplace((Behavior*)newComponent.get());
			}
			else if (std::is_base_of<UI, T>::value)
			{
				mEnginePtr->GetUIComponents().emplace_back((UI*)newComponent.get());
			}
			else if (std::is_base_of<Light, T>::value)
			{
				mEnginePtr->GetLights().emplace_back((Light*)newComponent.get());
			}

			mComponents.emplace_back(std::move(newComponent));
			return static_cast<T*>(mComponents.back().get());
		}

		template<typename T>
		bool RemoveComponent()
		{
			static_assert(std::is_base_of<Component, T>::value);

			// Ʈ������ ������Ʈ�� ���� �Ұ���.
			if (std::is_same<Transform, T>::value)
			{
				return false;
			}

			// ������ ������Ʈ�� ã�´�.
			auto eraseIt = std::find_if(mComponents.begin(), mComponents.end(),
				[](auto& component)
				{
					return dynamic_cast<T*>(component.get());
				});

			if (eraseIt != mComponents.end())
			{
				if (std::is_base_of<UI, T>::value)
				{
					auto uiIt = std::find(mEnginePtr->UIBegine(), mEnginePtr->UIEnd(), eraseIt->get());
					mEnginePtr->GetUIComponents().erase(uiIt);
				}

				mComponents.erase(eraseIt);
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

