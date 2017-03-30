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
	unsigned int cubeVAOHandle; ///< VAO for drawing the cube
	int faces; ///< Holds how many faces the cube has
	GLuint texID; ///< Holds a unique texture value for each of the 6 textures


public:
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which creates a cube of given size, position and with given textures
	///
	/// \param size How big you want the cube to be e.g. 1 would create a unit cube
	/// \param position Where in the worldspace should the skybox be
	/// \param FileLocation A string to a file location e.g. "assets/skyboxes/skybox"; 
	///
	////////////////////////////////////////////////////////////
	CubeMap(float size, glm::vec3 position, std::string FileLocations);
	////////////////////////////////////////////////////////////
	/// \brief Render the cube to the world
	///
	////////////////////////////////////////////////////////////
	void render();
	////////////////////////////////////////////////////////////
	/// \brief Get the texture ID
	/// /return TexID
	////////////////////////////////////////////////////////////
	GLuint GetTexID();


	glm::mat4 M; ///< Allows manipulation of the model matrix and therefore repositioning of the cube
};

////////////////////////////////////////////////////////////
/// \class CubeMap
///
/// This class is used to create flawless skyboxs above a world
/// scene in my code. The code constructs a scalable cubemap by
/// multiplying the coordinates of the cube. All the coordinates are
/// also indexed so code is very efficent. 6 .png images are also taken
/// to be the skybox image itself. These images should be in the same folder
///  and numbered one to six.
/// 
///
/// To initilise a CabeMap the constructor needs the size of the cube, position of the cube and 
/// a string which links to the location of the image files
////////////////////////////////////////////////////////////