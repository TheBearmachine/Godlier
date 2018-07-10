#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "EventManager.h"
#include "EventObserver.h"
#include "DrawingManager.h"
#include "SystemCoordinator.h"

class GameState;

class GameManager : public EventObserver
{
public:
	GameManager();
	~GameManager();

	void run();
	virtual bool observe(const sf::Event & _event) override;

private:
	bool initalizeGame();
	bool initalizeWindow();
	void close();
	void gameLoop();
	void handleEvents();

	GameState* m_currentGameState;
	SystemCoordinator m_systemCoordinator;

	sf::Clock m_clock;
	sf::RenderWindow m_window;
	EventManager m_eventManager;
	DrawingManager m_drawingManager;
};