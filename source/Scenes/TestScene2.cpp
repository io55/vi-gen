#include <MainApplication.hpp>
#include <Scenes/TestScene2.hpp>

void TestScene2::initialise()
{
}

void TestScene2::run()
{
	MainApplication* app     = MainApplication::gMainApp;
	sf::RenderWindow& window = app->getWindow();
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
