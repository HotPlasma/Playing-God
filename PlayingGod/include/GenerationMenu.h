#pragma once

#include "PreHeader.h"
#include <AbstractMenu.h>
#include <TextureLoader.h>
#include <Button.h>
#include <TextBox.h>
#include <DropDown.h>
#include <WorldGen.h>

class GenerationMenu : public AbstractMenu
{
private:
	// Buttons on menu screen

	Button m_Cancel;
	Button m_Create;

	// Drop Down Menus
	DropDownMenu m_WorldSizeOptions;
	DropDownMenu m_ClimateOptions;
	DropDownMenu m_MountainousOptions;
	DropDownMenu m_MiscOptions;
	DropDownMenu m_CivilisationOptions;
	DropDownMenu m_SkyBoxOptions;
	DropDownMenu m_FloraDensityOptions;
	// Vector which holds all menus
	vector<DropDownMenu> m_DropDownMenus;

	// Takes parameters and returns a world .cfg file
	WorldGen WorldGenerator;

	// Title text
	sf::Text m_WorldName;
	sf::Text m_WorldSize;
	sf::Text m_Climate;
	sf::Text m_Mountainous;
	sf::Text m_Misc;
	sf::Text m_Civilisation;
	sf::Text m_SkyBox;
	sf::Text m_FloraDensity;

	enum State { None = 0, Cancel = 1, Create = 2};
	State WhichState;

	bool m_bMenuOpen; // True if a menu is open


public:
	GenerationMenu(int WindowWidth, int WindowHeight); // Constructor
	TextBox* m_TextBox_WorldName;
	int update(float fTimestep);
	int ReturnButtonClicked();
	void TakeMousePos(sf::Vector2f Pos); // Returns mouse pos 
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};