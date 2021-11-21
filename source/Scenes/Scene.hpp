#ifndef _SCENE_HPP
#define _SCENE_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <limits>
#include <types.hpp>

enum class SceneState : u8 {
	MainMenu = 0,
	TestScene1,
	TestScene2,
};

struct Scene {
	Scene()          = default;
	virtual ~Scene() = default;

	virtual constexpr SceneState getState() const  = 0;
	virtual void initialise()                      = 0;
	virtual void run()                             = 0;
	virtual void cleanup()                         = 0;

	virtual void handleEvents(sf::Event&) = 0;
};

#endif