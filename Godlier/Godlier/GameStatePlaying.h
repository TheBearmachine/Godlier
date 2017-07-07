#pragma once
#include "GameState.h"
#include "Controller.h"

#include <vector>

namespace sf
{
	class RenderWindow;
}

class GameStatePlaying : public GameState
{
public:
	GameStatePlaying(sf::RenderWindow* window, class EventManager* eventManager);
	~GameStatePlaying();

	void setup() override;
	void update(sf::Clock& clock) override;
	void render() override;
	void observe(const sf::Event& _event) override;
	void handleEvents() override;

private:
	class EventManager* m_eventManager;
	class EntityManager* m_entityManager;
	sf::RenderWindow* m_window;
	class CameraController* m_camera;
	Controller controller;
	class Map* map;

	bool m_paused;
};
