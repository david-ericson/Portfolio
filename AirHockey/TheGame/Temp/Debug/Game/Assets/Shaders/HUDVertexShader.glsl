#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec2 uv;

uniform mat4 modelToWorld;
uniform mat4 viewToProjection;

out vec2 textCoord;

void main()
{
	gl_Position = modelToWorld*vec4(position, 1);
	textCoord = uv;
}
//Render shadow map
//On your second pass add a checkbox to show what it is sampling vs viewing. Ex. Drawing teapot, no shadow shows because camera pointed wrong direction.
//Set color to map.z???

