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
#pragma once

#include <string>
#include "ModelReader.h"
#include <Bitmap.h>
#include <Texture.h>

using namespace std;

class Model
{
private:
	string m_sName; // A moniker for each model
	string m_sFileName; // File location of the obj
	string m_sTexture; // File location of the texture
	int m_iMaterial; // Which material the model with have. Different integers are different materials.

	glm::vec3 m_position; // Position of Model
	glm::vec3 m_rotation; // Rotation of Model
	glm::vec3 m_scale; // Scale of Model

	bool m_bCollectable = false; // is the model a collectable?
	bool m_bCollected = false; // has the collectable been collected?

	GLuint m_textureID; // ID of the texture
	

	GLuint m_programHandle;
	tex::Texture *m_pTexture;
	

	GLuint m_vboHandles[2];
	GLuint m_vbo;
	GLuint m_vaoHandle;

	

public:
	Model(); // Constructor
	Model(string FileLocation, string TextureLocation, glm::vec3 Position, glm::vec3 Rotation, glm::vec3, int MaterialID); // Full constructor
	string getName() { return m_sName; }; // Returns moniker
	string getFileLocation() { return m_sFileName; }; // Returns location of obj
	GLuint getTextureLocation() { return m_textureID; }; // Returns location of texture
	glm::vec3 getPosition() { return m_position; }; // Returns rosition of model
	glm::vec3 getRotation() { return m_rotation; }; // Returns rotation of model
	glm::vec3 getScale() { return m_scale; }; // Returns scale of model
	bool isCollectable() { return m_bCollectable; }; // Check if a model is a collectable
	bool getCollected() { return m_bCollected; }; // Check if a collectable has been collected
	int getMaterial() { return m_iMaterial; }; // Returns materialID

	void setCollectable();
	void setCollected(bool bCollected); // Set collected or not collected for a collectable
	void setName(string sNewName);
	void setTexture(GLuint textureID); // Set texture ID
	void setFileLocation(string sNewLocation); // Set obj location
	void setTextureLocation(string sNewLocation); // Set texture location
	void setPosition(glm::vec3 newPosition); // Set model position
	void setRotation(glm::vec3 newRotation); // Set model rotation
	void setScale(glm::vec3 newScale); // Set model scale
	void setMaterial(int iMaterialID); // Set model MaterialID
	void buffer();

	vector<float> positionData;
	vector<float> uvData;

	ModelReader* m_pModelReader; // Model Reader for the render the model
	Bitmap m_bmp = Bitmap::bitmapFromFile("assets/textures/Default.bmp"); // Texture for model. Has a default texture to avoid hard crash if texture fails to load.

	glm::mat4 m_M;

	void LoadModel(string Model); // Loads in the model to be rendered
	void LoadTexture(GLuint Texture);
	void DrawModel(bool drawWithNormals, bool drawWithTexture); // Draws model


};

