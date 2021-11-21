#ifndef _SCENES_TESTSCENE1_HPP
#define _SCENES_TESTSCENE1_HPP

#include <Player.hpp>
#include <Scenes/Scene.hpp>

class TestScene1 : public Scene {
public:
	TestScene1()          = default;
	virtual ~TestScene1() = default;

	constexpr SceneState getState() const override { return SceneState::TestScene1; }
	void initialise() override;
	void run() override;
	void cleanup() override;
	void handleEvents(sf::Event&) override;

private:
	std::vector<sf::RectangleShape> mBackgroundShapes;
	Player mPlayer;
};

#endif