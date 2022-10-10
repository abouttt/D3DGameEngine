#pragma once

#include <memory>

#include "Component.h"
#include "D3DUtil.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Timer.h"
#include "Transform.h"

namespace engine
{
	class Behavior : 
		public Component, 
		public std::enable_shared_from_this<Behavior>
	{
	public:
		friend class GameEngine;
		friend class GameObject;

	public:
		Behavior() = default;
		virtual ~Behavior() = default;

	public:
		void SetActive(bool bActive) override;

	public: // 이벤트 함수.
		virtual void Awake() {}
		virtual void OnEnable() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void OnDisable() {}
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
		void addToEventContainer() override;
		void removeFromEventContainer() override;
	};
}

