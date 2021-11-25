#include <Player.hpp>

void Player::setup(const f32 halfWindowX, const f32 halfWindowY)
{
	sf::RectangleShape& lookShape = mLookRectShape;
	const sf::Vector2f lookShapeSize(50.0f, 10.0f);
	lookShape.setSize(lookShapeSize);
	lookShape.setOrigin(0.0f, lookShapeSize.y / 2);
	lookShape.setFillColor(sf::Color::Yellow);

	sf::CircleShape& playerShape = mMainShape;
	constexpr f32 radius         = 10.0f;
	playerShape.setRadius(radius);
	playerShape.setOrigin(radius, radius);
	playerShape.setFillColor(sf::Color::Red);

	setPosition(sf::Vector2f(halfWindowX, halfWindowY));
}

void Player::setPosition(sf::Vector2f nextPosition)
{
	mLookRectShape.setPosition(nextPosition);
	mMainShape.setPosition(nextPosition);
}

void Player::render(sf::RenderWindow& window)
{
	// Calculate the angle to the mouses cursor using our position, then
	// convert it to radians so that it can be applied using SFML
	const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	const sf::Vector2f mouseCoord    = window.mapPixelToCoords(mousePosition);

	const sf::Vector2f& lookRectPos = mLookRectShape.getPosition();
	const f32 angle                 = std::atan2f(mouseCoord.y - lookRectPos.y, mouseCoord.x - lookRectPos.x);
	mLookRectShape.setRotation(static_cast<f32>(angle * math::gRad2Deg));
	window.draw(mLookRectShape);

	window.draw(mMainShape);
}
