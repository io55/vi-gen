#ifndef _TestScene_HPP
#define _TestScene_HPP

#include <Scene.hpp>

class TestScene : public Scene {
public:
	TestScene()          = default;
	virtual ~TestScene() = default;

	SceneStates getState() const { return SceneStates::TestScene; }
	void initialise() override;
	SceneStates run() override;
	void cleanup() override;
	void handleEvents(sf::Event&) override;

private:
	std::vector<sf::RectangleShape> mBackgroundShapes;
	struct {
		sf::CircleShape mPlayerShape;
		sf::RectangleShape mLookRectShape;
	} mPlayer;
};

#endif