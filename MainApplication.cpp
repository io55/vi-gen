#include <MainApplication.hpp>
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

void MainApplication::switchScene(SceneStates nextState)
{
	if (nextState != SceneStates::Startup) {
		Scene* prevScene = getCurrentScene();
		if (prevScene->getState() == nextState) {
			return;
		}

		prevScene->cleanup();

		for (std::size_t i = 0; i < mSceneInfo.mList.size(); i++) {
			if (mSceneInfo.mList[i]->getState() == nextState) {
				mSceneInfo.mIndex = i;
				mSceneInfo.mState = nextState;
				break;
			}
		}
	}

	Scene* currScene = getCurrentScene();
	currScene->initialise();
}

void MainApplication::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::Closed) {
		mWindow.close();
		return;
	}

	getCurrentScene()->handleEvents(event);
}
