#version 400

in layout(location=0) vec3 position;

uniform mat4 modelToWorld;
uniform mat4 viewToProjection;
uniform vec3 dominantColor;

out vec3 deColor;

void main()
{
	gl_Position = viewToProjection*modelToWorld*vec4(position, 1);
	deColor = dominantColor;
}