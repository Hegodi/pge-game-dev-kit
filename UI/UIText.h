#pragma once
#include <olcPixelGameEngine.h>
#include <olcPGEX_Font.h>
#include <functional>
#include <UI/UIBase.h>

namespace devkit
{
	class UIText : public UIBase
	{
	public:
		UIText(int x, int y, const char* text, olc::Pixel textColor)
			: mPos(x, y)
			, mText(text)
			, mColorTxt(textColor)
		{
			CalculateTextPosition();
		}
		UIText(int x, int y, const char* text, olc::Pixel textColor, std::shared_ptr<olc::Font> font)
			: mPos(x, y)
			, mText(text)
			, mColorTxt(textColor)
			, mFont(font)
		{
			CalculateTextPosition();
		}

		bool UpdateInternal(olc::PixelGameEngine* pge) override
		{
			return false;
		}

		void DrawInternal(olc::PixelGameEngine* pge) const override
		{
			if (mFont)
			{
				mFont->DrawStringDecal(mPosText, mText, mColorTxt);
			}
			else
			{
				pge->DrawString(mPosText, mText, mColorTxt);
			}
		}

		void SetText(const char* text) { mText = text; }
		void SetColorText(olc::Pixel color) { mColorTxt = color; }

		void CalculateTextPosition()
		{
			// TODO: manage alignment here
			mPosText = mPos;
		}


	protected:
		olc::Pixel mColorTxt = olc::GREY;
		std::string mText;
		olc::vi2d mPos;
		olc::vi2d mPosText;
		std::shared_ptr<olc::Font> mFont = nullptr;
	};
}