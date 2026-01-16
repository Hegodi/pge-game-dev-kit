#pragma once
#include <olcPixelGameEngine.h>

namespace devkit
{
	class BoundingBox
	{
	public:
		void Init(olc::vi2d pos, olc::vi2d size)
		{
			mSize = size;
			mBBmin = pos;
			mBBmax = pos + size;
			mCenter = (mBBmin + mBBmax) / 2;
		}

		void Init(int x, int y, int w, int h)
		{
			Init(olc::vi2d(x, y), olc::vi2d(w, h));
		}

		olc::vi2d GetMin() const { return mBBmin; }
		olc::vi2d GetMax() const { return mBBmax; }
		olc::vi2d GetCenter() const { return mCenter; }
		olc::vi2d GetSize() const { return mSize; }

		bool IsInside(olc::vi2d p)
		{
			return p.x > mBBmin.x && p.x < mBBmax.x && p.y > mBBmin.y && p.y < mBBmax.y;
		}

	private:
		olc::vi2d mBBmin = { 0, 0 };
		olc::vi2d mBBmax = { 0, 0 };
		olc::vi2d mSize = { 0, 0 };
		olc::vi2d mCenter = { 0, 0 };
	};
}