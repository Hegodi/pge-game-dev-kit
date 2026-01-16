#pragma once
#include <olcPixelGameEngine.h>
#include <olcPGEX_Font.h>
#include <functional>
#include <UI/UIBase.h>
#include <UI/BoundingBox.h>

using OnClickCallback = std::function<void(void)>;

class UIButton : public UIBase
{
public:
	UIButton(int x, int y, int width, int height, const char* text, OnClickCallback onClick)
		: mText(text)
		, mCallback(onClick)
	{
		mBB.Init(x, y, width, height);

		mPosText = olc::vi2d(x + width / 2 - 8 * mText.length() / 2, y + height / 2 - 4);
	}

	void SetCallback(OnClickCallback callback)
	{
		mCallback = callback;
	}

	bool UpdateInternal(olc::PixelGameEngine* pge) override
	{
		auto pos = pge->GetMousePos();
		if (mBB.IsInside(pos))
		{
			if (pge->GetMouse(0).bPressed)
			{
				mColor = mColorPressed;
				if (mCallback != nullptr)
				{
					mCallback();
					return true;
				}
			}
			else
			{
				mColor = mColorHighlight;
			}
				
		}
		else
		{
			mColor = mColorDefault;

		}
		return false;
	}

	void DrawInternal(olc::PixelGameEngine* pge) const override
	{
		pge->FillRect(mBB.GetMin(), mBB.GetSize(), mColor);
		if (mFont)
		{
			mFont->DrawStringDecal(mPosText, mText, olc::BLACK);
		}
		else
		{
			pge->DrawString(mPosText, mText, olc::BLACK);
		}
	}

	void SetText(const char* text) { mText = text; }

	void SetDefaultColor(olc::Pixel color) { mColorDefault = color; }
	void SetHighLightColor(olc::Pixel color) { mColorHighlight = color; }
	void ResetDefaultColor() { mColorDefault = olc::GREY; }


private:
	olc::Pixel mColor = olc::GREY;
	olc::Pixel mColorDefault = olc::GREY;
	olc::Pixel mColorHighlight = olc::YELLOW;
	olc::Pixel mColorPressed = olc::RED;
	std::string mText;
	BoundingBox mBB;
	olc::vi2d mPosText;
	OnClickCallback mCallback = nullptr;
	std::shared_ptr<olc::Font> mFont = nullptr;
};