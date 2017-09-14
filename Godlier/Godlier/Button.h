#pragma once
#include "Clickable.h"
#include "Entity.h"
#include "Animation.h"
#include <string>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>

__interface IButtonListener
{
	void buttonAction(unsigned int action);
};

class EventManager;

class Button : public Clickable, public Entity
{
public:
	Button();
	~Button();

	void initalize(EventManager* eventManager, IButtonListener* listener, std::string textureName, unsigned int action);
	void finalize();
	void setSpriteTexture(std::string texName);
	void setTextString(const std::string &text);
	void setTextFont(const std::string &font);

	virtual void onMouseOver(bool mouseOver) override;
	virtual void onClickInside() override;
	virtual void onReleaseInside() override;

	virtual void setActive(bool active);

	virtual void tick(const sf::Time & deltaTime) override;
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	void adjustTextPosition();

	std::vector<sf::Event::EventType> m_interestedEvents;
	unsigned int m_clickAction;
	EventManager* m_eventManager;
	IButtonListener* m_listener;
	Animation m_sprite;
	sf::Text m_text;

	bool m_isActive;
};
