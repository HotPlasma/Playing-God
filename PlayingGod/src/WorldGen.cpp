#include "..\include\WorldGen.h"



WorldGen::WorldGen()
{
	srand(time(NULL)); // Seed random function with time
	m_sToken = "";
	m_iSelectedSkyBox = 0;
	m_iSelectedClimate = 0;
}

void WorldGen::CreateNewWorld(std::vector<DropDownMenu> WorldParameters, string WorldName)
{
	m_sWorldName = WorldName;
	GenPortal(WorldParameters.at(2).OptionSelected()); // Create file, map and portal.
	GenFloraDensity(WorldParameters.at(3).OptionSelected()); // Fill map with flora
	GenCivilisation(WorldParameters.at(5).OptionSelected()); // Fill map with ruins of civilisation
	GenMountains(WorldParameters.at(0).OptionSelected()); // Generate Mountains
	GenClimate(WorldParameters.at(1).OptionSelected()); // Generate Ground tiles
	GenSky(WorldParameters.at(4).OptionSelected()); // Generate SkyBox tiles
	GenWorldFile();
}


void WorldGen::GenPortal(int WorldSize)
{
	switch (WorldSize)
	{
	case 0: // Small
		u_iWorldSize = 7;
		break;
	case 1: // Medium
		u_iWorldSize = 12;
		break;
	case 2: // Large
		u_iWorldSize = 15;
		break;
	}

	//Extend vector to correct length
	m_WorldList.resize(u_iWorldSize);
	for (int i = 0; i < u_iWorldSize; ++i)
	{
		m_WorldList[i].resize(u_iWorldSize);
	}

	// Generate a random point within the map for the portal
	glm::vec2 PortalPos(rand() % u_iWorldSize, rand() % u_iWorldSize); 

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

void WorldGen::GenClimate(int Climate)
{
	

	switch (Climate)
	{
	case 0: // Cold
		m_iSelectedClimate = 1;
		break;
	case 1: // Warm
		m_iSelectedClimate = 2;
		break;
	case 2: // Hot
		m_iSelectedClimate = 3;
		break;
	}
}

void WorldGen::GenFloraDensity(int FloraDensity)
{
	int iFloraDensity;

	switch (FloraDensity)
	{
	case 0: // None
		iFloraDensity = 0;
		break;
	case 1: // Small
		iFloraDensity = 10;
		break;
	case 2: // Medium
		iFloraDensity = 5;
		break;
	case 3: // Large
		iFloraDensity = 3;
	}

	if (iFloraDensity != 0) // Stops potential division by 0
	{
		// Replace a ratio of # with flora tiles.
		for (int i = 0; i < u_iWorldSize; i++)
		{
			for (int j = 0; j < u_iWorldSize; j++)
			{
				if (m_WorldList[i][j] == '#') // Only replace hashtags
				{
					int iTreeChance = rand() % iFloraDensity;
					if (iTreeChance == 0)
					{
						m_WorldList[i][j] = 'T';
					}
				}
			}
		}
	}
		
}

void WorldGen::GenMountains(int MountainsDensity)
{
	int iMountainDensity;

	switch (MountainsDensity)
	{
	case 0: // None
		iMountainDensity = 0;
		break;
	case 1: // Mountainous
		iMountainDensity = 5;
		break;
	case 2: // Very Mountainous
		iMountainDensity = 3;
		break;
	}

	if (iMountainDensity != 0) // Stops potential division by 0
	{
		// Replace a ratio of # with flora tiles.
		for (int i = 0; i < u_iWorldSize; i++)
		{
			for (int j = 0; j < u_iWorldSize; j++)
			{
				if (i + 1 < u_iWorldSize && j + 1 < u_iWorldSize)
				{
					if (m_WorldList[i][j] == '#' && m_WorldList[i + 1][j] == '#' && m_WorldList[i][j + 1] == '#' && m_WorldList[i + 1][j + 1] == '#') // Only replace hashtags
					{

						int iCivChance = rand() % iMountainDensity;
						if (iCivChance == 0)
						{
							m_WorldList[i][j] = 'M';
							m_WorldList[i + 1][j] = 'M';
							m_WorldList[i][j + 1] = 'M';
							m_WorldList[i + 1][j + 1] = 'M';
						}
					}
				}
			}
		}
	}
}

void WorldGen::GenCivilisation(int CivDensity)
{
	int iCivilisationDensity;

	switch (CivDensity)
	{
	case 0: // None
		iCivilisationDensity = 0;
		break;
	case 1: // Remains
		iCivilisationDensity = 10;
		break;
	case 2: // Mass Remains
		iCivilisationDensity = 5;
		break;
	}

	if (iCivilisationDensity != 0) // Stops potential division by 0
	{
		// Replace a ratio of # with flora tiles.
		for (int i = 0; i < u_iWorldSize; i++)
		{
			for (int j = 0; j < u_iWorldSize; j++)
			{
				if (m_WorldList[i][j] == '#') // Only replace hashtags
				{
					int iCivChance = rand() % iCivilisationDensity;
					if (iCivChance == 0)
					{
						m_WorldList[i][j] = 'C';
					}
				}
			}
		}
	}

}

void WorldGen::GenSky(int Sky)
{

	switch (Sky)
	{
	case 0: // None
		m_iSelectedSkyBox = 1;
		break;
	case 1: // Remains
		m_iSelectedSkyBox = 2;
		break;
	case 2: // Mass Remains
		m_iSelectedSkyBox = 3;
		break;
	}
}

void WorldGen::GenWorldFile()
{
	// Creates a file and writes to it
	m_WorldFile.open(("assets/scenes/Worlds/" + m_sWorldName + ".cfg").c_str(), ios_base::app);

	m_WorldFile << u_iWorldSize << endl;

	for (int i = 0; i < u_iWorldSize; i++)
	{
		//m_WorldList[i].resize(u_iWorldSize);
		for (int j = 0; j < u_iWorldSize; j++)
		{
			char str[20];
			sprintf_s(str, "%c", m_WorldList[i][j]);
			m_WorldFile << str;
		}
		m_WorldFile << std::endl;
	}

	m_WorldFile << "Sky: " << m_iSelectedSkyBox << endl;

	m_WorldFile << "Ground: " << m_iSelectedClimate << endl;

	m_WorldFile.close();

}