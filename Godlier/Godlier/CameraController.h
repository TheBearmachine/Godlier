#pragma once
#include <SFML/Graphics/View.hpp>

namespace sf
{
	class RenderWindow;
}

class CameraController
{
public:
	CameraController();
	~CameraController();

	void initalize(sf::FloatRect size, sf::RenderWindow* window);
	void moveCamera(sf::Vector2f offset);
	void zoom(bool in);
	void updateCamera();

private:
	sf::RenderWindow* m_renderWindow;
	sf::View m_cameraView;
	sf::Vector2f m_center;
	float m_zoomLevel, m_desiredZoomLevel;
	const float ZOOM_MAX = 2.0f, ZOOM_MIN = 0.8f;
	bool m_controllable;
};