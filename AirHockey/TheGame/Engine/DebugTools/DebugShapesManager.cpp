#include <DebugTools\DebugShapesManager.h>
#include <DebugTools\DebugMemory.h>
#include <glm\gtx\transform.hpp>

#ifdef DEBUG_SHAPES_ON

static GeneralGLWindow::GeometryInfo* sphereGeometry;
static GeneralGLWindow::ShaderInfo* sphereCubeShader;
static GeneralGLWindow::ShaderInfo* vectorCrosshairShader;
static GeneralGLWindow::TextureInfo* theTexture;
static GeneralGLWindow::GeometryInfo* cubeGeometry;
static vector<DebugShapesManager::DebugShape*> debugShapes;

static bool madeSphere = false;
static bool madeCube = false;

void DebugShapesManager::initialize()
{
	GeneralGLWindow::BufferInfo;
	sphereCubeShader = GeneralGLWindow::createShaderInfo("UniformVertexShader.glsl","UniformFragmentShader.glsl");
	vectorCrosshairShader = GeneralGLWindow::createShaderInfo("ColorVertexShader.glsl","ColorFragmentShader.glsl");
	theTexture = GeneralGLWindow::addTexture("checkerboard.png", sphereCubeShader->programID);

}

void DebugShapesManager::addSphere(glm::mat4 location, glm::vec3 color, float lifetime, bool withDepthTest)
{
	if(!madeSphere)
	{
		Neumont::ShapeData sphere = Neumont::ShapeGenerator::makeSphere(10.0f);
		sphereGeometry = GeneralGLWindow::addGeometry(sphere.verts, sphere.vertexBufferSize(), sphere.indices, sphere.numIndices, GL_TRIANGLES);
		madeSphere = true;
	}

	GeneralGLWindow::RenderableInfo* sphereRenderable = GeneralGLWindow::addRenderable(sphereGeometry, location, sphereCubeShader, theTexture);
	GeneralGLWindow::addShaderStreamedParameter(sphereGeometry, sphereCubeShader->programID, 0, GeneralGLWindow::ParameterType::PT_VEC3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
	glm::vec3* shapeColor = new glm::vec3(color.x, color.y, color.z);
	GeneralGLWindow::addRenderableUniformParameter(sphereRenderable, "dominantColor", GeneralGLWindow::PT_VEC3, reinterpret_cast<float*>(shapeColor));
	int test = GeneralGLWindow::getCurrentRenderable()-1;
	DebugShape* sphereShape = new DebugShape(lifetime, withDepthTest, test);
	debugShapes.push_back(sphereShape);
}

void DebugShapesManager::addCube(glm::mat4 location, glm::vec3 color, float lifetime, bool withDepthTest)
{
	if(!madeCube)
	{
		Neumont::ShapeData cube = Neumont::ShapeGenerator::makeCube();
		cubeGeometry = GeneralGLWindow::addGeometry(cube.verts, cube.vertexBufferSize(), cube.indices, cube.numIndices, GL_TRIANGLES);
		madeCube = true;
	}
	GeneralGLWindow::RenderableInfo* cubeRenderable = GeneralGLWindow::addRenderable(cubeGeometry, location, sphereCubeShader, theTexture);
	GeneralGLWindow::addShaderStreamedParameter(cubeGeometry, sphereCubeShader->programID, 0, GeneralGLWindow::ParameterType::PT_VEC3, Neumont::Vertex::POSITION_OFFSET, Neumont::Vertex::STRIDE);
	glm::vec3* shapeColor = new glm::vec3(color.x, color.y, color.z);
	GeneralGLWindow::addRenderableUniformParameter(cubeRenderable, "dominantColor", GeneralGLWindow::PT_VEC3, reinterpret_cast<float*>(shapeColor));
	int currentIndex = GeneralGLWindow::getCurrentRenderable()-1;

	DebugShape* cubeShape = new DebugShape(lifetime, withDepthTest, currentIndex);
	debugShapes.push_back(cubeShape);
}

void DebugShapesManager::addVector(glm::vec3 tailPosition, glm::vec3 modelVector, glm::vec3 color, float lifetime, bool withDepthTest)
{
	glm::vec3 verts[] = 
	{
		tailPosition, 
		glm::vec3(0,0,0),
		modelVector + tailPosition,
		color,
	};
	GLushort indices[] =
	{
		0,1
	};
	GeneralGLWindow::GeometryInfo* vectorGeometry = GeneralGLWindow::addGeometry(verts, sizeof(verts), indices, 2, GL_LINES);
	glm::mat4 transform = glm::translate(0.0f,0.0f,0.0f);
	GeneralGLWindow::addRenderable(vectorGeometry, transform, vectorCrosshairShader, theTexture, withDepthTest);
	GeneralGLWindow::addShaderStreamedParameter(vectorGeometry, vectorCrosshairShader->programID, 0, GeneralGLWindow::ParameterType::PT_VEC3, 0, sizeof(float) * 6);
	GeneralGLWindow::addShaderStreamedParameter(vectorGeometry, vectorCrosshairShader->programID, 1, GeneralGLWindow::ParameterType::PT_VEC3, sizeof(float) * 3, sizeof(float) * 6);
	int currentIndex = GeneralGLWindow::getCurrentRenderable()-1;
	DebugShape* vectorShape = new DebugShape(lifetime, withDepthTest, currentIndex);
	debugShapes.push_back(vectorShape);
}

void DebugShapesManager::addLine(glm::vec3 start, glm::vec3 end, glm::vec3 color, float lifetime, bool withDepthTest)
{
	glm::vec3 verts[] = 
	{
		start, 
		color,
		end,
		color
	};
	GLushort indices[] =
	{
		0,1
	};
	GeneralGLWindow::GeometryInfo* vectorGeometry = GeneralGLWindow::addGeometry(verts, sizeof(verts), indices, 2, GL_LINES);
	glm::mat4 transform = glm::translate(0.0f,0.0f,0.0f);
	GeneralGLWindow::addRenderable(vectorGeometry, transform, vectorCrosshairShader, theTexture, withDepthTest);
	GeneralGLWindow::addShaderStreamedParameter(vectorGeometry, vectorCrosshairShader->programID, 0, GeneralGLWindow::ParameterType::PT_VEC3, 0, sizeof(float) * 6);
	GeneralGLWindow::addShaderStreamedParameter(vectorGeometry, vectorCrosshairShader->programID, 1, GeneralGLWindow::ParameterType::PT_VEC3, sizeof(float) * 3, sizeof(float) * 6);
	int currentIndex = GeneralGLWindow::getCurrentRenderable()-1;
	DebugShape* vectorShape = new DebugShape(lifetime, withDepthTest, currentIndex);
	debugShapes.push_back(vectorShape);
}

void DebugShapesManager::addPoint(glm::vec3 start, float lifetime, bool withDepthTest)
{
	glm::vec3 verts[] =
	{
		start + glm::vec3(1.0f,0,0),
		glm::vec3(1.0f,0,0),
		start - glm::vec3(1.0f,0,0),
		glm::vec3(0,0,0),
		start + glm::vec3(0,1.0f,0),
		glm::vec3(0,1.0f,0),
		start - glm::vec3(0,1.0f,0),
		glm::vec3(0,0,0),
		start + glm::vec3(0,0,1.0f),
		glm::vec3(0,0,1.0f),
		start - glm::vec3(0,0,1.0f),
		glm::vec3(0,0,0),
	};
	GLushort indices[] =
	{
		0,1, 2,3, 4,5
	};
	GeneralGLWindow::GeometryInfo* vectorGeometry = GeneralGLWindow::addGeometry(verts, sizeof(verts), indices, 6, GL_LINES);
	glm::mat4 transform = glm::translate(0.0f,0.0f,0.0f);
	GeneralGLWindow::addRenderable(vectorGeometry, transform, vectorCrosshairShader, theTexture, withDepthTest);
	GeneralGLWindow::addShaderStreamedParameter(vectorGeometry, vectorCrosshairShader->programID, 0, GeneralGLWindow::ParameterType::PT_VEC3, 0, sizeof(float) * 6);
	GeneralGLWindow::addShaderStreamedParameter(vectorGeometry, vectorCrosshairShader->programID, 1, GeneralGLWindow::ParameterType::PT_VEC3, sizeof(float) * 3, sizeof(float) * 6);
	int currentIndex = GeneralGLWindow::getCurrentRenderable()-1;
	DebugShape* vectorShape = new DebugShape(lifetime, withDepthTest, currentIndex);
	debugShapes.push_back(vectorShape);
}

void DebugShapesManager::Update(float dt)
{
	for(unsigned int i=0; i<debugShapes.size();i++)
	{
		debugShapes[i]->remainingLife -= dt;
		if(debugShapes[i]->remainingLife <= 0)
		{
			GeneralGLWindow::setVisibility(debugShapes[i]->index, false);
		}
	}
}

#endif //DEBUG_SHAPES_ON
