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
}


void WorldGen::GenPortal(int WorldSize)
{

	m_WorldFile.open(("assets/scenes/Worlds/" + m_sWorldName + ".txt").c_str(), ios_base::app );
	
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

	glm::vec2 PortalPos(rand() % u_iWorldSize - 1, rand() % u_iWorldSize - 1);

	// Create grid of # of specificed size
	for (int i = 0; i < u_iWorldSize; i++)
	{
		for (int j = 0; j < u_iWorldSize; j++)
		{
			if (i == PortalPos.x && j == PortalPos.y)
			{
				m_WorldFile << 'P';
			}
			else
			{
				m_WorldFile << '#';
			}
			//m_WorldList.at(i).at(j) = '#';
		}
		m_WorldFile << std::endl;
	}

	



	m_WorldFile.close();
}

void WorldGen::GenFloraDensity(int FloraDensity)
{
	//m_WorldFile.open(("assets/scenes/Worlds/" + m_sWorldName + ".txt").c_str(), ios_base::app );

	//std::fstream ReadableWorldFile("assets/scenes/Worlds/" + m_sWorldName + ".txt", ios_base::in);

	//istringstream iss(m_sLine);

	//int iDensity;

	//switch (FloraDensity)
	//{
	//case 0: // None
	//	iDensity = 0;
	//	break;
	//case 1: // Small
	//	iDensity = 10;
	//	break;
	//case 2: // Medium
	//	iDensity = 5;
	//	break;
	//case 3: // Large
	//	iDensity = 3;
	//}

	//// Replace a ratio of # with flora tiles.
	//while (getline(ReadableWorldFile, m_sLine))

	//iss >> m_sToken;

	//if (m_sToken == '#')
	//{
	//	/*	iss.
	//	}*/
	//}
		
	
		
	
}
