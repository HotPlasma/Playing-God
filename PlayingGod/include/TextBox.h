#pragma once

#include "PreHeader.h"

class TextBox : public sf::Drawable
{
public:
	std::string m_sText;
	sf::Font m_BlockFont;
	sf::Text m_TextInBox;

	TextBox();
	TextBox(int xPos, int yPos);
	void ProccessKeyRelease(sf::Keyboard::Key code);
	int returnStringSize();
	void ClearLastChar();
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};