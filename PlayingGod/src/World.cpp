#include "PreHeader.h"

#include "World.h"

#include <cstdio>
#include <cstdlib>

#include "ModelReader.h"


using std::string;
using std::ifstream;

void World::SetMatices(GLSLProgram * shader, mat4 model , mat4 view, mat4 projection)
{
	mat4 mv = view * model;
	shader->setUniform("ModelViewMatrix", mv);
	shader->setUniform("NormalMatrix",
		mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
	shader->setUniform("MVP", projection * mv);
	mat3 normMat = glm::transpose(glm::inverse(mat3(model)));
	shader->setUniform("M", model);
	shader->setUniform("V", view);
	shader->setUniform("P", projection);
}

World::World(sf::Vector2i windowSize)
{
	m_windowSize = windowSize;
}

void World::initScene()
{
	linkShaders();
	// Stops rendered models from being transparent
	gl::Enable(gl::DEPTH_TEST);

	LoadMap("assets/scenes/LabScene.xml", true);

	Cube = new CubeMap(1, vec3(10000,0,0), "FullMoon/Moon");

	if (!m_ThemeSong.loadFromFile("assets/sound/backgroundmusic.wav"));
	{
		sf::err() << "Failed to load music\n";
	}

	if (!m_Hello.loadFromFile("assets/sound/HelloExplorer.wav"));
	{
		sf::err() << "Failed to load music\n";
	}

	m_Sound.setBuffer(m_Hello); // Introductory voice lines
	m_Sound.play();
	
}

void World::setMousePos(GLFWwindow *Gwindow, sf::Vector2i mousepos)
{
	Window = Gwindow;
	MousePos = mousepos;
}

void World::linkShaders()
{

	try {

		// Shader which allows a cubemap to be textured
		m_SkyBox.compileShader("Shaders/skybox.vert");
		m_SkyBox.compileShader("Shaders/skybox.frag");
		m_SkyBox.link();
		m_SkyBox.validate();

		// Shader which allows first person camera and textured objects
		m_WorldShader.compileShader("Shaders/shader.vert");
		m_WorldShader.compileShader("Shaders/shader.frag");
		m_WorldShader.link();
		m_WorldShader.validate();
		

		
	}
	catch (GLSLProgramException & e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}

}

void World::update(float t)
{

	// Creates and updates camera and view using MVP

	 // Allows first person view changing with mouse movement
	sf::Vector2i WindowOrigin(getWindowSize().x / 2, getWindowSize().y / 2); // Middle of the screen

	float yAngle = (WindowOrigin - MousePos).x / 1000.0f;
	float zAngle = (WindowOrigin - MousePos).y / 1000.0f;

	glm::vec3 DistanceToLabPortal = FirstPersonView.GetCameraPos() - LabScene.ModelList.at(2).getPosition();

	glm::vec3 DistanceToWorldPortal = FirstPersonView.GetCameraPos() - CurrentWorld.m_PortalLocation;

	if (m_bWorldLoaded) // If word is loaded activate portal
	{

		// Portal collision and transportation for lab
		if (sqrtf(powf(DistanceToLabPortal.x, 2.0f) + powf(DistanceToLabPortal.z, 2.0f)) < 2) // If inside portal
		{
			FirstPersonView.setCameraPos(vec3(CurrentWorld.m_PortalLocation.x - 3, 0, CurrentWorld.m_PortalLocation.z));
			FirstPersonView.setCameraView(vec3(CurrentWorld.m_PortalLocation.x - 1.0f, 1.0f, CurrentWorld.m_PortalLocation.z - 1.0f));
		}

		// Portal collision and trasportation for world

		if (sqrtf(powf(DistanceToWorldPortal.x, 2.0f) + powf(DistanceToWorldPortal.z, 2.0f)) < 2) // If collision with a collectable mark it as collected and stop drawing it
		{
			FirstPersonView.setCameraPos(vec3(LabScene.ModelList.at(2).getPosition().x - 3, 0, LabScene.ModelList.at(2).getPosition().z));
			FirstPersonView.setCameraView(vec3(LabScene.ModelList.at(2).getPosition().x - 1.0f, 1.0f, LabScene.ModelList.at(2).getPosition().z - 1.0f));
		}
	}
	
	 V = glm::lookAt(glm::vec3(FirstPersonView.GetCameraPos().x, FirstPersonView.GetCameraPos().y, FirstPersonView.GetCameraPos().z), // Camera position
		glm::vec3(FirstPersonView.GetCameraView().x, FirstPersonView.GetCameraView().y, FirstPersonView.GetCameraView().z), // Looking at
		glm::vec3(0, 1, 0)); // Up


	P = glm::perspective(60.0f, (float)m_windowSize.x / m_windowSize.y, 1.f, 5000.f); // Sets FOV and vision culls

	// Repeat music once it ends
	if (m_Sound.getStatus() != sf::Sound::Playing)
	{
		m_Sound.setBuffer(m_ThemeSong);
		m_Sound.setVolume(40);
		m_Sound.play();
	}

	// Allows movement using WASD and mouse
	FirstPersonView.ProcessUserInput(yAngle, zAngle); // Send mouse position data to be processed in order to move camera


	// Send data to shader for processing
	for (int i = 0; i < CurrentWorld.ModelList.size(); i++)
	{
		if (CurrentWorld.ModelList.at(i).isCollectable()) // check if collectable
		{
			if (!CurrentWorld.ModelList.at(i).getCollected()) // if collectable then slowly rotate and bob up and down
			{
				glm::vec3 distance = FirstPersonView.GetCameraPos() - CurrentWorld.ModelList.at(i).getPosition(); // Work out distance between robot and a collectable

				if (sqrtf(powf(distance.x, 2.0f) + powf(distance.z, 2.0f)) < 5) // If collision with a collectable mark it as collected and stop drawing it
				{
					CurrentWorld.ModelList.at(i).setCollected(true);
				}
			}
		}
	}
	
}


void World::render()
{
	// Check depth and clear last frame
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	m_WorldShader.use(); // Generic shader for drawing world
	SetMatices(&m_WorldShader, glm::mat4(1.0f), V, P);
	for (int i = 0; i < LabScene.ModelList.size() - 1; i++)
	{
		LabScene.ModelList.at(i).buffer();
		m_WorldShader.setUniform("M", LabScene.ModelList.at(i).m_M);
		
		gl::DrawArrays(gl::TRIANGLES, 0, LabScene.ModelList.at(i).positionData.size());
	}

	//Create portal
	if (m_bWorldLoaded)
	{
		LabScene.ModelList.at(4).buffer();
		m_WorldShader.setUniform("M", LabScene.ModelList.at(4).m_M);

		gl::DrawArrays(gl::TRIANGLES, 0, LabScene.ModelList.at(4).positionData.size());
	}
	// Render all models in current scene
	for (int j = 0; j < CurrentWorld.ModelList.size(); j++)
	{
		if (!CurrentWorld.ModelList.at(j).getCollected())
		{
			CurrentWorld.ModelList.at(j).buffer();
			m_WorldShader.setUniform("M", CurrentWorld.ModelList.at(j).m_M);
			gl::DrawArrays(gl::TRIANGLES, 0, CurrentWorld.ModelList.at(j).positionData.size());
		}
	}

	// Skybox
	m_SkyBox.use(); // Shader for turning a cubemap into a beleiveable skybox
	SetMatices(&m_SkyBox, Cube->M, V, P);
	Cube->render();
	
}

void World::LoadMap(string FileLocation, bool isXML)
{
	if (isXML)
	{
		LabScene = SceneReader(FileLocation);
		for (int i = 0; i < LabScene.ModelList.size(); i++)
		{
			LabScene.ModelList[i].DrawModel();
		}
	}
	else
	{
		m_bWorldLoaded = true;
		CurrentWorld = WorldReader(FileLocation);

		for (int i = 0; i < CurrentWorld.ModelList.size(); i++)
		{
			CurrentWorld.ModelList[i].DrawModel();
			Cube = CurrentWorld.m_SkyBox;
		}
	}
}