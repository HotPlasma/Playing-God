#ifndef SceneTexture_H
#define SceneTexture_H

#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glm/glm/gtc/matrix_transform.hpp"
#include "../libraries/glm/glm/gtc/type_ptr.hpp"

#include "Texture.h"

#include "scene.h"

#include "gl_core_4_3.hpp"

class SceneTexture : public Scene
{
private:
	int width, height;
	GLuint vboHandles[3];
	GLuint vbo;
	GLuint vaoHandle;
	GLuint programHandle;
	GLuint indexSize;
	glm::mat4 M;
	float fRot;
	void linkMe(GLint vertShader, GLint fragShader);
	Texture *gTexture;

public:
	SceneTexture();

	void initScene();
	void update(float t);
	void render();
	void resize(int, int);

};
#endif  //SceneTexture_H#pragma once
