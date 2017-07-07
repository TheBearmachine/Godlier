#pragma once
#include "MapChunk.h"
#include "Controller.h"

namespace sf
{
	class RenderWindow;
}
class CameraController;

class Map : public IControllerListener
{
public:
	Map(CameraController* cameraController);
	~Map();

	void setupController(Controller* controller);
	void drawWorld(sf::RenderWindow* window);


private:
	CameraController* m_cameraController;
	MapChunk m_mapChunk;

	// Inherited via IControllerListener
	virtual void onButtonPress(Controller::Buttons button) override;
	virtual void onButtonHold(Controller::Buttons button, float time) override;
};