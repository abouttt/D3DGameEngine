#pragma once

#include "D3DUtil.h"
#include "Component.h"

namespace engine
{
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

	public:
		float GetNear() const;
		void SetNear(const float value);

		float GetFar() const;
		void SetFar(const float value);

		float GetFieldOfView() const;
		void SetFieldOfView(float value);

		const D3DXMATRIX& GetViewMatrix();
		const D3DXMATRIX& GetProjectionMatrix(const int width, const int height);

	private:
		float mNear;
		float mFar;
		float mFov;

		D3DXMATRIX mViewMatrix;
		D3DXMATRIX mProjMatrix;
	};
}
