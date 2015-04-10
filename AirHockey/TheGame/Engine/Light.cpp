#include <Light.h>
#include <ShapeGenerator.h>
#include <DebugTools\DebugMenus.h>
#include <DebugTools\DebugMemory.h>
#include <glm\gtx\transform.hpp>

Light::Light(glm::vec3 myPosition, glm::vec3 myColor, float myScale)
{
	graphic = nullptr;
	visible = true;
	position = myPosition;
	diffuseColor = myColor;
	scale = myScale;
	//index = GeneralGLWindow::getCurrentRenderable();

	/*Neumont::ShapeData cube = Neumont::ShapeGenerator::makeCube();
	GeneralGLWindow::GeometryInfo* cubeGeo = GeneralGLWindow::addGeometry(cube.verts, cube.vertexBufferSize(), cube.indices, cube.numIndices, GL_TRIANGLES);
	GeneralGLWindow::ShaderInfo* cubeShader = GeneralGLWindow::createShaderInfo("UniformVertexShader.glsl", "UniformFragmentShader.glsl");
	GeneralGLWindow::TextureInfo* cubeTexture = GeneralGLWindow::addTexture("White.png", cubeShader->programID);
	GeneralGLWindow::RenderableInfo* lightRender = GeneralGLWindow::addRenderable(cubeGeo, glm::translate(position)*glm::scale(scale,scale,scale), cubeShader, cubeTexture);
	GeneralGLWindow::addShaderStreamedParameter(cubeGeo, cubeShader->programID, 0, GeneralGLWindow::PT_VEC3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
	GeneralGLWindow::addRenderableUniformParameter(lightRender, "dominantColor", GeneralGLWindow::PT_VEC3, &diffuseColor[0]);
	graphic = lightRender;*/
}

void Light::addDebugMenu(menuType type, float min, float max, int granuality, char* tabName)
{
	switch(type)
	{
	case pos:
		DebugMenus::slideVec3("Light Position", min, max, granuality, 0, tabName,&position);
		break;
	case diffColor:
		DebugMenus::slideVec3("Diffuse Color", min, max, granuality, 0, tabName, &diffuseColor);
		break;
	case visibility:
		DebugMenus::checkbox(&visible, "Visibility", tabName);
		break;
	case scalar:
		DebugMenus::slide("Scale", min, max, granuality, scale, tabName, &scale);
		break;
	}
}


void Light::update(float dt)
{
	if(graphic)
	{
		dt;
		graphic->setVisibility(visible);
		if(visible)
		{
			graphic->setTransform(glm::translate(position)*glm::scale(scale,scale,scale));
		}
	}
}
