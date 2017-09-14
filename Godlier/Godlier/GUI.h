#pragma once
#include "Button.h"

class GUI : public IButtonListener
{
public:
	GUI();
	~GUI();

	virtual void buttonAction(unsigned int action) override;

private:
	enum GUIButtonActions
	{
		Powers,
		Populace

	};

	static const int m_nrButtons = 5;
	Button m_buttons[m_nrButtons];

};
