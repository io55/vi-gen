#ifndef _MainApplication_HPP
#define _MainApplication_HPP

#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <Scene.hpp>
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
	void switchScene(SceneStates next);

	static sf::Time gDeltaTimer;
	static const f32 getDeltaTime() { return gDeltaTimer.asSeconds(); }

	static MainApplication* gMainApp;

private:
	void handleEvents(sf::Event& ev);

	sf::RenderWindow& mWindow;

	struct {
		std::vector<Scene*> mList;
		std::size_t mIndex = 0;
		SceneStates mState = SceneStates::MainMenu;

		void addScene(Scene* toAdd) { mList.push_back(toAdd); }
	} mSceneInfo;
};

#endif