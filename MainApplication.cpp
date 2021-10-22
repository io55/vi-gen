#include <MainApplication.hpp>
#include <util.hpp>

sf::Time MainApplication::gDeltaTimer;

MainApplication::MainApplication(sf::RenderWindow& window)
    : mWindow(window)
{
	mSceneInfo.mList.resize(0);
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
		switchScene(getCurrentScene()->run(*this));
		mWindow.display();
	}
}

void MainApplication::switchScene(SceneStates nextState)
{
	Scene* prevScene    = getCurrentScene();
	const bool isBootup = nextState == SceneStates::Startup;
	if (prevScene->getState() == nextState && !isBootup) {
		return;
	}

	if (!isBootup) {
		prevScene->cleanup(*this);

		for (std::size_t i = 0; i < mSceneInfo.mList.size(); i++) {
			if (mSceneInfo.mList[i]->getState() == nextState) {
				mSceneInfo.mIndex = i;
				mSceneInfo.mState = nextState;
			}
		}
	}

	Scene* currScene = getCurrentScene();
	currScene->initialise(*this);
}

void MainApplication::handleEvents(sf::Event& event)
{
	if (event.type == sf::Event::Closed) {
		mWindow.close();
		return;
	}

	getCurrentScene()->handleEvents(*this, event);
}
