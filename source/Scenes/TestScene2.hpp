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

	const f32 mSizeDenom = 1.0f;
	sf::Vector2u mSize;

	struct Background {
		Background()  = default;
		~Background() = default;

		sf::Image mPixelBuffer;
		sf::Texture mPixelTexture;
		sf::Sprite mRenderedBuffer;

		std::vector<u32> mPixelProductList;

		inline void resize(u32 x, u32 y) { mPixelBuffer.create(x, y); }
		inline void setPixel(u32 x, u32 y, const sf::Color& color) { mPixelBuffer.setPixel(x, y, color); }
		inline void draw(sf::RenderWindow& window)
		{
			mPixelTexture.loadFromImage(mPixelBuffer);
			mRenderedBuffer.setTexture(mPixelTexture);
			window.draw(mRenderedBuffer);
		}
	} mBackground;
};

#endif