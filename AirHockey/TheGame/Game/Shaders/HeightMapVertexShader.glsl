#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec2 uv;
in layout(location=2) vec3 normal;

uniform mat4 modelToWorld;
uniform mat4 viewToProjection;
uniform float heightMapIndex;
uniform float ripple;
uniform sampler2D png;

out vec2 textCoord;
out float index;

void main()
{
	vec4 textColor = texture(png, uv);
	int value = int(heightMapIndex);
	vec3 newPosition = vec3(0, textColor[value]*ripple,textColor[value]*ripple);
	newPosition *= normal;
	gl_Position = viewToProjection*modelToWorld*vec4(position+newPosition, 1);
	index = heightMapIndex;
	textCoord = uv;
}