#include "PreHeader.h"
#include "Model.h"

Model::Model()
{
	M = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
}

Model::Model(string FileLocation, string TextureLocation, glm::vec3 Position, float Rotation, glm::vec3 Scale, int MaterialID)
{
	// Constucts a model with the given variables
	sFileName = FileLocation;
	sTexture = TextureLocation;
	ModelPosition = Position;
	ModelRotation = Rotation;
	ModelScale = Scale;
	ModelMaterial = MaterialID;

	M = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
}

string Model::GetFileLocation()
{
	return sFileName;
}

GLuint Model::GetTextureLocation()
{
	return m_textureID;
}

glm::vec3 Model::GetPosition()
{
	return ModelPosition;
}

float Model::GetRotation()
{
	return ModelRotation;
}

glm::vec3 Model::GetScale()
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

void  Model::SetPosition(glm::vec3 NewPosition)
{
	ModelPosition = NewPosition;
}

void  Model::SetRotation(float NewRotation)
{
	ModelRotation = NewRotation;
}

void  Model::SetScale(glm::vec3 NewScale)
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

	// Create rotation matrix for each model

	glm::mat4 rotMatrix = { cos(glm::radians(ModelRotation)),0,sin(glm::radians(ModelRotation)),0,
		0,1,0,0,
		-sin(glm::radians(ModelRotation)),0,cos(glm::radians(ModelRotation)),0,
		0,0,0,1 };


	// Create scale matrix for each model
	glm::mat4 scaleMatrix = { ModelScale.x,0,0,0,
		0,ModelScale.y,0,0,
		0,0,ModelScale.z,0,
		0,0,0,1 };

	// Create transform matrix for each model

	glm::mat4 transMatrix = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		ModelPosition.x,ModelPosition.y,ModelPosition.z,1 };

	// Create Trasnform matrix for each model
	M = transMatrix * rotMatrix * scaleMatrix;


	positionData = m_modelReader->GetVertices();
	uvData = m_modelReader->GetTextureCoordinates();


	gl::GenBuffers(2, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint uvBufferHandle = vboHandles[1];


	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, positionData.size() * sizeof(float), positionData.data(), gl::STATIC_DRAW);

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

	bmp = Bitmap::bitmapFromFile(sTexture);
	bmp.flipVertically();
	gTexture = new Texture(bmp);
	//Set texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	GLint loc = gl::GetUniformLocation(programHandle, "tex");

	gl::Uniform1f(loc, 1);


}