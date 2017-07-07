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
	static const int CHUNKS_X = 4;
	static const int CHUNKS_Y = 4;
	static const int NR_CHUNKS = 16;

	CameraController* m_cameraController;
	MapChunk m_mapChunk[NR_CHUNKS];

	// Inherited via IControllerListener
	virtual void onButtonPress(Controller::Buttons button) override;
	virtual void onButtonHold(Controller::Buttons button, float time) override;
};