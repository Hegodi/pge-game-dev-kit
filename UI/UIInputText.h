#pragma once
#include <olcPixelGameEngine.h>
#include <olcPGEX_Font.h>
#include <functional>
#include <UI/UIText.h>
#include <UI/BoundingBox.h>


namespace InputTextInternal
{
	constexpr char letters[] = {
	'a','b','c','d','e','f','g','h','i','j','k','l','m',
	'n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
	constexpr char letters_capital[] = {
	'A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	constexpr char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };


}
namespace devkit
{

	class UIInputText : public UIText
	{
	public:
		UIInputText(int x, int y, int width, int height, const char* text, olc::Pixel textColor) : UIText(x, y, text, textColor)
		{
			mBB.Init(x, y, width, height);
			SetSelected(false);
			mPosText = olc::vi2d(x, y + height / 2 - 4);
		}
		UIInputText(int x, int y, int width, int height, const char* text, olc::Pixel textColor, std::shared_ptr<olc::Font> font) : UIText(x, y, text, textColor, font)
		{
			mBB.Init(x, y, width, height);
			SetSelected(false);
			mPosText = olc::vi2d(x, y + height / 2 - 4);
		}

		void SetMaxLength(int numCharacters)
		{
			mMaxLengthText = numCharacters;
		}

	private:

		void DrawInternal(olc::PixelGameEngine* pge) const override
		{
			pge->FillRect(mBB.GetMin(), mBB.GetSize(), mColorBG);
			if (mFont)
			{
				mFont->DrawStringDecal(mPosText, mText, mColorTxt);
			}
			else
			{
				pge->DrawString(mPosText, mText, mColorTxt);
			}

			if (mSelected)
			{
				const int characterWidth = 8;
				pge->FillRect(mPosText.x + mCursorPosition * characterWidth, mBB.GetMin().y + 3, 2, mBB.GetSize().y - 6, olc::BLACK);
			}
		}


		bool UpdateInternal(olc::PixelGameEngine* pge) override
		{
			if (pge->GetMouse(0).bPressed)
			{
				auto pos = pge->GetMousePos();
				SetSelected(mBB.IsInside(pos));
			}

			if (mSelected)
			{
				UpdateInput(pge);
			}
			return false;
		}

	private:
		void UpdateInput(olc::PixelGameEngine* pge)
		{
			if (pge->GetKey(olc::LEFT).bPressed)
			{
				mCursorPosition = mCursorPosition <= 0 ? mCursorPosition : mCursorPosition - 1;
			}
			else if (pge->GetKey(olc::RIGHT).bPressed)
			{
				mCursorPosition = mCursorPosition >= mText.length() ? mCursorPosition : mCursorPosition + 1;
			}
			else if (pge->GetKey(olc::BACK).bPressed)
			{
				if (mCursorPosition > 0)
				{
					mText.erase(mCursorPosition - 1, 1);
					mCursorPosition--;
				}
			}

			if (mText.length() < mMaxLengthText)
			{
				if (pge->GetKey(olc::SPACE).bPressed)
				{
					mText.insert(mCursorPosition, 1, ' ');
					mCursorPosition++;
				}
				else if (pge->GetKey(olc::PERIOD).bPressed || pge->GetKey(olc::NP_DECIMAL).bReleased)
				{
					mText.insert(mCursorPosition, 1, '.');
					mCursorPosition++;
				}
				else if (pge->GetKey(olc::COMMA).bPressed)
				{
					mText.insert(mCursorPosition, 1, ',');
					mCursorPosition++;
				}
				else if (pge->GetKey(olc::MINUS).bPressed)
				{
					mText.insert(mCursorPosition, 1, '-');
					mCursorPosition++;
				}
				else
				{
					for (int k = olc::A; k <= olc::Z; ++k)
					{
						if (pge->GetKey(static_cast<olc::Key>(k)).bPressed)
						{
							int ind = k - olc::A;
							if (pge->GetKey(olc::SHIFT).bHeld)
							{
								mText.insert(mCursorPosition, 1, InputTextInternal::letters_capital[ind]);
							}
							else
							{
								mText.insert(mCursorPosition, 1, InputTextInternal::letters[ind]);
							}
							mCursorPosition++;
							return;
						}
					}
					for (int k = olc::K0; k <= olc::K9; ++k)
					{
						if (pge->GetKey(static_cast<olc::Key>(k)).bPressed)
						{
							int ind = k - olc::K0;
							mText.insert(mCursorPosition, 1, InputTextInternal::numbers[ind]);
							mCursorPosition++;
							return;
						}
					}
					for (int k = olc::NP0; k <= olc::NP9; ++k)
					{
						if (pge->GetKey(static_cast<olc::Key>(k)).bPressed)
						{
							int ind = k - olc::NP0;
							mText.insert(mCursorPosition, 1, InputTextInternal::numbers[ind]);
							mCursorPosition++;
							return;
						}
					}
				}
			}


		}


		void SetSelected(bool selected)
		{
			if (!mSelected)
			{
				mCursorPosition = mText.length();
			}

			mSelected = selected;
			if (mSelected)
			{
				mColorBG = mColorBGselected;
			}
			else
			{
				mColorBG = mColorBGdefault;
			}
		}

	private:
		olc::Pixel mColorBG = olc::BLACK;
		olc::Pixel mColorBGselected = olc::WHITE;
		olc::Pixel mColorBGdefault = olc::GREY;
		bool mSelected = false;
		BoundingBox mBB;
		int mCursorPosition = 0;
		int mMaxLengthText = 120;
	};
}