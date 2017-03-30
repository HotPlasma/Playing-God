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
#include <WorldReader.h>

class LoadingMenu : public AbstractMenu
{
private:

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	// Buttons on menu screen
	Button m_Cancel;///< Button for returning to main menu
	Button m_Load; ///< Button for loading currently typed in world

	// Reads file and creates models for world.
	WorldReader LoadWorld;///< WorldReader for loading world

	// Title text
	sf::Text m_Instructions;///< sf::text for describing to the user what to do

	sf::Text m_LoadingText; ///< sf::text to tell the user to wait

	enum State { None = 0, Cancel = 1, Load = 2 }; //< Enum used for knowing which button is clicked
	State WhichState; ///< Instance of State enum



public:
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a menu from its width and hight
	///
	/// \param WindowWidth Width of menu int
	/// \param WindowHeight Height of menu int
	///
	////////////////////////////////////////////////////////////
	LoadingMenu(int WindowWidth, int WindowHeight);


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

	TextBox* m_TextBox_WorldName; ///< Textbox for naming the world
};

////////////////////////////////////////////////////////////
/// \class LoadingMenu
///
///	This menu allows the user to enter the name of a existing
/// world file to be loaded for exploration. It uses a textbox similar
/// to the generation menu with the main difference being that this
/// class loads previously made worlds as opposed to creating them.
/// 
/// To be instantiated the class needs a width and height to dictate the 
/// size of the menu.
////////////////////////////////////////////////////////////