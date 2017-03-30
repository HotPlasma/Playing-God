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

#include "gl_core_4_3.hpp"
#include <PreHeader.h>
#include <vector>
#include "Bitmap.h"

class CubeMap 
{
private:
	// VAO for drawing cube
	unsigned int cubeVAOHandle;
	// used for drawing
	int faces;
	// Holds texture ID
	GLuint texID;


public:
	// Creates a cube of given size
	CubeMap(float size, glm::vec3 position, std::string FileLocations);
	// Renders cube
	void render();
	// Return texture ID
	GLuint GetTexID();
	glm::mat4 M;
};