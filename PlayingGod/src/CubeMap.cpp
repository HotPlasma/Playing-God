#include "CubeMap.h"

GLuint CubeMap::GetTexID()
{
	return texID;
}

CubeMap::CubeMap(float size, glm::vec3 position, std::string FileLocations)
{
	faces = 6;

	float CubePositions[] = {
		-size, -size,  size,
		size , -size,  size,
		size ,  size,  size,
		-size,  size,  size,
		// back
		-size, -size, -size,
		size ,-size ,-size ,
		size , size ,-size ,
		-size,  size, -size,
	};


	int CubeIndex[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,


	};

	glm::mat4 transMatrix = { 1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		position.x,position.y,position.z,1 };

	// Generate buffers

	M = transMatrix;

	GLuint buffer[2];

	gl::GenBuffers(2, buffer);

	gl::GenVertexArrays(1, &cubeVAOHandle);
	gl::BindVertexArray(cubeVAOHandle);


	// Bind position buffers
	gl::BindBuffer(gl::ARRAY_BUFFER, buffer[0]);
	gl::BufferData(gl::ARRAY_BUFFER, 3 * sizeof(CubePositions), CubePositions, gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(0);  // Vertex position

	// Bind index buffer
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, buffer[1]);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, 6 * sizeof(CubeIndex), CubeIndex, gl::STATIC_DRAW);

	gl::BindVertexArray(0);

	gl::GenTextures(1, &texID);
	gl::ActiveTexture(gl::TEXTURE0);

	gl::BindTexture(gl::TEXTURE_CUBE_MAP, texID);

	// Load images from files
	for (int i = 0; i < 6; i++)
	{
		std::string textureFile = std::string("assets/textures/SkyBoxes/") + FileLocations + std::to_string(i + 1) + ".png";
		Bitmap bmp = Bitmap::bitmapFromFile(textureFile);
		gl::TexImage2D(gl::TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, gl::RGB, bmp.width(), bmp.height(), 0, gl::RGB, gl::UNSIGNED_BYTE, bmp.pixelBuffer());


	}

	// Set Textures to cubemap
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);

	gl::BindTexture(texID, 0);

}




void CubeMap::render()
{
	gl::BindVertexArray(cubeVAOHandle);
	gl::DrawElements(gl::TRIANGLES, 6 * faces, gl::UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}