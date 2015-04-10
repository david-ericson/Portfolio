#include <MirrorManager.h>
#include <ShapeGenerator.h>
#include <LightManager.h>
#include <DebugTools\DebugShapesManager.h>
#include <DebugTools\DebugMenus.h>
#include <glm\gtx\transform.hpp>

MirrorManager::Mirror mirrors[10];
GeneralGLWindow::GeometryInfo* mirrorGeo;
GeneralGLWindow::ShaderInfo* mirrorShader;

int light;
float specExp;
float withDiff;
glm::vec3 mainCameraPosition;

void MirrorManager::Mirror::update(float dt)
{
	dt;
	graphic->setVisibility(visible);
}

void MirrorManager::initialize()
{
	withDiff = 1.0f;
	specExp = 20.0f;
	Neumont::ShapeData plane = Neumont::ShapeGenerator::makePlane(10);
	mirrorGeo = GeneralGLWindow::addGeometry(plane.verts, plane.vertexBufferSize(), plane.indices, plane.numIndices, GL_TRIANGLES);
	mirrorShader = GeneralGLWindow::createShaderInfo("AlphaMapVertexShader.glsl", "TextureFragmentShader.glsl");
	GeneralGLWindow::addShaderStreamedParameter(mirrorGeo, mirrorShader->programID, 0, GeneralGLWindow::PT_VEC3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
	GeneralGLWindow::addShaderStreamedParameter(mirrorGeo, mirrorShader->programID, 1, GeneralGLWindow::PT_VEC2, Neumont::Vertex::UV_OFFSET, Neumont::Vertex::STRIDE);
	GeneralGLWindow::addShaderStreamedParameter(mirrorGeo, mirrorShader->programID, 2, GeneralGLWindow::PT_VEC3, Neumont::Vertex::NORMAL_OFFSET, Neumont::Vertex::STRIDE);
	light = LightManager::addLight(glm::vec3(0, 1.0f, -4.0f), glm::vec3(1.0f,1.0f,1.0f), 0);	
	DebugMenus::addTab("Mirrors");
}

void MirrorManager::createNewPassForMirror(int mirror)
{
	mirrors[mirror].graphic->setTexture(GeneralGLWindow::addFrameBufferTexture(GL_RGBA));
}

void MirrorManager::addMirror(glm::vec3 position, float yAngle, float xAngle)
{
	mirrors[currentMirror].camera = GeneralGLWindow::addCamera(position, glm::vec3());
	GeneralGLWindow::addPass(512, 512, mirrors[currentMirror].camera);
	GeneralGLWindow::TextureInfo* mirrorTex = GeneralGLWindow::addFrameBufferTexture(GL_RGBA);
	mirrors[currentMirror].graphic = GeneralGLWindow::addRenderable(mirrorGeo, glm::translate(position)*glm::rotate(xAngle, glm::vec3(1.0f,0,0))*glm::rotate(yAngle, glm::vec3(0,1.0f,0)), mirrorShader, mirrorTex);
	mirrors[currentMirror].camera->setPosition(position*2.65f+glm::vec3(.45f,-.45f,0));
	glm::vec3 viewDir = glm::vec3(glm::vec4(0,0,-1.0f,1.0f)*glm::rotate(yAngle, glm::vec3(0,1.0f,0)));
	mirrors[currentMirror].camera->setViewDirection(viewDir);
	mirrors[currentMirror].angle = 270.0f;
	mirrors[currentMirror].normal = glm::vec3(0,1.0f,0);
	mirrors[currentMirror].ambColor = glm::vec3(0,0,0);
	mirrors[currentMirror].position = position*2.65f;
	mirrors[currentMirror].visible = true;
	
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "ambColor", GeneralGLWindow::PT_VEC3, &mirrors[currentMirror].ambColor[0]);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "diffuseColor", GeneralGLWindow::PT_VEC3, &LightManager::getLight(light)->diffuseColor[0]);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "specularColor", GeneralGLWindow::PT_VEC3, &LightManager::getLight(light)->diffuseColor[0]);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "lightPosition", GeneralGLWindow::PT_VEC3, &LightManager::getLight(light)->position[0]);
	mainCameraPosition = GeneralGLWindow::getCameraPosition();
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "cameraPosition", GeneralGLWindow::PT_VEC3, &mainCameraPosition[0]);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "specExponent", GeneralGLWindow::PT_FLOAT, &specExp);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "withNormalMap", GeneralGLWindow::PT_FLOAT, &mirrors[currentMirror].ambColor[0]);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "withDiffuse", GeneralGLWindow::PT_FLOAT, &withDiff);
	GeneralGLWindow::addRenderableUniformParameter(mirrors[currentMirror].graphic, "withOcclusion", GeneralGLWindow::PT_FLOAT, &mirrors[currentMirror].ambColor[0]);

	DebugMenus::checkbox(&mirrors[currentMirror].visible, "Mirror Visible?", "Mirrors");
	currentMirror++;
}

void MirrorManager::update(float dt)
{
	mainCameraPosition = GeneralGLWindow::getCameraPosition();
	for(int i=0; i<currentMirror; i++)
	{
		mirrors[i].update(dt);
	}
}
