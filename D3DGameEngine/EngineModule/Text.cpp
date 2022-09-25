#include "Text.h"
#include "Transform.h"

namespace engine
{
	Text::Text()
		: mFont()
		, mText()
		, mDesc()
		, mColor(d3d::WHITE)
		, mFlag(DT_LEFT)
	{
		::ZeroMemory(&mDesc, sizeof(D3DXFONT_DESC));
		mDesc.Width = 0;
		mDesc.Height = 14;
		mDesc.Weight = FW_NORMAL;
		mDesc.MipLevels = 1;
		mDesc.Italic = false;
		mDesc.CharSet = DEFAULT_CHARSET;
		mDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		mDesc.Quality = DEFAULT_QUALITY;
		mDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		strcpy_s(mDesc.FaceName, "±¼¸²");

		createFontIndirect();
	}

	void Text::SetSize(const UINT size)
	{
		mDesc.Height = size;
		createFontIndirect();
	}

	void Text::SetWeight(const UINT weight)
	{
		mDesc.Weight = weight;
		createFontIndirect();
	}

	void Text::SetItalic(const bool bItalic)
	{
		mDesc.Italic = bItalic;
		createFontIndirect();
	}

	void Text::SetColor(const D3DXCOLOR& color)
	{
		mColor = color;
	}

	void Text::SetFlag(const DWORD flag)
	{
		mFlag = flag;
	}

	void Text::SetFont(const std::string& fontName)
	{
		strcpy_s(mDesc.FaceName, fontName.c_str());
		createFontIndirect();
	}

	void Text::SetText(const std::string& text)
	{
		mText = text;
	}

	void Text::Draw()
	{
		if (!mFont.Get())
		{
			return;
		}

		auto pos = GetTransform()->GetPosition();
		RECT rect;
		rect.left = static_cast<LONG>(pos.x);
		rect.top = static_cast<LONG>(pos.y);
		mFont->DrawText(nullptr, mText.c_str(), _TRUNCATE, &rect, DT_NOCLIP | mFlag, mColor);
	}

	bool Text::createFontIndirect()
	{
		if (mFont.Get())
		{
			mFont.Get()->Release();
		}

		if (FAILED(D3DXCreateFontIndirect(d3d::gDevice, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, "Text - D3DXCreateFontIndirect() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		return true;
	}
}