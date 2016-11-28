#ifndef SceneTexture_H
#define SceneTexture_H



#include "Texture.h"

#include "scene.h"
#include "Camera.h"
#include "ModelReader.h"

class SceneTexture : public Scene
{
private:
	int width, height;
	GLuint vboHandles[2];
	GLuint vbo;
	GLuint vaoHandle;
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
	vector<float>positionData;
	vector<float>uvData;
	vector<float>normalsData;
public:
	SceneTexture();
	//void PassWindowToScreen(GLFWwindow *window);
	void initScene();
	void GetMousePos(GLFWwindow *Gwindow, sf::Vector2i mousepos);
	void update(float t);
	void render();
	void resize(int, int);

};
#endif  
