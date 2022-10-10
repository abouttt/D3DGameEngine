#pragma once

#include "D3DUtil.h"
#include "EngineUtil.h"

namespace engine
{
	struct Material
	{
	public:
		Material();
		Material(const D3DMATERIAL9& mtrl);

	public:
		RenderingMode GetRenderingMode() const;
		void SetRenderingMode(RenderingMode mode);

		std::size_t GetTextureKey() const;
		void SetTextureKey(const std::size_t& key);

		void SetColor(const D3DXCOLOR& color);

		const D3DMATERIAL9& GetD3DMaterial();

	private:
		RenderingMode mRenderingMode;
		std::size_t mTextureKey;
		D3DMATERIAL9 mD3DMaterial;
	};
}

