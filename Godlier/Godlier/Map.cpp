#include "Map.h"
#include "CameraController.h"
#include <fstream>
#include "Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map(CameraController* cameraController, unsigned int seed) :
	m_cameraController(cameraController)
{
	sf::Vector2f pos;
	m_seed = seed;
	if (seed == 0)
		m_seed = std::rand();

	readFile(sf::Vector2f(0.0f, 0.0f));
}

Map::~Map()
{

}

void Map::setupController(Controller * controller)
{
	controller->registerNewListener(this);
}

void Map::drawWorld(sf::RenderWindow* window)
{
	for (int i = 0; i < NR_CHUNKS; i++)
		window->draw(m_mapChunk[i]);
}

int charArrayToInt(char* arr)
{
	int val = 0;
	for (int i = 0; i < 4; i++)
	{
		val += arr[i] << (24 - i * 8);
	}
	return val;
}

void Map::readFile(sf::Vector2f &pos)
{
	std::string filepath = Constants::Filepaths::MapsFolder;
	std::string filename;

	// Data should be arranged in an orderly fashion so all we have to do is retrieve it
	for (int i = 0; i < CHUNKS_X; i++)
	{
		for (int j = 0; j < CHUNKS_Y; j++)
		{
			pos.x = float(i * ChunkNrTilesX * TileWidth);
			pos.y = float(j * ChunkNrTilesY * TileHeight);
			int posX = (int)pos.x, posY = (int)pos.y;
			filename = filepath + std::to_string(posX) + "-" + std::to_string(posY) + ".txt";
			std::ifstream is(filename, std::ios::binary);
			bool fileExists = is.is_open();
			is.close();
			int index = (i + j * CHUNKS_X);
			m_mapChunk[index].setPosition(pos);
			if (fileExists)
			{
				m_mapChunk[index].setupFromData(filename.c_str());
			}
			else
			{
				m_mapChunk[index].setupNew(0.001f, m_seed);
			}
		}
	}
}

unsigned int Map::getSeed() const
{
	return m_seed;
}

void Map::onButtonPress(Controller::Buttons button)
{

}

void Map::onButtonHold(Controller::Buttons button, float val)
{
	sf::Vector2f dir;
	switch (button)
	{
	case Controller::Left:
		dir.x = -val;
		m_cameraController->moveCamera(dir);
		break;

	case Controller::Right:
		dir.x = val;
		m_cameraController->moveCamera(dir);
		break;

	case Controller::Down:
		dir.y = val;
		m_cameraController->moveCamera(dir);
		break;

	case Controller::Up:
		dir.y = -val;
		m_cameraController->moveCamera(dir);
		break;
	}
}
