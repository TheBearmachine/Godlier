#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"
#include "EventObserver.h"

class GameState;

class GameManager : public EventObserver
{
public:
	GameManager();
	~GameManager();

	void run();
	virtual void observe(const sf::Event & _event) override;

private:
	bool initalizeGame();
	bool initalizeWindow();
	void close();
	void gameLoop();

	GameState* m_currentGameState;

	sf::Clock m_clock;
	sf::RenderWindow m_window;
	EventManager m_eventManager;
};