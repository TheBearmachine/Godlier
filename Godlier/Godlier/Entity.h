#pragma once
#include "Transformabetter.h"
#include "DrawThis.h"

namespace sf
{
	class Time;
}

class Entity : public DrawThis, public Transformabetter
{
public:
	Entity();
	virtual ~Entity();

	virtual void tick(const sf::Time& deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

private:

};