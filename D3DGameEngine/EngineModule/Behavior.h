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
		Behavior() = default;
		virtual ~Behavior() = default;

	public: // �̺�Ʈ �Լ�.
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

	public:
		Timer& GetTimer();
		InputManager& GetInput();

	public:
		template<typename T>
		T* GetComponent()
		{
			return GetGameObject()->GetComponent<T>();
		}
	};
}

