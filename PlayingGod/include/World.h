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
#ifndef WORLD_H
#define WORLD_H



#include "Texture.h"

#include "scene.h"
#include "Camera.h"
#include "SceneReader.h"
#include "WorldReader.h"
#include "glslprogram.h"
#include "CubeMap.h"
#include <SFML\Audio.hpp>

class World : public Scene
{
private:
	GLSLProgram m_WorldShader;
	GLSLProgram m_SkyBox;
	int width, height; // Dimentions of window
	GLuint programHandle; // Program context
	glm::mat4 M; // Allows manipulation of each models position, rotation and scale
	void linkShaders(); // Connects shaders
	tex::Texture *gTexture; // Holds texture
	Camera FirstPersonView; // Camera which user can control
	GLFWwindow *Window; // The window
	sf::Vector2i MousePos; // Holds mouse cursor position
	SceneReader LabScene; // Reads .txt file in order to create world
	WorldReader CurrentWorld;
	CubeMap *Cube;
	glm::mat4 V, P; // View and Perspective
	sf::SoundBuffer m_theme; // Theme music
	sf::SoundBuffer m_Hello; // Intro voice line
	sf::Sound m_Sound;
	void SetMatices(GLSLProgram * shader, mat4 model, mat4 view, mat4 projection);
	vec3 m_Collectablespeed;
	//void linkMe(GLint vertShader, GLint fragShader); // Connects shaders

public:
	World(sf::Vector2i windowSize);
	void initScene();
	bool m_bWorldLoaded = false;
	void setMousePos(GLFWwindow *pWindow, sf::Vector2i mousepos);
	void update(float t);
//	void ModelUpdate(int index);
	void render();
	void LoadMap(string FileLocation, bool isXML);
	//bool m_bPortalReady;
};
#endif  
