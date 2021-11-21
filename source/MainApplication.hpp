#ifndef _MAINAPPLICATION_HPP
#define _MAINAPPLICATION_HPP

#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Scenes/Scene.hpp>
#include <types.hpp>

class MainApplication : public Application {
public:
	MainApplication(sf::RenderWindow& window);
	virtual ~MainApplication() = default;

	const Scene* getCurrentScene() const { return mSceneInfo.mList[mSceneInfo.mIndex]; }
	Scene* getCurrentScene() { return mSceneInfo.mList[mSceneInfo.mIndex]; }

	const auto& getSceneInfo() const { return mSceneInfo; }
	auto& getSceneInfo() { return mSceneInfo; }

	const sf::RenderWindow& getWindow() const { return mWindow; }
	sf::RenderWindow& getWindow() { return mWindow; }

	void run() override;
	void switchScene(SceneState next);

	static sf::Time gDeltaTimer;
	static const f32 getDeltaTime() { return gDeltaTimer.asSeconds(); }

	static MainApplication* gMainApp;

private:
	void handleEvents(sf::Event& ev);

	sf::RenderWindow& mWindow;

	struct {
		std::vector<Scene*> mList;
		std::size_t mIndex = 0;
		SceneState mState  = SceneState::MainMenu;

		void addScene(Scene* toAdd) { mList.push_back(toAdd); }
	} mSceneInfo;
};

static std::pair<MainApplication*, sf::RenderWindow&> GetAppAndWindow()
{
	MainApplication* app = MainApplication::gMainApp;
	return { app, app->getWindow() };
}

#endif