#include <WorldReader.h>

WorldReader::WorldReader()
{

}

WorldReader::WorldReader(std::vector<std::vector<char>> World)
{

}

WorldReader::WorldReader(std::string WorldFileName)
{
	ReadWorldFile(WorldFileName);
	LoadModels();
}

void WorldReader::ReadWorldFile(string FileName)
{
	std::ifstream WorldFile; // World file
	std::string sLineFromFile; // Line from world file
	std::string sDiscard; // To discard unwanted characters
	
	m_WorldList.resize(10);

	WorldFile.open(FileName); //Open File 1

	if (WorldFile.is_open())
	{
		for (int i = 0; i < 10; i++) //For every row
		{
			getline(WorldFile, sLineFromFile); //Read a line
			remove_if(sLineFromFile.begin(), sLineFromFile.end(), isspace);
			for (int j = 0; j < 10; j++) //For every char
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
	//getline(WorldFile, sLineFromFile);
	//int iSkybox = sLineFromFile.back();

	WorldFile.close();

}

void WorldReader::LoadModels()
{
	unsigned const int u_kiTileSize = 50; // Size of each tile
	unsigned const int u_kWorldOffset = 0; // Offset for position world will be rendered

	for (int i = 0; i < m_WorldList.size(); i++)//For every Row
	{
		for (int j = 0; j < m_WorldList[i].size(); j++)//For every bit
		{
			switch (m_WorldList[i][j])
			{
			default:
				ModelList.resize(ModelList.size() + 1);
				ModelList.at(i * m_WorldList.size() + j).setPosition(glm::vec3(u_kWorldOffset + (i*u_kiTileSize,-2,(j+u_kiTileSize)))); //Make the gametile empty
				ModelList.at(i * m_WorldList.size() + j).setFileLocation("assets/models/WorldTiles/Plane.obj");
				ModelList.at(i * m_WorldList.size() + j).setTextureLocation("assets/textures/WorldTiles/grassy.bmp");
				ModelList.at(i * m_WorldList.size() + j).setRotation(glm::vec3(0, 0, 0));
				ModelList.at(i * m_WorldList.size() + j).setScale(glm::vec3(1, 1, 1));
				ModelList.at(i * m_WorldList.size() + j).setMaterial(1);
				//m_bmp = Bitmap::bitmapFromFile("assets/textures/World Tiles/grassy.bmp");
				//m_bmp.flipVertically();
				//m_pTexture = new tex::Texture(m_bmp);
				////Set texture
				//gl::ActiveTexture(gl::TEXTURE0);
				//gl::BindTexture(gl::TEXTURE_2D, m_pTexture->object());
				//GLint loc = gl::GetUniformLocation(m_programHandle, "tex");

				//gl::Uniform1f(loc, 1);
				break;
			case 'w':

				break;
			case 'd':
				
				break;
			case 'u':
				
				break;
			case 'l':
				
				break;
			case 'r':
				
				break;
			case 't':
				
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
			}
		}

		ModelList[i].LoadModel(ModelList[i].getFileLocation()); // Load in models to be ready for drawing
	}
}

