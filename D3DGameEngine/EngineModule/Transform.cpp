#include "Transform.h"

namespace engine
{
	Transform::Transform()
		: mWorldTransform()
		, mLocalTransform()
		, mParentPtr(nullptr)
		, mChildrenPtr()
	{}

	Transform::Transform(const TransformPart& localTransform)
		: mWorldTransform()
		, mLocalTransform(localTransform)
		, mParentPtr(nullptr)
		, mChildrenPtr()
	{
		updateWorld();
	}

	Transform::~Transform()
	{
		mParentPtr = nullptr;
		mChildrenPtr.clear();
	}

	D3DXVECTOR3 Transform::GetPosition() const
	{
		return mWorldTransform.GetPosition();
	}

	void Transform::SetPosition(const D3DXVECTOR3& position)
	{
		mWorldTransform.SetPosition(position);
		updateLocal();
	}

	void Transform::AddPosition(const D3DXVECTOR3& position)
	{
		mWorldTransform.AddPosition(position);
		updateLocal();
	}

	D3DXQUATERNION Transform::GetRotation() const
	{
		return mWorldTransform.GetRotation();
	}

	D3DXVECTOR3 Transform::GetEulerAngles() const
	{
		return mWorldTransform.GetEulerAngles();
	}

	void Transform::SetRotation(const D3DXQUATERNION& rotation)
	{
		mWorldTransform.SetRotation(rotation);
		updateLocal();
	}

	void Transform::SetRotation(const D3DXVECTOR3& eulerAngles)
	{
		mWorldTransform.SetRotation(eulerAngles);
		updateLocal();
	}

	void Transform::AddRotation(const D3DXVECTOR3& eulerAngles)
	{
		mWorldTransform.AddRotation(eulerAngles);
		updateLocal();
	}

	void Transform::AddRotationX(const float degree)
	{
		mWorldTransform.AddRotationX(degree);
		updateLocal();
	}

	void Transform::AddRotationY(const float degree)
	{
		mWorldTransform.AddRotationY(degree);
		updateLocal();
	}

	void Transform::AddRotationZ(const float degree)
	{
		mWorldTransform.AddRotationZ(degree);
		updateLocal();
	}

	D3DXVECTOR3 Transform::GetScale() const
	{
		return mWorldTransform.GetScale();
	}

	void Transform::SetScale(const D3DXVECTOR3& scale)
	{
		mWorldTransform.SetScale(scale);
		updateLocal();
	}

	void Transform::AddScale(const D3DXVECTOR3& scale)
	{
		mWorldTransform.AddScale(scale);
		updateLocal();
	}

	D3DXVECTOR3 Transform::GetXAxis() const
	{
		return mWorldTransform.GetXAxis();
	}

	D3DXVECTOR3 Transform::GetYAxis() const
	{
		return mWorldTransform.GetYAxis();
	}

	D3DXVECTOR3 Transform::GetZAxis() const
	{
		return mWorldTransform.GetZAxis();
	}

	D3DXMATRIX Transform::GetMatrix() const
	{
		return mWorldTransform.GetMatrix();
	}

	D3DXVECTOR3 Transform::GetLocalPosition() const
	{
		return mLocalTransform.GetPosition();
	}

	void Transform::SetLocalPosition(const D3DXVECTOR3& position)
	{
		mLocalTransform.SetPosition(position);
		updateWorld();
	}

	void Transform::AddLocalPosition(const D3DXVECTOR3& position)
	{
		mLocalTransform.AddPosition(position);
		updateWorld();
	}

	D3DXQUATERNION Transform::GetLocalRotation() const
	{
		return mLocalTransform.GetRotation();
	}

	D3DXVECTOR3 Transform::GetLocalEulerAngles() const
	{
		return mLocalTransform.GetEulerAngles();
	}

	void Transform::SetLocalRotation(const D3DXQUATERNION& rotation)
	{
		mLocalTransform.SetRotation(rotation);
		updateWorld();
	}

	void Transform::SetLocalRotation(const D3DXVECTOR3& eulerAngles)
	{
		mLocalTransform.SetRotation(eulerAngles);
		updateWorld();
	}

	void Transform::AddLocalRotation(const D3DXVECTOR3& eulerAngles)
	{
		mLocalTransform.AddRotation(eulerAngles);
		updateWorld();
	}

	void Transform::AddLocalRotationX(const float degree)
	{
		mLocalTransform.AddRotationX(degree);
		updateWorld();
	}

	void Transform::AddLocalRotationY(const float degree)
	{
		mLocalTransform.AddRotationY(degree);
		updateWorld();
	}

	void Transform::AddLocalRotationZ(const float degree)
	{
		mLocalTransform.AddRotationZ(degree);
		updateWorld();
	}

	D3DXVECTOR3 Transform::GetLocalScale() const
	{
		return mLocalTransform.GetScale();
	}

	void Transform::SetLocalScale(const D3DXVECTOR3& scale)
	{
		mLocalTransform.SetScale(scale);
		updateWorld();
	}

	void Transform::AddLocalScale(const D3DXVECTOR3& scale)
	{
		mLocalTransform.AddScale(scale);
		updateWorld();
	}

	D3DXVECTOR3 Transform::GetLocalXAxis() const
	{
		return mLocalTransform.GetXAxis();
	}

	D3DXVECTOR3 Transform::GetLocalYAxis() const
	{
		return mLocalTransform.GetYAxis();
	}

	D3DXVECTOR3 Transform::GetLocalZAxis() const
	{
		return mLocalTransform.GetZAxis();
	}

	void Transform::Translate(const D3DXVECTOR3& translation)
	{
		mLocalTransform.Translate(translation);
		updateWorld();
	}

	Transform* Transform::GetRoot()
	{
		Transform* parent = nullptr;
		Transform* current = this;
		while ((parent = current->GetParent()) != nullptr)
		{
			current = parent;
		}

		return current;
	}

	bool Transform::SetRoot()
	{
		if (!RemoveFromParent())
		{
			return false;
		}

		// 최상위 루트가 되었기에 로컬 정보를 월드 정보로 변경한다.
		updateLocal();
		return true;
	}

	bool Transform::RemoveFromParent()
	{
		if (!HasParent())
		{
			return true;
		}

		auto it = std::find(mParentPtr->ChildrenBegin(), mParentPtr->ChildrenEnd(), this);
		if (it != mParentPtr->ChildrenEnd())
		{
			mParentPtr->GetChildren().erase(it);
			mParentPtr = nullptr;
			return true;
		}

		return false;
	}

	bool Transform::HasParent() const
	{
		return mParentPtr != nullptr;
	}

	Transform* Transform::GetParent()
	{
		return mParentPtr;
	}

	bool Transform::SetParent(Transform* const parent)
	{
		assert(parent);

		// 부모로부터 분리한다. 
		if (!SetRoot())
		{
			return false;
		}

		// 이미 있는 경우에는 넘어간다.
		auto it = std::find(parent->ChildrenBegin(), parent->ChildrenEnd(), this);
		if (it != parent->ChildrenEnd())
		{
			return false;
		}

		// 새로운 트랜스폼 노드로 부모 재설정
		parent->GetChildren().emplace_back(this);
		mParentPtr = parent;

		// 새로운 부모에 맞춰 자신의 로컬 정보를 업데이트한다.
		updateLocal();

		return true;
	}

	std::vector<Transform*>& Transform::GetChildren()
	{
		return mChildrenPtr;
	}

	std::vector<Transform*>::const_iterator Transform::ChildrenBegin() const
	{
		return mChildrenPtr.begin();
	}

	std::vector<Transform*>::const_iterator Transform::ChildrenEnd() const
	{
		return mChildrenPtr.end();
	}

	void Transform::updateWorld()
	{
		if (HasParent())
		{
			mWorldTransform = mLocalTransform.LocalToWorld(mParentPtr->mWorldTransform);
		}
		else
		{
			mWorldTransform = mLocalTransform;
		}

		updateChildrenWorld();
	}

	void Transform::updateLocal()
	{
		if (HasParent())
		{
			mLocalTransform = mWorldTransform.WorldToLocal(mParentPtr->mWorldTransform);
		}
		else
		{
			mLocalTransform = mWorldTransform;
		}

		updateChildrenWorld();
	}

	void Transform::updateChildrenWorld()
	{
		for (auto child : mChildrenPtr)
		{
			child->updateWorld();
		}
	}

}
