#include <AbstractMenu.h>

AbstractMenu::AbstractMenu()
{
	if (!m_BlockFont.loadFromFile("assets\\fonts\\3x5.TTF"))
	{
		cout << "Error";
	}
}

AbstractMenu::AbstractMenu(int WindowWidth, int WindowHeight)
{
	if (!m_BlockFont.loadFromFile("assets\\fonts\\3x5.TTF"))
	{
		cout << "Error";
	}
}

void AbstractMenu::Click()
{
	m_bClicked = true;
}

void AbstractMenu::ResetClick()
{
	m_bClicked = false;
}
