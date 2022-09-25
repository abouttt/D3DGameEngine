#pragma once

#include "D3DUtil.h"

namespace engine
{
	class TransformPart
	{
	public:
		TransformPart(
			const D3DXVECTOR3& inPosition = d3d::VECTOR3_ZERO,
			const D3DXQUATERNION& inRotation = d3d::QUATERNION_IDENTITY,
			const D3DXVECTOR3& inScale = d3d::VECTOR3_ONE);
		~TransformPart() = default;

	public:
		D3DXVECTOR3 GetPosition() const;
		void SetPosition(const D3DXVECTOR3& position);
		void AddPosition(const D3DXVECTOR3& position);

		D3DXQUATERNION GetRotation() const;
		D3DXVECTOR3 GetEulerAngles() const;
		void SetRotation(const D3DXQUATERNION& rotation);
		void SetRotation(const D3DXVECTOR3& eulerAngles);
		void AddRotation(const D3DXVECTOR3& eulerAngles);
		void AddRotationX(const float degree);
		void AddRotationY(const float degree);
		void AddRotationZ(const float degree);

		D3DXVECTOR3 GetScale() const;
		void SetScale(const D3DXVECTOR3& scale);
		void AddScale(const D3DXVECTOR3& scale);

		D3DXVECTOR3 GetXAxis() const;
		D3DXVECTOR3 GetYAxis() const;
		D3DXVECTOR3 GetZAxis() const;

		void Translate(const D3DXVECTOR3& translation);

		D3DXMATRIX GetMatrix() const;

		TransformPart Inverse() const;
		TransformPart LocalToWorld(const TransformPart& parentWorldTransform) const;
		TransformPart WorldToLocal(const TransformPart& parentWorldTransform) const;

	private:
		void clameRotation();
		float getAxisClampedValue(const float value);

	private:
		D3DXVECTOR3 mPosition;
		D3DXQUATERNION mRotation;
		D3DXVECTOR3 mRotationValue;
		D3DXVECTOR3 mScale;
	};
}