#pragma once

#include "D3DUtil.h"
#include "Component.h"

namespace engine
{
	class Camera : public Component
	{
	public:
		Camera();

	public:
		float GetNear() const;
		void SetNear(const float inNear);

		float GetFar() const;
		void SetFar(const float inFar);

		float GetFieldOfView() const;
		void SetFieldOfView(float inFov);

		const D3DXMATRIX& GetViewMatrix();
		const D3DXMATRIX& GetProjectionMatrix(const int inWidth, const int inHeight);

	private:
		float mNear;
		float mFar;
		float mFov;

		D3DXMATRIX mViewMatrix;
		D3DXMATRIX mProjMatrix;
	};
}
