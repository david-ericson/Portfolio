#version 400

in layout(location=0) vec3 position;
in layout(location=1) vec2 uv;	
in layout(location=2) vec3 normal;
in layout(location=3) vec4 tangent;


uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 cameraPosition;
uniform mat4 viewToProjection;
uniform mat4 modelToWorld;
uniform vec3 lightPosition;
uniform vec3 scale;
uniform float specExponent;
uniform float withDiffuse;
uniform float withNormalMap;
uniform float withOcclusion;
uniform mat4 rotation;

out mat3 transform;
out vec3 normals;
out vec3 pos;
out vec3 translation;
out vec3 difColor;
out vec3 specColor;
out vec3 ambColor;
out vec3 cameraPos;
out vec3 lightPos;
out vec2 textCoord;
out float specExp;
out float withDif;
out float withNM;
out float withOcc;
out mat3 rotate;

void main()
{
	gl_Position = viewToProjection*modelToWorld * vec4(position.x, position.y,position.z, 1);
	translation = vec3(modelToWorld[3][0], modelToWorld[3][1], modelToWorld[3][2]);
	difColor = diffuseColor;
	ambColor = ambientColor;
	specColor = specularColor;
	cameraPos = cameraPosition;
	rotate = mat3(rotation);
	lightPos = lightPosition;
	textCoord = uv;
	pos = position*scale;
	specExp = specExponent;
	normals = normal;
	withDif = withDiffuse;
	withNM = withNormalMap;
	withOcc = withOcclusion;
	
	vec3 bitangent = tangent.w*cross(normal, vec3(tangent));
	transform = mat3(modelToWorld) * mat3(vec3(tangent), bitangent, normal);
}