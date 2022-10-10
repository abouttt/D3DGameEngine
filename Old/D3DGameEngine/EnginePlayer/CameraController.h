#pragma once

#include "Behavior.h"
#include "Camera.h"

using namespace engine;

class CameraController : public Behavior
{
public:
	CameraController() = default;

public:
	void Start() override
	{
		mCameraPtr = GetGameEngine()->GetMainCamera();
	}

	void Update() override
	{
		if (GetInput().GetKey(DIK_W))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(0, 0, mSpeed * GetTimer().GetDeltaTime()));
		}
		if (GetInput().GetKey(DIK_S))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(0, 0, -mSpeed * GetTimer().GetDeltaTime()));
		}
		if (GetInput().GetKey(DIK_A))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(-mSpeed * GetTimer().GetDeltaTime(), 0, 0));
		}
		if (GetInput().GetKey(DIK_D))
		{
			mCameraPtr->GetTransform()->Translate(D3DXVECTOR3(mSpeed * GetTimer().GetDeltaTime(), 0, 0));
		}
		if (GetInput().GetKey(DIK_R))
		{
			mCameraPtr->GetTransform()->AddPosition(D3DXVECTOR3(0, mSpeed * GetTimer().GetDeltaTime(), 0));
		}
		if (GetInput().GetKey(DIK_F))
		{
			mCameraPtr->GetTransform()->AddPosition(D3DXVECTOR3(0, -mSpeed * GetTimer().GetDeltaTime(), 0));
		}

		mCameraPtr->GetTransform()->AddRotationX(GetInput().GetAxisMouseY() * 0.3f);
		mCameraPtr->GetTransform()->AddRotationY(GetInput().GetAxisMouseX() * 0.3f);
	}

private:
	Camera* mCameraPtr = nullptr;
	float mSpeed = 20;
};
