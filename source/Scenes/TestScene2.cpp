#include <MainApplication.hpp>
#include <Scenes/TestScene2.hpp>
#include <numeric>
#include <util.hpp>

void TestScene2::initialise()
{
	auto appWindowPair       = GetAppAndWindow();
	MainApplication* app     = appWindowPair.first;
	sf::RenderWindow& window = appWindowPair.second;

	const sf::Vector2u windowSize = window.getSize();

	mSize.x = static_cast<u32>(std::floor(windowSize.x / mSizeDenom));
	mSize.y = static_cast<u32>(std::floor(windowSize.y / mSizeDenom));
	mBackground.resize(mSize.x, mSize.y);
	for (u32 x = 0; x < mSize.x; x++) {
		for (u32 y = 0; y < mSize.y; y++) {
			mBackground.mPixelProductList.push_back(((x ^ y) + 1 + x) % 250);
		}
	}
}

void TestScene2::run()
{
	MainApplication* app     = MainApplication::gMainApp;
	sf::RenderWindow& window = app->getWindow();

	if (mInfluence == 0xFF) {
		mInfluence -= 0xFF;
	}

	for (u32 x = 0; x < mSize.x; x++) {
		for (u32 y = 0; y < mSize.y; y++) {
			const u32 product = mBackground.mPixelProductList[y * mSize.x + x];
			const u8 red      = static_cast<u8>(mInfluence + product + (x ^ y));
			const u8 green    = static_cast<u8>(static_cast<u8>(product + (x ^ y)) / 2);
			const u8 blue     = static_cast<u8>(static_cast<u8>(x * y + product + (x ^ y)) / 2);
			mBackground.setPixel(x, y, sf::Color(util::RGBAToInt(red, green, blue, 0x80)));
		}
	}

	mBackground.draw(window);

	mInfluence++;
}

void TestScene2::cleanup() { mInfluence = 0; }

void TestScene2::handleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::Key::Escape) {
			MainApplication::gMainApp->switchScene(SceneState::MainMenu);
		}
	}
}
