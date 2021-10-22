#include <MainApplication.hpp>
#include <MainMenu.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(575, 575), "io55-generator");

	// Generate application
	MainApplication app(window);

	// Configure scene information
	MainMenu scene0;

	auto& sceneInfo  = app.getSceneInfo();
	sceneInfo.mIndex = 0;
	sceneInfo.mState = SceneStates::MainMenu;
	sceneInfo.mList.push_back(&scene0);

	// Trigger startup!
	app.switchScene(SceneStates::Startup);
	app.run();

	return EXIT_SUCCESS;
}