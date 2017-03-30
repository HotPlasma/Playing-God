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

class Menu : public AbstractMenu
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Button m_NewWorldButton; ///< Button for generation menu
	Button m_LoadWorldButton; ///< Button for load menu
	Button m_ExitButton; ///< Button for closing down the menu

	// Title text
	sf::Text m_Title; ///< Title text

	enum State { None = 0, NewWorld = 1, LoadWorld = 2, ExitMenu = 3}; //< Enum used for knowing which button is clicked
	State WhichState; ///< Instance of State enum

public:
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a menu from its width and hight
	///
	/// \param WindowWidth Width of menu int
	/// \param WindowHeight Height of menu int
	///
	////////////////////////////////////////////////////////////
	Menu(int WindowWidth, int WindowHeight); 

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
	void draw(sf::RenderTarget &target, RenderStates states) const;
};