#pragma once

#include <vector>

#include "Component.h"
#include "D3DUtil.h"
#include "TransformPart.h"

namespace engine
{
	class Transform : public Component
	{
	public:
		Transform();
		Transform(const TransformPart& localTransform);
		~Transform();

	public: // 월드 트랜스폼.
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

		D3DXMATRIX GetMatrix() const;

	public: // 로컬 트랜스폼.
		D3DXVECTOR3 GetLocalPosition() const;
		void SetLocalPosition(const D3DXVECTOR3& position);
		void AddLocalPosition(const D3DXVECTOR3& position);

		D3DXQUATERNION GetLocalRotation() const;
		D3DXVECTOR3 GetLocalEulerAngles() const;
		void SetLocalRotation(const D3DXQUATERNION& rotation);
		void SetLocalRotation(const D3DXVECTOR3& rotation);
		void AddLocalRotation(const D3DXVECTOR3& rotation);
		void AddLocalRotationX(const float degree);
		void AddLocalRotationY(const float degree);
		void AddLocalRotationZ(const float degree);

		D3DXVECTOR3 GetLocalScale() const;
		void SetLocalScale(const D3DXVECTOR3& scale);
		void AddLocalScale(const D3DXVECTOR3& scale);

		D3DXVECTOR3 GetLocalXAxis() const;
		D3DXVECTOR3 GetLocalYAxis() const;
		D3DXVECTOR3 GetLocalZAxis() const;

		void Translate(const D3DXVECTOR3& translation);

	public: // 계층 구조.
		Transform* GetRoot();
		bool SetRoot();
		bool RemoveFromParent();

		bool HasParent() const;
		Transform* GetParent();
		bool SetParent(Transform* const parent);

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

