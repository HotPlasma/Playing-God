#pragma once

#include "PreHeader.h"
#include <AbstractMenu.h>
#include <TextureLoader.h>
#include <Button.h>

class Menu : public AbstractMenu
{
private:
	// Buttons on menu screen
	sf::Sprite m_Background;
	
	Button m_NewWorldButton;
	Button m_LoadWorldButton;
	Button m_SettingsButton;
	Button m_OptionsButton;
	Button m_ExitButton;

	// Title text
	sf::Text m_Title;

	enum State { None = 0, NewWorld = 1, LoadWorld = 2, ExitMenu = 3};
	State WhichState;

public:
	Menu(int WindowWidth, int WindowHeight); // Constructor
	int update(float fTimestep);
	int ReturnButtonClicked();
	void TakeMousePos(sf::Vector2f Pos); // Returns mouse pos 
	void draw(sf::RenderTarget &target, RenderStates states) const;
};