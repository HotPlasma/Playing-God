////////////////////////////////////////////////////////////
//
// Playing God (3D Procedural World Generation) - Created by Jegor Kharlamov
// Created for Personal Final Year Project Year 3 at De Montfort University - Games Programming Course
//
// Playing God is a 3D world exploration game where the player can operate 
// a computer which generates new worlds based on selected parameters and creates a portal to them.
// The player can then travel through the portal to explore the worlds and search
// for powercells around the procedurally generated maps.
//
////////////////////////////////////////////////////////////
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class TextureLoader
{
	private:
		vector<sf::Texture> m_Textures;// A vector of textures which all textures used in the program should be loaded into.
		string m_sBaseDirectory;// A string holding a base directory to find textures

	public:
		TextureLoader(); // Initialises the Texture Loader
		void setBaseDirectory(string dir); // Allows the base directory which the textures are loaded from to be changed.
		void load(std::vector<string> fileNames); // Function where all necessary textures should be loaded in.
		std::vector<sf::Texture>::iterator getTextureIterator(const int &k_iIndex); // Allows textures from the Texture Loader to be used for sprite in other classes
};

#endif