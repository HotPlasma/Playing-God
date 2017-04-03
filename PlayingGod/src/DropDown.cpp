#include "..\include\DropDown.h"

DropDownMenu::DropDownMenu()
{
	if (!m_BlockFont.loadFromFile("assets\\fonts\\3x5.TTF")) // Load font
	{
		cout << "Error";
	}
	m_iOptionSelected = 0; // Assign default value
}

DropDownMenu::DropDownMenu(float fX, float fY, int iTextureID, TextureLoader * TexLoader, vector<string> Options)
{
	SetProperties(fX, fY, iTextureID, TexLoader, Options);
}

void DropDownMenu::SetProperties(float fX, float fY, int iTextureID, TextureLoader * TexLoader, vector<string> Options)
{
	m_TexLoader = TexLoader;
	m_Sprite.setPosition(fX, fY);
	m_Sprite.setTexture(*m_TexLoader->getTextureIterator(iTextureID));
	m_iCurrentTexID = iTextureID;
	m_bActive = false;
	m_bOpen = false;
	float offset = 0.f;

	m_CurrentlySelected.setFont(m_BlockFont);
	m_CurrentlySelected.setString(Options.at(0));
	m_CurrentlySelected.setFillColor(sf::Color::Green);
	m_CurrentlySelected.setCharacterSize(50);
	m_CurrentlySelected.setPosition(fX + 55, fY + 5 + offset);

	for (int i = 0; i < Options.size(); i++)
	{
		m_DropDownOptions.resize(m_DropDownOptions.size() + 1);
		m_Extention.resize(m_Extention.size() + 1);
		m_DropDownOptions.at(i).setFont(m_BlockFont);
		m_DropDownOptions.at(i).setString(Options.at(i));
		m_DropDownOptions.at(i).setFillColor(sf::Color::Green);
		m_DropDownOptions.at(i).setCharacterSize(50);
		m_DropDownOptions.at(i).setPosition(fX + 55, fY + 60 + offset);
		m_Extention.at(i).setTexture(*m_TexLoader->getTextureIterator(iTextureID + 1));
		m_Extention.at(i).setPosition(fX + 10, fY + 70 + offset);
		offset += 50;
	}
}

void DropDownMenu::ChangeTexture(int iNewTextureID)
{
	m_Sprite.setTexture(*m_TexLoader->getTextureIterator(iNewTextureID));
}

void DropDownMenu::CheckHover(Vector2f MousePos)
{
	// Mouse is pointing at button
	if (MousePos.x > m_Sprite.getPosition().x && MousePos.x < m_Sprite.getPosition().x + m_Sprite.getGlobalBounds().width &&
		MousePos.y > m_Sprite.getPosition().y && MousePos.y < m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height)
	{
		m_bActive = true;
	}
	// Mouse is not pointing at button
	else
	{
		m_bActive = false;
	}
}

void DropDownMenu::CheckHoverDropDownOptions(Vector2f MousePos) 
{
	for (int i = 0; i < m_DropDownOptions.size(); i++) // For all options
	{
		// Check if option is hovered
		if (MousePos.x > m_Extention.at(i).getPosition().x && MousePos.x < m_Extention.at(i).getPosition().x + m_Extention.at(i).getGlobalBounds().width &&
			MousePos.y > m_Extention.at(i).getPosition().y && MousePos.y < m_Extention.at(i).getPosition().y + m_Extention.at(i).getGlobalBounds().height)
		{
			m_CurrentlySelected.setString(m_DropDownOptions.at(i).getString()); // If hovered option becomes new currently selected
			m_iOptionSelected = i;
			cout << m_iOptionSelected << endl;
		}
	}
}

void DropDownMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
	target.draw(m_CurrentlySelected);
	if (m_bOpen)
	{
		for (auto Lines : m_Extention)
		{
			target.draw(Lines);
		}
		for (auto strings : m_DropDownOptions)
		{
			target.draw(strings);
		}
	}
}

void DropDownMenu::ToggleOpen()
{
	m_bOpen = !m_bOpen;
}

void DropDownMenu::CloseMenu()
{
	m_bOpen = false;
}

bool DropDownMenu::isOpen()
{
	return m_bOpen;
}

bool DropDownMenu::isActive()
{
	return m_bActive;
}

int DropDownMenu::OptionSelected()
{
	return m_iOptionSelected;
}

DropDownMenu::~DropDownMenu()
{
}
