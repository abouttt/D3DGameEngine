#include "Text.h"
#include "Transform.h"

namespace engine
{
	Text::Text()
		: mFont()
		, mStr()
		, mDesc()
		, mColor(d3d::WHITE)
		, mFlag(DT_LEFT)
	{
		::ZeroMemory(&mDesc, sizeof(D3DXFONT_DESC));
		mDesc.Width = 0;
		mDesc.Height = 30;
		mDesc.Weight = FW_NORMAL;
		mDesc.MipLevels = 1;
		mDesc.Italic = false;
		mDesc.CharSet = HANGUL_CHARSET;
		mDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
		mDesc.Quality = DEFAULT_QUALITY;
		mDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
		strcpy_s(mDesc.FaceName, "±¼¸²");

		if (FAILED(D3DXCreateFontIndirect(d3d::gDevice, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, "Text - D3DXCreateFontIndirect() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
		}
	}

	void Text::SetSize(const UINT size)
	{
		mDesc.Height = size;
		if (FAILED(D3DXCreateFontIndirect(d3d::gDevice, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, "Text - D3DXCreateFontIndirect() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
		}
	}

	void Text::SetItalic(const bool bItalic)
	{
		mDesc.Italic = bItalic;
		if (FAILED(D3DXCreateFontIndirect(d3d::gDevice, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, "Text D3DXCreateFontIndirect() - FAILED", 0, 0);
		}
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
		if (FAILED(D3DXCreateFontIndirect(d3d::gDevice, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, "Text - D3DXCreateFontIndirect() : FAILED", "Error", MB_ICONEXCLAMATION | MB_OK);
		}
	}

	void Text::SetText(const std::string& text)
	{
		mStr = text;
	}

	void Text::Draw()
	{
		auto pos = GetTransform()->GetPosition();
		RECT rect;
		rect.left = static_cast<LONG>(pos.x);
		rect.top = static_cast<LONG>(pos.y);
		mFont->DrawTextA(nullptr, mStr.c_str(), (int)mStr.size(), &rect, DT_NOCLIP | mFlag, mColor);
	}
}