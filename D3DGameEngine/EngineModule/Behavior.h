#pragma once

#include "Component.h"
#include "GameEngine.h"
#include "InputManager.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"

namespace engine
{
	class Behavior : public Component
	{
	public:
		friend class GameObject;

	public:
		Behavior() = default;
		virtual ~Behavior();

	public: // 이벤트 함수.
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void OnDestroy() {}

	public:
		Timer& GetTimer();
		InputManager& GetInput();

	public:
		template<typename T>
		T* GetComponent()
		{
			return GetGameObject()->GetComponent<T>();
		}

	private:
		void addToComponentPtrContainer() override;
	};
}

