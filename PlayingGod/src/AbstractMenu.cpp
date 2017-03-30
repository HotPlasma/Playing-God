#include <AbstractMenu.h>

AbstractMenu::AbstractMenu()
{
	// Load in font
	if (!m_BlockFont.loadFromFile("assets\\fonts\\3x5.TTF"))
	{
		cout << "Error";
	}
}

AbstractMenu::AbstractMenu(int WindowWidth, int WindowHeight)
{
	// Load in font
	if (!m_BlockFont.loadFromFile("assets\\fonts\\3x5.TTF"))
	{
		cout << "Error";
	}
}

void AbstractMenu::Click()
{
	// To be run if mouse clicked
	m_bClicked = true;
}

void AbstractMenu::ResetClick()
{
	// Set click to false
	m_bClicked = false;
}
