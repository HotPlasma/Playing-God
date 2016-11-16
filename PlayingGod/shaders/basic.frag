#version 430

uniform sampler2D tex;
in vec2 texCoord;
out vec4 FragColour;
//in vec3 Colour;
//layout (location=0) out vec4 FragColour;

void main()
{
	FragColour = texture(tex,texCoord);
}
