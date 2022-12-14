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
		Component(const Component& inOther) = delete;
		Component operator=(const Component& inOther) = delete;
		virtual ~Component();

	public:
		GameEngine* GetGameEngine();
		const GameEngine* GetGameEngine() const;

		GameObject* GetGameObject();
		const GameObject* GetGameObject() const;

		Transform* GetTransform();
		const Transform* GetTransform() const;

	private:
		GameEngine* mGameEnginePtr;
		GameObject* mGameObjectPtr;
		Transform* mTransformPtr;
	};
}
