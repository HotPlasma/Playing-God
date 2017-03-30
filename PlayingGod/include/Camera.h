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
#include <SFML\Audio.hpp>

class Camera 
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	glm::vec3 CameraPos; ///< vector holding the position of the Camera
	glm::vec3 CameraView; ///< vector holding the view of the Camera
	sf::SoundBuffer m_FootStep; ///< sf::Soundbuffer for a footstep sound effect
	sf::Sound m_Sound;  ///< sf::Sound for making sound.
public:
	////////////////////////////////////////////////////////////
	/// \brief Default camera constructor. Starts at 1,1,1 with a view of 0,1,0
	///
	///
	////////////////////////////////////////////////////////////
	Camera();
	////////////////////////////////////////////////////////////
	/// \brief Returns camera position
	/// \return Camera Position as a glm::vec3
	///
	////////////////////////////////////////////////////////////
	glm::vec3 GetCameraPos(); 
	////////////////////////////////////////////////////////////
	/// \brief Returns camera view
	/// \return Camera View as a glm::vec3
	///
	////////////////////////////////////////////////////////////
	glm::vec3 GetCameraView();

	////////////////////////////////////////////////////////////
	/// \brief Set camera position
	/// \param NewCameraPos glm::vec3 A new position to set to
	///
	////////////////////////////////////////////////////////////
	void setCameraPos(glm::vec3 NewCameraPos);

	////////////////////////////////////////////////////////////
	/// \brief Set camera view
	/// \param NewCameraView glm::vec3 A new view to set to
	///
	////////////////////////////////////////////////////////////
	void setCameraView(glm::vec3 NewCameraView);
	
	////////////////////////////////////////////////////////////
	/// \brief Processes user input to allow movement of camera and view
	/// 
	/// \param yAngle Used for moving the view left and right
	/// \param zAngle Used for moving the view up and down
	////////////////////////////////////////////////////////////
	void ProcessUserInput(float yAngle, float zAngle); 

	////////////////////////////////////////////////////////////
	/// \brief Plays footsteps when the character moves
	/// 
	////////////////////////////////////////////////////////////
	void PlayFootstepsSound();
};



////////////////////////////////////////////////////////////
/// \class Camera
///
/// Class Designed to hold my camera positions and navigate it on user input.
/// This class similates a 1st person camera by using trigonometry to 
/// create a mobile view. Arrow keys move the camera and mouse movements
/// navigate the view.
/// 
/// Camera takes no parameters to be initilised. It always beings at X: 0 
/// Y: 0, Z: 0 with a view of X:0, Y:1, Z:0
///
////////////////////////////////////////////////////////////