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
#include <Freetype.h>

class World : public Scene
{
private:
	GLSLProgram m_WorldShader; ///< GLSL shader for rendering everything but the skybox
	GLSLProgram m_SkyBox; ///< GLSL shader for rendering the skybox
	GLSLProgram m_FreeType;
	Freetype* HUD; ///< The Heads Up Display which 2D and drawn infront of the world
	unsigned int m_uiPowerCellsCollected; ///< Collectable counter
	GLuint programHandle; ///< GLuint Program context
	glm::mat4 M; ///<  Allows manipulation of each models position, rotation and scale
	Camera FirstPersonView; ///< Camera class which user can control
	GLFWwindow *Window; ///< Local window context
	sf::Vector2i MousePos; ///< Holds mouse cursor position
	SceneReader LabScene; ///< Reads .xml file in order to create labratory
	WorldReader CurrentWorld; ///< Reads a cfg file in order to create worlds
	CubeMap *Cube; ///< Skybox cube
	glm::mat4 V, P; ///< View and Perspective glm::mat4s
	sf::SoundBuffer m_ThemeSong; ///< Theme music
	sf::SoundBuffer m_Hello; ///< Intro voice line
	sf::SoundBuffer m_PortalIntro; ///< Discription of how to use portal
	sf::SoundBuffer m_PowercellsIntro; ///< Reveals objective to find powercells
	sf::SoundBuffer m_CollectableSound;
	sf::Sound m_Sound; ///< The sound for the game
	sf::Clock m_ToastTimer; ///< Timer for how long a message should be displayed

	////////////////////////////////////////////////////////////
	/// \brief Used to set the marticies and uniform variables for shaders
	///
	/// \param shader Which shaders uniform variables are being set
	/// \param model The model matrix for the shader
	/// \param view The view matrix for the shader
	/// \param projection The projection matrix for the shader
	////////////////////////////////////////////////////////////
	void SetMatices(GLSLProgram * shader, mat4 model, mat4 view, mat4 projection);

	////////////////////////////////////////////////////////////
	/// \brief Connects, compiles and validates shaders 
	////////////////////////////////////////////////////////////
	void linkShaders(); 

public:
	////////////////////////////////////////////////////////////
	/// \brief Create a world and set up projection to be the size of the window
	///
	/// \param windowSize Vector2i the size of the window
	////////////////////////////////////////////////////////////
	World(sf::Vector2i windowSize);

	////////////////////////////////////////////////////////////
	/// \brief Initiate the scene. Sets up variables, enable depth-test, load in soundfx
	////////////////////////////////////////////////////////////
	void initScene(Freetype* Overlay);
	
	////////////////////////////////////////////////////////////
	/// \brief Set local mouse position to given coordinates based on a GLFW window
	/// \param pWindow GLFW window in which mouse should exist
	/// \param Vector2 The position of the mouse
	////////////////////////////////////////////////////////////
	void setMousePos(GLFWwindow *pWindow, sf::Vector2i mousepos);

	////////////////////////////////////////////////////////////
	/// \brief Updates variables/view/camera position every frame
	/// \param t time
	////////////////////////////////////////////////////////////
	void update(float t);

	////////////////////////////////////////////////////////////
	/// \brief Draw the models to the screen
	////////////////////////////////////////////////////////////
	void render();

	////////////////////////////////////////////////////////////
	/// \brief Load either a XML file or a .cfg file
	/// \param FileLocation A string location of a file
	/// \param isXML Bool which asks if file to load is a XML file or not
	////////////////////////////////////////////////////////////
	void LoadMap(string FileLocation, bool isXML);

	bool m_bWorldLoaded = false; ///< bool which equals true if a world is loaded
};
#endif  

////////////////////////////////////////////////////////////
/// \class World
///
/// This could be considered the game class of this project.
/// It pulls together many classes and ensures they work together
/// to generate the project.
/// 
/// This class sets up the camera and allows movement, creates the
/// lab and allows the creation and deletion of worlds. Renders 
/// everything using shaders and ensures it stays updated.
/// 
/// To set up this class a scene pointer should be created which
/// runs initScene() once and update + render every frame.
/// 
////////////////////////////////////////////////////////////