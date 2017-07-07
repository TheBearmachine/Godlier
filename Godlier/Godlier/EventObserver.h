#pragma once

namespace sf
{
	class Event;
}

class EventObserver
{
public:
	virtual void observe(const sf::Event& _event) = 0;
};