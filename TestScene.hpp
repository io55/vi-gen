#ifndef _TestScene_HPP
#define _TestScene_HPP

#include <Player.hpp>
#include <Scene.hpp>

class TestScene : public Scene {
public:
	TestScene()          = default;
	virtual ~TestScene() = default;

	SceneStates getState() const { return SceneStates::TestScene; }
	void initialise() override;
	void run() override;
	void cleanup() override;
	void handleEvents(sf::Event&) override;

private:
	std::vector<sf::RectangleShape> mBackgroundShapes;
	Player mPlayer;
};

#endif