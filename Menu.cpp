#include <Menu.hpp>

MenuItem::MenuItem(sf::Shape* shape, sf::Color hlColor, std::function<void()> callback)
    : mShape(shape)
    , mDefaultColor(shape->getFillColor())
    , mHighlightedColor(hlColor)
    , mPressCallback(callback)
{
}

MenuItem::~MenuItem() { delete mShape; }

void MenuItem::startHighlight() { mShape->setFillColor(mHighlightedColor); }
void MenuItem::endHighlight() { mShape->setFillColor(mDefaultColor); }

void MenuItem::click() { mPressCallback(); }

void Menu::draw(sf::RenderWindow& window)
{
	for (MenuItem* item : mItems) {
		window.draw(*item->getShape());
	}
}

void Menu::tickMouse(sf::Vector2f mousePos)
{
	for (MenuItem*& item : mItems) {
		// Check if the mouse overlaps the shapes box
		if (item->getShape()->getGlobalBounds().contains(mousePos)) {
			item->startHighlight();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				item->click();
				break;
			}
		} else {
			item->endHighlight();
		}
	}
}
