#include "GameStatePlaying.h"
#include "Constants.h"
#include "EventManager.h"
#include "MapGenerator.h" 
#include "MapChunk.h"
#include "Map.h"
#include "CameraController.h"
#include "SystemCoordinator.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include "CameraController.h"
#include "Controller.h"

GameStatePlaying::GameStatePlaying(SystemCoordinator* systemCoordinator) :
	m_systemCoordinator(systemCoordinator), controller(systemCoordinator)
{
	m_window = systemCoordinator->getRenderTarget();
	m_eventManager = systemCoordinator->getEventManager();

}

GameStatePlaying::~GameStatePlaying()
{
	unregisterEvents();
}

void GameStatePlaying::setup()
{
	sf::VideoMode video = sf::VideoMode::getDesktopMode();
	sf::FloatRect screenSize(0.0f, 0.0f, (float)video.width, (float)video.height);
	m_camera = new CameraController();
	m_camera->initalize(screenSize, m_window);

	map = new Map(m_camera);
	map->setupController(&controller);
}

void GameStatePlaying::update(sf::Clock& clock)
{
	sf::Time time = clock.restart();
	if (!m_paused)
	{
		//m_entityManager->updateEntities(time);
		controller.tick(time);
		m_camera->updateCamera();
	}
}

void GameStatePlaying::drawPrep()
{
	//mEntityManager->renderElements(*mWindow);
	map->drawWorld(m_window);
}

bool GameStatePlaying::observe(const sf::Event & _event)
{
	return false;

}

void GameStatePlaying::registerEvents()
{
	m_eventManager->registerObserver(this, sf::Event::EventType::KeyPressed);
}

void GameStatePlaying::unregisterEvents()
{
	m_eventManager->unregisterObserver(this, sf::Event::EventType::KeyPressed);
}
