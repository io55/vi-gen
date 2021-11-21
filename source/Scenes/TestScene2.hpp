#ifndef _SCENES_TESTSCENE2_HPP
#define _SCENES_TESTSCENE2_HPP

#include <Player.hpp>
#include <Scenes/Scene.hpp>

class TestScene2 : public Scene {
public:
	TestScene2()          = default;
	virtual ~TestScene2() = default;

	constexpr SceneState getState() const override { return SceneState::TestScene2; }
	void initialise() override;
	void run() override;
	void cleanup() override;
	void handleEvents(sf::Event&) override;

private:
	sf::Vector2u mSize;

	sf::Vector2i mInfluence             = { 0, 0 };
	std::pair<bool, bool> mInfluenceDir = { true, true };

	std::vector<sf::RectangleShape> mBackgroundShapes;
};

#endif