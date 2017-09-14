#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "EventObserver.h"

namespace sf
{
	class RenderWindow;
}

class Clickable : public EventObserver
{
public:
	Clickable(sf::FloatRect area);
	~Clickable();

	virtual void observe(const sf::Event & _event);
	virtual void onMouseOver(bool mouseOver) = 0;
	virtual void onClickInside() = 0;
	virtual void onReleaseInside() = 0;

protected:
	sf::FloatRect m_interactArea;

private:
	sf::RenderWindow* m_window;
	bool m_mouseInside;
};
