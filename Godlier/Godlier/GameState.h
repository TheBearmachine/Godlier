#pragma once

#include "EventObserver.h"
#include <SFML/System/Clock.hpp>

class GameState : public EventObserver
{
public:
	virtual void setup() = 0;
	virtual void update(sf::Clock& clock) = 0;
	virtual void render() = 0;
	virtual void observe(const sf::Event& _event) = 0;
	virtual void handleEvents() = 0;
};
