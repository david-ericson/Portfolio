#version 400

in vec2 textCoord;
out vec4 finalColor;

uniform sampler2D png;

float Linearize(float depth)
{
	float near = 0.1f;
	float far = 100.0f;

	return(2.0 * near) / (far + near - depth * (far - near));
}

void main()
{
	float newTextCoordx = -1.0f*(textCoord.x - .5f)+.5f;
	vec3 color = (vec3(texture2D(png, textCoord)));
	float value = Linearize(color.x);
	finalColor = vec4(value, value, value, 1.0f);
	finalColor = (texture(png,vec2(textCoord.x, textCoord.y)));
	if(finalColor.a < .75f)
	{
		finalColor = vec4(.25f,.25f,.25f,1.0f);
	}
}

