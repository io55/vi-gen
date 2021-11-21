#include <MainApplication.hpp>

#include <Scenes/MainMenu.hpp>
#include <Scenes/TestScene1.hpp>
#include <Scenes/TestScene2.hpp>

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(575, 575), "io55-generator");

	MainApplication::gMainApp = new MainApplication(window);
	MainApplication* app      = MainApplication::gMainApp;

	// Configure scene information
	auto& sceneInfo = app->getSceneInfo();

	MainMenu scene0;
	sceneInfo.addScene(&scene0);

	TestScene1 scene1;
	sceneInfo.addScene(&scene1);

	TestScene2 scene2;
	sceneInfo.addScene(&scene2);

	// Trigger startup
	app->switchScene(SceneState::MainMenu);
	app->run();

	// Cleanup resources
	delete MainApplication::gMainApp;

	return EXIT_SUCCESS;
}