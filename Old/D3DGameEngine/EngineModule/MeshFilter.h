#pragma once

#include "Component.h"
#include "D3DUtil.h"

namespace engine
{
	class MeshFilter : public Component
	{
	public:
		MeshFilter();

		std::size_t GetMeshKey() const;
		void SetMesh(const std::size_t& inMeshHashKey);

		ID3DXMesh* GetMesh() const;

	private:
		std::size_t mMeshHashKey;
	};
}
