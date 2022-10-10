#include "MeshFilter.h"
#include "EngineUtil.h"
#include "GameEngine.h"

namespace engine
{
	MeshFilter::MeshFilter()
		: mMeshHashKey(HashKey::InvalidHash)
	{}

	std::size_t MeshFilter::GetMeshKey() const
	{
		return mMeshHashKey;
	}

	void MeshFilter::SetMesh(const std::size_t& inMeshHashKey)
	{
		mMeshHashKey = inMeshHashKey;
	}

	ID3DXMesh* MeshFilter::GetMesh() const
	{
		return GameEngine::MeshResources[mMeshHashKey].Get();
	}
}
