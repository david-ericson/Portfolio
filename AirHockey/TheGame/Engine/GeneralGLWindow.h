#pragma once
#include <GL\glew.h>
#include <ExportHeader.h>
#include <glm\glm.hpp>
#include <Qt\qstring.h>
#include <QtOpenGL\qglwidget>
#include <Qt\qimage.h>
#include <Qt\qtimer.h>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include <Camera.h>

static int currentGeometry = 0;
static int currentRenderable;
static int currentTexture = 0;
static int currentShader = 0;
static int currentPass = 0;
static int currentCamera = 1;

static const int MAX_UNIFORM_PARAMETERS_PER_RENDERABLE = 50;
static const int MAX_NUMBER_GEOMETRIES = 200;
static const int MAX_NUMBER_TEXTURES = 50;
static const int MAX_NUMBER_SHADERS = 200;
static const int MAX_NUMBER_RENDERABLES = 200;
static const int MAX_NUMBER_BUFFERINFOS = 50;
static const int MAX_NUMBER_PASSINFOS = 20;

static const int MAX_NUMBER_CAMERAS = 10;

class Light;
class RenderableComponent;

class GeneralGLWindow : public QGLWidget
{
	Q_OBJECT

public:
	QTimer timer;
	enum ParameterType
	{
		PT_FLOAT = sizeof(float) * 1,
		PT_VEC2 = sizeof(float) * 2,
		PT_VEC3 = sizeof(float) * 3,
		PT_VEC4 = sizeof(float) * 4,
		PT_MAT3 = sizeof(float) * 9,
		PT_MAT4 = sizeof(float) *16,
		PT_TEXTURE,
	};

	static class ShaderUniformParamter
	{
		ParameterType type;
		const float* value;
		const char* name;
		GLuint location;
		friend class GeneralGLWindow;
	};

	static class BufferInfo
	{
		GLuint BufferID;
		GLuint remainingSize;
		GLsizeiptr offset;
		friend class GeneralGLWindow;
	public:
		BufferInfo()
		{
			offset = 0;
			remainingSize = 3048576;
		}
	};
	static class GeometryInfo
	{
		GLuint vertexArrayID;
		GLuint bufferID;
		GLuint numIndices;
		GLuint indexOffset;
		GLuint indexingMode;
		GLuint streamOffset;
		friend class GeneralGLWindow;
	};

	static class ShaderInfo
	{
	public:
		GLuint programID;
		friend class GeneralGLWindow;
	};

	static class TextureInfo
	{
		QString fileName;
		GLuint textureID;
		GLuint alphaMapID;
		GLuint normalMapID;
		GLuint aoMapID;
		GLuint cubeMapID;
		friend class GeneralGLWindow;
	};
	static class ReadFiles
	{
		QString name;
		GeometryInfo* geo;
		ShaderInfo* shaders;
		glm::vec3 bounds;
		friend class GeneralGLWindow;
	};
	static class RenderableInfo
	{
		GeometryInfo* whatGeometryIndex;
		ShaderInfo* howShaderIndex;
		QList<GLuint> framebuffers;
		glm::mat4 where;
		bool visible;
		bool withDepthTest;
		int numUniforms;
		TextureInfo* texture;
		ShaderUniformParamter uniformParameters[MAX_UNIFORM_PARAMETERS_PER_RENDERABLE];
		friend class GeneralGLWindow;
	public:
		glm::vec3 bounds;
		RenderableInfo()
		{
			numUniforms = 0;
		}
		void draw();
		glm::mat4* getTransform()
		{
			return &where;
		}
		bool getVisibility()
		{
			return visible;
		}
		void setTransform(glm::mat4 transform)
		{
			where = transform;
		}
		void setVisibility(bool visibility)
		{
			visible = visibility;
		}
		void setTexture(TextureInfo* newText)
		{
			texture = newText;
		}
		void addFramebufferID(int id)
		{
			framebuffers.push_back(id);
		}
		TextureInfo* getTexture()
		{
			return texture;
		}
		GeometryInfo* getGeo(){return whatGeometryIndex;}
		ShaderInfo* getShader(){return howShaderIndex;}
	};
	
	static struct PassInfo
	{
		GLuint framebufferID;
		int cam;
		GLuint xDimension;
		GLuint yDimension;
	};

	ENGINE_SHARED static RenderableInfo* readBinaryFile(char* fileName, char* vertexShader, char* fragShader, char* texture, char* alphaMap, char* normalMap, char* aoMap, glm::mat4 transform);

	ENGINE_SHARED static GeometryInfo* addGeometry(
		const void* verts, GLuint vertexDataSize, 
		ushort* indices, GLuint numIndices,
		GLuint indexingMode);

	ENGINE_SHARED static ShaderInfo* createShaderInfo(
		const char* vertexShaderFileName,
		const char* fragmentShaderFileName);

	ENGINE_SHARED static RenderableInfo* addRenderable(
		GeometryInfo* whatGeometry,
		const glm::mat4& whereMatrix,
		ShaderInfo* howShaders,
		TextureInfo* texture,
		bool withDepthTest = true, glm::vec3 bounds = glm::vec3());

	ENGINE_SHARED static void addShaderStreamedParameter(
		GeometryInfo* geometry,
		GLuint shaderID,
		GLuint layoutLocation, 
		GeneralGLWindow::ParameterType parameterType,
		GLuint bufferOffset,
		GLuint bufferStride);

	ENGINE_SHARED static void addRenderableUniformParameter(
		RenderableInfo* renderable,
		const char* name,
		GeneralGLWindow::ParameterType parameterType, 
		const float* value);

	ENGINE_SHARED static void updateUniform(
		RenderableInfo* renderable,
		const char* name,
		const float* newValue);

	ENGINE_SHARED static TextureInfo* addTexture(const char* fileName, GLuint programID, char* alphaMapName = nullptr, char* normalMapName = nullptr, char* aoMap = nullptr);
		void SendDataToHardware();
		void SetUpFrameBuffer();
	ENGINE_SHARED static TextureInfo* addFrameBufferTexture(GLuint bufferType = GL_RGBA);
	ENGINE_SHARED static TextureInfo* addCubeMap(const char* folderPath);
	ENGINE_SHARED static int addPass(GLuint x, GLuint y, Camera* camToUse = nullptr);
	static int searchTextures(const char* fileName);
	
	static std::string readShaderCode(const char* fileName);
	static void createTexture(const char* name,int textureID, int programID, GLuint* data, char* paramName);

	ENGINE_SHARED static void setVisibility(int renderIndex, bool visibility);
	ENGINE_SHARED static QByteArray createOBJ(char* filePath, bool forceWrite = false);
	ENGINE_SHARED static Camera* getMainCamera();

	ENGINE_SHARED static int getCurrentRenderable();
	ENGINE_SHARED void checkKeys();
	ENGINE_SHARED static glm::vec3 getCameraPosition();
	ENGINE_SHARED static void createHeightMap(int dimensions, char* name);
	ENGINE_SHARED static Camera* addCamera(glm::vec3 position, glm::vec3 lookAt);
	ENGINE_SHARED static void switchMainCameraTo(Camera* cam = nullptr);
	ENGINE_SHARED static glm::mat4 getPerspective();
	ENGINE_SHARED static TextureInfo* setupTextTexture(QString& text, TextureInfo* swap, glm::vec3 color = glm::vec3(255.0f,0,0), int textWidth = 300);
	ENGINE_SHARED static void addLightingUniforms(RenderableComponent* render, Light* light, float* specExp, glm::vec3* ambColor, glm::vec4* dominantColor = nullptr);
	ENGINE_SHARED static void shutdown();
	ENGINE_SHARED static void restart();
	private:
	/*static float getNoiseValueAt(noise::module::Perlin p,float x, float y, int dimensions);*/
protected:
	ENGINE_SHARED void initializeGL();
	ENGINE_SHARED void paintGL();
	ENGINE_SHARED void mouseMoveEvent(QMouseEvent* e);
	ENGINE_SHARED void keyPressEvent(QKeyEvent* e);

private slots:
	ENGINE_SHARED void myUpdate();
};


