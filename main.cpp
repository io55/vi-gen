#include <MainApplication.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "io55-generator");
	window.setFramerateLimit(200);
	MainApplication app(window);
	app.run();

	return EXIT_SUCCESS;
}