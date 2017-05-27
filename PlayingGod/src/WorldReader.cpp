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

	Model TempModel;


	// Snowy Plane 0
	TempModel.setName("Snow Plane");
	TempModel.setFileLocation("assets/models/WorldTiles/Plane.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	TempModel.setScale(glm::vec3(1, 1, 1));
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);


	// Grassy Plane 1
	TempModel.setName("Grass Plane");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);


	// Sandy Plane 2
	TempModel.setName("Sand Plane");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Archway 3
	TempModel.setName("Archway");
	TempModel.setFileLocation("assets/models/WorldTiles/Portal.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Portal.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);


	// Portal 4
	TempModel.setName("Portal");
	TempModel.setFileLocation("assets/models/Portal.obj");
	TempModel.setTextureLocation("assets/textures/Portal.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Powercell 5
	TempModel.setName("Powercell");
	TempModel.setFileLocation("assets/models/Powercell.obj");
	TempModel.setTextureLocation("assets/textures/Powercell.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// DeadTree1 6
	TempModel.setName("DeadTree1");
	TempModel.setFileLocation("assets/models/WorldTiles/Flora/DeadTree.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Flora/DeadTree.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// DeadTree2 7
	TempModel.setName("DeadTree2");
	TempModel.setFileLocation("assets/models/WorldTiles/Flora/DeadTree2.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Flora/DeadTree.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Stump 8
	TempModel.setName("Stump");
	TempModel.setFileLocation("assets/models/WorldTiles/Flora/Stump.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Flora/Stump.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Rock 9
	TempModel.setName("Rock");
	TempModel.setFileLocation("assets/models/WorldTiles/Flora/Rock.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Flora/Rock.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// GreenTree 10
	TempModel.setName("GreenTree");
	TempModel.setFileLocation("assets/models/WorldTiles/Flora/GreenTree.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Flora/GreenTree.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// LeafTree 11
	TempModel.setName("LeafTree");
	TempModel.setFileLocation("assets/models/WorldTiles/Flora/LeafTree.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Flora/LeafTree.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Mountain1 12
	TempModel.setName("Mountain1");
	TempModel.setFileLocation("assets/models/WorldTiles/Mountains/Mountain.obj");
	if (m_iClimate == 1)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	}
	else if (m_iClimate == 2)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	}
	else if (m_iClimate == 3)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	}
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Mountain2 13
	TempModel.setName("Mountain2");
	TempModel.setFileLocation("assets/models/WorldTiles/Mountains/Mountain2.obj");
	if (m_iClimate == 1)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	}
	else if (m_iClimate == 2)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	}
	else if (m_iClimate == 3)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	}
	TempModel.LoadModel(TempModel.getFileLocation());

	ModelList.push_back(TempModel);

	// Mountain3 14
	TempModel.setName("Mountain3");
	TempModel.setFileLocation("assets/models/WorldTiles/Mountains/Mountain3.obj");
	if (m_iClimate == 1)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	}
	else if (m_iClimate == 2)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	}
	else if (m_iClimate == 3)
	{
		TempModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	}
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Farmhouse 15
	TempModel.setName("Farmhouse");
	TempModel.setFileLocation("assets/models/WorldTiles/Civilisation/FarmHouse.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/FarmHouse.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Fence 16
	TempModel.setName("Fence");
	TempModel.setFileLocation("assets/models/WorldTiles/Civilisation/Fence.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Fence.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Cart 17
	TempModel.setName("Cart");
	TempModel.setFileLocation("assets/models/WorldTiles/Civilisation/Cart.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Cart.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Big Rock 18
	TempModel.setName("Big Rock");
	TempModel.setFileLocation("assets/models/WorldTiles/Civilisation/BigRock.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/BigRock.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Logs 19
	TempModel.setName("Logs");
	TempModel.setFileLocation("assets/models/WorldTiles/Civilisation/Logs.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Logs.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

	// Crate 20
	TempModel.setName("Crate");
	TempModel.setFileLocation("assets/models/WorldTiles/Civilisation/Crate.obj");
	TempModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Crate.bmp");
	TempModel.LoadModel(TempModel.getFileLocation());
	ModelList.push_back(TempModel);

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

	 Model *Plane = new Model(ModelList.at(0));
	// CubeMap *SkyBox;
	 //Plane->setFileLocation("assets/models/WorldTiles/Plane.obj");
	

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

				 if (m_iClimate == 1)
				 {
					 Plane = new Model(ModelList.at(0));
				 }
				 else if (m_iClimate == 2)
				 {
					 Plane = new Model(ModelList.at(1));
				 }
				 else if (m_iClimate == 3)
				 {
					 Plane = new Model(ModelList.at(2));
				 }
				 Plane->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize)));
				 Plane->setRotation(glm::vec3(0, 0, 0));
				 Plane->setScale(glm::vec3(1, 1, 1));
				 Plane->setMaterial(1);
				 ModelLocationList.push_back(Plane);
			 }
		 }
	 }


	 //for (int i = 0; i < ModelList.size(); i++)
	 //{
		// ModelList.at(i).LoadModel(ModelList.at(i).getFileLocation());
		// cout << "Loading: " << ((i + 1) * 100) / ModelList.size() << "%" << endl; // Loading cout
	 //}


	 //for (int i = 0; i < ModelLocationList.size(); i++)
	 //{
		// ModelLocationList[i]->LoadModel(ModelLocationList[i]->getFileLocation());
		// cout << "Loading: " << ((i + 1) * 100) / ModelLocationList.size() << "%" << endl; // Loading cout
	 //}

	 Model *TempModel = new Model(ModelList.at(0));

	 for (int i = 0; i < m_WorldList.size(); i++) //For every Row
	 {
		 for (int j = 0; j < m_WorldList[i].size(); j++) //For every bit
		 {
			 switch (m_WorldList[i][j])
			 {
			 case 'P': // Portal
				 // Portal archway
				 TempModel = new Model(ModelList.at(3));
				 m_textureID.resize(m_textureID.size() + 1);
				 TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
				 TempModel->setRotation(glm::vec3(0, 0, 0));
				 TempModel->setScale(glm::vec3(1, 1, 1));
				 TempModel->setMaterial(1);
				 ModelLocationList.push_back(TempModel);

				 // Portal
				 TempModel = new Model(ModelList.at(4));
				 m_textureID.resize(m_textureID.size() + 1);
				 TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize) + 0.3f, -5, (j*u_kiTileSize))); //Make the gametile empty
				 TempModel->setRotation(glm::vec3(0, 0, 0));
				 TempModel->setScale(glm::vec3(1, 1, 1));
				 TempModel->setMaterial(1);
				 ModelLocationList.push_back(TempModel);

				 // Set portal location
				 m_PortalLocation = vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize));
				 break;

			case '#': // Ground Tile
				iPowerCellChance = rand() % 100 + 1; // Chance for powercell to spawn

				if (iPowerCellChance == 1)
				{
					TempModel = new Model(ModelList.at(5));
				 	m_textureID.resize(m_textureID.size() + 1);
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, 0, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					TempModel->setCollectable(true); // Make it a collectable
					ModelLocationList.push_back(TempModel);
					//TempModel->setCollectable(false); // Stop following objects from also being a collectable
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
							TempModel = new Model(ModelList.at(6));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
				 			ModelList.at(ModelList.size() - 1).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
				 			ModelList.at(ModelList.size() - 1).setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 2)
				 		{
							TempModel = new Model(ModelList.at(7));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
				 			TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
				 			TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 3)
				 		{
							TempModel = new Model(ModelList.at(8));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 4)
				 		{
							TempModel = new Model(ModelList.at(9));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
							ModelLocationList.push_back(TempModel);

				 		}
				 	}
				 	else
				 	{
				 		iTreeType = rand() % 4 + 1;
				 		if (iTreeType == 1)
				 		{
							TempModel = new Model(ModelList.at(10));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 2)
				 		{
							TempModel = new Model(ModelList.at(8));
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 3)
				 		{
							TempModel = new Model(ModelList.at(11));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
				 		}
				 		else if (iTreeType == 4)
				 		{
							TempModel = new Model(ModelList.at(9));
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 	}
				 	m_textureID.resize(m_textureID.size() + 1);

				 	//ModelList.at(ModelList.size() - 1).setScale(glm::vec3(1, 1, 1));
				 	//ModelList.at(ModelList.size() - 1).setMaterial(1);
				}
				 		 
				break;

			case 'M': // Mountain
				if (i + 1 <= m_WorldList.size() - 1 && j + 1 <= m_WorldList[i].size() -1) // Ensures not out of bounds
				{
				 	if (m_WorldList[i + 1][j] == 'M' && m_WorldList[i][j + 1] == 'M' && m_WorldList[i + 1][j + 1] == 'M') // Ensure only ran once selection of 4 Ms
				 	{
				 		iMountainType = rand() % 3 + 1;

					

				 		if (iMountainType == 1)
				 		{
							m_textureID.resize(m_textureID.size() + 1);
							TempModel = new Model(ModelList.at(12));
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							TempModel->setScale(glm::vec3(1, 1, 1));
							TempModel->setMaterial(1);

							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iMountainType == 2)
				 		{
							m_textureID.resize(m_textureID.size() + 1);
							TempModel = new Model(ModelList.at(13));
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							TempModel->setScale(glm::vec3(1, 1, 1));
							TempModel->setMaterial(1);


							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iMountainType == 3)
				 		{
							m_textureID.resize(m_textureID.size() + 1);
							TempModel = new Model(ModelList.at(14));
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							TempModel->setScale(glm::vec3(1, 1, 1));
							TempModel->setMaterial(1);

							ModelLocationList.push_back(TempModel);
				 		}
				 		
						

						
				 	}
				}
				break;
			case 'C': // Civilisation
				iCivType = rand() % 6 + 1;

				if (iCivType == 1)
				{
				 	TempModel = new Model(ModelList.at(15));
				 	//iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
				 	TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
				 	TempModel->setRotation(glm::vec3(0, 0, 0));
				 	TempModel->setScale(glm::vec3(1, 1, 1));
				 	TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 2)
				{
					TempModel = new Model(ModelList.at(16));
				 	//iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, 0, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 3)
				{
					TempModel = new Model(ModelList.at(17));
				 	//iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 4)
				{
				 	TempModel = new Model(ModelList.at(18));
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 5)
				{
					TempModel = new Model(ModelList.at(19));
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -4, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, 0, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 6)
				{
					TempModel = new Model(ModelList.at(20));
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, 0, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				 		
				break;
			}
		}
		}

				 //for (int i = 0; i < ModelList.size(); i++)
				 //{
					// if (i > 0) // Avoid checking none existant memory
					// {
					//	 // If model is has the same name as previous model reuse model and dont load it in again
					//	 if (ModelList.at(i).getName().compare(ModelList.at(i - 1).getName()) == 0)
					//	 {
					//		 ModelList.at(i).m_pModelReader = ModelList.at(i - 1).m_pModelReader; // Set model to previous model
					//		 ModelList.at(i).m_bmp = ModelList.at(i - 1).m_bmp; // Set texture to previous texture
					//		 ModelList.at(i).LoadTexture(ModelList.at(i - 1).getTextureLocation());
					//	 }
					//	 else
					//	 {
					//		 ModelList[i].LoadModel(ModelList[i].getFileLocation()); // Load in models to be ready for drawing
					//	 }
					// }
					// else
					// {
					//	 ModelList[i].LoadModel(ModelList[i].getFileLocation()); // Load in models to be ready for drawing
					// }
				 //}
		//	cout << "Loading: " << ((i + 1) * 100) / ModelList.size() << "%" << endl; // Loading cout


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

