#include <TextureLoader.h>

TextureLoader::TextureLoader()
{
	m_sBaseDirectory = "assets\\"; //Default base directory
}


void TextureLoader::setBaseDirectory(string dir) // Allows base directory to be changed if neccessary
{
	m_sBaseDirectory = dir;
}

void TextureLoader::load(std::vector<string> fileNames) // Loads in all needed textures and adds them to the textures vector
{
	sf::Texture Holder;
	for (int i = 0; i < fileNames.size(); i++)
	{
		if (!Holder.loadFromFile(m_sBaseDirectory + fileNames.at(i)))
		{
			sf::err() << "Could not load " << fileNames.at(i) << endl;
		}
		m_Textures.push_back(Holder);
	}
}

std::vector<sf::Texture>::iterator TextureLoader::getTextureIterator(const int &k_iIndex) //Allows the assigning of textures to sprites
{
	return std::vector<sf::Texture>::iterator(m_Textures.begin() + k_iIndex);
}