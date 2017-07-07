#pragma once
#include <SFML/System/Vector2.hpp>

class MapGenerator
{
public:
	enum TileType
	{
		Grass,
		Water,
		Snow,
		Sand,
		Stone
	};

	static void generateMap(int* tileArr, int* heightArr, int width, int height, float frequency, sf::Vector2f &position);
private:

};
