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
#include <PreHeader.h>
#include <TextureLoader.h>
#include <Button.h>

class AbstractMenu : public sf::Drawable
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Allows creation of a window without variables.
	///
	////////////////////////////////////////////////////////////
	AbstractMenu();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a menu from its width and hight
	///
	/// \param WindowWidth Width of menu int
	/// \param WindowHeight Height of menu int
	///
	////////////////////////////////////////////////////////////
	AbstractMenu(int WindowWidth, int WindowHeight); // Constructor					
	
	////////////////////////////////////////////////////////////
	/// \brief Updates the local mouse position variable with a external variable
	///
	/// \param Pos Position vector Vector2f
	///
	/// \see m_MousePos
	///
	////////////////////////////////////////////////////////////
	virtual void TakeMousePos(Vector2f Pos) {}; 

	////////////////////////////////////////////////////////////
	/// \brief Allows sub-classes to draw drawables to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	virtual void draw(RenderTarget &target, RenderStates states) const {};

	////////////////////////////////////////////////////////////
	/// \brief Allows variables to be updated
	///
	/// \param fTimestep Float game time
	///
	////////////////////////////////////////////////////////////
	virtual int update(float fTimestep) { return 1; };

	////////////////////////////////////////////////////////////
	/// \brief Allows variables to be updated
	///
	/// \param fTimestep Float game time
	///
	////////////////////////////////////////////////////////////
	void Click();

	////////////////////////////////////////////////////////////
	/// \brief Reset the click bool
	///
	/// 
	///
	////////////////////////////////////////////////////////////
	void ResetClick();

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Sprite m_Background; ///< sf::Sprite designated to hold a background image for each menu
	bool m_bClicked; ///< std::bool which is true when the mouse has been clicked
	Font m_BlockFont; ///< sf::font which holds a font for sf::text to use
	TextureLoader m_TexLoader; ///< TextureLoader file which preloads all textures for use within a menu
	Vector2f m_MousePos; ///< sf::vector2f which holds the position of the mouse cursor
};

////////////////////////////////////////////////////////////
/// \class AbstractMenu
///
/// Abstract Menu is a base-class from which all 2D menus
/// inherit from. The main purpose of this class is to provide 
/// commonly used variables to the other menu classes e.g. all 
/// menus use the same font so it would be unefficent to load it in
/// 5 times. By use of polymorphism and inheritance this class 
/// decreases the repetition of code and overall efficency of the
/// program.
/// 
/// To be instantiated AbstractMenu takes the same parameters as 
/// all the other menu classes in this project which are Window Width
/// and WindowHeight.
///
/// This class is provides the following for all classes which inherit from it:
/// A sprite for the background image, abilty to register mouse clicks and react accordingly,
/// preloaded access to the 3x5 font, ability to draw and update all members as needed, a textureloader
/// which ensures multiple models are never loaded in twice.
/// 
////////////////////////////////////////////////////////////