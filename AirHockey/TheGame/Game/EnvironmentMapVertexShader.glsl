#version 400

in layout(location = 0) vec3 position;
in layout(location = 2) vec3 normal;

uniform mat4 viewToProjection;
uniform mat4 modelToWorld;
uniform vec3 eyePosition;

out vec3 reflectedEye;

void main()
{
	gl_Position = viewToProjection*modelToWorld*vec4(position,1.0f);
	vec3 eyeDirection = normalize(position - eyePosition);
	reflectedEye = reflect(eyeDirection, normal);
}