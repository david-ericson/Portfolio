#version 400
	

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
uniform sampler2D normalMap;

void main()
{
	vec3 normalMap = (vec3(texture(normalMap, textCoord)));
	vec3 normal = vec3(2*(normalMap.x-.5f),2*(normalMap.y-.5f),2*(normalMap.z-.5f));

	float diffuseLight = dot(normal,normalize(lightPos-(pos+translation)));

	vec3 diffuseLightBrightness = clamp(diffuseLight,0,1) * difColor;

	vec3 reflectedLight = reflect(normalize(lightPos), normal);
	float specularBrightness = dot(normalize(cameraPos - (pos+translation)), (-reflectedLight));
	specularBrightness = clamp(specularBrightness, 0, 1);
	specularBrightness = pow(specularBrightness, specExp);
	vec3 specularColor = specularBrightness * specColor;
	vec3 deColor = ambColor+diffuseLightBrightness;
	{
		theFinalColor = vec4(deColor,1.0f) * (texture(png, textCoord))+vec4(specularColor,1.0f);
		//theFinalColor = vec4(cameraPos.x,cameraPos.y,cameraPos.z,1.0f);
	}
}