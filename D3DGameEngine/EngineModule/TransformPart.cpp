#include "TransformPart.h"

namespace engine
{
	TransformPart::TransformPart(
		const D3DXVECTOR3& position,
		const D3DXQUATERNION& rotation,
		const D3DXVECTOR3& scale)
		: mPosition(position)
		, mRotation(rotation)
		, mScale(scale)
		, mRotationValue(d3d::VECTOR3_ZERO)
	{}

	D3DXVECTOR3 TransformPart::GetPosition() const
	{
		return mPosition;
	}

	void TransformPart::SetPosition(const D3DXVECTOR3& position)
	{
		mPosition = position;
	}

	void TransformPart::AddPosition(const D3DXVECTOR3& position)
	{
		mPosition += position;
	}

	D3DXQUATERNION TransformPart::GetRotation() const
	{
		return mRotation;
	}

	void TransformPart::SetRotation(const D3DXQUATERNION& rotation)
	{
		mRotation = rotation;
		clameRotation();
		D3DXQuaternionNormalize(&mRotation, &mRotation);
	}

	void TransformPart::SetRotation(const D3DXVECTOR3& eulerAngles)
	{
		mRotationValue = D3DXToRadian(eulerAngles);
		clameRotation();
		D3DXQuaternionRotationYawPitchRoll(
			&mRotation,
			mRotationValue.y,
			mRotationValue.x,
			mRotationValue.z);
		D3DXQuaternionNormalize(&mRotation, &mRotation);
	}

	void TransformPart::AddRotation(const D3DXVECTOR3& eulerAngles)
	{
		mRotationValue += D3DXToRadian(eulerAngles);
		clameRotation();
		D3DXQuaternionRotationYawPitchRoll(
			&mRotation,
			mRotationValue.y,
			mRotationValue.x,
			mRotationValue.z);
		D3DXQuaternionNormalize(&mRotation, &mRotation);
	}

	void TransformPart::AddRotationX(const float degree)
	{
		mRotationValue.x += D3DXToRadian(degree);
		clameRotation();
		D3DXQuaternionRotationYawPitchRoll(
			&mRotation,
			mRotationValue.y,
			mRotationValue.x,
			mRotationValue.z);
		D3DXQuaternionNormalize(&mRotation, &mRotation);
	}

	void TransformPart::AddRotationY(const float degree)
	{
		mRotationValue.y += D3DXToRadian(degree);
		clameRotation();
		D3DXQuaternionRotationYawPitchRoll(
			&mRotation,
			mRotationValue.y,
			mRotationValue.x,
			mRotationValue.z);
		D3DXQuaternionNormalize(&mRotation, &mRotation);
	}

	void TransformPart::AddRotationZ(const float degree)
	{
		mRotationValue.z += D3DXToRadian(degree);
		clameRotation();
		D3DXQuaternionRotationYawPitchRoll(
			&mRotation,
			mRotationValue.y,
			mRotationValue.x,
			mRotationValue.z);
		D3DXQuaternionNormalize(&mRotation, &mRotation);
	}

	D3DXVECTOR3 TransformPart::GetScale() const
	{
		return mScale;
	}

	void TransformPart::SetScale(const D3DXVECTOR3& scale)
	{
		mScale = scale;
	}

	void TransformPart::AddScale(const D3DXVECTOR3& scale)
	{
		mScale += scale;
	}

	D3DXVECTOR3 TransformPart::GetXAxis() const
	{
		return d3d::Math::Vec3Rotate(d3d::VECTOR3_RIGHT, mRotation);
	}

	D3DXVECTOR3 TransformPart::GetYAxis() const
	{
		return d3d::Math::Vec3Rotate(d3d::VECTOR3_UP, mRotation);
	}

	D3DXVECTOR3 TransformPart::GetZAxis() const
	{
		return d3d::Math::Vec3Rotate(d3d::VECTOR3_FORWARD, mRotation);
	}

	void TransformPart::Translate(const D3DXVECTOR3& translation)
	{
		D3DXVECTOR3 right = GetXAxis();
		D3DXVECTOR3 up = GetYAxis();
		D3DXVECTOR3 look = GetZAxis();

		D3DXVECTOR3 posX = D3DXVECTOR3(right.x, right.y, right.z) * translation.x;
		D3DXVECTOR3 posY = D3DXVECTOR3(up.x, up.y, up.z) * translation.y;
		D3DXVECTOR3 posZ = D3DXVECTOR3(look.x, look.y, look.z) * translation.z;

		mPosition += posX + posY + posZ;
	}

	D3DXMATRIX TransformPart::GetMatrix() const
	{
		D3DXMATRIX matPos;
		D3DXMatrixTranslation(&matPos, mPosition.x, mPosition.y, mPosition.z);

		D3DXMATRIX matRot;
		D3DXMatrixRotationQuaternion(&matRot, &mRotation);

		D3DXMATRIX matScale;
		D3DXMatrixScaling(&matScale, mScale.x, mScale.y, mScale.z);

		return matScale * matRot * matPos;
	}

	D3DXVECTOR3 TransformPart::GetEulerAngles() const
	{
		return d3d::Math::QuaternionToEuler(mRotation);
	}

	TransformPart TransformPart::Inverse() const
	{
		D3DXVECTOR3 reciprocalScale = d3d::VECTOR3_ZERO;
		if (!d3d::Math::EqualsInTolerance(mScale.x, 0.f))
		{
			reciprocalScale.x = 1.f / mScale.x;
		}
		if (!d3d::Math::EqualsInTolerance(mScale.y, 0.f))
		{
			reciprocalScale.y = 1.f / mScale.y;
		}
		if (!d3d::Math::EqualsInTolerance(mScale.z, 0.f))
		{
			reciprocalScale.z = 1.f / mScale.z;
		}

		TransformPart result;

		result.SetScale(reciprocalScale);

		D3DXQUATERNION rot;
		D3DXQuaternionConjugate(&rot, &mRotation);
		result.SetRotation(rot);

		D3DXVECTOR3 pos = d3d::Math::Vec3Rotate(-mPosition, result.GetRotation());
		pos = d3d::Math::Vec3Multiply(pos, result.GetScale());
		result.SetPosition(pos);

		return result;
	}

	TransformPart TransformPart::LocalToWorld(const TransformPart& parentWorldTransform) const
	{
		TransformPart result;
		result.SetScale(d3d::Math::Vec3Multiply(parentWorldTransform.GetScale(), GetScale()));
		result.SetRotation(parentWorldTransform.GetRotation() * GetRotation());

		D3DXVECTOR3 vecMul = d3d::Math::Vec3Multiply(GetPosition(), parentWorldTransform.GetScale());
		D3DXVECTOR3 vecRot = d3d::Math::Vec3Rotate(vecMul, parentWorldTransform.GetRotation());
		result.SetPosition(parentWorldTransform.GetPosition() + vecRot);

		return result;
	}

	TransformPart TransformPart::WorldToLocal(const TransformPart& parentWorldTransform) const
	{
		TransformPart invParent = parentWorldTransform.Inverse();

		TransformPart result;
		result.SetScale(d3d::Math::Vec3Multiply(invParent.GetScale(), GetScale()));
		result.SetRotation(invParent.GetRotation() * GetRotation());

		D3DXVECTOR3 pos = d3d::Math::Vec3Multiply(invParent.GetScale(), GetPosition());
		pos = d3d::Math::Vec3Rotate(pos, invParent.GetRotation());
		result.SetPosition(pos + invParent.GetPosition());

		return result;
	}

	void TransformPart::clameRotation()
	{
		mRotationValue.y = getAxisClampedValue(mRotationValue.y);
		mRotationValue.z = getAxisClampedValue(mRotationValue.z);
		mRotationValue.x = getAxisClampedValue(mRotationValue.x);
	}

	float TransformPart::getAxisClampedValue(const float value)
	{
		float radian = D3DXToRadian(360.f);
		float angle = d3d::Math::FMod(value, radian);
		if (angle < 0.f)
		{
			angle += radian;
		}

		return angle;
	}
}