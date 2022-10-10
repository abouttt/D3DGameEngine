#include "Camera.h"
#include "Transform.h"

namespace engine
{
	Camera::Camera()
		: mNear(0.3f)
		, mFar(1000.f)
		, mFov(60)
		, mViewMatrix()
		, mProjMatrix()
	{}

	float Camera::GetNear() const
	{
		return mNear;
	}

	void Camera::SetNear(const float inNear)
	{
		mNear = inNear;
	}

	float Camera::GetFar() const
	{
		return mFar;
	}

	void Camera::SetFar(const float inFar)
	{
		mFar = inFar;
	}

	float Camera::GetFieldOfView() const
	{
		return mFov;
	}

	void Camera::SetFieldOfView(const float inFov)
	{
		mFov = inFov;
	}

	const D3DXMATRIX& Camera::GetViewMatrix()
	{
		D3DXVECTOR3 right = GetTransform()->GetLocalXAxis();
		D3DXVECTOR3 up = GetTransform()->GetLocalYAxis();
		D3DXVECTOR3 look = GetTransform()->GetLocalZAxis();

		D3DXVECTOR3 pos = GetTransform()->GetPosition();
		float x = -D3DXVec3Dot(&right, &pos);
		float y = -D3DXVec3Dot(&up, &pos);
		float z = -D3DXVec3Dot(&look, &pos);

		mViewMatrix(0, 0) = right.x; mViewMatrix(0, 1) = up.x; mViewMatrix(0, 2) = look.x; mViewMatrix(0, 3) = 0.f;
		mViewMatrix(1, 0) = right.y; mViewMatrix(1, 1) = up.y; mViewMatrix(1, 2) = look.y; mViewMatrix(1, 3) = 0.f;
		mViewMatrix(2, 0) = right.z; mViewMatrix(2, 1) = up.z; mViewMatrix(2, 2) = look.z; mViewMatrix(2, 3) = 0.f;
		mViewMatrix(3, 0) = x;       mViewMatrix(3, 1) = y;    mViewMatrix(3, 2) = z;      mViewMatrix(3, 3) = 1.f;

		return mViewMatrix;
	}

	const D3DXMATRIX& Camera::GetProjectionMatrix(int width, int height)
	{
		D3DXMatrixPerspectiveFovLH(
			&mProjMatrix,
			D3DXToRadian(mFov),
			static_cast<float>(width) / static_cast<float>(height),
			mNear,
			mFar);
		return mProjMatrix;
	}
}