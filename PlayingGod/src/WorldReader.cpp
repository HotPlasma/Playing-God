#include <WorldReader.h>

WorldReader::WorldReader()
{
	srand(time(NULL));
}

WorldReader::WorldReader(std::vector<std::vector<char>> World)
{
	srand(time(NULL));
}

WorldReader::WorldReader(std::string WorldFileName)
{
	srand(time(NULL));
	ReadWorldFile(WorldFileName);
	LoadModels();
}

void WorldReader::ReadWorldFile(string FileName)
{
	std::ifstream WorldFile; // World file
	std::string sLineFromFile; // Line from world file
	std::string sDiscard; // To discard unwanted characters
	
	

	WorldFile.open(FileName.c_str()); //Open File 1

	if (WorldFile.is_open())
	{
		
		getline(WorldFile, sLineFromFile);
		
		m_iWorldSize = stoi(sLineFromFile);

		m_WorldList.resize(m_iWorldSize);

		for (int i = 0; i < m_iWorldSize; i++) //For every row
		{
			getline(WorldFile, sLineFromFile); //Read a line
			remove_if(sLineFromFile.begin(), sLineFromFile.end(), isspace); // Removes spaces from file
			for (int j = 0; j < m_iWorldSize; j++) //For every char
			{
				m_WorldList[i].push_back(sLineFromFile[j]); // Push char into the vector
			}
		}
	}
	else
	{
		cout << "WorldFile Failed to open" << endl;
	}

	// Gets skybox value
	getline(WorldFile, sLineFromFile);
	m_iSkybox = int(sLineFromFile.back() - '0');

	getline(WorldFile, sLineFromFile);
	m_iClimate = int(sLineFromFile.back() - '0');

	WorldFile.close();

}

void WorldReader::LoadModels()
{
	 const float u_kiTileSize = 50; // Size of each tile
	 const float u_kWorldOffset = 1000; // Offset for position world will be rendered

	 // Flora
	 int iNumTrees; // How many trees/flora
	 vec2 iPositionVariance; // Potential varience for the positioning of a object
	 int iTreeType; // Which tree model gets loaded in
	 int iPowerCellChance; // Chance of a powercell spawning
	 int iCivType; // Which form of civilisaiton appears


	 //Mountains
	 int iMountainType;

	 Model Plane;
	// CubeMap *SkyBox;
	 Plane.setFileLocation("assets/models/WorldTiles/Plane.obj");
	 if (m_iClimate == 1)
	 {
		 Plane.setName("Snow Plane");
		 Plane.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	 }
	 else if (m_iClimate == 2)
	 {
		 Plane.setName("Grass Plane");
		 Plane.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	 }
	 else if (m_iClimate == 3)
	 {
		 Plane.setName("Sand Plane");
		 Plane.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	 }

	 if (m_iSkybox == 1) // Day
	 {
		 m_SkyBox = new CubeMap(800, vec3(u_kWorldOffset, 0, 0), "ThickCloudsWater/Clouds");
	 }
	 else if (m_iSkybox == 2) // Sunset
	 {
		 m_SkyBox = new CubeMap(800, vec3(u_kWorldOffset, 0, 0), "SunSet/Sunset");
	 }
	 else if (m_iSkybox == 3) // Night
	 {
		 m_SkyBox = new CubeMap(800, vec3(u_kWorldOffset, 0, 0), "FullMoon/Moon");
	 }

	 for (int i = 0; i < m_WorldList.size(); i++)//For every Row
	 {
		 for (int j = 0; j < m_WorldList[i].size(); j++)//For every bit
		 {
			 if ((m_WorldList[i][j]) != 'M')
			 {
				 Plane.setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize)));
				 Plane.setRotation(glm::vec3(0, 0, 0));
				 Plane.setScale(glm::vec3(1, 1, 1));
				 Plane.setMaterial(1);
				 ModelList.push_back(Plane);
			 }
		 }
	 }

	for (int i = 0; i < m_WorldList.size(); i++) //For every Row
	{
		for (int j = 0; j < m_WorldList[i].size(); j++) //For every bit
		{
			switch (m_WorldList[i][j])
			{
			case 'P': // Portal
				// Portal archway
				ModelList.resize(ModelList.size() + 1);
				ModelList.at(ModelList.size() -1).setName("Archway");
				ModelList.at(ModelList.size() -1).setFileLocation("assets/models/WorldTiles/Portal.obj");

				m_textureID.resize(m_textureID.size() + 1);
				ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Portal.bmp");
				ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
				ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
				ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
				ModelList.at(ModelList.size() - 1).setMaterial(1);

				// Portal
				ModelList.resize(ModelList.size() + 1);
				ModelList.at(ModelList.size() - 1).setName("Portal");
				ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/Portal.obj");

				m_textureID.resize(m_textureID.size() + 1);
				ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/Portal.bmp");
				ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize) + 0.3f, -5, (j*u_kiTileSize)) ); //Make the gametile empty
				ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
				ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
				ModelList.at(ModelList.size() - 1).setMaterial(1);

				// Set portal location
				m_PortalLocation = vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize));
				break;

			case '#': // Ground Tile
				iPowerCellChance = rand() % 100 + 1; // Chance for powercell to spawn

				if (iPowerCellChance == 1)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("Powercell");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/Powercell.obj");

					m_textureID.resize(m_textureID.size() + 1);
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/Powercell.bmp");

					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
					ModelList.at(ModelList.size() - 1).setCollectable(); // Make it a collectable
				}
				
				break;
			case 'T': // Flora
				iNumTrees = rand() % 4 + 1;

				for (int i = 0; i < iNumTrees; i++)
				{
					if (m_iClimate == 1 || m_iClimate == 3)
					{
						iTreeType = rand() % 4 + 1;

						if (iTreeType == 1)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("DeadTree1");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/DeadTree.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/DeadTree.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
						}
						else if (iTreeType == 2)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("DeadTree2");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/DeadTree2.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/DeadTree.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
						}
						else if (iTreeType == 3)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Stump");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/Stump.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/Stump.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
						}
						else if (iTreeType == 4)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Rock");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/Rock.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/Rock.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, rand() % 359, 0));
						}
					}
					else
					{
						iTreeType = rand() % 4 + 1;
						if (iTreeType == 1)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("GreenTree");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/GreenTree.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/GreenTree.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
						}
						else if (iTreeType == 2)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Stump");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/Stump.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/Stump.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
						}
						else if (iTreeType == 3)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("LeafTree");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/LeafTree.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/LeafTree.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, rand() % 359, 0));
						}
						else if (iTreeType == 4)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Rock");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Flora/Rock.obj");
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Flora/Rock.bmp");
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, rand() % 359, 0));
						}
					}
					m_textureID.resize(m_textureID.size() + 1);

					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
			 
				break;

			case 'M': // Mountain
				if (i + 1 <= m_WorldList.size() - 1 && j + 1 <= m_WorldList[i].size() -1) // Ensures not out of bounds
				{
					if (m_WorldList[i + 1][j] == 'M' && m_WorldList[i][j + 1] == 'M' && m_WorldList[i + 1][j + 1] == 'M') // Ensure only ran once selection of 4 Ms
					{
						iMountainType = rand() % 4 + 1;

						if (iMountainType == 1)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Mountain");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Mountains/Mountain.obj");
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
							ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
							ModelList.at(ModelList.size() - 1).setMaterial(1);
						}
						else if (iMountainType == 2)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Mountain");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Mountains/Mountain2.obj");
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
							ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
							ModelList.at(ModelList.size() - 1).setMaterial(1);
						}
						else if (iMountainType == 3)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Mountain");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Mountains/Mountain3.obj");
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
							ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
							ModelList.at(ModelList.size() - 1).setMaterial(1);
						}
						else if (iMountainType == 4)
						{
							ModelList.resize(ModelList.size() + 1);
							ModelList.at(ModelList.size() - 1).setName("Mountain");
							ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Mountains/Mountain4.obj");
							ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
							ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
							ModelList.at(ModelList.size() - 1).setMaterial(1);
						}
						if (m_iClimate == 1)
						{
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
						}
						else if (m_iClimate == 2)
						{
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
						}
						else if (m_iClimate == 3)
						{
							ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
						}
					}
				}
				break;
			case 'C': // Civilisation
				iCivType = rand() % 6 + 1;

				if (iCivType == 1)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("FarmHouse");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Civilisation/FarmHouse.obj");
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Civilisation/FarmHouse.bmp");
					iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
				else if (iCivType == 2)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("Fence");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Civilisation/Fence.obj");
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Civilisation/Fence.bmp");
					iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
				else if (iCivType == 3)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("Cart");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Civilisation/Cart.obj");
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Civilisation/Cart.bmp");
					iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, rand() % 359, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
				else if (iCivType == 4)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("Big Rock");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Civilisation/BigRock.obj");
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Civilisation/BigRock.bmp");
					iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, rand() % 359, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
				else if (iCivType == 5)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("Logs");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Civilisation/Logs.obj");
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Civilisation/Logs.bmp");
					iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -4, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
				else if (iCivType == 6)
				{
					ModelList.resize(ModelList.size() + 1);
					ModelList.at(ModelList.size() - 1).setName("Crate");
					ModelList.at(ModelList.size() - 1).setFileLocation("assets/models/WorldTiles/Civilisation/Crate.obj");
					ModelList.at(ModelList.size() - 1).setTextureLocation("assets/textures/WorldTiles/Civilisation/Crate.bmp");
					iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
					ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
					ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
			
				break;
			}
		}
	}

	for (int i = 0; i < ModelList.size(); i++)
	{
		if (i > 0) // Avoid checking none existant memory
		{
			// If model is has the same name as previous model reuse model and dont load it in again
			if (ModelList.at(i).getName().compare(ModelList.at(i - 1).getName()) == 0)
			{
				ModelList.at(i).m_pModelReader = ModelList.at(i - 1).m_pModelReader; // Set model to previous model
				ModelList.at(i).m_bmp = ModelList.at(i - 1).m_bmp; // Set texture to previous texture
				ModelList.at(i).LoadTexture(ModelList.at(i - 1).getTextureLocation());
			}
			else
			{
				ModelList[i].LoadModel(ModelList[i].getFileLocation()); // Load in models to be ready for drawing
			}
		}
		else
		{
			ModelList[i].LoadModel(ModelList[i].getFileLocation()); // Load in models to be ready for drawing
		}
		cout << "Loading: " << ((i + 1) * 100) / ModelList.size() << "%" << endl; // Loading cout
	}

}

void WorldReader::SetFlatPlane(int xPos, int yPos, Model TexturedPlane, float WorldOffset, float TileSize)
{
	ModelList.resize(ModelList.size() + 1);
	ModelList.at(xPos * m_WorldList.size() + yPos) = TexturedPlane;
	ModelList.at(xPos * m_WorldList.size() + yPos).setPosition(glm::vec3(WorldOffset + (xPos*TileSize), -5, (yPos*TileSize))); 
	ModelList.at(xPos * m_WorldList.size() + yPos).setRotation(glm::vec3(0, 0, 0));
	ModelList.at(xPos * m_WorldList.size() + yPos).setScale(glm::vec3(1, 1, 1));
	ModelList.at(xPos * m_WorldList.size() + yPos).setMaterial(1);
}

