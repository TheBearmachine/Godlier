#include "Controller.h"
#include "EventManager.h"
#include <SFML/System/Time.hpp>

Controller::Controller(EventManager* eventManager) :
	m_eventManager(eventManager)
{
	m_eventManager->registerObserver(this, sf::Event::EventType::KeyPressed);

	setupDefaultControls();
}

Controller::~Controller()
{
	m_eventManager->unregisterObserver(this, sf::Event::EventType::KeyPressed);
}

void Controller::setupDefaultControls()
{
	m_menuKey = sf::Keyboard::Escape;
	m_leftKey = sf::Keyboard::A;
	m_rightKey = sf::Keyboard::D;
	m_downKey = sf::Keyboard::S;
	m_upKey = sf::Keyboard::W;
}

bool Controller::setupControlsFromFile(char * file)
{
	return false;
}

void Controller::registerNewListener(IControllerListener * newListener)
{
	m_currentControllerListener = newListener;
}

void Controller::tick(sf::Time &deltaTime)
{
	float val = deltaTime.asSeconds();
	if (!m_currentControllerListener) return;

	if (sf::Keyboard::isKeyPressed(m_leftKey))
		m_currentControllerListener->onButtonHold(Buttons::Left, val);
	if (sf::Keyboard::isKeyPressed(m_rightKey))
		m_currentControllerListener->onButtonHold(Buttons::Right, val);
	if (sf::Keyboard::isKeyPressed(m_downKey))
		m_currentControllerListener->onButtonHold(Buttons::Down, val);
	if (sf::Keyboard::isKeyPressed(m_upKey))
		m_currentControllerListener->onButtonHold(Buttons::Up, val);
}

void Controller::observe(const sf::Event & _event)
{

	if (_event.type == sf::Event::EventType::KeyPressed)
	{
		if (_event.key.code == m_menuKey)
		{

		}
	}
}
