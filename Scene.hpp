#ifndef _Scene_HPP
#define _Scene_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <limits>
#include <types.hpp>

// clang-format off
enum class SceneStates : u8 { 
	Startup = std::numeric_limits<std::uint8_t>::max(), 

	MainMenu = 0, 
	TestScene
};
// clang-format on

struct Scene {
	Scene()          = default;
	virtual ~Scene() = default;

	virtual SceneStates getState() const = 0;
	virtual void initialise()            = 0;
	virtual void run()                   = 0; // Return value is the next scene, ignore if the same scene
	virtual void cleanup()               = 0;

	virtual void handleEvents(sf::Event&) = 0;
};

#endif