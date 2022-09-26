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
		virtual ~UI();

	public:
		virtual void Draw() = 0;

	private:
		void addToComponentPtrContainer() override;
	};
}

