#include "Map.h"
#include "CameraController.h"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map(CameraController* cameraController) :
	m_cameraController(cameraController)
{

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
	window->draw(m_mapChunk);
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
