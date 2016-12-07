#ifndef WORLD_H
#define WORLD_H



#include "Texture.h"

#include "scene.h"
#include "Camera.h"
#include "ModelReader.h"
#include "SceneReader.h"

class World : public Scene
{
private:
	int width, height;
	GLuint programHandle;
	glm::mat4 M;
	float fRot;
	void linkMe(GLint vertShader, GLint fragShader);
	Texture *gTexture;
	Camera FirstPersonView;
	GLFWwindow *Window;
	sf::Vector2i MousePos;
	ModelReader* m_ModelReader;
	SceneReader world;

public:
	World();
	void initScene();
	void GetMousePos(GLFWwindow *Gwindow, sf::Vector2i mousepos);
	void update(float t);
	void render();
	void resize(int, int);

};
#endif  
