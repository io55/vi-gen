#ifndef _Scene_HPP
#define _Scene_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <limits>
#include <types.hpp>

enum class SceneStates : u8 {
	Startup    = std::numeric_limits<u8>::max(),
	ErrorScene = Startup - 1,

	MainMenu = 0,
	TestScene,
};

struct Scene {
	Scene()          = default;
	virtual ~Scene() = default;

	virtual SceneStates getState() const = 0;
	virtual void initialise()            = 0;
	virtual void run()                   = 0;
	virtual void cleanup()               = 0;

	virtual void handleEvents(sf::Event&) = 0;
};

#endif