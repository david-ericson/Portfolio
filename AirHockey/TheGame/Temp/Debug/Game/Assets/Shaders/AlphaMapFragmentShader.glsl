#version 400
	
in vec2 textCoord;
out vec4 theFinalColor;

uniform sampler2D png;
uniform sampler2D alphaMap;

void main()
{
	if(vec3(texture(alphaMap, textCoord))[0] > .8)
	{
		discard;
	}
	else
	{
		theFinalColor = ((texture(png, textCoord)));
	}
}