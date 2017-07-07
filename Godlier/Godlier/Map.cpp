#include "Map.h"
#include "CameraController.h"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map(CameraController* cameraController) :
	m_cameraController(cameraController)
{
	sf::Vector2f pos;
	for (int i = 0; i < CHUNKS_X; i++)
	{
		for (int j = 0; j < CHUNKS_Y; j++)
		{
			pos.x = i * ChunkNrTilesX * TileWidth;
			pos.y = j * ChunkNrTilesY * TileHeight;
			int index = (i + j * CHUNKS_X);
			m_mapChunk[index].setPosition(pos);
			m_mapChunk[index].setup();
		}
	}
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
