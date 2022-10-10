#pragma once

#include <assert.h>
#include <d3dx9.h>
#include <vector>
#include "Material.h"

#include "Component.h"

namespace engine
{
	class MeshFilter;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

	public:
		bool IsCastShadow() const;
		void SetCastShadow(const bool inbCastShadow);

		bool HasMeshFilter() const;
		const MeshFilter* GetMeshFilter() const;
		void SetMeshFilter(MeshFilter* const inMeshFilter);

		const std::vector<std::size_t>& GetMaterialHashKeys();
		std::size_t GetMaterialHashKey(const std::size_t inIndex);
		void SetMaterialHashKey(const std::size_t inIndex, const std::size_t inMtrlHashKey);
		void AddMaterialHashKey(const std::size_t inMtrlHashKey);
		void RemoveMaterialHashKey();
		void RemoveMaterialHashKey(const std::size_t inIndex);

		Material& GetMaterial(const std::size_t inIndex) const;

		void Render(IDirect3DDevice9* const inDevice) const;

	private:
		bool mbCastShadow;
		MeshFilter* mMeshFilterPtr;
		std::vector<std::size_t> mMaterialHashKeys;
	};
}
