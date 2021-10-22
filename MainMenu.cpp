#include <MainApplication.hpp>
#include <MainMenu.hpp>
#include <util.hpp>

void MainMenu::initialise(Application& app)
{
	mAnimationSquares.resize(mSizeX * mSizeY);
	for (u32 x = 0; x < mSizeX; x++) {
		for (u32 y = 0; y < mSizeY; y++) {
			mAnimationSquares[y * mSizeX + x]
			    = sf::RectangleShape(sf::Vector2f(static_cast<f32>(mSizeX), static_cast<f32>(mSizeY)));
		}
	}
}

SceneStates MainMenu::run(Application& app)
{
	MainApplication& mainApp = dynamic_cast<MainApplication&>(app);

	// Play animation
	const f32 dt = mainApp.getDeltaTime();
	mAnimTimer += dt;
	for (u32 x = 0; x < mSizeX; x++) {
		for (u32 y = 0; y < mSizeY; y++) {
			sf::RectangleShape& curRect = mAnimationSquares[x + y * mSizeX];
			curRect.setPosition(static_cast<f32>(mSizeX) * x, static_cast<f32>(mSizeY) * y);

			const u8 red   = util::WrapValue(static_cast<u8>(x + y + mAnimTimer * 10), 0xFF, 0x00);
			const u8 green = util::WrapValue(static_cast<u8>(y + mAnimTimer * 3), 0xAA, 0x20);
			const u8 blue  = util::WrapValue(static_cast<u8>(y + x + mAnimTimer * 50), 0x80, 0x50);

			curRect.setFillColor(sf::Color(util::RGBAToInt(red, green, blue)));

			curRect.rotate(dt * 15);
			mainApp.getWindow().draw(curRect);
		}
	}

	// TODO: Render text and get input on buttons

	return SceneStates::MainMenu;
}

void MainMenu::cleanup(Application& app)
{
	mAnimationSquares.clear();
	mAnimTimer = 0;
}

void MainMenu::handleEvents(Application& app, sf::Event& event) { }
