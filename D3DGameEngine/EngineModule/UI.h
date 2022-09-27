#pragma once

#include "Component.h"

namespace engine
{
	class GameObjet;

	class UI : public Component
	{
	public:
		friend class GameObject;

	public:
		UI() = default;
		virtual ~UI() = default;

	public:
		virtual void Draw() = 0;

	private:
		void addToEventContainer() override;
		void removeFromEventContainer() override;
	};
}

