#pragma once

#include "PreHeader.h"
#include <TextureLoader.h>
#include <Button.h>

class Menu : public sf::Drawable
{
private:
	// Buttons on menu screen
	sf::Sprite m_Background;
	enum WhichMenu {MainMenu = 0, NewWorldMenu  = 1, LoadWorldMenu = 2};
	
	Button m_NewWorldButton;
	Button m_LoadWorldButton;
	Button m_SettingsButton;
	Button m_OptionsButton;
	Button m_ExitButton;

	// Font for menu screen
	sf::Font m_OldSchoolFont;

	// Title text
	sf::Text m_Title;

	TextureLoader m_TexLoader; // Holds textures for buttons

	sf::Vector2f m_MousePos; // Holds mouse position
	bool m_bClicked; // True if button has been clicked


public:
	Menu(int WindowWidth, int WindowHeight); // Constructor
	WhichMenu CurrentMenu;
	void TakeMousePos(sf::Vector2f Pos); // Returns mouse pos 
	void draw(sf::RenderTarget &target, RenderStates states) const;
	int update(float fTimestep);
	void Click();
};