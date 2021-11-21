#include <MainApplication.hpp>
#include <Scenes/TestScene2.hpp>
#include <util.hpp>

void TestScene2::initialise()
{
	auto appWindowPair       = GetAppAndWindow();
	MainApplication* app     = appWindowPair.first;
	sf::RenderWindow& window = appWindowPair.second;

	const sf::Vector2u windowSize = window.getSize();

	mSize.x = static_cast<u32>(std::floor(windowSize.x / 5.0f));
	mSize.y = static_cast<u32>(std::floor(windowSize.y / 5.0f));
	mBackgroundShapes.resize(mSize.x * mSize.y);
	for (u32 x = 0; x < mSize.x; x++) {
		for (u32 y = 0; y < mSize.y; y++) {
			mBackgroundShapes[y * mSize.x + x] = sf::RectangleShape(sf::Vector2f(5.0f, 5.0f));
		}
	}
}

void TestScene2::run()
{
	MainApplication* app     = MainApplication::gMainApp;
	sf::RenderWindow& window = app->getWindow();

	for (u32 x = 0; x < mSize.x; x++) {
		for (u32 y = 0; y < mSize.y; y++) {
			sf::RectangleShape& curShape = mBackgroundShapes[y * mSize.x + x];
			curShape.setPosition(x * 5, y * 5);
			const u8 red   = util::WrapValue(static_cast<u8>(x + mInfluence.x), 0xFF, 0x00);
			const u8 green = util::WrapValue(static_cast<s8>(y - mInfluence.y), 0xFF, 0x00);
			const u8 blue  = x + y;
			curShape.setFillColor(sf::Color(util::RGBAToInt(red, green, blue)));
			window.draw(curShape);
		}
	}

	if (mInfluenceDir.first) {
		mInfluence.x++;
	} else {
		mInfluence.x--;
	}

	if (mInfluenceDir.second) {
		mInfluence.y--;
	} else {
		mInfluence.y++;
	}

	if (mInfluence.x <= 0 && !mInfluenceDir.first) {
		mInfluenceDir.first = true;
	} else if (mInfluence.x >= 0xFF && mInfluenceDir.first) {
		mInfluenceDir.first = false;
	}

	if (mInfluence.y <= 0 && mInfluenceDir.second) {
		mInfluenceDir.second = true;
	} else if (mInfluence.y >= 0xFF && !mInfluenceDir.second) {
		mInfluenceDir.second = false;
	}
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
