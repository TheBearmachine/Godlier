#pragma once

namespace sf {
	class RenderTarget;
}

class EventManager;

class SystemCoordinator
{
public:
	SystemCoordinator(sf::RenderTarget* renderTarget, EventManager* eventManager);
	~SystemCoordinator();

	sf::RenderTarget* getRenderTarget();
	EventManager* getEventManager();

private:
	sf::RenderTarget* mRenderTarget;
	EventManager* mEventManager;
};
