#pragma once

#include <string>
#include <wrl.h>

#include "D3DUtil.h"
#include "UI.h"

namespace engine
{
	class Text : public UI
	{
	public:
		Text();

	public:
		void SetSize(const UINT inSize);
		void SetItalic(const bool inbItalic);
		void SetColor(const D3DXCOLOR& inColor);
		void SetFlag(const DWORD inFlag);
		void SetFont(const std::string& inFontName);
		void SetText(const std::string& inText);

		void Draw() override;

	private:
		Microsoft::WRL::ComPtr<ID3DXFont> mFont;
		std::string mStr;
		D3DXFONT_DESC mDesc;
		D3DXCOLOR mColor;
		DWORD mFlag;
	};
}