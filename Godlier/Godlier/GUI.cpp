#include "GUI.h"

GUI::GUI()
{
	for (int i = 0; i < m_nrButtons; i++)
	{
		//m_buttons[i].initalize();
	}
}

GUI::~GUI()
{
}

void GUI::buttonAction(unsigned int action)
{
	switch (GUIButtonActions(action))
	{
	case Powers:

		break;

	case Populace:

		break;
	}
}
