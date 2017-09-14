#include "Button.h"
#include "ResourceManager.h"
#include "EventManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderWindow.hpp>

Button::Button() :
	Clickable::Clickable(sf::FloatRect()),
	m_text("Button",
		   ResourceManager::getInstance().getFont(Constants::Filepaths::DefaultFont),
		   26)
{
	m_interestedEvents.push_back(sf::Event::EventType::MouseMoved);
	m_interestedEvents.push_back(sf::Event::EventType::MouseButtonPressed);
	m_interestedEvents.push_back(sf::Event::EventType::MouseButtonReleased);

}

Button::~Button()
{

}

void Button::initalize(EventManager * eventManager, IButtonListener * listener, std::string textureName, unsigned int action)
{
	m_eventManager = eventManager;
	if (m_eventManager)
		m_eventManager->registerObserver(this, m_interestedEvents);
	m_listener = listener;
	m_clickAction = action;

	AnimationSetup animSetup = AnimationSetup::DefaultButtonSetup();
	animSetup.textureName = textureName;
	m_sprite.setup(animSetup);
}

void Button::finalize()
{
	if (m_eventManager)
	{
		m_eventManager->unregisterObserver(this, m_interestedEvents);
		m_eventManager = nullptr;
	}
}

void Button::setSpriteTexture(std::string texName)
{
	m_sprite.setTexture(ResourceManager::getInstance().getTexture(texName));
	m_interactArea.left = getPosition().x;
	m_interactArea.top = getPosition().y;
	m_interactArea.width = (float)m_sprite.getTextureRect().width;
	m_interactArea.height = (float)m_sprite.getTextureRect().height;
}

void Button::setTextString(const std::string &text)
{
	m_text.setString(text);
	adjustTextPosition();
}

void Button::setTextFont(const std::string & font)
{
	m_text.setFont(ResourceManager::getInstance().getFont(font));
	adjustTextPosition();
}

void Button::onMouseOver(bool mouseOver)
{
	if (m_isActive)
	{
		if (mouseOver)
			m_sprite.setFrame(1);
		else
			m_sprite.setFrame(0);
	}
}

void Button::onClickInside()
{
	m_sprite.setFrame(3);
}

void Button::onReleaseInside()
{
	if (m_listener)
		m_listener->buttonAction(m_clickAction);
	m_sprite.setFrame(0);

}

void Button::setActive(bool active)
{
	m_isActive = active;
}

void Button::tick(const sf::Time & deltaTime)
{

}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
	target.draw(m_text, states);
}

void Button::adjustTextPosition()
{
	sf::Vector2f pos;
	float x = (m_sprite.getLocalBounds().width - m_text.getLocalBounds().width) / 2.0f;
	float y = (m_sprite.getLocalBounds().height - m_text.getLocalBounds().height) / 2.0f;
	m_text.setPosition(pos);
}
