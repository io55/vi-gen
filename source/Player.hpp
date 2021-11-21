#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <types.hpp>

class Player {
public:
	Player()  = default;
	~Player() = default;

	void setup(const f32 halfWindowX, const f32 halfWindowY);

	const sf::Vector2f getPosition() const { return mMainShape.getPosition(); }
	void setPosition(sf::Vector2f nextPosition);

	void render(sf::RenderWindow& window);

	sf::CircleShape& getPlayerShape() { return mMainShape; }
	const sf::CircleShape& getPlayerShape() const { return mMainShape; }

	sf::RectangleShape& getLookRectShape() { return mLookRectShape; }
	const sf::RectangleShape& getLookRectShape() const { return mLookRectShape; }

private:
	sf::CircleShape mMainShape;
	sf::RectangleShape mLookRectShape;
};

#endif
