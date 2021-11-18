#ifndef _MainMenu_HPP
#define _MainMenu_HPP

#include <Scene.hpp>
#include <Menu.hpp>

class MainMenu : public Scene {
public:
	MainMenu()          = default;
	virtual ~MainMenu() = default;

	SceneStates getState() const { return SceneStates::MainMenu; }
	void initialise() override;
	void run() override;
	void cleanup() override;
	void handleEvents(sf::Event&) override;

private:
	Menu mMenu;

	const u32 mSizeX = 25;
	const u32 mSizeY = 25;
	f32 mAnimTimer   = 0;
	std::vector<sf::RectangleShape> mAnimationSquares;
};

#endif