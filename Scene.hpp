#ifndef _Scene_HPP
#define _Scene_HPP

#include <Application.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <limits>
#include <types.hpp>

enum class SceneStates : u8 { Startup = std::numeric_limits<std::uint8_t>::max(), MainMenu = 0 };

struct Scene {
	Scene()          = default;
	virtual ~Scene() = default;

	virtual SceneStates getState() const  = 0;
	virtual void initialise(Application&) = 0;
	virtual SceneStates run(Application&) = 0; // Return value is the next scene, ignore if the same scene
	virtual void cleanup(Application&)    = 0;

	virtual void handleEvents(Application&, sf::Event&) = 0;
};

#endif