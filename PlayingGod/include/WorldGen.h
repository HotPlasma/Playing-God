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
#include <DropDown.h>
#include <random>
#include <time.h>
#include <tinyxml2.h>

class WorldGen
{
private:
	std::vector<std::vector<char>> m_WorldList; ///< 2D vector of tiles in which the world is generated
	ofstream m_WorldFile; ///< File to write to
	string m_sWorldName; ///< Strng name of world
	string m_sLine; ///< Line used for file generation
	string m_sToken; ///< Token e.g. "i" used for file generation
	unsigned int m_iSelectedSkyBox; ///< integer which represents which skybox is requires
	unsigned int m_iSelectedClimate; ///< integer which represents climate of the world
	unsigned int u_iWorldSize; ///< integer which resents how large the world is

	////////////////////////////////////////////////////////////
	/// \brief Generates a portal for which to travel to the world with. Also creates a default world of selected size and therefore MUST BE RAN FIRST.
	///
	/// \param WorldSize Describes how large the world is
	///
	////////////////////////////////////////////////////////////
	void GenPortal(int WorldSize);

	////////////////////////////////////////////////////////////
	/// \brief Selects what climate the world should be. Changes tiles/flora types dependent on value
	///
	/// \param Climate The climate of the map. Range for the variable is 0-2
	///
	////////////////////////////////////////////////////////////
	void GenClimate(int Climate);

	////////////////////////////////////////////////////////////
	/// \brief Generates flora around the map. The amount of flora generated is dependent on the density given.
	///
	/// \param FloraDensity Range 0-2 Higher the number the more flora will be generated
	///
	////////////////////////////////////////////////////////////
	void GenFloraDensity(int FloraDensity);

	////////////////////////////////////////////////////////////
	/// \brief Generates mountains around the map. A mountain must take a 4x4 tile section.
	///
	/// \param MountainsDensity How many mountains to be generated. Range for this variable is 0-2
	///
	////////////////////////////////////////////////////////////
	void GenMountains(int MountainsDensity);

	////////////////////////////////////////////////////////////
	/// \brief Generates Civilisation around the map. Can be anything from a house to a fence.
	///
	/// \param CivDensity How much civilisation is created. Range for this variable is 0-2
	///
	////////////////////////////////////////////////////////////
	void GenCivilisation(int CivDensity);

	////////////////////////////////////////////////////////////
	/// \brief Generates correct skybox for the world
	///
	/// \param Sky Which skybox to be added to the file
	///
	////////////////////////////////////////////////////////////
	void GenSky(int Sky);

	////////////////////////////////////////////////////////////
	/// \brief Generates a .cfg file to be read by WorldReader
	///
	////////////////////////////////////////////////////////////
	void GenWorldFile();

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	////////////////////////////////////////////////////////////
	WorldGen();

	////////////////////////////////////////////////////////////
	/// \brief Runs all necessary functions to generate a world file
	////////////////////////////////////////////////////////////
	void CreateNewWorld(std::vector<DropDownMenu> WorldParameters, string WorldName);


public:

};