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
		Behavior();
		virtual ~Behavior() = default;

	public:
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

	public:
		bool IsStart() const;
		void SetStart(bool bStart);

		GameEngine& GetEngine();
		InputManager& GetInput();
		Timer& GetTimer();

	public:
		template<typename T>
		T* GetComponent()
		{
			return GetGameObject()->GetComponent<T>();
		}

	private:
		bool mbStart;
	};
}