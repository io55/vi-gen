#include <MainApplication.hpp>
#include <TestScene.hpp>
#include <chrono>
#include <random>
#include <util.hpp>

void TestScene::initialise()
{
	MainApplication* app          = MainApplication::gMainApp;
	sf::RenderWindow& window      = app->getWindow();
	const sf::Vector2u windowSize = window.getSize();

	const f32 halfWindowX = static_cast<f32>(windowSize.x / 2);
	const f32 halfWindowY = static_cast<f32>(windowSize.y / 2);

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> sizeDistGen(static_cast<u32>(windowSize.x / 5),
	                                            static_cast<u32>(windowSize.x / 1.5f));

	const sf::Color bgColA = { 0x33, 0x55, 0x77 };
	const sf::Color bgColB = { 0x77, 0x55, 0x33 };

	for (u32 i = 0; i < 2; i++) {
		const u32 randomSizeX = sizeDistGen(gen);

		sf::RectangleShape shape1(sf::Vector2f(static_cast<f32>(randomSizeX), halfWindowY));
		shape1.setPosition(0, static_cast<f32>(i * halfWindowY));
		shape1.setFillColor(i % 2 == 0 ? bgColA : bgColB);

		sf::RectangleShape shape2(sf::Vector2f(static_cast<f32>(windowSize.x - randomSizeX), halfWindowY));
		shape2.setPosition(static_cast<f32>(randomSizeX), static_cast<f32>(i * halfWindowY));
		shape2.setFillColor(i % 2 == 0 ? bgColB : bgColA);

		mBackgroundShapes.push_back(shape1);
		mBackgroundShapes.push_back(shape2);
	}

	// Configure Player sprites
	{
		sf::RectangleShape& lookShape = mPlayer.mLookRectShape;
		const sf::Vector2f lookShapeSize(50.0f, 10.0f);
		lookShape.setSize(lookShapeSize);
		lookShape.setOrigin(0.0f, lookShapeSize.y / 2);
		lookShape.setPosition(halfWindowX, halfWindowY);
		lookShape.setFillColor(sf::Color::Yellow);

		sf::CircleShape& playerShape = mPlayer.mPlayerShape;
		playerShape.setRadius(10.0f);
		playerShape.setOrigin(10.0f, 10.0f);
		playerShape.setPosition(halfWindowX, halfWindowY);
		playerShape.setFillColor(sf::Color::Red);
	}
}

SceneStates TestScene::run()
{
	MainApplication* app     = MainApplication::gMainApp;
	sf::RenderWindow& window = app->getWindow();

	// Generate cool random bg
	for (const sf::RectangleShape& rectShape : mBackgroundShapes) {
		window.draw(rectShape);
	}

	// Player handling
	{
		sf::RectangleShape& lookShape = mPlayer.mLookRectShape;
		const sf::Vector2f& lookPos   = lookShape.getPosition();

		const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		const sf::Vector2f mouseCoord    = window.mapPixelToCoords(mousePosition);

		// Calculate the angle to the mouses cursor using our position,
		// then convert it to radians so that it can be applied to SFML
		const f32 angle = std::atan2f(mouseCoord.y - lookPos.y, mouseCoord.x - lookPos.x);
		lookShape.setRotation(angle * math::gRad2Deg);
		window.draw(lookShape);

		sf::CircleShape& playerShape = mPlayer.mPlayerShape;
		window.draw(playerShape);
	}

	return SceneStates::TestScene;
}

void TestScene::cleanup() { mBackgroundShapes.clear(); }

void TestScene::handleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::Key::R) {
			cleanup();
			initialise();
		} else if (ev.key.code == sf::Keyboard::Key::Escape) {
			MainApplication::gMainApp->switchScene(SceneStates::MainMenu);
		}
	}
}
