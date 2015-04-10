#version 400

in layout (location=0) vec3 position;
in layout (location=1) vec3 color;

uniform mat4 modelToWorld;
uniform mat4 viewToProjection;
out vec3 deColor;

void main()
{
	gl_Position = viewToProjection*modelToWorld*vec4(position, 1);
	deColor = color;
}