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
	finalColor = texture(png,vec2(textCoord.x, textCoord.y));
}

