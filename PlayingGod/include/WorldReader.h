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
#include <PreHeader.h>
#include "Texture.h"
#include "Model.h"
#include "CubeMap.h"
#include "glslprogram.h"
#include <random>
#include <time.h>
#include <memory>

class WorldReader
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Default contructor for a WorldReader
	////////////////////////////////////////////////////////////
	WorldReader();
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer reads a 2D vector of characters as a world
	///
	/// \param World 2D vector of characters which represents the world tile system
	///
	////////////////////////////////////////////////////////////
	WorldReader(std::vector<std::vector<char>> World);

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer reads a world file (.cfg) to create a world
	///
	/// \param WorldFileName A .cfg file containing a grid of characters
	///
	////////////////////////////////////////////////////////////
	WorldReader(std::string WorldFileName);
	
	////////////////////////////////////////////////////////////
	/// \brief Reads a world file (.cfg) to create a world
	///
	/// \param FileName A .cfg file containing a grid of characters
	///
	////////////////////////////////////////////////////////////
	void ReadWorldFile(string FileName);

	////////////////////////////////////////////////////////////
	/// \brief Reads a world file (.cfg) to create a world
	///
	/// \param FileName A .cfg file containing a grid of characters
	///
	////////////////////////////////////////////////////////////
	void LoadModels();

	////////////////////////////////////////////////////////////
	/// \brief Creates a flat plane with with dependent textures based on other parameters
	///
	/// \param xPos X position of tile
	/// \param yPos Y position of tile
	/// \param TexturedPlane Plane with the correct texture
	/// \param WorldOffset A arbatry world offset value
	/// \param TileSize The size of a tile in the world
	///
	////////////////////////////////////////////////////////////


	std::vector<std::vector<char>> m_WorldList; ///< 2D vector of characters which represent the world
	int m_iSkybox; ///< integer which represents which skybox is requires
	int m_iClimate; ///< integer which represents climate of the world
	int m_iWorldSize; ///< integer which resents how large the world is
	glm::vec3 m_PortalLocation; ///< vector3 of where the portal is located. Used for portal linking.
	vector<GLuint> m_textureID; ///< vector if textures used in the scene
	std::vector<Model> ModelList;
	std::vector<std::shared_ptr<Model>> ModelLocationList; ///< Vector of models used in the scene
	GLuint m_programHandle; ///< Program handle for world
	tex::Texture *m_pTexture; ///< Pointer to a texture
	Bitmap m_bmp = Bitmap::bitmapFromFile("assets/textures/Default.bmp"); ///< bmp used to set textures for models. Loads a default texture if no texture assigned
	CubeMap *m_SkyBox; ///< CubeMap for the Skybox
	
};



////////////////////////////////////////////////////////////
/// \class WorldReader
///
/// The WorldReader class takes either 2D vector of characters 
/// or a .cfg file location as a overloaded constructor parameter
/// and from that creates a renderable list of Models which make 
/// up the world.  
/// 
/// Each of the different world parameters is creates work slightly 
/// e.g. Mountains must take 4x4 space and therefore are the size
/// of a 4x4 tile and centred in the middle of all 4 tiles. Also multiple
/// flora items will be generated or a flora tile, but the amount is random.
/// 
////////////////////////////////////////////////////////////