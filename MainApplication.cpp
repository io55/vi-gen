#include <MainApplication.hpp>
#include <util.hpp>

MainApplication::MainApplication(sf::RenderWindow& window)
    : mWindow(window)
{
	const sf::Vector2u& windowSize = window.getSize();

	// Configure the circle shape
	{
		constexpr u32 circleCount = 250;
		constexpr f32 radius      = 100;
		constexpr f32 stepSize    = radius / ((circleCount / 2));
		for (u32 i = 0; i < circleCount; i++) {

			sf::CircleShape cs((i + 1) * stepSize);
			cs.setPosition(
			    util::CenterOfBounds(sf::Vector2f(radius, radius), windowSize));
			cs.setPointCount(15);

			sf::Color color(0, 0, 0);
			// TODO: Figure out why we have to use 67 to offset it closer to 255
			if (i % 2 == 0) {

				color.r = static_cast<u8>(
				    std::ceil(std::lerp(0.0f, 255.0f, (stepSize * i) / 255)));
				color.r += 67;
			} else if (i % 2 == 1) {
				color.b = static_cast<u8>(
				    std::ceil(std::lerp(0.0f, 255.0f, (stepSize * i) / 255)));
				color.b += 67;
			}
			cs.setFillColor(color);

			mCircleShapes.push_back(cs);
		}
	}
}

void MainApplication::run()
{
	sf::Clock deltaClock;
	f32 timer = 0;

	while (mWindow.isOpen()) {
		sf::Time dcTime     = deltaClock.restart();
		const f32 deltaTime = dcTime.asSeconds();
		timer += deltaTime;

		sf::Event event;
		while (mWindow.pollEvent(event)) {
			handleEvents(event);
		}

		mWindow.clear();

		// Rendering the pair of 2 circle shapes, as such we need to split the
		// list in half and iterate by two to get the Red & Blue components
		for (std::size_t i = 0; i < mCircleShapes.size() / 2; i += 2) {
			sf::CircleShape& shape  = mCircleShapes[i];
			sf::CircleShape& shape2 = mCircleShapes[i + 1];

			// Position at the center of the screen, for the circle
			sf::Vector2f centerCircle = util::CenterOfBounds(
			    mWindow.getSize(),
			    sf::Vector2f { shape.getRadius(), shape.getRadius() });

			// Try and counteract the offsetting effect of rotate
			centerCircle.x += 75;
			centerCircle.y += 75;

			// Calculate a "slice" of 360 using the amount of circles we have
			const f32 step = (360 / static_cast<f32>(mCircleShapes.size()));

			// Calculate the position around the circle and offset it by the
			// timer
			f32 xPos = sin(static_cast<f32>(step * i * math::gDeg2Rad) + timer);
			f32 yPos = cos(static_cast<f32>(step * i * math::gDeg2Rad) + timer);

			// Set the position to the center of the screen, with the offset of
			// the xPos and yPos calculations
			constexpr f32 boundRadius = 200;
			shape.setPosition(centerCircle.x + xPos * boundRadius,
			                  centerCircle.y + yPos * boundRadius);

			shape2.setPosition(centerCircle.x + yPos * boundRadius,
			                   centerCircle.y + xPos * boundRadius);

			// Rotate for the nice animation
			shape.rotate(i * deltaTime * 2);
			shape2.rotate(i * deltaTime * 2);

			mWindow.draw(shape);
			mWindow.draw(shape2);
		}
		mWindow.display();
	}
}

void MainApplication::handleEvents(sf::Event& event)
{
	switch (event.type) {
	case sf::Event::Closed: {
		mWindow.close();
		break;
	}
	case sf::Event::KeyPressed: {
		switch (event.key.code) {
		case sf::Keyboard::Key::W:
			for (sf::CircleShape& shape : mCircleShapes) {
				shape.setPointCount(
				    std::min(shape.getPointCount() + 1, static_cast<u32>(15)));
			}
			break;
		case sf::Keyboard::Key::S:
			for (sf::CircleShape& shape : mCircleShapes) {
				shape.setPointCount(
				    std::max(shape.getPointCount() - 1, static_cast<u32>(3)));
			}
			break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}
