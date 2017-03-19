#include "PreHeader.h"
#include "Model.h"

Model::Model()
{
	m_M = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
}

Model::Model(string sFileLocation, string sTextureLocation, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, int iMaterialID)
{
	// Constucts a model with the given variables
	m_sFileName = sFileLocation;
	m_sTexture = sTextureLocation;
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	m_iMaterial = iMaterialID;

	m_M = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
}
void Model::setCollectable()
{
	m_bCollectable = true;
}

void Model::setCollected(bool bCollected)
{
	m_bCollected = bCollected;
}

void Model::setName(string sNewName)
{
	m_sName = sNewName;
}

void Model::setFileLocation(string sNewLocation)
{
	m_sFileName = sNewLocation;
}

void  Model::setTextureLocation(string sNewLocation)
{
	m_sTexture = sNewLocation;
}

void  Model::setPosition(glm::vec3 newPosition)
{
	m_position = newPosition;
}

void  Model::setRotation(glm::vec3 newRotation)
{
	m_rotation = newRotation;
}

void  Model::setScale(glm::vec3 newScale)
{
	m_scale = newScale;
}

void Model::setTexture(GLuint textureID)
{
	m_textureID = textureID;
}

void Model::setMaterial(int iMaterial)
{
	m_iMaterial = iMaterial;
}


void Model::LoadModel(string Model)
{
	m_pModelReader = new ModelReader(Model);

	m_bmp = Bitmap::bitmapFromFile(m_sTexture);
	m_bmp.flipVertically();
	m_pTexture = new tex::Texture(m_bmp);
	//Set texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, m_pTexture->object());
	GLint loc = gl::GetUniformLocation(m_programHandle, "tex");

	gl::Uniform1f(loc, 1);
}

void Model::LoadTexture(GLuint Texture)
{
	m_bmp = Bitmap::bitmapFromFile(m_sTexture);
	m_bmp.flipVertically();
	m_pTexture = new tex::Texture(m_bmp);
	//Set texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, m_pTexture->object());
	GLint loc = gl::GetUniformLocation(m_programHandle, "tex");

	gl::Uniform1f(loc, 1);
}

void Model::buffer()
{
	gl::BindVertexArray(m_vaoHandle);
	gl::BindTexture(gl::TEXTURE_2D, m_pTexture->object());
	
}

void Model::DrawModel(bool drawWithNormals, bool drawWithTexture)
{

	/*glm::mat4 xRotMatrix = { cos(m_rotation.x),0,-sin(m_rotation.x),0,
		0,1,0,0,
		sin(m_rotation.x),0,cos(m_rotation.x),0,
		0,0,0,1 };

	glm::mat4 yRotMatrix = { cos(m_rotation.y),0,sin(m_rotation.y),0,
		0,1,0,0,
		-sin(m_rotation.y),0,cos(m_rotation.y),0,
		0,0,0,1 };

	glm::mat4 zRotMatrix = { cos(m_rotation.z),0,-sin(m_rotation.z),0,
		0,1,0,0,
		sin(m_rotation.z),0,cos(m_rotation.z),0,
		0,0,0,1 };


	glm::mat4 rotMatrix = xRotMatrix * yRotMatrix * zRotMatrix;*/

	glm::mat4 rotMatrix = glm::mat4(1.0f);
	rotMatrix = glm::rotate(rotMatrix, m_rotation.x, glm::vec3(1, 0, 0));
	rotMatrix = glm::rotate(rotMatrix, m_rotation.y, glm::vec3(0, 1, 0));
	rotMatrix = glm::rotate(rotMatrix, m_rotation.z, glm::vec3(0, 0, 1));

	glm::mat4 scaleMatrix = { m_scale.x,0,0,0,
		0,m_scale.y,0,0,
		0,0,m_scale.z,0,
		0,0,0,1 };

	// Create transform matrix for each model

	glm::mat4 transMatrix = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		m_position.x,m_position.y,m_position.z,1 };

	// Create Trasnform matrix for each model
	m_M = transMatrix * rotMatrix * scaleMatrix;


	positionData = m_pModelReader->GetVertices();
	uvData = m_pModelReader->GetTextureCoordinates();


	gl::GenBuffers(2, m_vboHandles);
	GLuint positionBufferHandle = m_vboHandles[0];
	GLuint uvBufferHandle = m_vboHandles[1];


	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, positionData.size() * sizeof(float), positionData.data(), gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, uvData.size() * sizeof(float), uvData.data(), gl::STATIC_DRAW);



	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &m_vaoHandle);
	gl::BindVertexArray(m_vaoHandle);

	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::EnableVertexAttribArray(1);  // Vertex color

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);


	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

	gl::BindVertexArray(m_vaoHandle);

	


}