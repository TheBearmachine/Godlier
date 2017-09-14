#include "Clickable.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Clickable::Clickable(sf::FloatRect area) :
	m_interactArea(area), m_mouseInside(false)
{

}

Clickable::~Clickable()
{

}

void Clickable::observe(const sf::Event & _event)
{
	sf::Vector2f mousePos;
	switch (_event.type)
	{
	case sf::Event::MouseMoved:
		mousePos = m_window->mapPixelToCoords(sf::Vector2i(_event.mouseMove.x, _event.mouseMove.y));
		if (m_interactArea.contains(mousePos))
		{
			if (!m_mouseInside)
			{
				m_mouseInside = true;
				onMouseOver(true);
			}
		}
		else
		{
			if (m_mouseInside)
			{
				m_mouseInside = false;
				onMouseOver(false);
			}
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (m_mouseInside)
			onClickInside();
		break;

	case sf::Event::MouseButtonReleased:
		if (m_mouseInside)
			onReleaseInside();
		break;
	}
}
