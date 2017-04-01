#include "..\include\TextBox.h"

TextBox::TextBox()
{

}

TextBox::TextBox(int xPos, int yPos)
{
	// Load in font
	if (!m_BlockFont.loadFromFile("assets\\fonts\\3X5.TTF"))
	{
		std::cout << "Error";
	}

	m_sText.clear(); // Clear string

	m_sText = "";

	m_TextInBox.setFont(m_BlockFont);
	m_TextInBox.setString(m_sText);
	m_TextInBox.setCharacterSize(50);

	// Centre text
	sf::FloatRect TempRect = m_TextInBox.getLocalBounds();
	m_TextInBox.setOrigin(TempRect.left + TempRect.width / 2.0f, TempRect.top + TempRect.height / 2.0f);
	m_TextInBox.setPosition(sf::Vector2f(xPos, yPos));

}

void TextBox::ProcessKeyRelease(sf::Keyboard::Key code)
{
	m_sText.push_back(toupper(char(code))); // Add uppercase letter to string
	m_TextInBox.setString(m_sText); // Update visible text box
}

int TextBox::returnStringSize()
{
	return m_sText.size();
}

void TextBox::ClearLastChar()
{
	m_sText.pop_back();
	m_TextInBox.setString(m_sText);
}

void TextBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_TextInBox);
}
