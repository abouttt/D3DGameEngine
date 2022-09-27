#pragma once

#include <string>

#include "GameObject.h"
#include "Behavior.h"
#include "Text.h"

using namespace engine;

class FPSText : public Behavior
{
public:
	FPSText() = default;

public:
	void Awake() override
	{
		::MessageBox(nullptr, "Awake()", ".", MB_ICONEXCLAMATION | MB_OK);
	}

	void OnEnable() override
	{
		::MessageBox(nullptr, "OnEnable()", ".", MB_ICONEXCLAMATION | MB_OK);
	}

	void Start() override
	{
		::MessageBox(nullptr, "Start()", ".", MB_ICONEXCLAMATION | MB_OK);

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
			str = "FPS : " + std::to_string(int(GetTimer().GetFrameFPS()));
			mTextPtr->SetText(str);
			previousTimer = currentTime;
		}
	}

	void OnDisable() override
	{
		::MessageBox(nullptr, "OnDisable()", ".", MB_ICONEXCLAMATION | MB_OK);
	}

	void OnDestroy() override
	{
		::MessageBox(nullptr, "OnDestroy()", ".", MB_ICONEXCLAMATION | MB_OK);
	}

private:
	Text* mTextPtr = nullptr;
	std::string str;
};

