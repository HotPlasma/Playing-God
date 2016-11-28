#version 430

in vec4 vertPosition;

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 fragTexCoord;

out vec2 texCoord;


uniform mat4 mModel;        //Matrix to convert to world 
   //coordinate system
uniform mat4 mView;         //Matrix to convert into 
   //camera coordinate system
uniform mat4 mProjection;   //Matrix to convert to 
   //normalised screen 
   //coordinates

in vec3  vertColour;
out vec3 Colour;

void main()
{
texCoord = fragTexCoord;

//Transform from local to world to camera to NDCs
gl_Position = mProjection * mView * mModel * vertPosition;
}
