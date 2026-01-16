#pragma once 
namespace olc
{
	class PixelGameEngine;
}

namespace devkit
{

	class UIBase
	{
	public:
		virtual ~UIBase() = default;

		void Update(olc::PixelGameEngine* pge)
		{
			if (!mEnabled)
			{
				return;
			}

			UpdateInternal(pge);
			DrawInternal(pge);
		}

		void Enable() { mEnabled = true; }
		void Disable() { mEnabled = false; }

	protected:
		virtual void DrawInternal(olc::PixelGameEngine* pge) const = 0;
		virtual bool UpdateInternal(olc::PixelGameEngine* pge) = 0;

	private:
		bool mEnabled = true;
	};
}