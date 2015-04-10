#version 400

in vec3 deColor;
out vec4 finalColor;

void main()
{
	finalColor = vec4(deColor,1.0f);
}