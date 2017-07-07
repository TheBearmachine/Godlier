#pragma once

#include "Constants.h"
#include <SFML/System/Vector2.hpp>

namespace IsometricProjection
{
	sf::Vector2f getScreenCoord(const sf::Vector2f& inVec)
	{
		sf::Vector2f vec;
		vec.x = (inVec.x - inVec.y) * Constants::World::Tile::HalfWidth;
		vec.y = (inVec.x + inVec.y) * Constants::World::Tile::HalfHeight;

		return vec;
	}
}