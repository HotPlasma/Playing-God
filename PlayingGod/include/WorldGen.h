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