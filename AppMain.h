#include <olcPixelGameEngine.h>

#include <UI/UIBase.h>

namespace devkit
{
	class AppMain : public olc::PixelGameEngine
	{
	public:
		AppMain(const char* appName)
		{
			sAppName = appName;
		}

		virtual void Update(float dt) = 0;
		void SetClearColor(olc::Pixel color) { mColorClear = color; }

		template<typename T, typename... Args>
		std::shared_ptr<T> CreateUiElement(Args&&... args)
		{
			static_assert(std::is_base_of_v<UIBase, T>);
			std::shared_ptr<T> uiElement = std::make_shared<T>(std::forward<Args>(args)...);
			mUiElements.push_back(std::shared_ptr<UIBase>(uiElement));
			return uiElement;
		}

		void ClearUiElements()
		{
			mUiElements.clear();
		}

	private:
		bool OnUserUpdate(float fElapsedTime) final
		{
			Clear(mColorClear);

			Update(fElapsedTime);
			UpdateUIElements();

			return true;
		}

		void UpdateUIElements()
		{
			for (auto& ui : mUiElements)
			{
				ui->Update(this);
			}
		}


	private:
		olc::Pixel mColorClear = olc::BLACK;
	public:
		std::vector<std::shared_ptr<UIBase>> mUiElements;

	};
}
