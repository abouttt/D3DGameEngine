#pragma once

#include <string>

#include "D3DUtil.h"
#include "UI.h"

namespace engine
{
	class Text : public UI
	{
	public:
		Text();

	public:
		void SetSize(const UINT size);
		void SetItalic(const bool bItalic);
		void SetColor(const D3DXCOLOR& color);
		void SetFlag(const DWORD flag);
		void SetFont(const std::string& fontName);
		void SetText(const std::string& text);

	public:
		void Draw() override;

	private:
		Microsoft::WRL::ComPtr<ID3DXFont> mFont;
		std::string mStr;
		D3DXFONT_DESC mDesc;
		D3DXCOLOR mColor;
		DWORD mFlag;
	};
}
