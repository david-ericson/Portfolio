#version 400

in vec3 cubeMapUVS;

uniform samplerCube cubeMap;

out vec4 theFinalColor;

void main()
{
	theFinalColor = (texture(cubeMap, cubeMapUVS));
}