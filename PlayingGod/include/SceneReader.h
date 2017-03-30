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
#include "Model.h"
#include <vector>
#include "Texture.h"
#include <tinyxml2.h>

class SceneReader
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Allows creation of a SceneReader 
	///
	////////////////////////////////////////////////////////////
	SceneReader();
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs scene from a xml file
	///
	/// \param filename Location of xml scene file.
	///
	////////////////////////////////////////////////////////////
	SceneReader(string filename);
	vector<Model> ModelList; ///< Vector of models which makes up the scene

private:
	vector<GLuint> m_textureID; ///< Vector of all the textures for models
	tex::Texture *gTexture; ///< Pointer to a texture
	////////////////////////////////////////////////////////////
	/// \brief Reads a .xml file and converts this into a scene to be rendered
	///
	/// \param filename Location of xml scene file.
	///
	////////////////////////////////////////////////////////////
	void ReadSceneFile(string filename); // Function to proccess textfile
};

////////////////////////////////////////////////////////////
/// \class SceneReader
///
/// SceneReader reads a .XML file and creates a list of Model
/// class objects to be drawn elsewhere. It's purpose is for 
/// drawing scene which are not procedurally generatic or in other
/// words static. 
/// 
/// In this project it is used to create the labratory in which
/// the player starts.
/// 
/// To initilise a SceneReader the constructor takes a path
/// to a .XML file as a string.
////////////////////////////////////////////////////////////