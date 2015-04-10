#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec2 uv;	

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 cameraPosition;
uniform mat4 viewToProjection;
uniform mat4 modelToWorld;
uniform vec3 lightPosition;
uniform float specExponent;

out vec3 pos;
out vec3 translation;
out vec3 difColor;
out vec3 specColor;
out vec3 ambColor;
out vec3 cameraPos;
out vec3 lightPos;
out vec2 textCoord;
out float specExp;

void main()
{
	gl_Position = viewToProjection*modelToWorld * vec4(position.x, position.y,position.z, 1);
	translation = vec3(modelToWorld[3][0], modelToWorld[3][1], modelToWorld[3][2]);
	difColor = diffuseColor;
	ambColor = ambientColor;
	specColor = specularColor;
	cameraPos = cameraPosition;
	lightPos = lightPosition;
	textCoord = uv;
	pos = position;
	specExp = specExponent;
}