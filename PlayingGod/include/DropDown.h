////////////////////////////////////////////////////////////
//
// Playing God (3D Procedural World Generation) - Created by Jegor Kharlamov
// Created for Personal Final Year Project Year 3 at De Montfort University - Games Programming Course
//
// Playing God is a 3D world exploration game where the player can operate 
// a computer which generates new worlds based on selected parameters and creates a portal to them.
// The player can then travel through the portal to explore the worlds and search
// for powercells around the procedurally generated maps.
//
////////////////////////////////////////////////////////////
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <TextureLoader.h>

class DropDownMenu : public sf::Drawable
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Sprite m_Sprite; ///< sf::Sprite which represents the dropdown box
	vector<sf::Sprite> m_Extention; ///< vector of sf::sprites which are extentions for the dropdown box options
	int m_iCurrentTexID; ///< int which represents assigned texture for drop down box
	TextureLoader* m_TexLoader;
	bool m_bActive; ///< bool which is true if dropdown box is being hovered over
	sf::Font m_BlockFont; ///< sf::font holding the Font for dropdown box
	vector<sf::Text>m_DropDownOptions; ///< vector of sf::text which Holds the options for the drop down box
	sf::Text m_CurrentlySelected; ///< sf::Text which holds the currently selected option for the drop box
	bool m_bOpen; ///< std:: bool which is true if the dropbox is expanded
	int m_iOptionSelected; ///< std::int which is equal to the option selected from the dropdown box (indexed at 0)

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Allows creation of a dropdown box
	///
	////////////////////////////////////////////////////////////
	DropDownMenu();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a dropdown box from a X position, Y position, Texture ID and a TextureLoader
	///
	/// \param fX X Position of button
	/// \param fY Y Position of button
	/// \param iTextureID int Texture assigned to button
	/// \param TexLoader TextureLoader holding textures for button
	/// \param Options Vector of strings with all potential options
	///
	/// \see SetProperties
	///
	////////////////////////////////////////////////////////////
	DropDownMenu(float fX, float fY, int iTextureID, TextureLoader* TexLoader, vector<string> Options); // Creates drop down box with given parameters
	////////////////////////////////////////////////////////////

	/// \brief Creates a dropdown box using these given parameters
	///
	/// \param fX X Position of button
	/// \param fY Y Position of button
	/// \param iTextureID int Texture assigned to button
	/// \param TexLoader TextureLoader holding textures for button
	/// \param Options Vector of strings with all potential options
	///
	/// \see DropDownMenu
	///
	////////////////////////////////////////////////////////////
	void SetProperties(float fX, float fY, int iTextureID, TextureLoader* TexLoader, vector<string> Options);

	////////////////////////////////////////////////////////////
	/// \brief Changes active texture on the dropdown box
	///
	/// \param iNewTextureID Texture index of dropdown box TextureLoader
	///
	/// \see m_TexLoader
	///
	////////////////////////////////////////////////////////////
	void ChangeTexture(int iNewTextureID); 

	////////////////////////////////////////////////////////////
	/// \brief Checks if the button is being hovered over
	///
	/// \param MousePos Mouse cursor position
	///
	////////////////////////////////////////////////////////////
	void CheckHover(Vector2f MousePos); 

	////////////////////////////////////////////////////////////
	/// \brief Checks which option is being hovered over in the expanded dropdown box
	///
	/// \param MousePos Mouse cursor position
	///
	////////////////////////////////////////////////////////////
	void CheckHoverDropDownOptions(Vector2f MousePos);

	////////////////////////////////////////////////////////////
	/// \brief Allows class to draw drawables to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Allows the opening/closing of a dropdown box
	///
	///
	////////////////////////////////////////////////////////////
	void ToggleOpen();


	////////////////////////////////////////////////////////////
	/// \brief Closes menu
	///
	///
	////////////////////////////////////////////////////////////
	void CloseMenu();


	////////////////////////////////////////////////////////////
	/// \brief Returns true if the drop box is expanded
	///
	/// \return bool depended on if box expanded
	////////////////////////////////////////////////////////////
	bool isOpen();


	////////////////////////////////////////////////////////////
	/// \brief Returns true if drop box is being hovered over
	///
	/// \return bool dependent on if the dropdown box is being hovered over
	////////////////////////////////////////////////////////////
	bool isActive(); // Checks if drop down box is Active

	
	////////////////////////////////////////////////////////////
	/// \brief Returns selected option in dropdown menu
	///
	/// \return int of selected option
	////////////////////////////////////////////////////////////
	int OptionSelected();
	~DropDownMenu();

};

////////////////////////////////////////////////////////////
/// \class DropDowm
///	
/// Allows creation of drop down menus which any number of options
/// contained within. Clicking this button like object will cause
/// it to expand allowing you to select from a list of options.
/// 
/// The class is able to distiguish which option was selected and
/// return a value based on that option for other classes to use.
/// 
/// 
/// 
/// 
/// 
////////////////////////////////////////////////////////////