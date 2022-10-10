#pragma once

#include "D3DUtil.h"
#include "Component.h"
#include "TransformPart.h"

namespace engine
{
	class Transform : public Component
	{
	public:
		Transform();
		Transform(const TransformPart& inLocalTransform);
		~Transform();

	public: // 월드 트랜스폼.
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

		D3DXMATRIX GetMatrix() const;

	public: // 로컬 트랜스폼.
		D3DXVECTOR3 GetLocalPosition() const;
		void SetLocalPosition(const D3DXVECTOR3& inPosition);
		void AddLocalPosition(const D3DXVECTOR3& inPosition);

		D3DXQUATERNION GetLocalRotation() const;
		D3DXVECTOR3 GetLocalEulerAngles() const;
		void SetLocalRotation(const D3DXQUATERNION& inRotation);
		void SetLocalRotation(const D3DXVECTOR3& inRotation);
		void AddLocalRotation(const D3DXVECTOR3& inRotation);
		void AddLocalRotationX(const float inDegree);
		void AddLocalRotationY(const float inDegree);
		void AddLocalRotationZ(const float inDegree);

		D3DXVECTOR3 GetLocalScale() const;
		void SetLocalScale(const D3DXVECTOR3& inScale);
		void AddLocalScale(const D3DXVECTOR3& inScale);

		D3DXVECTOR3 GetLocalXAxis() const;
		D3DXVECTOR3 GetLocalYAxis() const;
		D3DXVECTOR3 GetLocalZAxis() const;

		void Translate(const D3DXVECTOR3& inTranslation);

	public: // 계층 구조.
		Transform* GetRoot();
		bool SetRoot();
		bool RemoveFromParent();

		bool HasParent() const;
		Transform* GetParent();
		bool SetParent(Transform* const inParent);

		std::vector<Transform*>& GetChildren();
		std::vector<Transform*>::const_iterator ChildrenBegin() const;
		std::vector<Transform*>::const_iterator ChildrenEnd() const;

	private:
		void updateWorld();
		void updateLocal();
		void updateChildrenWorld();

	private:
		TransformPart mWorldTransform;
		TransformPart mLocalTransform;

		Transform* mParentPtr;
		std::vector<Transform*> mChildrenPtr;
	};
}
