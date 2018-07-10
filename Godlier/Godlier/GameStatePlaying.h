#pragma once
#include "GameState.h"
#include "Controller.h"
#include <vector>

class SystemCoordinator;

namespace sf
{
	class RenderTarget;
}

class GameStatePlaying : public GameState
{
public:
	GameStatePlaying(SystemCoordinator* systemCoordinator);
	~GameStatePlaying();

	void setup() override;
	void update(sf::Clock& clock) override;
	void drawPrep() override;
	bool observe(const sf::Event& _event) override;
	virtual void registerEvents();
	virtual void unregisterEvents();

private:
	class EventManager* m_eventManager;
	class EntityManager* m_entityManager;
	sf::RenderTarget* m_window;
	SystemCoordinator* m_systemCoordinator;
	class CameraController* m_camera;
	Controller controller;
	class Map* map;

	bool m_paused;
};
