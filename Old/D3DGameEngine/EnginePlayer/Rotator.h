#pragma once

#include "Behavior.h"

using namespace engine;

class Rotator : public Behavior
{
public:
	void Update() override
	{
		float speed = 50 * GetTimer().GetDeltaTime();
		GetTransform()->AddRotation(D3DXVECTOR3(speed, speed, speed));
	}
};