#pragma once

#include "PreHeader.h"
#include <AbstractMenu.h>
#include <TextureLoader.h>
#include <Button.h>
#include <TextBox.h>

class GenerationMenu : public AbstractMenu
{
private:
	// Buttons on menu screen

	Button m_Cancel;
	Button m_Create;

	

	// Title text
	sf::Text m_WorldName;
	sf::Text m_WorldSize;
	sf::Text m_Temperature;
	sf::Text m_Mountainous;
	sf::Text m_Misc;
	sf::Text m_Civilisation;
	sf::Text m_SkyBox;
	sf::Text m_TreeDensity;

	enum State { None = 0, Cancel = 1, Create = 2};
	State WhichState;


public:
	GenerationMenu(int WindowWidth, int WindowHeight); // Constructor
	TextBox* m_TextBox_WorldName;
	int update(float fTimestep);
	int ReturnButtonClicked();
	void TakeMousePos(sf::Vector2f Pos); // Returns mouse pos 
	void draw(sf::RenderTarget &target, RenderStates states) const;
};