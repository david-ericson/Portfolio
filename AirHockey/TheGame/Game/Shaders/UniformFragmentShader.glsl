#version 400
	
in vec3 deColor;
out vec4 theFinalColor;

void main()
{
	theFinalColor = vec4(deColor,1.0f);
}
	