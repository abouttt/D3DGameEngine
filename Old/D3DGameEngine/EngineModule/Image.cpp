#include "Image.h"
#include "EngineUtil.h"
#include "GameEngine.h"
#include "Transform.h"

namespace engine
{
	Image::Image()
		: mSprite()
		, mTextureHashKey(HashKey::InvalidHash)
		, mColor(d3d::WHITE)
	{
		auto sprite = mSprite.Get();
		if (FAILED(D3DXCreateSprite(d3d::Var::Device, &sprite)))
		{
			::MessageBox(nullptr, _T("Image D3DXCreateSprite() - FAILED"), 0, 0);
		}
		mSprite = sprite;
	}

	Image::Image(const std::size_t inTextureHashKey)
		: mSprite()
		, mTextureHashKey(inTextureHashKey)
		, mColor(d3d::WHITE)
	{
		auto sprite = mSprite.Get();
		if (FAILED(D3DXCreateSprite(d3d::Var::Device, &sprite)))
		{
			::MessageBox(nullptr, _T("Image D3DXCreateSprite() - FAILED"), 0, 0);
		}
		mSprite = sprite;
	}

	std::size_t Image::GetTextureKey() const
	{
		return mTextureHashKey;
	}

	void Image::SetTextureKey(const std::size_t inTextureHashKey)
	{
		mTextureHashKey = inTextureHashKey;
	}

	void Image::SetColor(const D3DXCOLOR& inColor)
	{
		mColor = inColor;
	}

	void Image::Draw()
	{
		if ((!mSprite.Get()) ||
			(mTextureHashKey == HashKey::InvalidHash))
		{
			return;
		}

		auto tex = GameEngine::TextureResources[mTextureHashKey].Get();
		auto pos = GetTransform()->GetPosition();

		auto mat = GetTransform()->GetMatrix();
		mSprite->SetTransform(&mat);

		mSprite->Begin(D3DXSPRITE_ALPHABLEND);
		mSprite->Draw(tex, nullptr, nullptr, &pos, mColor);
		mSprite->End();
	}
}