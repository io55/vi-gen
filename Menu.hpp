#ifndef _Menu_HPP
#define _Menu_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <types.hpp>
#include <vector>

class MenuItem {
public:
	MenuItem(sf::Shape* shape, sf::Color hlColor, std::function<void()> callback);
	~MenuItem();

	sf::Shape* getShape() { return mShape; }

	void startHighlight();
	void endHighlight();

	void click();

private:
	sf::Shape* mShape;
	sf::Color mDefaultColor;
	sf::Color mHighlightedColor;
	std::function<void()> mPressCallback;
};

struct Menu {
	Menu()  = default;
	~Menu() = default;

	void draw(sf::RenderWindow& window);
	void tickMouse(sf::Vector2f mousePos);

	std::vector<MenuItem*> mItems;
};

#endif