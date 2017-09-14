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
	Map(CameraController* cameraController, unsigned int seed = 0);
	~Map();

	void setupController(Controller* controller);
	void drawWorld(sf::RenderWindow* window);

	void readFile(sf::Vector2f &pos);
	unsigned int getSeed() const;


private:
	static const int CHUNKS_X = 12;
	static const int CHUNKS_Y = 12;
	static const int NR_CHUNKS = CHUNKS_X * CHUNKS_Y;
	unsigned int m_seed;

	CameraController* m_cameraController;
	MapChunk m_mapChunk[NR_CHUNKS];

	virtual void onButtonPress(Controller::Buttons button) override;
	virtual void onButtonHold(Controller::Buttons button, float time) override;
};