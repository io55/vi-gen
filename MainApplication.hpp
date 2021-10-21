#ifndef _MainApplication_HPP
#define _MainApplication_HPP

#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <types.hpp>

class MainApplication : public Application {
public:
	MainApplication(sf::RenderWindow& window);
	virtual ~MainApplication() = default;

	void run() override;

private:
	void handleEvents(sf::Event& ev);

	std::vector<sf::CircleShape> mCircleShapes;

	sf::RenderWindow& mWindow;
};

#endif