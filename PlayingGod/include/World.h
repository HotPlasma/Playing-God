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
	/*GLuint vboHandles[2];
	GLuint vbo;
	GLuint vaoHandle;*/
	GLuint programHandle;
	//GLuint indexSize;
	glm::mat4 M;
	float fRot;
	void linkMe(GLint vertShader, GLint fragShader);
	Texture *gTexture;
	Camera FirstPersonView;
	GLFWwindow *Window;
	sf::Vector2i MousePos;
	ModelReader* m_ModelReader;
	SceneReader world;
	//vector<float>positionData;
	//vector<float>uvData;
	//vector<float>normalsData;

	//ModelReader* m_ModelReader2;
	//vector<float>positionData2;
	//vector<float>uvData2;
	//vector<float>normalsData2;
public:
	World();
	//void PassWindowToScreen(GLFWwindow *window);
	void initScene();
	void GetMousePos(GLFWwindow *Gwindow, sf::Vector2i mousepos);
	void update(float t);
	void render();
	void resize(int, int);

};
#endif  
