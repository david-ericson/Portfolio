#version 400
	
in mat3 transform;
in vec4 shadowCoord;
in vec3 normals;
in vec3 pos;
in vec3 translation;
in vec3 difColor;
in vec3 ambColor;
in vec3 specColor;
in vec3 cameraPos;
in vec3 lightPos;
in vec2 textCoord;
in float specExp;

out vec4 theFinalColor;

uniform sampler2D png;

float Linearize(float depth)
{
	float near = 0.1f;
	float far = 100.0f;
	return(2.0 * near) / (far + near - depth * (far - near));
}

void main()
{
	vec3 normal = normals;
	vec4 shadowUV = shadowCoord / shadowCoord.w;
	shadowUV = vec4((shadowUV.x+1)/2,(shadowUV.y+1)/2,(shadowUV.z+1)/2,shadowUV.w);
	float diffuseLight = dot(normal,normalize(lightPos-(pos+translation)));
	vec3 diffuseLightBrightness = clamp(diffuseLight,0,1) * difColor;

	vec3 reflectedLight = reflect(normalize(lightPos), normal);
	float specularBrightness = dot(normalize(cameraPos - (pos+translation)), (-reflectedLight));
	specularBrightness = clamp(specularBrightness, 0, 1);
	specularBrightness = pow(specularBrightness, specExp);
	vec3 specularColor = specularBrightness * specColor;
	vec3 deColor = ambColor+diffuseLightBrightness;
	float shadowValue = (texture(png, shadowUV.xy)).x;
	if(shadowValue < shadowUV.z-.0005f)
	{
		theFinalColor = vec4(ambColor,1.0f);
	}
	else
	{
		{
			theFinalColor = vec4(deColor,1.0f)+vec4(specularColor,1.0f);
		}
	}
	
}