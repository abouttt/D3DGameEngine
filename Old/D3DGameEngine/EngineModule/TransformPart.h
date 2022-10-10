#pragma once

#include "D3DUtil.h"

namespace engine
{
	struct TransformPart
	{
	public:
		TransformPart(
			const D3DXVECTOR3& inPosition = d3d::VECTOR3_ZERO,
			const D3DXQUATERNION& inRotation = d3d::QUATERNION_IDENTITY,
			const D3DXVECTOR3& inScale = d3d::VECTOR3_ONE);

	public:
		D3DXVECTOR3 GetPosition() const;
		void SetPosition(const D3DXVECTOR3& inPosition);
		void AddPosition(const D3DXVECTOR3& inPosition);

		D3DXQUATERNION GetRotation() const;
		D3DXVECTOR3 GetEulerAngles() const;
		void SetRotation(const D3DXQUATERNION& inRotation);
		void SetRotation(const D3DXVECTOR3& inEulerAngles);
		void AddRotation(const D3DXVECTOR3& inEulerAngles);
		void AddRotationX(const float inDegree);
		void AddRotationY(const float inDegree);
		void AddRotationZ(const float inDegree);

		D3DXVECTOR3 GetScale() const;
		void SetScale(const D3DXVECTOR3& inScale);
		void AddScale(const D3DXVECTOR3& inScale);

		D3DXVECTOR3 GetXAxis() const;
		D3DXVECTOR3 GetYAxis() const;
		D3DXVECTOR3 GetZAxis() const;

		void Translate(const D3DXVECTOR3& inTranslation);

		D3DXMATRIX GetMatrix() const;

		TransformPart Inverse() const;
		TransformPart LocalToWorld(const TransformPart& inParentWorldTransform) const;
		TransformPart WorldToLocal(const TransformPart& inParentWorldTransform) const;

	private:
		void clameRotation();
		float getAxisClampedValue(const float inValue);

	private:
		D3DXVECTOR3 mPosition;
		D3DXQUATERNION mRotation;
		D3DXVECTOR3 mRotationValue;
		D3DXVECTOR3 mScale;
	};
}