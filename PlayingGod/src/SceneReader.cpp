#include "PreHeader.h"
#include "SceneReader.h"

SceneReader::SceneReader()
{

}

SceneReader::SceneReader(string filename)
{
	ReadSceneFile(filename); // Send file to be read
	//tl = new TextureLoader(); // Create a new textureloader
}

void SceneReader::ReadSceneFile(string sFilename)
{
	Model temp; // Temperary model to be pushed into Scene Vector
	string sData; // Current sData being read

	tinyxml2::XMLDocument doc; // XML document

	doc.LoadFile(sFilename.c_str()); // Load document

	for (tinyxml2::XMLNode* iNode = doc.FirstChild(); iNode != NULL; iNode = iNode->NextSibling())
	{
		if (strcmp(iNode->Value(), "Scene") == 0) // For each scene
		{
			for (tinyxml2::XMLNode* iNode2 = iNode->FirstChild(); iNode2 != NULL; iNode2 = iNode2->NextSibling())
			{
				if (strcmp(iNode2->Value(), "Object") == 0) // For each object within a scene
				{
					for (tinyxml2::XMLNode* iNode3 = iNode2->FirstChild(); iNode3 != NULL; iNode3 = iNode3->NextSibling())
					{
						istringstream iss(iNode3->ToElement()->GetText());
						if (strcmp(iNode3->Value(), "Name") == 0) // Assign name
						{
							iss >> sData;
							temp.setName(sData);
						}
						if (strcmp(iNode3->Value(), "OBJLocation") == 0) // Assign .obj file location
						{

							iss >> sData;
							temp.setFileLocation(sData);
						}
						if (strcmp(iNode3->Value(), "TexLocation") == 0) // Assign .bmp texture file location
						{
							iss >> sData;
							m_textureID.resize(m_textureID.size() + 1); // Make the textureID vector 1 bigger
																		// Set texture to end of vector
																		//	tl->LoadBMP(data, m_textureID[m_textureID.size() - 1], true); 

							temp.setTextureLocation(sData);
						}
						if (strcmp(iNode3->Value(), "Translation") == 0) // Read in 3 values for the position of the model
						{
							glm::vec3 position;
							iss >> sData;
							position.x = stof(sData);
							iss >> sData;
							position.y = stof(sData);
							iss >> sData;
							position.z = stof(sData);
							temp.setPosition(position);
						}
						if (strcmp(iNode3->Value(), "Rotation") == 0) // Read in 3 values for the rotation of the model
						{

							glm::vec3 rotation;
							iss >> sData;
							rotation.x = stof(sData);
							iss >> sData;
							rotation.y = stof(sData);
							iss >> sData;
							rotation.z = stof(sData);
							temp.setRotation(rotation);
						}
						if (strcmp(iNode3->Value(), "Scale") == 0) // Read in 3 values for the scale of the model
						{

							glm::vec3 scale;
							iss >> sData;
							scale.x = stof(sData);
							iss >> sData;
							scale.y = stof(sData);
							iss >> sData;
							scale.z = stof(sData);
							temp.setScale(scale);
						}
						if (strcmp(iNode3->Value(), "Material") == 0) // Assign a material for the model
						{

							iss >> sData;
							temp.setMaterial(stoi(sData));
						}
						if (strcmp(iNode3->Value(), "Collectable") == 0) // Check if model is a collectable
						{

							iss >> sData;
							if (sData == "true")
							{
								temp.setCollectable();
							}
						}
					}
					ModelList.push_back(temp); // Push to vector of models 
				}
			}
		}
	}
	// Load in models
	for (int i = 0; i < ModelList.size(); i++)
	{
		if (i > 0) // Avoid checking none existant memory
		{
			// If model is has the same name as previous model reuse model and dont load it in again
			if (ModelList.at(i).getName().compare(ModelList.at(i - 1).getName()) == 0);
			{
				ModelList.at(i).m_pModelReader = ModelList.at(i - 1).m_pModelReader;
			}
		}

		ModelList[i].LoadModel(ModelList[i].getFileLocation()); // Load in models to be ready for drawing
	}
}
