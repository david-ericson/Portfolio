#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec2 uv;

uniform mat4 modelToWorld;
uniform mat4 viewToProjection;
uniform vec3 dominantColor;

out vec3 deColor;
out vec2 textCoord;

void main()
{
	gl_Position = viewToProjection*modelToWorld*vec4(position, 1);
	deColor = dominantColor;
	textCoord = uv;
}