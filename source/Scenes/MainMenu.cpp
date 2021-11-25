#include <MainApplication.hpp>
#include <Scenes/MainMenu.hpp>
#include <util.hpp>

static void Button1Press() { MainApplication::gMainApp->switchScene(SceneState::TestScene1); }
static void Button2Press() { MainApplication::gMainApp->switchScene(SceneState::TestScene2); }
static void Button3Press() { std::exit(EXIT_SUCCESS); }

static MenuItem gMenuItems[] = {
	MenuItem(new sf::RectangleShape(sf::Vector2f(200, 30)), sf::Color(util::RGBAToInt(0xFF, 0x00, 0x00)), Button1Press),
	MenuItem(new sf::RectangleShape(sf::Vector2f(200, 30)), sf::Color(util::RGBAToInt(0x00, 0xFF, 0x00)), Button2Press),
	MenuItem(new sf::RectangleShape(sf::Vector2f(200, 30)), sf::Color(util::RGBAToInt(0x00, 0x00, 0xFF)), Button3Press)
};

void MainMenu::initialise()
{
	// Populate animation squares
	mAnimationSquares.resize(mSizeX * mSizeY);
	for (u32 x = 0; x < mSizeX; x++) {
		for (u32 y = 0; y < mSizeY; y++) {
			mAnimationSquares[y * mSizeX + x]
			    = sf::RectangleShape(sf::Vector2f(static_cast<f32>(mSizeX), static_cast<f32>(mSizeY)));
		}
	}

	// Populate menu
	const sf::Vector2u windowSize = MainApplication::gMainApp->getWindow().getSize();

	mMenu.mItems.clear();
	for (u32 i = 0; i < static_cast<u32>(sizeof(gMenuItems) / sizeof(MenuItem)); i++) {
		sf::RectangleShape* curShape = static_cast<sf::RectangleShape*>(gMenuItems[i].getShape());

		sf::Vector2f position = sf::Vector2f((windowSize.x / 2) - curShape->getSize().x / 2,
		                                     (windowSize.y / 2 - curShape->getSize().y / 2) + i * 50);

		curShape->setPosition(position);
		mMenu.mItems.push_back(&gMenuItems[i]);
	}

	mMainMenuText.setFont(MainApplication::gFont);
	mMainMenuText.setString("IO55 VISUAL GENERATOR");
	mMainMenuText.setCharacterSize(36);
	mMainMenuText.setPosition(
	    sf::Vector2f((windowSize.x / 2) - (mMainMenuText.getGlobalBounds().width / 2),
	                 (windowSize.y / 2) - (mMainMenuText.getGlobalBounds().height / 2) - (windowSize.y / 4)));
	mMainMenuText.setFillColor(sf::Color::White);
	mMainMenuText.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

void MainMenu::run()
{
	sf::RenderWindow& window = MainApplication::gMainApp->getWindow();

	const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	const sf::Vector2f mouseCoord    = window.mapPixelToCoords(mousePosition);

	if (mMenu.tickMouse(mouseCoord)) {
		return;
	}

	// Play animation
	const f32 dt = MainApplication::gMainApp->getDeltaTime();
	mAnimTimer += dt;
	for (u32 x = 0; x < mSizeX; x++) {
		for (u32 y = 0; y < mSizeY; y++) {
			sf::RectangleShape& curRect = mAnimationSquares[x + y * mSizeX];
			curRect.setPosition(static_cast<f32>(mSizeX) * x, static_cast<f32>(mSizeY) * y);

			const u8 red   = util::WrapValue(static_cast<u8>((x + 1) ^ (y + 1)), 0xFF, 0x00);
			const u8 green = util::WrapValue(static_cast<u8>(y + mAnimTimer * 3), 0xAA, 0x20);
			const u8 blue  = util::WrapValue(static_cast<u8>(y + x + mAnimTimer * 50), 0x80, 0x50);
			curRect.setFillColor(sf::Color(util::RGBAToInt(red, green, blue)));

			curRect.rotate(dt * 15);
			window.draw(curRect);
		}
	}

	mMenu.draw(window);
	window.draw(mMainMenuText);
}

void MainMenu::cleanup()
{
	mAnimationSquares.clear();
	mAnimTimer = 0.0f;
}

void MainMenu::handleEvents(sf::Event& event) { }
