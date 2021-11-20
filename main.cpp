#include <MainApplication.hpp>
#include <MainMenu.hpp>
#include <SFML/Graphics.hpp>
#include <TestScene.hpp>

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(575, 575), "io55-generator");

	MainApplication::gMainApp = new MainApplication(window);
	MainApplication* app      = MainApplication::gMainApp;

	// Configure scene information
	auto& sceneInfo = app->getSceneInfo();

	MainMenu scene0;
	sceneInfo.addScene(&scene0);

	TestScene scene1;
	sceneInfo.addScene(&scene1);

	// Trigger startup
	app->switchScene(SceneStates::MainMenu);
	app->run();

	// Cleanup resources
	delete MainApplication::gMainApp;

	return EXIT_SUCCESS;
}