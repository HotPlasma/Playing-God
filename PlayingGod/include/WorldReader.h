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
#pragma once
#include <PreHeader.h>
#include "Texture.h"
#include "Model.h"
#include "CubeMap.h"
#include "glslprogram.h"
#include <random>
#include <time.h>

class WorldReader
{
public:
	std::vector<std::vector<char>> m_WorldList;
	//GLSLProgram m_SkyBox;
	WorldReader();
	WorldReader(std::vector<std::vector<char>> World);
	WorldReader(std::string WorldFileName);
	int m_iSkybox;
	int m_iClimate;
	int m_iWorldSize;
	glm::vec3 m_PortalLocation;
	vector<GLuint> m_textureID;
	std::vector<Model> ModelList;
	GLuint m_programHandle;
	tex::Texture *m_pTexture;
	Bitmap m_bmp = Bitmap::bitmapFromFile("assets/textures/Default.bmp");
	void ReadWorldFile(string FileName);
	void LoadModels();
	void SetFlatPlane(int xPos, int yPos, Model TexturedPlane, float WorldOffset, float TileSize);
	CubeMap *m_SkyBox;
};