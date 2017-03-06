#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <TextureLoader.h>

class DropDownMenu : public sf::Drawable
{
private:
	sf::Sprite m_Sprite; // Drop down box sprite
	vector<sf::Sprite> m_Extention; // Extentions for the dropdown box
	int m_iCurrentTexID; // Assigned texture for drop down box
	TextureLoader* m_TexLoader;
	bool m_bActive; // drop down box is active if being hovered over
	sf::Font m_BlockFont; // Font
	vector<sf::Text>m_DropDownOptions; // Holds the options for the drop down box
	sf::Text m_CurrentlySelected; // Holds the currently selected option for the drop box
	bool m_bOpen; // If the box is open or not
	int m_iOptionSelected;

public:
	DropDownMenu(); // Default constructor 
	DropDownMenu(float fX, float fY, int iTextureID, TextureLoader* texLoader2, vector<string> Options); // Creates drop down box with given parameters
	void SetProperties(float fX, float fY, int iTextureID, TextureLoader* texLoader2, vector<string> Options);
	void ChangeTexture(int iNewTextureID); // Allows drop down box texture to be changed
	void CheckHover(Vector2f MousePos); // Checks if mouse curser is hovering over drop down box 
	void CheckHoverDropDownOptions(Vector2f MousePos);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void ToggleOpen();
	void CloseMenu();
	bool isOpen();
	bool isActive(); // Checks if drop down box is Active
	int OptionSelected();
	~DropDownMenu();

};