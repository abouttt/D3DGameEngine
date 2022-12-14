#include "Transform.h"

namespace engine
{
	Transform::Transform()
		: mWorldTransform()
		, mLocalTransform()
		, mParentPtr(nullptr)
		, mChildrenPtr()
	{}

	Transform::Transform(const TransformPart& inLocalTransform)
		: mWorldTransform()
		, mLocalTransform(inLocalTransform)
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

	void Transform::SetPosition(const D3DXVECTOR3& inPosition)
	{
		mWorldTransform.SetPosition(inPosition);
		updateLocal();
	}

	void Transform::AddPosition(const D3DXVECTOR3& inPosition)
	{
		mWorldTransform.AddPosition(inPosition);
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

	void Transform::SetRotation(const D3DXQUATERNION& inRotation)
	{
		mWorldTransform.SetRotation(inRotation);
		updateLocal();
	}

	void Transform::SetRotation(const D3DXVECTOR3& inEulerAngles)
	{
		mWorldTransform.SetRotation(inEulerAngles);
		updateLocal();
	}

	void Transform::AddRotation(const D3DXVECTOR3& inEulerAngles)
	{
		mWorldTransform.AddRotation(inEulerAngles);
		updateLocal();
	}

	void Transform::AddRotationX(const float inDegree)
	{
		mWorldTransform.AddRotationX(inDegree);
		updateLocal();
	}

	void Transform::AddRotationY(const float inDegree)
	{
		mWorldTransform.AddRotationY(inDegree);
		updateLocal();
	}

	void Transform::AddRotationZ(const float inDegree)
	{
		mWorldTransform.AddRotationZ(inDegree);
		updateLocal();
	}

	D3DXVECTOR3 Transform::GetScale() const
	{
		return mWorldTransform.GetScale();
	}

	void Transform::SetScale(const D3DXVECTOR3& inScale)
	{
		mWorldTransform.SetScale(inScale);
		updateLocal();
	}

	void Transform::AddScale(const D3DXVECTOR3& inScale)
	{
		mWorldTransform.AddScale(inScale);
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

	void Transform::SetLocalPosition(const D3DXVECTOR3& inPosition)
	{
		mLocalTransform.SetPosition(inPosition);
		updateWorld();
	}

	void Transform::AddLocalPosition(const D3DXVECTOR3& inPosition)
	{
		mLocalTransform.AddPosition(inPosition);
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

	void Transform::SetLocalRotation(const D3DXQUATERNION& inRotation)
	{
		mLocalTransform.SetRotation(inRotation);
		updateWorld();
	}

	void Transform::SetLocalRotation(const D3DXVECTOR3& inEulerAngles)
	{
		mLocalTransform.SetRotation(inEulerAngles);
		updateWorld();
	}

	void Transform::AddLocalRotation(const D3DXVECTOR3& inEulerAngles)
	{
		mLocalTransform.AddRotation(inEulerAngles);
		updateWorld();
	}

	void Transform::AddLocalRotationX(const float inDegree)
	{
		mLocalTransform.AddRotationX(inDegree);
		updateWorld();
	}

	void Transform::AddLocalRotationY(const float inDegree)
	{
		mLocalTransform.AddRotationY(inDegree);
		updateWorld();
	}

	void Transform::AddLocalRotationZ(const float inDegree)
	{
		mLocalTransform.AddRotationZ(inDegree);
		updateWorld();
	}

	D3DXVECTOR3 Transform::GetLocalScale() const
	{
		return mLocalTransform.GetScale();
	}

	void Transform::SetLocalScale(const D3DXVECTOR3& inScale)
	{
		mLocalTransform.SetScale(inScale);
		updateWorld();
	}

	void Transform::AddLocalScale(const D3DXVECTOR3& inScale)
	{
		mLocalTransform.AddScale(inScale);
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

	void Transform::Translate(const D3DXVECTOR3& inTranslation)
	{
		mLocalTransform.Translate(inTranslation);
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

		// ?????? ?????? ???????? ???? ?????? ???? ?????? ????????.
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

	bool Transform::SetParent(Transform* const inParent)
	{
		assert(inParent);

		// ?????????? ????????. 
		if (!SetRoot())
		{
			return false;
		}

		// ???? ???? ???????? ????????.
		auto it = std::find(inParent->ChildrenBegin(), inParent->ChildrenEnd(), this);
		if (it != inParent->ChildrenEnd())
		{
			return false;
		}

		// ?????? ???????? ?????? ???? ??????
		inParent->GetChildren().emplace_back(this);
		mParentPtr = inParent;

		// ?????? ?????? ???? ?????? ???? ?????? ????????????.
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
