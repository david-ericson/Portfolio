#version 400

in vec3 reflectedEye;

uniform samplerCube cubeMap;

out vec4 theFinalColor;

void main()
{
	theFinalColor = vec4(vec3(texture(cubeMap, reflectedEye)),1.0f);
}