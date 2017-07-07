#pragma once
#include "EventObserver.h"
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
	class Time;
}
class EventManager;
__interface IControllerListener;

class Controller : public EventObserver
{
public:
	enum Buttons
	{
		Menu,
		Left,
		Right,
		Down,
		Up
	};

	Controller(EventManager* eventManager);
	~Controller();
	void setupDefaultControls();
	bool setupControlsFromFile(char* file);

	void registerNewListener(IControllerListener* newListener);

	void tick(sf::Time &deltaTime);
	virtual void observe(const sf::Event & _event) override;

private:
	IControllerListener* m_currentControllerListener;
	EventManager* m_eventManager;

	sf::Keyboard::Key m_menuKey, m_leftKey, m_rightKey, m_upKey, m_downKey;
};

__interface IControllerListener
{
	void onButtonPress(Controller::Buttons button);
	void onButtonHold(Controller::Buttons button, float val);
};
