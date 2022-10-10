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
		wcsncpy_s(mDesc.FaceName, _countof(mDesc.FaceName), _T("±¼¸²"), _TRUNCATE);

		if (FAILED(D3DXCreateFontIndirect(d3d::Var::Device, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, _T("Text D3DXCreateFontIndirect() - FAILED"), 0, 0);
		}
	}

	void Text::SetSize(const UINT inSize)
	{
		mDesc.Height = inSize;
		if (FAILED(D3DXCreateFontIndirect(d3d::Var::Device, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, _T("Text D3DXCreateFontIndirect() - FAILED"), 0, 0);
		}
	}

	void Text::SetItalic(const bool inbItalic)
	{
		mDesc.Italic = inbItalic;
		if (FAILED(D3DXCreateFontIndirect(d3d::Var::Device, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, _T("Text D3DXCreateFontIndirect() - FAILED"), 0, 0);
		}
	}

	void Text::SetColor(const D3DXCOLOR& inColor)
	{
		mColor = inColor;
	}

	void Text::SetFlag(DWORD inFlag)
	{
		mFlag = inFlag;
	}

	void Text::SetFont(const std::string& inFontName)
	{
		std::wstring wstr(inFontName.begin(), inFontName.end());
		wcsncpy_s(mDesc.FaceName, _countof(mDesc.FaceName), wstr.c_str(), _TRUNCATE);
		if (FAILED(D3DXCreateFontIndirect(d3d::Var::Device, &mDesc, &mFont)))
		{
			::MessageBox(nullptr, _T("Text D3DXCreateFontIndirect() - FAILED"), 0, 0);
		}
	}

	void Text::SetText(const std::string& inText)
	{
		mStr = inText;
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