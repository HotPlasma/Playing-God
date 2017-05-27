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

	Model TemporaryModel;


	// Snowy Plane 0
	TemporaryModel.setName("Snow Plane");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Plane.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	TemporaryModel.setScale(glm::vec3(1, 1, 1));
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);


	// Grassy Plane 1
	TemporaryModel.setName("Grass Plane");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);


	// Sandy Plane 2
	TemporaryModel.setName("Sand Plane");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Archway 3
	TemporaryModel.setName("Archway");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Portal.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Portal.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);


	// Portal 4
	TemporaryModel.setName("Portal");
	TemporaryModel.setFileLocation("assets/models/Portal.obj");
	TemporaryModel.setTextureLocation("assets/textures/Portal.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Powercell 5
	TemporaryModel.setName("Powercell");
	TemporaryModel.setFileLocation("assets/models/Powercell.obj");
	TemporaryModel.setTextureLocation("assets/textures/Powercell.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// DeadTree1 6
	TemporaryModel.setName("DeadTree1");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Flora/DeadTree.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Flora/DeadTree.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// DeadTree2 7
	TemporaryModel.setName("DeadTree2");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Flora/DeadTree2.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Flora/DeadTree.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Stump 8
	TemporaryModel.setName("Stump");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Flora/Stump.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Flora/Stump.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Rock 9
	TemporaryModel.setName("Rock");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Flora/Rock.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Flora/Rock.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// GreenTree 10
	TemporaryModel.setName("GreenTree");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Flora/GreenTree.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Flora/GreenTree.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// LeafTree 11
	TemporaryModel.setName("LeafTree");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Flora/LeafTree.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Flora/LeafTree.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Mountain1 12
	TemporaryModel.setName("Mountain1");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Mountains/Mountain.obj");
	if (m_iClimate == 1)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	}
	else if (m_iClimate == 2)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	}
	else if (m_iClimate == 3)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	}
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Mountain2 13
	TemporaryModel.setName("Mountain2");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Mountains/Mountain2.obj");
	if (m_iClimate == 1)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	}
	else if (m_iClimate == 2)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	}
	else if (m_iClimate == 3)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	}
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());

	ModelList.push_back(TemporaryModel);

	// Mountain3 14
	TemporaryModel.setName("Mountain3");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Mountains/Mountain3.obj");
	if (m_iClimate == 1)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Snowy.bmp");
	}
	else if (m_iClimate == 2)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Grassy.bmp");
	}
	else if (m_iClimate == 3)
	{
		TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Sandy.bmp");
	}
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Farmhouse 15
	TemporaryModel.setName("Farmhouse");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Civilisation/FarmHouse.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/FarmHouse.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Fence 16
	TemporaryModel.setName("Fence");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Civilisation/Fence.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Fence.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Cart 17
	TemporaryModel.setName("Cart");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Civilisation/Cart.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Cart.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Big Rock 18
	TemporaryModel.setName("Big Rock");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Civilisation/BigRock.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/BigRock.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Logs 19
	TemporaryModel.setName("Logs");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Civilisation/Logs.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Logs.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

	// Crate 20
	TemporaryModel.setName("Crate");
	TemporaryModel.setFileLocation("assets/models/WorldTiles/Civilisation/Crate.obj");
	TemporaryModel.setTextureLocation("assets/textures/WorldTiles/Civilisation/Crate.bmp");
	TemporaryModel.LoadModel(TemporaryModel.getFileLocation());
	ModelList.push_back(TemporaryModel);

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

	 
	 std::shared_ptr<Model> Plane( new Model(ModelList.at(0)));
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
					 Plane.reset(new Model(ModelList.at(0)));
				 }
				 else if (m_iClimate == 2)
				 {
					 Plane.reset(new Model(ModelList.at(1)));
				 }
				 else if (m_iClimate == 3)
				 {
					 Plane.reset(new Model(ModelList.at(2)));
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

	 std::shared_ptr<Model> TempModel(new Model(ModelList.at(0)));

	 for (int i = 0; i < m_WorldList.size(); i++) //For every Row
	 {
		 for (int j = 0; j < m_WorldList[i].size(); j++) //For every bit
		 {
			 switch (m_WorldList[i][j])
			 {
			 case 'P': // Portal
				 // Portal archway
				 TempModel.reset(new Model(ModelList.at(3)));
				 m_textureID.resize(m_textureID.size() + 1);
				 TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
				 TempModel->setRotation(glm::vec3(0, 0, 0));
				 TempModel->setScale(glm::vec3(1, 1, 1));
				 TempModel->setMaterial(1);
				 ModelLocationList.push_back(TempModel);

				 // Portal
				 TempModel.reset(new Model(ModelList.at(4)));
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
					TempModel.reset(new Model(ModelList.at(5)));
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

				for (int k = 0; k < iNumTrees; k++)
				{
				 	if (m_iClimate == 1 || m_iClimate == 3)
				 	{
				 		iTreeType = rand() % 4 + 1;

				 		if (iTreeType == 1)
				 		{
							TempModel.reset(new Model(ModelList.at(6)));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 2)
				 		{
							TempModel.reset(new Model(ModelList.at(7)));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
				 			TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
				 			TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 3)
				 		{
							TempModel.reset(new Model(ModelList.at(8)));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 4)
				 		{
							TempModel.reset(new Model(ModelList.at(9)));
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
							TempModel.reset(new Model(ModelList.at(10)));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 2)
				 		{
							TempModel.reset(new Model(ModelList.at(8)));
							iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 3)
				 		{
							TempModel.reset(new Model(ModelList.at(11)));
				 			iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + iPositionVariance.x), -5, (j*u_kiTileSize + iPositionVariance.y))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iTreeType == 4)
				 		{
							TempModel.reset(new Model(ModelList.at(9)));
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
							TempModel.reset(new Model(ModelList.at(12)));
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							TempModel->setScale(glm::vec3(1, 1, 1));
							TempModel->setMaterial(1);

							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iMountainType == 2)
				 		{
							m_textureID.resize(m_textureID.size() + 1);
							TempModel.reset(new Model(ModelList.at(13)));
							TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize + (u_kiTileSize / 2)), -5, (j*u_kiTileSize + (u_kiTileSize / 2)))); //Make the gametile empty
							TempModel->setRotation(glm::vec3(0, 0, 0));
							TempModel->setScale(glm::vec3(1, 1, 1));
							TempModel->setMaterial(1);


							ModelLocationList.push_back(TempModel);
				 		}
				 		else if (iMountainType == 3)
				 		{
							m_textureID.resize(m_textureID.size() + 1);
							TempModel.reset(new Model(ModelList.at(14)));
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
					TempModel.reset(new Model(ModelList.at(15)));
				 	//iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
				 	TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
				 	TempModel->setRotation(glm::vec3(0, 0, 0));
				 	TempModel->setScale(glm::vec3(1, 1, 1));
				 	TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 2)
				{
					TempModel.reset(new Model(ModelList.at(16)));
				 	//iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, 0, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 3)
				{
					TempModel.reset(new Model(ModelList.at(17)));
				 	//iPositionVariance = vec2(rand() % 50 + (-25), rand() % 50 + (-25)); // Random number between -25 and 25
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 4)
				{
					TempModel.reset(new Model(ModelList.at(18)));
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -5, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, rand() % 359, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 5)
				{
					TempModel.reset(new Model(ModelList.at(19)));
					TempModel->setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize), -4, (j*u_kiTileSize))); //Make the gametile empty
					TempModel->setRotation(glm::vec3(0, 0, 0));
					TempModel->setScale(glm::vec3(1, 1, 1));
					TempModel->setMaterial(1);
					ModelLocationList.push_back(TempModel);
				}
				else if (iCivType == 6)
				{
					TempModel.reset(new Model(ModelList.at(20)));
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

}


