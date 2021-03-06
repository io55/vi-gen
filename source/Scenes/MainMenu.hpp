#ifndef _SCENES_MAINMENU_HPP
#define _SCENES_MAINMENU_HPP

#include <Menu.hpp>
#include <Scenes/Scene.hpp>

class MainMenu : public Scene {
public:
	MainMenu()
	{
		if (!mFont.loadFromFile("TerminusTTF.ttf")) {
			std::exit(EXIT_FAILURE);
		}
	}
	virtual ~MainMenu() = default;

	constexpr SceneState getState() const override { return SceneState::MainMenu; }
	void initialise() override;
	void run() override;
	void cleanup() override;
	void handleEvents(sf::Event&) override;

private:
	Menu mMenu;

	sf::Font mFont;
	sf::Text mMainMenuText;

	const u32 mSizeX = 25;
	const u32 mSizeY = 25;
	f32 mAnimTimer   = 0.0f;
	std::vector<sf::RectangleShape> mAnimationSquares;
};

#endif