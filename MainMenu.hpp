#ifndef _MainMenu_HPP
#define _MainMenu_HPP

#include <Scene.hpp>

class MainMenu : public Scene {
public:
	MainMenu()          = default;
	virtual ~MainMenu() = default;

	SceneStates getState() const { return SceneStates::MainMenu; }
	void initialise(Application&) override;
	SceneStates run(Application&) override;
	void cleanup(Application&) override;
	void handleEvents(Application&, sf::Event&) override;

private:
	const u32 mSizeX = 25;
	const u32 mSizeY = 25;

	f32 mAnimTimer = 0;

	std::vector<sf::RectangleShape> mAnimationSquares;
};

#endif