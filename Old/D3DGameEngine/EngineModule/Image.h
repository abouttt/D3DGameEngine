#pragma once

#include <wrl.h>
#include <string>

#include "D3DUtil.h"
#include "UI.h"

namespace engine
{
	class Image : public UI
	{
	public:
		Image();
		Image(const std::size_t inTextureHashKey);

	public:
		std::size_t GetTextureKey() const;
		void SetTextureKey(const std::size_t inTextureHashKey);

		void SetColor(const D3DXCOLOR& inColor);

		void Draw() override;

	private:
		Microsoft::WRL::ComPtr<ID3DXSprite> mSprite;
		std::size_t mTextureHashKey;
		D3DXCOLOR mColor;
	};
}