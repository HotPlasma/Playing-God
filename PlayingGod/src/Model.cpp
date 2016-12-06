#include "stdafx.h"
#include "Model.h"

Model::Model()
{

}

Model::Model(string FileLocation, string TextureLocation, sf::Vector3f Position, sf::Vector3f Rotation, sf::Vector3f Scale, int MaterialID)
{
	// Constucts a model with the given variables
	sFileName = FileLocation;
	sTexture = TextureLocation;
	ModelPosition = Position;
	ModelRotation = Rotation;
	ModelScale = Scale;
	ModelMaterial = MaterialID;
}

string Model::GetFileLocation()
{
	return sFileName;
}

GLuint Model::GetTextureLocation()
{
	return m_textureID;
}

sf::Vector3f Model::GetPosition()
{
	return ModelPosition;
}

sf::Vector3f Model::GetRotation()
{
	return ModelRotation;
}

sf::Vector3f Model::GetScale()
{
	return ModelScale;
}

int Model::GetMaterial()
{
	return ModelMaterial;
}



void Model::SetFileLocation(string NewLocation)
{
	sFileName = NewLocation;
}

void  Model::SetTextureLocation(string NewLocation)
{
	sTexture = NewLocation;
}

void  Model::SetPosition(sf::Vector3f NewPosition)
{
	ModelPosition = NewPosition;
}

void  Model::SetRotation(sf::Vector3f NewRotation)
{
	ModelRotation = NewRotation;
}

void  Model::SetScale(sf::Vector3f NewScale)
{
	ModelScale = NewScale;
}

void Model::SetTexture(GLuint TextureID)
{
	m_textureID = TextureID;
}

void Model::SetMaterial(int Material)
{
	ModelMaterial = Material;
}

void Model::LoadModel(string Model)
{
	m_modelReader = new ModelReader(Model);
}

void Model::Buffer()
{
	gl::BindVertexArray(vaoHandle);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	
}

void Model::DrawModel(bool drawWithNormals, bool drawWithTexture)
{

	//float positionData[] = {
	//	-1.0f, -0.5f, 0.0f,
	//	1.0f, -0.5f, 0.0f,
	//	-1.0f, 0.5f, 0.0f,
	//	1.0f, 0.5f, 0.0f
	//};

	positionData = m_modelReader->GetVertices();
	uvData = m_modelReader->GetTextureCoordinates();


	gl::GenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint uvBufferHandle = vboHandles[1];


	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, positionData.size() * sizeof(float), positionData.data(), gl::STATIC_DRAW);
	//gl::BindBuffer(gl::ARRAY_BUFFER, 0);

	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, uvData.size() * sizeof(float), uvData.data(), gl::STATIC_DRAW);



	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::EnableVertexAttribArray(1);  // Vertex color

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);


	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

	gl::BindVertexArray(vaoHandle);

	
	//GLuint IndexBufferHandle = vboHandles[2];
	//gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
	//Load the texture
	bmp = Bitmap::bitmapFromFile(sTexture);
	bmp.flipVertically();
	gTexture = new Texture(bmp);
	//Set texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	GLint loc = gl::GetUniformLocation(programHandle, "tex");

	gl::Uniform1f(loc, 1);


}