#pragma once

#include "Component.h"

namespace engine
{
	class UI : public Component
	{
	public:
		UI() = default;
		virtual ~UI() = default;

	public:
		virtual void Draw() = 0;
	};
}