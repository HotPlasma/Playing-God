#include "..\include\WorldGen.h"



WorldGen::WorldGen()
{
	srand(time(NULL)); // Seed random function with time
	m_sToken = "";
}

void WorldGen::CreateNewWorld(std::vector<DropDownMenu> WorldParameters, string WorldName)
{
	m_sWorldName = WorldName;
	GenPortal(WorldParameters.at(2).OptionSelected()); // Create file, map and portal.
	GenFloraDensity(WorldParameters.at(3).OptionSelected());
	GenWorldFile();
}


void WorldGen::GenPortal(int WorldSize)
{
	switch (WorldSize)
	{
	case 0: // Small
		u_iWorldSize = 10;
		break;
	case 1: // Medium
		u_iWorldSize = 20;
		break;
	case 2: // Large
		u_iWorldSize = 30;
		break;
	}

	//Extend vector to correct length
	m_WorldList.resize(u_iWorldSize);
	for (int i = 0; i < u_iWorldSize; ++i)
	{
		m_WorldList[i].resize(u_iWorldSize);
	}

	// Generate a random point within the map for the portal
	glm::vec2 PortalPos(rand() % u_iWorldSize - 1, rand() % u_iWorldSize - 1); 

	// Create grid of # of specificed size
	for (int i = 0; i < u_iWorldSize; i++)
	{
		for (int j = 0; j < u_iWorldSize; j++)
		{
			if (i == PortalPos.x && j == PortalPos.y)
			{
				m_WorldList[i][j] = 'P';
			}
			else
			{
				m_WorldList[i][j] = '#';
			}
		}
	}
}

void WorldGen::GenFloraDensity(int FloraDensity)
{
	int iDensity;

	switch (FloraDensity)
	{
	case 0: // None
		iDensity = 0;
		break;
	case 1: // Small
		iDensity = 10;
		break;
	case 2: // Medium
		iDensity = 5;
		break;
	case 3: // Large
		iDensity = 3;
	}

	// Replace a ratio of # with flora tiles.
	for (int i = 0; i < u_iWorldSize; i++)
	{
		for (int j = 0; j < u_iWorldSize; j++)
		{
			if (m_WorldList[i][j] == '#')
			{
				int TreeChance = rand() % iDensity;
				if (TreeChance == 0)
				{
					m_WorldList[i][j] = 'T';
				}
			}
		}
	}
		
}

void WorldGen::GenWorldFile()
{
	// Creates a file and writes to it
	m_WorldFile.open(("assets/scenes/Worlds/" + m_sWorldName + ".txt").c_str(), ios_base::app);

	for (int i = 0; i < u_iWorldSize; i++)
	{
		//m_WorldList[i].resize(u_iWorldSize);
		for (int j = 0; j < u_iWorldSize; j++)
		{
			char str[20];
			sprintf_s(str, "%c ", m_WorldList[i][j]);
			m_WorldFile << str;
		}
		m_WorldFile << std::endl;
	}

	m_WorldFile.close();
}