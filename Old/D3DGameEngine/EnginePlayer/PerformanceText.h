#pragma once

#include <string>

#include "GameObject.h"
#include "Behavior.h"
#include "Text.h"

using namespace engine;

class PerformanceText : public Behavior
{
public:
	void Start() override
	{
		mTextPtr = GetComponent<Text>();
		mTextPtr->SetColor(d3d::GREEN);
		mTextPtr->SetSize(15);
		GetTransform()->SetPosition(D3DXVECTOR3(10, 10, 0));
	}

	void Update() override
	{
		static float previousTimer = -300.f;
		static float updatePeriod = 300.f;
		float currentTime = GetTimer().GetElapsedTime();
		if (currentTime - previousTimer > updatePeriod)
		{
			str = "FPS : " + std::to_string(GetTimer().GetFrameFPS());
			mTextPtr->SetText(str);
			previousTimer = currentTime;
		}
	}

private:
	Text* mTextPtr;
	std::string str;
};