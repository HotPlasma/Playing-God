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
	// Reads in a .txt file and creates models from the data
	SceneReader();
	SceneReader(string filename); // Takes a file name and loads in a scene
	vector<Model> ModelList; // Vector of models which makes up the scene

private:
	vector<GLuint> m_textureID; // Vector of all the textures for models
//	vector<string> m_
	tex::Texture *gTexture;
	void ReadSceneFile(string filename); // Function to proccess textfile
};