#pragma once
#include <PreHeader.h>
#include "Texture.h"
#include "Model.h"

class WorldReader
{
public:
	std::vector<std::vector<char>> m_WorldList;
	WorldReader();
	WorldReader(std::vector<std::vector<char>> World);
	WorldReader(std::string WorldFileName);
	vector<GLuint> m_textureID;
	std::vector<Model> ModelList;
	GLuint m_programHandle;
	tex::Texture *m_pTexture;
	Bitmap m_bmp = Bitmap::bitmapFromFile("assets/textures/Default.bmp");
	void ReadWorldFile(string FileName);
	void LoadModels();
};