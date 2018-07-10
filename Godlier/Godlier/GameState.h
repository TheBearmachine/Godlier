#pragma once

#include "EventObserver.h"
#include <SFML/System/Clock.hpp>

class GameState : public EventObserver
{
public:
	virtual void setup() = 0;
	virtual void update(sf::Clock& clock) = 0;
	virtual void drawPrep() = 0;
	virtual bool observe(const sf::Event& _event) = 0;
	virtual void registerEvents() = 0;
	virtual void unregisterEvents() = 0;

};
