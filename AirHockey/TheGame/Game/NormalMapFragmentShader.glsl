#version 400
	
in mat3 transform;
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
in float withDif;
in float withNM;
in float withOcc;

out vec4 theFinalColor;

uniform sampler2D png;
uniform sampler2D AOMap;
uniform sampler2D normalMap;

void main()
{
	vec3 theNormalMap = (vec3(texture(normalMap, textCoord)));
	vec3 normal = vec3(2*(theNormalMap.x-.5f),2*(theNormalMap.y-.5f),2*(theNormalMap.z-.5f));
	vec3 test = normal;
	normal = (withNM > 0)?transform*normal:normals;
	
	float diffuseLight = dot(normal,normalize(lightPos-(pos+translation)));
	vec3 diffuseLightBrightness = clamp(diffuseLight,0,1) * difColor;

	vec3 reflectedLight = reflect(normalize(lightPos), normal);
	float specularBrightness = dot(normalize(cameraPos - (pos+translation)), (-reflectedLight));
	specularBrightness = clamp(specularBrightness, 0, 1);
	specularBrightness = pow(specularBrightness, specExp);
	vec3 specularColor = specularBrightness * specColor;
	vec3 deColor = ambColor+diffuseLightBrightness;
	float AOFactor = (withOcc>0)? texture(AOMap, textCoord).x:1.0f;
	deColor = AOFactor * deColor;
	vec4 theTexture = (withDif > 0)?(texture(png, textCoord)):vec4(1.0f,1.0f,1.0f,1.0f);
	{
		theFinalColor = (vec4(deColor,1.0f) *theTexture +vec4(specularColor,1.0f));
	}
}