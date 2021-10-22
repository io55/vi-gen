#include <MainApplication.hpp>
#include <TestScene.hpp>
#include <chrono>
#include <random>
#include <util.hpp>

void TestScene::initialise()
{
	MainApplication* app     = MainApplication::gMainApp;
	sf::RenderWindow& window = app->getWindow();

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(window.getSize().x / 5, window.getSize().x / 1.2f);

	for (u32 i = 0; i < 2; i++) {
		const u32 randomSizeX = distrib(gen);

		sf::RectangleShape shape1(
		    sf::Vector2f(static_cast<f32>(randomSizeX), static_cast<f32>(window.getSize().y / 2)));
		shape1.setPosition(0, static_cast<f32>(i * (window.getSize().y / 2)));
		shape1.setFillColor(i % 2 == 0 ? sf::Color::Red : sf::Color::Blue);

		sf::RectangleShape shape2(
		    sf::Vector2f(static_cast<f32>(window.getSize().x - randomSizeX), static_cast<f32>(window.getSize().y / 2)));
		shape2.setPosition(static_cast<f32>(randomSizeX), static_cast<f32>(i * (window.getSize().y / 2)));
		shape2.setFillColor(i % 2 == 0 ? sf::Color::Blue : sf::Color::Red);

		mBackgroundShapes.push_back(shape1);
		mBackgroundShapes.push_back(shape2);
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

	return SceneStates::TestScene;
}

void TestScene::cleanup() { mBackgroundShapes.clear(); }

void TestScene::handleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed) {
		if (ev.key.code == sf::Keyboard::Key::F) {
			cleanup();
			initialise();
		}
	}
}
