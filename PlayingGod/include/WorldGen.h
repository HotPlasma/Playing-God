#pragma once

#include <PreHeader.h>
#include <DropDown.h>
#include <random>
#include <time.h>

class WorldGen
{
private:
	std::vector<std::vector<char>> m_WorldList;
	ofstream m_WorldFile;
	string m_sWorldName;
	string m_sLine;
	string m_sToken;
	unsigned int u_iWorldSize;


	void GenPortal(int WorldSize); // Creates the base world and portal. MUST BE RAN FIRST
	void GenClimate();
	void GenFloraDensity(int FloraDensity); // Generates forests / plants
	void GenMountains();
	void GenCivilisation();
	void GenSky();
	void GenMisc();
	void GenPowercells();
	void GenWorldFile();

public:
	WorldGen();
	void CreateNewWorld(std::vector<DropDownMenu> WorldParameters, string WorldName);


public:

};