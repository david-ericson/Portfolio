#version 400
uniform sampler2D png;
uniform sampler2D realTexture;
uniform float tolerance;

in vec2 textCoord;
in float index;

out vec4 finalColor;



void main()
{
	vec4 color = texture(realTexture, textCoord);
	int theIndex = int(index+.01f);
	color = vec4(color[theIndex],color[theIndex],color[theIndex],1.0f);
	if(color.x >= tolerance && tolerance != 1.0f)
	{
		discard;
	}
	float low = .85*tolerance;
	if(color.x > low && tolerance != 1.0f)
	{
		color = vec4(1.0f, (tolerance-color.x)/(tolerance-low), 0, 1.0f);
	}
	finalColor = color;
}