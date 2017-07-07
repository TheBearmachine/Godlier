#include "GameStatePlaying.h"
#include "Constants.h"
#include "EventManager.h"
#include "MapGenerator.h" 
#include "MapChunk.h"
#include "Map.h"
#include "CameraController.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include "CameraController.h"
#include "Controller.h"

GameStatePlaying::GameStatePlaying(sf::RenderWindow* window, EventManager* eventManager) :
	m_window(window), m_eventManager(eventManager), controller(eventManager)
{
	m_eventManager->registerObserver(this, sf::Event::EventType::KeyPressed);

}

GameStatePlaying::~GameStatePlaying()
{
	m_eventManager->unregisterObserver(this, sf::Event::EventType::KeyPressed);
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

void GameStatePlaying::render()
{
	m_window->clear();
	//mEntityManager->renderElements(*mWindow);
	map->drawWorld(m_window);
	m_window->display();
}

void GameStatePlaying::observe(const sf::Event & _event)
{

}

void GameStatePlaying::handleEvents()
{
	sf::Event currEvent;
	while (m_window->pollEvent(currEvent))
	{
		m_eventManager->notify(currEvent);
	}
}
