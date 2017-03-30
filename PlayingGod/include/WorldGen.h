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
	std::vector<std::vector<char>> m_WorldList;
	ofstream m_WorldFile;
	tinyxml2::XMLDocument doc;
	string m_sWorldName;
	string m_sLine;
	string m_sToken;
	unsigned int m_iSelectedSkyBox;
	unsigned int m_iSelectedClimate;
	unsigned int u_iWorldSize;


	void GenPortal(int WorldSize); // Creates the base world and portal. MUST BE RAN FIRST
	void GenClimate(int Climate);
	void GenFloraDensity(int FloraDensity); // Generates forests / plants
	void GenMountains(int MountainsDensity);
	void GenCivilisation(int CivDensity);
	void GenSky(int Sky);
	void GenMisc();
	void GenPowercells();
	void GenWorldFile();

public:
	WorldGen();
	void CreateNewWorld(std::vector<DropDownMenu> WorldParameters, string WorldName);


public:

};