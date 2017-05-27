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
	string m_sName; ///< A string which is a moniker for each model
	string m_sFileName; ///< A string which is a file location of the obj
	string m_sTexture; ///< A string holding the file location of the texture
	int m_iMaterial; ///< A integer which represents the material the model with have. Different integers are different materials.

	glm::vec3 m_position; ///< vector3 representing the position of the Model
	glm::vec3 m_rotation; ///< vector3 representing the rotation of the Model
	glm::vec3 m_scale; ///< vector3 representing the scale of theModel

	bool m_bCollectable = false; ///< boolean which equates to true if the model is a collectable
	bool m_bCollected = false; ///< boolean which equates to true if the collectable has been collected

	GLuint m_textureID; ///< GluInteger which represents the ID of the texture
	

	GLuint m_programHandle; ///< GluInteger for the program handle
	tex::Texture *m_pTexture; ///< Pointer to a texture
	

	GLuint m_vboHandles[2]; ///< vbo handles one for verticies and the other for UV coordinates
	GLuint m_vbo; ///< GL vbo for drawing models
	GLuint m_vaoHandle; ///< VAO handle for drawing

	

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Allows creation of a model
	///
	////////////////////////////////////////////////////////////
	Model(); 

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs a model from a file location, texture location, desired world position, desired rotation, desired scale and the models ID
	///
	/// \param FileLocation X Position of button
	/// \param TextureLocation Y Position of button
	/// \param Position int Texture assigned to button
	/// \param Rotation TextureLoader holding textures for button
	/// \param Scale Vector of strings with all potential options
	/// \param MaterialID
	///
	/// \see m_pModelReader
	///
	////////////////////////////////////////////////////////////
	Model(string FileLocation, string TextureLocation, glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale, int MaterialID);

	////////////////////////////////////////////////////////////
	/// \brief Gets string m_sName
	///
	/// \return Name of model
	////////////////////////////////////////////////////////////
	string getName() { return m_sName; };

	////////////////////////////////////////////////////////////
	/// \brief Gets string m_sFileName
	///
	/// \return Location of model
	////////////////////////////////////////////////////////////
	string getFileLocation() { return m_sFileName; };

	////////////////////////////////////////////////////////////
	/// \brief Gets GLuinteger m_textureID
	///
	/// \return TextureID of model
	////////////////////////////////////////////////////////////
	GLuint getTextureLocation() { return m_textureID; };

	////////////////////////////////////////////////////////////
	/// \brief Gets vector3 m_position
	///
	/// \return World position of model
	////////////////////////////////////////////////////////////
	glm::vec3 getPosition() { return m_position; };

	////////////////////////////////////////////////////////////
	/// \brief Gets vector3 m_rotation
	///
	/// \return World rotation of model
	////////////////////////////////////////////////////////////
	glm::vec3 getRotation() { return m_rotation; };

	////////////////////////////////////////////////////////////
	/// \brief Gets vector3 m_scale
	///
	/// \return Relative scale of model
	////////////////////////////////////////////////////////////
	glm::vec3 getScale() { return m_scale; };

	////////////////////////////////////////////////////////////
	/// \brief Gets bool m_bCollectable
	///
	/// \return Check if model is a collectable
	////////////////////////////////////////////////////////////
	bool isCollectable() { return m_bCollectable; };

	////////////////////////////////////////////////////////////
	/// \brief Gets bool m_bCollected
	///
	/// \return Checks if model has been collected
	////////////////////////////////////////////////////////////
	bool getCollected() { return m_bCollected; };

	////////////////////////////////////////////////////////////
	/// \brief Gets int m_iMaterial
	///
	/// \return Return material value
	////////////////////////////////////////////////////////////
	int getMaterial() { return m_iMaterial; };


	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_bCollectable to true
	///
	////////////////////////////////////////////////////////////
	void setCollectable(bool newSetting);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_bCollected 
	/// /param New setting for m_bCollected
	////////////////////////////////////////////////////////////
	void setCollected(bool bCollected);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_sName 
	/// /param New setting for m_sName
	////////////////////////////////////////////////////////////
	void setName(string sNewName);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_TextureID 
	/// /param New setting for m_TextureID
	////////////////////////////////////////////////////////////
	void setTexture(GLuint textureID);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_sFileName 
	/// /param New setting for m_sFileName 
	////////////////////////////////////////////////////////////
	void setFileLocation(string sNewLocation);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's texture location
	/// /param New setting for texture location
	////////////////////////////////////////////////////////////
	void setTextureLocation(string sNewLocation);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_position
	/// /param New setting for m_position
	////////////////////////////////////////////////////////////
	void setPosition(glm::vec3 newPosition);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_rotation
	/// /param New setting for m_rotation
	////////////////////////////////////////////////////////////
	void setRotation(glm::vec3 newRotation);

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_scale
	/// /param New setting for m_scale
	////////////////////////////////////////////////////////////
	void setScale(glm::vec3 newScale); 

	////////////////////////////////////////////////////////////
	/// \brief Sets model's m_iMaterial
	/// /param New setting for m_iMaterial
	////////////////////////////////////////////////////////////
	void setMaterial(int iMaterialID);

	////////////////////////////////////////////////////////////
	/// \brief Sets up personal model matrix so multiple models can be loaded in different locations
	////////////////////////////////////////////////////////////
	void buffer();

	vector<float> positionData; ///< The verticies of the model
	vector<float> uvData; ///< The UV coordinates of the model

	ModelReader* m_pModelReader; ///< Model Reader for the render of the model
	Bitmap m_bmp = Bitmap::bitmapFromFile("assets/textures/Default.bmp"); ///< Texture for model. Has a default texture to avoid hard crash if texture fails to load.

	glm::mat4 m_M; ///< Model's personal model matrix

	////////////////////////////////////////////////////////////
	/// \brief Loads in current model
	/// /param Model Model to be loaded
	////////////////////////////////////////////////////////////
	void LoadModel(string Model);

	////////////////////////////////////////////////////////////
	/// \brief Loads in texture to model
	/// /param Texture to be loaded
	////////////////////////////////////////////////////////////
	void LoadTexture(GLuint Texture);

	////////////////////////////////////////////////////////////
	/// \brief Draws model to world
	////////////////////////////////////////////////////////////
	void DrawModel();


};

////////////////////////////////////////////////////////////
/// \class Model
///
/// Model is a class which stores all the required attributes of 
/// a model in order to store them efficently. It also ensures 
/// that all its models are ready to be drawn by running their
/// .obj through the ModelReader and their texture through the 
/// bitmap class. 
/// 
/// To create a model it would a .obj file location, a .bmp texture location,
/// a scale, position and rotation. Everything else is optional but can 
/// be required for cirtain functionality e.g. collectable bool set if the
/// item is a collectable. 
///
/// The most effective use of this class is to create a vector 
/// of models and therefore be able to manage all the models
/// easily and efficently.
/// 
////////////////////////////////////////////////////////////