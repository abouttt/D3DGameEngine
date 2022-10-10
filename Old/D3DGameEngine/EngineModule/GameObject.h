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
	class MeshRenderer;
	class Behavior;
	class UI;

	class GameObject
	{
	public:
		friend class GameEngine;

	public:
		GameObject();
		GameObject(const std::string& inName);
		~GameObject();

	public:
		bool IsActive() const;
		void SetActive(const bool inbActive);

		const std::string& GetName() const;
		void SetName(const std::string& inName);

		Transform* GetTransform();
		const Transform* GetTransform() const;

		GameEngine* GetGameEngine();
		const GameEngine* GetGameEngine() const;

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
		T* AddComponent(Args&&...inArgs)
		{
			static_assert(std::is_base_of<Component, T>::value);

			auto newComponent = std::make_unique<T>(std::forward<Args>(inArgs)...);
			newComponent.get()->mGameObjectPtr = this;
			if (mTransformPtr)
			{
				newComponent.get()->mTransformPtr = mTransformPtr;
			}
			if (mGameEnginePtr)
			{
				newComponent.get()->mGameEnginePtr = mGameEnginePtr;
			}

			// ������Ʈ �������� �˸��� ������Ʈ �����̳ʿ� �߰��Ѵ�.
			if (std::is_base_of<Behavior, T>::value)
			{
				mGameEnginePtr->GetBehaviors().emplace_back((Behavior*)newComponent.get());
			}
			else if (std::is_same<T, MeshRenderer>::value)
			{
				mGameEnginePtr->GetMeshRenderers().emplace_back((MeshRenderer*)newComponent.get());
			}
			else if (std::is_base_of<UI, T>::value)
			{
				mGameEnginePtr->GetUIs().emplace_back((UI*)newComponent.get());
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
			auto it = std::find_if(mComponents.begin(), mComponents.end(),
				[](auto& component)
				{
					return dynamic_cast<T*>(component.get());
				});

			// �ش� ������Ʈ�� �����͸� �����ϴ� ���� ������ ���� �����Ѵ�.
			if (it != mComponents.end())
			{
				if (std::is_base_of<Behavior, T>::value)
				{
					auto cit = std::find(mGameEnginePtr->BehaviorBegin(), mGameEnginePtr->BehaviorEnd(), it->get());
					mGameEnginePtr->GetBehaviors().erase(cit);
				}
				else if (std::is_same<T, MeshRenderer>::value)
				{
					auto mit = std::find(mGameEnginePtr->MeshRendererBegin(), mGameEnginePtr->MeshRendererEnd(), it->get());
					mGameEnginePtr->GetMeshRenderers().erase(mit);
				}
				else if (std::is_base_of<UI, T>::value)
				{
					auto uit = std::find(mGameEnginePtr->UIBegin(), mGameEnginePtr->UIEnd(), it->get());
					mGameEnginePtr->GetUIs().erase(uit);
				}

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
		GameEngine* mGameEnginePtr;
	};

}
