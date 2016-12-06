#pragma once

#include "stdafx.h"
#include "Model.h"
#include <vector>
#include "Texture.h"

class SceneReader
{
public:
	SceneReader();
	SceneReader(string filename); // Takes a file name and loads in a scene
	vector<Model> ModelList; // Vector of models which makes up the scene

private:
	vector<GLuint> m_textureID; // Vector of all the textures for models
	Texture *gTexture;
	void ReadSceneFile(string filename); // Function to proccess textfile
};