#pragma once
#include <ExportHeader.h>
#include <vector>
#include <GeneralGLWindow.h>
#include <Qt\qdebug.h>
#include <ShapeData.h>
#include <ShapeGenerator.h>
using std::vector;

class DebugShapesManager
{

public:
	struct DebugShape
	{
	public:
		glm::vec3 color;
		char* name;
		float remainingLife;
		int index;
		bool withDepthTest;
		DebugShape(float lifetime, bool withDepth, int renderIndex)
		{
			index = renderIndex;
			remainingLife = lifetime;
			withDepthTest = withDepth;
			name = "dominantColor";
		}
	};
#if DEBUG_SHAPES_ON

	ENGINE_SHARED static void initialize();

	ENGINE_SHARED static void addSphere(glm::mat4 location, glm::vec3 color, float lifetime, bool withDepthTest);

	ENGINE_SHARED static void addCube(glm::mat4 location, glm::vec3 color, float lifetime, bool withDepthTest);

	ENGINE_SHARED static void addVector(glm::vec3 tailPosition, glm::vec3 modelVector, glm::vec3 color, float lifetime, bool withDepthTest);

	ENGINE_SHARED static void addLine(glm::vec3 start, glm::vec3 end, glm::vec3 color, float lifetime, bool withDepthTest);

	ENGINE_SHARED static void addPoint(glm::vec3 start, float lifetime, bool withDepthTest);

	ENGINE_SHARED static void Update(float dt);
	
	
#else

	ENGINE_SHARED static void initialize(){}

	ENGINE_SHARED static void addSphere(glm::mat4 , glm::vec3 , float , bool ){}

	ENGINE_SHARED static void addCube(glm::mat4 , glm::vec3 , float , bool ){}

	ENGINE_SHARED static void addVector(glm::vec3 , glm::vec3 , glm::vec3 , float , bool){}

	ENGINE_SHARED static void addLine(glm::vec3 , glm::vec3 , glm::vec3 , float , bool ){}

	ENGINE_SHARED static void addPoint(glm::vec3 , float , bool ){}

	ENGINE_SHARED static void Update(float){}

#endif


};

