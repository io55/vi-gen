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
	u32 mInfluence = 0;

	const f32 mSizeDenom = 5.0f;
	sf::Vector2u mSize;
	std::vector<sf::RectangleShape> mBackgroundShapes;
};

#endif