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

class TextBox : public sf::Drawable
{
public:
	std::string m_sText; ///< String contained within the textbox
	sf::Font m_BlockFont; ///< sf::Font for textbox string
	sf::Text m_TextInBox; ///< sf::Text which is usually equal to m_sText

	////////////////////////////////////////////////////////////
	/// \brief Default constructor which allows textbox creation without parameters
	///
	///
	////////////////////////////////////////////////////////////
	TextBox();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a textbox at the location of a given X and Y postion
	///
	/// \param xPos The X position of the text box
	/// \param yPos The Y position of the text box
	///
	////////////////////////////////////////////////////////////
	TextBox(int xPos, int yPos);

	////////////////////////////////////////////////////////////
	/// \brief Allows text to be entered into the text box
	///
	/// \param code The key that was pressed and needs tro be added to the string
	/// 
	///
	////////////////////////////////////////////////////////////
	void ProcessKeyRelease(sf::Keyboard::Key code);

	////////////////////////////////////////////////////////////
	/// \brief Returns the size of the string inside the textbox
	///
	/// \return int which is equal to the string size e.g. 8
	/// 
	///
	////////////////////////////////////////////////////////////
	int returnStringSize();

	////////////////////////////////////////////////////////////
	/// \brief Deleates the previous character very similarly to how backspace usually functions
	///
	/// 
	/// 
	///
	////////////////////////////////////////////////////////////
	void ClearLastChar();

	////////////////////////////////////////////////////////////
	/// \brief Allows class to draw drawables to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};


////////////////////////////////////////////////////////////
/// \class TextBox
///
///	This is a class which is conceptually similar to button 
/// as it is required for my menu classes. It is by near all
/// definition a textbox class like anyother that can be experienced
/// on much software and online. 
/// 
/// Typing will edit the string within the class and therefore change 
/// the text the player sees. Also pressing backspace will delete the 
/// last character like usual.
///
/// A textbox only needs a X position and a y position in order to be
/// instantated.
///
////////////////////////////////////////////////////////////