#include "Material.h"
#include "EngineUtil.h"

namespace engine
{
	Material::Material()
		: mRenderingMode(RenderingMode::Opaque)
		, mTextureKey(HashKey::InvalidHash)
		, mD3DMaterial(d3d::WHITE_MTRL)
	{}

	Material::Material(const D3DMATERIAL9& mtrl)
		: mRenderingMode(RenderingMode::Opaque)
		, mTextureKey(HashKey::InvalidHash)
		, mD3DMaterial(mtrl)
	{}

	RenderingMode Material::GetRenderingMode() const
	{
		return mRenderingMode;
	}

	void Material::SetRenderingMode(RenderingMode mode)
	{
		mRenderingMode = mode;
	}

	std::size_t Material::GetTextureKey() const
	{
		return mTextureKey;
	}

	void Material::SetTextureKey(const std::size_t& key)
	{
		mTextureKey = key;
	}

	void Material::SetColor(const D3DXCOLOR& color)
	{
		mD3DMaterial.Ambient = color;
		mD3DMaterial.Diffuse = color;
		mD3DMaterial.Specular = color;
		mD3DMaterial.Emissive = d3d::BLACK;
		mD3DMaterial.Power = 8.0f;
	}

	const D3DMATERIAL9& Material::GetD3DMaterial()
	{
		return mD3DMaterial;
	}
}
