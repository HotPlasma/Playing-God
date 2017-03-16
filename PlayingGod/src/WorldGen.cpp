#include "..\include\WorldGen.h"



WorldGen::WorldGen()
{
	srand(time(NULL)); // Seed random function with time
	m_sToken = "";
	m_iSelectedSkyBox = 0;
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
	int iClimate;

	switch (Climate)
	{
	case 0: // Cold
		iClimate = 1;
		break;
	case 1: // Warm
		iClimate = 2;
		break;
	case 2: // Hot
		iClimate = 3;
		break;
	}

	for (int i = 0; i < u_iWorldSize; i++)
	{
		for (int j = 0; j < u_iWorldSize; j++)
		{
			if (m_WorldList[i][j] == '#') // Only replace hashtags
			{
				if (iClimate = 1);
				{
					m_WorldList[i][j] = 'S';
				}

				if (iClimate = 2);
				{
					m_WorldList[i][j] = 'G';
				}

				if (iClimate = 3);
				{
					m_WorldList[i][j] = 'D';
				}
			}
		}
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
		m_iSelectedSkyBox = 0;
		break;
	case 1: // Remains
		m_iSelectedSkyBox = 1;
		break;
	case 2: // Mass Remains
		m_iSelectedSkyBox = 2;
		break;
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
			sprintf_s(str, "%c", m_WorldList[i][j]);
			m_WorldFile << str;
		}
		m_WorldFile << std::endl;
	}

	m_WorldFile << "Sky: " << m_iSelectedSkyBox;

	m_WorldFile.close();

	//tinyxml2::XMLDeclaration * decl = new tinyxml2::XMLDeclaration("1.0", "", "");

	//tinyxml2::XMLNode * pWorld = doc.NewElement("WorldMap");
	//doc.InsertFirstChild(pWorld);

	//tinyxml2::XMLElement * pElement = doc.NewElement("TileLayout");
	//
	//char str[256];
	//
	//string MapLine;
	//for (int i = 0; i < u_iWorldSize; i++)
	//{
	//	//m_WorldList[i].resize(u_iWorldSize);
	//	for (int j = 0; j < u_iWorldSize; j++)
	//	{
	//		tinyxml2::XMLElement * pListElement = doc.NewElement("Tile");
	//		sprintf_s(str, "%c", m_WorldList[i][j]);
	//		pListElement->SetText(str);
	//		pWorld->InsertEndChild(pListElement);
	//	}
	//}

	// 
	//pElement = doc.NewElement("Climate");
	//pElement->SetText(0.5f);
	//pWorld->InsertEndChild(pElement);

	//pElement = doc.NewElement("SkyBox");
	//pElement->SetText(0.5f);

	//pWorld->InsertEndChild(pElement);
	//
	//tinyxml2::XMLError eResult = doc.SaveFile(("assets/scenes/Worlds/" + m_sWorldName + ".xml").c_str());

}