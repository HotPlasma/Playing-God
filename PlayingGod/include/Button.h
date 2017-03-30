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

class Button : public sf::Drawable
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Sprite m_Sprite; ///< sf::Sprite which is the button
	int m_iCurrentTexID; ///< int which represents the assigned texture for button
	TextureLoader* m_TexLoader; ///< TextureLoader which holds potential textures for button
	bool m_bActive; ///< bool which becomes active if button is hovered over

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Allows creation of a button without variables.
	///
	////////////////////////////////////////////////////////////
	Button(); 

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a button from a X position, Y position, Texture ID and a TextureLoader
	///
	/// \param fX X Position of button
	/// \param fY Y Position of button
	/// \param iTextureID int Texture assigned to button
	/// \param TexLoader TextureLoader holding textures for button
	///
	/// \see SetProperties
	///
	////////////////////////////////////////////////////////////
	Button(float fX, float fY, int iTextureID, TextureLoader* TexLoader); // Creates button with given parameters

	////////////////////////////////////////////////////////////
	/// \brief Creates a button using these given parameters
	///
	/// \param fX X Position of button
	/// \param fY Y Position of button
	/// \param iTextureID int Texture assigned to button
	/// \param TexLoader TextureLoader holding textures for button
	///
	/// \see Button
	///
	////////////////////////////////////////////////////////////
	void SetProperties(float fX, float fY, int iTextureID, TextureLoader* TexLoader);

	////////////////////////////////////////////////////////////
	/// \brief Changes active texture on the button
	///
	/// \param iNewTextureID Texture index of buttons TextureLoader
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
	///
	////////////////////////////////////////////////////////////
	void CheckHover(Vector2f MousePos);

	////////////////////////////////////////////////////////////
	/// \brief Allows class to draw drawables to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Returns true if button is being hovered over
	///
	///
	////////////////////////////////////////////////////////////
	bool isActive();
	~Button(); 

};

////////////////////////////////////////////////////////////
/// \class Button
///	
/// Allows creation of clickable sprites which can perform actions.
/// These sprites are used within the menu system for this project.
/// 
/// Buttons check if they are being hovered and are able to change
/// their texture if they are. If a button is clicked while being hovered
/// it will return its m_bActive bool as true allowing for tasked to be
/// run and completed because of it.
/// 
/// To be instantiated a button needs a X position, a Y position, a int which
/// represents which texture it should currently have and a textureloader
/// 
////////////////////////////////////////////////////////////