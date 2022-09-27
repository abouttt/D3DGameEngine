#pragma once

namespace engine
{
	class GameEngine;
	class GameObjet;
	class Transform;

	class Component
	{
	public:
		friend class GameObject;

	public:
		Component();
		Component(const Component& other) = delete;
		Component operator=(const Component& other) = delete;
		virtual ~Component();

	public:
		virtual bool IsActive() const;
		virtual void SetActive(bool bActive);

	public:
		GameEngine* GetEngine();
		const GameEngine* GetEngine() const;

		GameObject* GetGameObject();
		const GameObject* GetGameObject() const;

		Transform* GetTransform();
		const Transform* GetTransform() const;

	private:
		virtual void addToEventContainer() {}
		virtual void removeFromEventContainer() {}

	private:
		bool mbActive;

		GameEngine* mEnginePtr;
		GameObject* mGameObjectPtr;
		Transform* mTransformPtr;
	};
}
