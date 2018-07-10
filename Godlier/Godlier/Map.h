#pragma once
#include "MapChunk.h"
#include "DrawThis.h"
#include "Controller.h"

namespace sf
{
	class RenderTarget;
}
class CameraController;

class Map : public IControllerListener, public DrawThis
{
public:
	Map(CameraController* cameraController, unsigned int seed = 0);
	~Map();

	void setupController(Controller* controller);

	void drawPrep(DrawingManager* drawingMan) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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