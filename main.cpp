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
	auto& sceneInfo  = app->getSceneInfo();
	sceneInfo.mIndex = 0;
	sceneInfo.mState = SceneStates::MainMenu;

	MainMenu scene0;
	sceneInfo.mList.push_back(&scene0);

	TestScene scene1;
	sceneInfo.mList.push_back(&scene1);

	// Trigger startup!
	app->switchScene(SceneStates::Startup);
	app->run();

	return EXIT_SUCCESS;
}