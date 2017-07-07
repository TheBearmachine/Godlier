#include "CameraController.h"
#include "Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

CameraController::CameraController()
	:m_zoomLevel(1.0f), m_desiredZoomLevel(m_zoomLevel), m_controllable(true)
{
}

CameraController::~CameraController()
{
}

void CameraController::initalize(sf::FloatRect size, sf::RenderWindow* window)
{
	m_cameraView.reset(size);
	m_renderWindow = window;
	m_center.x = (size.width + size.left) / 2.0f;
	m_center.y = (size.height + size.top) / 2.0f;
}

void CameraController::moveCamera(sf::Vector2f offset)
{
	m_center += offset * Constants::Camera::Speed;
	printf("X: %f, Y: %f\n", offset.x, offset.y);
	sf::Vector2f roundedPos(m_center);
	// Only increment in integers or it will look ugly as fuck
	roundedPos.x = (int)(roundedPos.x);
	roundedPos.y = (int)(roundedPos.y);
	m_cameraView.setCenter(roundedPos);
	m_cameraView.move(offset);
}

void CameraController::zoom(bool in)
{

	if (in)
		m_desiredZoomLevel += 0.1f;
	else
		m_desiredZoomLevel -= 0.1f;

	m_desiredZoomLevel = std::max(m_desiredZoomLevel, ZOOM_MIN);
	m_desiredZoomLevel = std::min(m_desiredZoomLevel, ZOOM_MAX);
}

void CameraController::updateCamera()
{
	if (m_renderWindow)
		m_renderWindow->setView(m_cameraView);
}
