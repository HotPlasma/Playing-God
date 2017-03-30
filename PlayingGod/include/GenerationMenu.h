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

#include "PreHeader.h"
#include <AbstractMenu.h>
#include <TextureLoader.h>
#include <Button.h>
#include <TextBox.h>
#include <DropDown.h>
#include <WorldGen.h>
#include <WorldReader.h>

class GenerationMenu : public AbstractMenu
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////

	// Buttons on menu screen
	Button m_Cancel; ///< Button for returning to main menu
	Button m_Create; ///< Button for creating world

	// Drop Down Menus
	DropDownMenu m_WorldSizeOptions; ///< Dropdown menu for world size
	DropDownMenu m_ClimateOptions; ///< Dropdown menu for climate
	DropDownMenu m_MountainousOptions; ///< Dropdown menu for options
	DropDownMenu m_CivilisationOptions; ///< Dropdown menu civilsation options
	DropDownMenu m_SkyBoxOptions; ///< Dropdown menu for time of day
	DropDownMenu m_FloraDensityOptions; ///< Dropdown menu for flora

	// Takes parameters and returns a world .cfg file
	WorldGen WorldGenerator; ///< Generates a world file
	WorldReader CreateWorld; ///< Reads created worldfile

	// Title text
	sf::Text m_WorldName; ///< Static text for world name
	sf::Text m_WorldSize; ///< Static text for world size
	sf::Text m_Climate; ///< Static text for world climate
	sf::Text m_Mountainous; ///< Static text for mountainous
	sf::Text m_Civilisation;  ///< Static text for civilsation
	sf::Text m_SkyBox;  ///< Static text for time of day
	sf::Text m_FloraDensity; ///< Static text for flora
	 
	sf::Text m_LoadingText;  ///< Static text which warns player of potential long load times

	enum State { None = 0, Cancel = 1, Create = 2};  ///< Enum used for knowing which button is clicked
	State WhichState;  ///< Instance of State enum

	bool m_bMenuOpen;  ///< Bool which equates to true if menu is open


public:
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a menu from its width and hight
	///
	/// \param WindowWidth Width of menu int
	/// \param WindowHeight Height of menu int
	///
	////////////////////////////////////////////////////////////
	GenerationMenu(int WindowWidth, int WindowHeight);

	////////////////////////////////////////////////////////////
	/// \brief Allows variables to be updated
	///
	/// \param fTimestep Float game time
	///
	////////////////////////////////////////////////////////////
	int update(float fTimestep);

	////////////////////////////////////////////////////////////
	/// \brief Returns which button is clicked
	///
	/// \return int representing which button was clicked
	///
	////////////////////////////////////////////////////////////
	int ReturnButtonClicked();

	////////////////////////////////////////////////////////////
	/// \brief Updates the local mouse position variable with a external variable
	///
	/// \param Pos Position vector Vector2f
	///
	/// \see m_MousePos
	///
	////////////////////////////////////////////////////////////
	void TakeMousePos(sf::Vector2f Pos);

	////////////////////////////////////////////////////////////
	/// \brief Allows class to draw drawables to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	vector<DropDownMenu> m_DropDownMenus; ///< Vector holding all dropdown menus for easier itteration
	TextBox* m_TextBox_WorldName; ///< Textbox for naming the world
};

////////////////////////////////////////////////////////////
/// \class GenerationMenu
///
///	GenerationMenu inherits from AbstractMenu and its purpose
/// is to allow the user to select the parameters for a world they create.
/// This data is then sent to the WorldGen class so it can generate a file with
/// said parameters. Finally, that file is read by the WorldReader class and rendered
/// to be explored.
///
/// Like the other menu classes all that is needed to to initilise a 
/// is the width and height of the desired menu.
///
/// The worldfiles that this file creates are the same ones that can
/// be loaded in the Loading Menu
///
////////////////////////////////////////////////////////////