#include <MainApplication.hpp>
#include <cassert>
#include <util.hpp>

sf::Time MainApplication::gDeltaTimer;
MainApplication* MainApplication::gMainApp;

MainApplication::MainApplication(sf::RenderWindow& window)
    : mWindow(window)
{
}

void MainApplication::run()
{
	sf::Clock deltaClock;
	while (mWindow.isOpen()) {
		gDeltaTimer = deltaClock.restart();

		sf::Event event;
		while (mWindow.pollEvent(event)) {
			handleEvents(event);
		}

		mWindow.clear();
		getCurrentScene()->run();
		mWindow.display();
	}
}

void MainApplication::switchScene(SceneState nextState)
{
	// Cleanup the previous scene and find the new scene
	Scene* prevScene = getCurrentScene();
	prevScene->cleanup();

	bool found = false;
	for (std::size_t i = 0; i < mSceneInfo.mList.size(); i++) {
		if (mSceneInfo.mList[i]->getState() == nextState) {
			mSceneInfo.mIndex = i;
			mSceneInfo.mState = nextState;
			found             = true;
			break;
		}
	}

	assert(found && "Couldn't find wanted scene");

	// Initialise current scene
	getCurrentScene()->initialise();
}

void MainApplication::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::Closed) {
		mWindow.close();
		return;
	}

	getCurrentScene()->handleEvents(event);
}
