#ifndef WORLD_H
#define WORLD_H



#include "Texture.h"

#include "scene.h"
#include "Camera.h"
#include "SceneReader.h"
#include "WorldReader.h"

class World : public Scene
{
private:
	int width, height; // Dimentions of window
	GLuint programHandle; // Program context
	glm::mat4 M; // Allows manipulation of each models position, rotation and scale
	void linkMe(GLint vertShader, GLint fragShader); // Connects shaders
	tex::Texture *gTexture; // Holds texture
	Camera FirstPersonView; // Camera which user can control
	GLFWwindow *Window; // The window
	sf::Vector2i MousePos; // Holds mouse cursor position
	SceneReader LabScene; // Reads .txt file in order to create world
	WorldReader CurrentWorld;

public:
	World(sf::Vector2i windowSize);
	void initScene();
	void setMousePos(GLFWwindow *pWindow, sf::Vector2i mousepos);
	void update(float t);
	void ModelUpdate(int index);
	void render();
	void LoadMap(string FileLocation, bool isXML);
};
#endif  
