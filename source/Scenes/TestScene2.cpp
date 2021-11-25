#include <MainApplication.hpp>
#include <Scenes/TestScene2.hpp>
#include <numeric>
#include <util.hpp>

void TestScene2::initialise()
{
	auto appWindowPair       = GetAppAndWindow();
	MainApplication* app     = appWindowPair.first;
	sf::RenderWindow& window = appWindowPair.second;

	mInfluence = 0;

	const sf::Vector2u windowSize = window.getSize();

	constexpr f32 scaleWeight = 4.0f;
	mSize.x                   = static_cast<u32>(std::floor(windowSize.x / scaleWeight));
	mSize.y                   = static_cast<u32>(std::floor(windowSize.y / scaleWeight));
	mBackgroundShapes.resize(mSize.x * mSize.y);
	for (u32 x = 0; x < mSize.x; x++) {
		for (u32 y = 0; y < mSize.y; y++) {
			mBackgroundShapes[y * mSize.x + x] = sf::RectangleShape(sf::Vector2f(scaleWeight, scaleWeight));
		}
	}
}

void TestScene2::run()
{
	MainApplication* app     = MainApplication::gMainApp;
	sf::RenderWindow& window = app->getWindow();

	if (mInfluence >= 250) {
		mInfluence -= 250;
	}

	for (u32 x = 0; x < mSize.x; x++) {
		for (u32 y = 0; y < mSize.y; y++) {
			sf::RectangleShape& curShape = mBackgroundShapes[y * mSize.x + x];
			curShape.setPosition(x * 4.0f, y * 4.0f);
			const u32 product = x + y + (750 % ((y ^ x) + 1));
			const u8 red      = static_cast<u8>(mInfluence + product);
			const u8 blue     = static_cast<u8>(x * y + product);
			curShape.setFillColor(sf::Color(util::RGBAToInt(red, 0x00, blue, 0x80)));
			window.draw(curShape);
		}
	}

	mInfluence++;
}

void TestScene2::cleanup() { }

void TestScene2::handleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::Key::Escape) {
			MainApplication::gMainApp->switchScene(SceneState::MainMenu);
		}
	}
}
