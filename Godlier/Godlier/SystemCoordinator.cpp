#include "SystemCoordinator.h"

SystemCoordinator::SystemCoordinator(sf::RenderTarget * renderTarget, EventManager * eventManager) :
	mRenderTarget(renderTarget), mEventManager(eventManager)
{
}

SystemCoordinator::~SystemCoordinator()
{
}

sf::RenderTarget * SystemCoordinator::getRenderTarget()
{
	return mRenderTarget;
}

EventManager * SystemCoordinator::getEventManager()
{
	return mEventManager;
}
