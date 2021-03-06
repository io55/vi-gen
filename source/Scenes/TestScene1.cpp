#include <MainApplication.hpp>
#include <Scenes/TestScene1.hpp>
#include <chrono>
#include <random>
#include <util.hpp>

void TestScene1::initialise()
{
	MainApplication* app          = MainApplication::gMainApp;
	sf::RenderWindow& window      = app->getWindow();
	const sf::Vector2u windowSize = window.getSize();

	const f32 halfWindowX = static_cast<f32>(windowSize.x / 2);
	const f32 halfWindowY = static_cast<f32>(windowSize.y / 2);

	mPlayer.setup(halfWindowX, halfWindowY);

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
}

void TestScene1::run()
{
	auto appWindowPair       = GetAppAndWindow();
	MainApplication* app     = appWindowPair.first;
	sf::RenderWindow& window = appWindowPair.second;

	// Generate cool random bg
	for (const sf::RectangleShape& rectShape : mBackgroundShapes) {
		window.draw(rectShape);
	}

	if (window.hasFocus()) {
		constexpr f32 speed = 0.1f;
		const f32 deltaTime = MainApplication::getDeltaTime();

		sf::Vector2f nextPos = mPlayer.getPosition();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			nextPos.y -= speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			nextPos.y += speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			nextPos.x -= speed;
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			nextPos.x += speed;
		}
		mPlayer.setPosition(nextPos);
	}

	// Player handling
	mPlayer.render(window);
}

void TestScene1::cleanup() { mBackgroundShapes.clear(); }

void TestScene1::handleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {

		switch (ev.key.code) {
		case sf::Keyboard::Key::R:
			cleanup();
			initialise();
			break;
		case sf::Keyboard::Key::Escape:
			MainApplication::gMainApp->switchScene(SceneState::MainMenu);
			break;
		default:
			break;
		}
	}
}
