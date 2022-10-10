#include "MeshRenderer.h"
#include "EngineUtil.h"
#include "MeshFilter.h"
#include "Material.h"
#include "GameEngine.h"

namespace engine
{
	MeshRenderer::MeshRenderer()
		: mbCastShadow(true)
		, mMeshFilterPtr(nullptr)
		, mMaterialHashKeys()
	{}

	MeshRenderer::~MeshRenderer()
	{
		mMeshFilterPtr = nullptr;
	}

	bool MeshRenderer::IsCastShadow() const
	{
		return mbCastShadow;
	}

	void MeshRenderer::SetCastShadow(const bool inbCastShadow)
	{
		mbCastShadow = inbCastShadow;
	}

	bool MeshRenderer::HasMeshFilter() const
	{
		return mMeshFilterPtr != nullptr;
	}

	const MeshFilter* MeshRenderer::GetMeshFilter() const
	{
		return mMeshFilterPtr;
	}

	void MeshRenderer::SetMeshFilter(MeshFilter* const inMeshFilter)
	{
		mMeshFilterPtr = inMeshFilter;
	}

	const std::vector<std::size_t>& MeshRenderer::GetMaterialHashKeys()
	{
		return mMaterialHashKeys;
	}

	std::size_t MeshRenderer::GetMaterialHashKey(const std::size_t inIndex)
	{
		assert(inIndex < mMaterialHashKeys.size());

		return mMaterialHashKeys[inIndex];
	}

	void MeshRenderer::SetMaterialHashKey(const std::size_t inIndex, const std::size_t inMtrlHashKey)
	{
		assert(inIndex < mMaterialHashKeys.size());

		mMaterialHashKeys[inIndex] = inMtrlHashKey;
	}

	void MeshRenderer::AddMaterialHashKey(const std::size_t inMtrlHashKey)
	{
		mMaterialHashKeys.emplace_back(inMtrlHashKey);
	}

	void MeshRenderer::RemoveMaterialHashKey()
	{
		RemoveMaterialHashKey(mMaterialHashKeys.size() - 1);
	}

	void MeshRenderer::RemoveMaterialHashKey(const std::size_t inIndex)
	{
		assert(inIndex < mMaterialHashKeys.size());

		mMaterialHashKeys.erase(mMaterialHashKeys.begin() + inIndex);
	}

	Material& MeshRenderer::GetMaterial(const std::size_t inIndex) const
	{
		return *GameEngine::MaterialResources[inIndex].get();
	}

	void MeshRenderer::Render(IDirect3DDevice9* const inDevice) const
	{
		assert(inDevice);

		if (!HasMeshFilter())
		{
			return;
		}

		ID3DXMesh* mesh = mMeshFilterPtr->GetMesh();

		for (DWORD mtrlIndex = 0; mtrlIndex < mMaterialHashKeys.size(); ++mtrlIndex)
		{
			auto mtrlHashKey = mMaterialHashKeys[mtrlIndex];
			auto mtrl = GameEngine::MaterialResources[mtrlHashKey].get();

			auto texHashKey = mtrl->GetTextureKey();
			auto tex = GameEngine::TextureResources[texHashKey].Get();

			inDevice->SetMaterial(&mtrl->GetD3DMaterial());
			inDevice->SetTexture(mtrlIndex, tex);
			mesh->DrawSubset(0);
		}
	}

}
