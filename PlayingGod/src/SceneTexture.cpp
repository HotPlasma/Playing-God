#include "stdafx.h"

#include "SceneTexture.h"

#include <cstdio>
#include <cstdlib>



#include <iostream>
#include <fstream>
using std::ifstream;
#include <sstream>
#include <string>
using std::string;


//#define SINGLE_BUFFER

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


SceneTexture::SceneTexture() { }

void SceneTexture::initScene()
{
	//////////////////////////////////////////////////////
	/////////// Vertex shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file
	ifstream inFile("shaders/basic.vert");
	if (!inFile) {
		fprintf(stderr, "Error opening file: shader/basic.vert\n");
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	string codeStr(code.str());

	// Create the shader object
	GLuint vertShader = gl::CreateShader(gl::VERTEX_SHADER);
	if (0 == vertShader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object
	const GLchar* codeArray[] = { codeStr.c_str() };
	gl::ShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(vertShader);

	// Check compilation status
	GLint result;
	gl::GetShaderiv(vertShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(vertShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment shader //////////////////////////
	//////////////////////////////////////////////////////

	// Load contents of file into shaderCode here
	ifstream fragFile("shaders/basic.frag");
	if (!fragFile) {
		fprintf(stderr, "Error opening file: shader/basic.frag\n");
		exit(1);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Create the shader object
	GLuint fragShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (0 == fragShader) {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
	}

	// Load the source code into the shader object
	codeArray[0] = codeStr.c_str();
	gl::ShaderSource(fragShader, 1, codeArray, NULL);

	// Compile the shader
	gl::CompileShader(fragShader);

	// Check compilation status
	gl::GetShaderiv(fragShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Fragment shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(fragShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	linkMe(vertShader, fragShader);

	/////////////////// Create the VBO ////////////////////
	float positionData[] = {
		//-0.8f, -0.8f, 0.0f,
		//0.8f, -0.8f, 0.0f,
		//0.0f,  0.8f, 0.0f 

	-1.0f, -0.5f, 0.0f,
	1.0f, -0.5f, 0.0f,
	-1.0f, 0.5f, 0.0f,
	1.0f, 0.5f, 0.0f
	};

	float uvData[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f
		/*0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f */};

	


	/*float colourData[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,



	};*/



	int indicesData[] = {
		0, 1, 2,
		3, 1 ,2


	};


	fRot = 0;
	indexSize = sizeof(indicesData);



#ifdef SINGLE_BUFFER
	// Create and set-up the vertex array object using an interlaced buffer
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	//Create and load buffer
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, 3 * 6 * sizeof(GLfloat), NULL, gl::STATIC_DRAW);
	gl::BufferSubData(gl::ARRAY_BUFFER, 0, 3 * 3 * sizeof(GLfloat), positionData);
	gl::BufferSubData(gl::ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), 3 * 3 * sizeof(GLfloat), colourData);


	//Get the VertexPosition attrib handle
	GLuint loc1;
	loc1 = gl::GetAttribLocation(programHandle, "VertexPosition");
	gl::EnableVertexAttribArray(loc1);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, 0);

	//Get the VertexColour attrib handle
	GLuint loc2;
	loc2 = gl::GetAttribLocation(programHandle, "VertexColour");
	gl::EnableVertexAttribArray(loc2);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc2, 3, gl::FLOAT, FALSE, 0, BUFFER_OFFSET(3 * 3 * sizeof(GLfloat)));

#else

	// Create and populate the buffer objects using separate buffers
	// GLuint vboHandles[2];
	gl::GenBuffers(3, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint uvBufferHandle = vboHandles[1];

	GLuint index_buffer = vboHandles[2];

	//gl::GenBuffers(1, &index_buffer);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, index_buffer);

	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, indexSize, indicesData, gl::STATIC_DRAW);


	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(positionData) * sizeof(float), positionData, gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(uvData) * sizeof(float), uvData, gl::STATIC_DRAW);


	// Create and set-up the vertex array object
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::EnableVertexAttribArray(1);  // Vertex color

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

	gl::BindBuffer(gl::ARRAY_BUFFER, uvBufferHandle);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

	//Load the texture
	Bitmap bmp = Bitmap::bitmapFromFile("./assets/Flag_Of_Wales.png");
	bmp.flipVertically();
	gTexture = new Texture(bmp);
	//Set texture
	gl::ActiveTexture(gl::TEXTURE0);
	gl::BindTexture(gl::TEXTURE_2D, gTexture->object());
	GLint loc = gl::GetUniformLocation(programHandle, "tex");

	gl::Uniform1f(loc, 0);

#endif



}

void SceneTexture::linkMe(GLint vertShader, GLint fragShader)
{


	// Create the program object
	programHandle = gl::CreateProgram();
	if (0 == programHandle) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}


	// Attach the shaders to the program object
	gl::AttachShader(programHandle, vertShader);
	gl::AttachShader(programHandle, fragShader);

	// Link the program
	gl::LinkProgram(programHandle);

	// Check for successful linking
	GLint status;
	gl::GetProgramiv(programHandle, gl::LINK_STATUS, &status);
	if (FALSE == status) {

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		gl::GetProgramiv(programHandle, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetProgramInfoLog(programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	else {
		gl::UseProgram(programHandle);
	}

}

void SceneTexture::update(float t)
{
	//M = { 1,0,0,0,
	//0,1,0,0,
	//0,0,1,0,
	//0,0,0,1 };

	fRot += 0.01;

	glm::mat4 rotMatrix = { cos(fRot),0,-sin(fRot),0,
							0,1,0,0,
							sin(fRot),0,cos(fRot),0,
							0,0,0,1 };

	glm::mat4 scaleMatrix = { 1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1 };

	glm::mat4 transMatrix = { 1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1 };

	M = scaleMatrix * transMatrix * rotMatrix;

	glm::mat4 V = glm::lookAt(glm::vec3(0, 0, 5), // Camera position
		glm::vec3(0, 0, 0), // Looking at
		glm::vec3(0, 1, 0)); // Up

	glm::mat4 P = glm::perspective(35.0f, 1.0f, 0.1f, 100.f);

	GLuint modelMatrixID = gl::GetUniformLocation(programHandle, "mModel");
	GLuint viewMatrixID = gl::GetUniformLocation(programHandle, "mView");
	GLuint projectionMatrixID = gl::GetUniformLocation(programHandle, "mProjection");

	gl::UniformMatrix4fv(modelMatrixID, 1, gl::FALSE_, glm::value_ptr(M));
	gl::UniformMatrix4fv(viewMatrixID, 1, gl::FALSE_, glm::value_ptr(V));
	gl::UniformMatrix4fv(projectionMatrixID, 1, gl::FALSE_, glm::value_ptr(P));
}

void SceneTexture::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT);

	gl::BindVertexArray(vaoHandle);
	GLuint IndexBufferHandle = vboHandles[2];
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, IndexBufferHandle);
	//gl::DrawArrays(gl::TRIANGLES, 0, (3*4) );
	gl::DrawElements(gl::TRIANGLES, indexSize / sizeof(GLuint), gl::UNSIGNED_INT, NULL);

}

void SceneTexture::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
}
