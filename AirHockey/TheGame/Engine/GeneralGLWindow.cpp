#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <Qt\qdebug.h>
#include <string.h>
#include <fstream>
#include <noise\noise.h>
#include <DebugTools\Timer.h>
#include <GeneralGLWindow.h>
#include <ShapeGenerator.h>
#include <ShapeData.h>
#include <DebugTools\DebugShapesManager.h>
#include <Engine.h>
#include <QtGui\qfiledialog.h>
#include <QtGui\qapplication.h>
#include <DebugTools\DebugMenus.h>
#include <noiseutils.h>
#include <DebugTools\DebugMemory.h>
#include "ComponentSystem\RenderableComponent.h"
#include "Light.h"
#include <iostream>
#include <fstream>

using namespace noise;

Camera camera[MAX_NUMBER_CAMERAS];

GeneralGLWindow::BufferInfo bufferInfos[MAX_NUMBER_BUFFERINFOS];
GeneralGLWindow::ShaderInfo shaderInfos[MAX_NUMBER_SHADERS];
GeneralGLWindow::GeometryInfo geometryInfos[MAX_NUMBER_GEOMETRIES];
GeneralGLWindow::TextureInfo textureInfos[MAX_NUMBER_TEXTURES];
GeneralGLWindow::RenderableInfo renderableInfos[MAX_NUMBER_RENDERABLES];
GeneralGLWindow::PassInfo passInfos[MAX_NUMBER_PASSINFOS];
QList<GeneralGLWindow::ReadFiles*> files;

GLuint FrameBufferID;
GLuint ColorTextureID;
GLuint DepthTextureID;
float fps;
int mainCamera = 0;
QString append = "Assets/";

glm::mat4 viewToProjection;
glm::mat4 perspective;
//GeneralGLWindow::RenderableInfo* cubeRenderer;
//GeneralGLWindow::RenderableInfo* cubeRenderer2;
//GeneralGLWindow::RenderableInfo* teapotRender;
//GeneralGLWindow::RenderableInfo* teapotRender2;

glm::vec3 planeColor(1.0f,1.0f,0);
glm::vec3 cameraPosition;
bool cameraLocked = false;
bool cameraLockedLastFrame = false;
bool checkLeKeys = false;
bool once = false;

void GeneralGLWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	setMouseTracking(true);
	currentRenderable = 0;
	SendDataToHardware();
	glm::mat4 transform = glm::translate(glm::vec3(0,0,-2.0f));
	glm::mat4 transform2 = glm::translate(glm::vec3(0.0f, .2f, -7.0f));
	DebugShapesManager::initialize();
	camera[mainCamera].setPosition(glm::vec3(0, 9.5f, 11.0f));
	camera[mainCamera].setViewDirection(glm::vec3(0,-1.5f,-1.0f));

	//DebugMenus::addTab("Game Overview");
	//DebugMenus::checkbox(&checkLeKeys, "Enable Camera movement", "Game Overview");
	//DebugMenus::label("FPS: ", &fps, "Game Overview");

	perspective = glm::perspective(50.0f, (float)width()/height(), .1f, 100.0f) ;
	viewToProjection = perspective * camera[mainCamera].getWorldToViewMatrix();

	connect(&timer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	timer.start(12);
}

GeneralGLWindow::RenderableInfo* GeneralGLWindow::readBinaryFile(char* fileName, char* vertexShader, char* fragShader, char* texture, char* alphaMap, char* normalMap, char* aoMap, glm::mat4 transform)
{
	RenderableInfo* render = nullptr;
	/*for(int i=0; i<files.size() && !render; i++)
	{
		if(files[i]->name == fileName)
		{
			GeometryInfo* geo = files[i]->geo;
			TextureInfo* binaryTexture = addTexture(texture, files[i]->shaders->programID, alphaMap, normalMap, aoMap);
			render = addRenderable(geo, transform, files[i]->shaders, binaryTexture, true, files[i]->bounds);
		}
	}*/
	if(!render)
	{

		std::ifstream binaryFile(fileName, std::ios::binary | std::ios::in | std::ios::ate);
		if(binaryFile.good())
		{
			int fileSize = binaryFile.tellg();
			binaryFile.seekg(0,std::ios::beg);
			char* fileChars = new char[fileSize];
			char* modifier = fileChars;
			binaryFile.read(fileChars, fileSize);
			binaryFile.close();
			int vertCount = *reinterpret_cast<int*>(modifier);
			modifier += sizeof(int);
			int indexCount = *reinterpret_cast<int*>(modifier);
			modifier += sizeof(int);
			float width = *reinterpret_cast<float*>(modifier);
			modifier += sizeof(float);
			float height = *reinterpret_cast<float*>(modifier);
			modifier += sizeof(float);
			float thickness = *reinterpret_cast<float*>(modifier);
			modifier += sizeof(float);

			GLuint vertSize = 12*sizeof(float);

			GeometryInfo* binaryInfo = addGeometry(modifier, vertCount*vertSize, (ushort*)(modifier+(vertCount*vertSize)), indexCount, GL_TRIANGLES);
			ShaderInfo* binaryShader = createShaderInfo(vertexShader, fragShader);
			TextureInfo* binaryTexture = addTexture(texture, binaryShader->programID, alphaMap, normalMap, aoMap);
			ReadFiles* file = new ReadFiles;
			file->geo = binaryInfo;
			file->name = fileName;
			file->shaders = binaryShader;
			file->bounds = glm::vec3(width, height, thickness);
			files.push_back(file);
			render = addRenderable(binaryInfo, transform, binaryShader, binaryTexture, true, glm::vec3(width, height, thickness));

			addShaderStreamedParameter(binaryInfo, binaryShader->programID, 0, PT_VEC3, 0, vertSize);
			addShaderStreamedParameter(binaryInfo, binaryShader->programID, 2, PT_VEC3, 3*sizeof(float), vertSize);
			addShaderStreamedParameter(binaryInfo, binaryShader->programID, 1, PT_VEC2, 6*sizeof(float), vertSize);
			addShaderStreamedParameter(binaryInfo, binaryShader->programID, 3, PT_VEC4, 8*sizeof(float), vertSize);
			delete fileChars;
		}
	}
	return render;

}

QByteArray GeneralGLWindow::createOBJ(char* filePath, bool forceWrite)
{
	QString obj = filePath;
	QStringList stringList = obj.split('/');
	obj = stringList.last();
	stringList = obj.split('.');
	obj = stringList.first()+".bin";
	QByteArray ba = obj.toUtf8();
	char* objName = ba.data();

	QString targetObj = append+"OBJs/";
	targetObj += filePath;
	std::ifstream binaryFile(objName, std::ios::binary | std::ios::in | std::ios::ate);
	if(binaryFile.good() && !forceWrite)
	{
		return ba;
	}
	binaryFile.close();
	QString command("DataParser.exe ");
	const char* nativeFileName = objName;
	command += "\""+targetObj+"\"" + " " + nativeFileName;
	int result = system(command.toUtf8().constData());
	assert(result == 0);
	return ba;
}

void GeneralGLWindow::SendDataToHardware()
{	
	//SetUpFrameBuffer();
}

void GeneralGLWindow::SetUpFrameBuffer()
{
	glGenFramebuffers(1, &FrameBufferID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBufferID);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &ColorTextureID);
	glBindTexture(GL_TEXTURE_2D, ColorTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_DRAW_FRAMEBUFFER,0,GL_RGB,width(), height(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTextureID, 0);

	/*glGenTextures(1, &DepthTextureID);
	glBindTexture(GL_TEXTURE_2D, DepthTextureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width(), height(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTextureID,0);*/

	GLuint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		qDebug() << "Frame buffer isn't working....";
	}
}

int GeneralGLWindow::addPass(GLuint x, GLuint y, Camera* cam)
{
	glGenFramebuffers(1,&passInfos[currentPass].framebufferID);
	passInfos[currentPass].xDimension = x;
	passInfos[currentPass].yDimension = y;
	if(cam)
	{
		bool found = false;
		for(int i=0;i<currentCamera; i++)
		{
			if(&camera[i] == cam)
			{
				passInfos[currentPass].cam = i;
				found = true;
			}
		}
	}
	else
	{
		passInfos[currentPass].cam = 0;
	}
	return currentPass++;
}

void GeneralGLWindow::checkKeys()
{
	if(GetAsyncKeyState('W'))
	{
		camera[mainCamera].moveForward();
	}
	if(GetAsyncKeyState('S'))
	{
		camera[mainCamera].moveBackward();
	}
	if(GetAsyncKeyState('D'))
	{
		camera[mainCamera].strafeRight();
	}
	if(GetAsyncKeyState('A'))
	{
		camera[mainCamera].strafeLeft();
	}
	if(GetAsyncKeyState('R'))
	{
		camera[mainCamera].moveUp();
	}
	if(GetAsyncKeyState('F'))
	{
		camera[mainCamera].moveDown();
	}
	if(GetAsyncKeyState('C'))
	{
		cameraLocked = (!cameraLockedLastFrame)?!cameraLocked:cameraLocked;
		cameraLockedLastFrame = true;
		qDebug() << cameraLocked;
	}
	else
	{
		cameraLockedLastFrame = false;
	}
}

GeneralGLWindow::GeometryInfo* GeneralGLWindow::addGeometry(const void* verts, GLuint vertexDataSize,ushort* indices, GLuint numIndices,GLuint indexingMode)
{
	GLuint indexDataSize = numIndices * sizeof(ushort);
	bool foundBuffer = false;

	for(int i=0; i<MAX_NUMBER_BUFFERINFOS && !foundBuffer;i++)
	{
		if(bufferInfos[i].remainingSize > vertexDataSize + indexDataSize)
		{
			if(bufferInfos[i].remainingSize == 3048576)
			{
				glGenBuffers(1, &bufferInfos[i].BufferID);
			}

			foundBuffer = true;
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfos[i].BufferID);
			glBufferData(GL_ARRAY_BUFFER, 3048576, 0, GL_STATIC_DRAW);

			geometryInfos[currentGeometry].streamOffset = bufferInfos[i].offset;

			glBufferSubData(GL_ARRAY_BUFFER, bufferInfos[i].offset, vertexDataSize, verts);
			bufferInfos[i].offset += vertexDataSize;
			glBufferSubData(GL_ARRAY_BUFFER, bufferInfos[i].offset, indexDataSize, indices);
			bufferInfos[i].offset += indexDataSize;

			glGenVertexArrays(1, &geometryInfos[currentGeometry].vertexArrayID);

			geometryInfos[currentGeometry].numIndices = numIndices;
			geometryInfos[currentGeometry].indexOffset = bufferInfos[i].offset-indexDataSize;
			geometryInfos[currentGeometry].indexingMode = indexingMode;
			geometryInfos[currentGeometry].bufferID = bufferInfos[i].BufferID;

			bufferInfos[i].remainingSize -= vertexDataSize + indexDataSize;
		}
	}
	return &geometryInfos[currentGeometry++];
}

GeneralGLWindow::ShaderInfo* GeneralGLWindow::createShaderInfo(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	std::string temp =  readShaderCode(vertexShaderFileName);
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp =  readShaderCode(fragmentShaderFileName);
	adapter[0] = temp.c_str();
	glShaderSource(fragShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragShaderID);

	GLint compileStatus;
	glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(fragShaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* buffer = new char[logLength];
		GLsizei bitBucket;
		glGetShaderInfoLog(fragShaderID, logLength, &bitBucket, buffer);
		qDebug() << buffer;
		delete [] buffer;
	}
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLint logLength;
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* buffer = new char[logLength];
		GLsizei bitBucket;
		glGetShaderInfoLog(vertexShaderID, logLength, &bitBucket, buffer);
		qDebug() << buffer;
		delete [] buffer;
	}
	shaderInfos[currentShader].programID = glCreateProgram();
	glAttachShader(shaderInfos[currentShader].programID, vertexShaderID);
	glAttachShader(shaderInfos[currentShader].programID, fragShaderID);

	glLinkProgram(shaderInfos[currentShader].programID);

	return &shaderInfos[currentShader++];
}

GeneralGLWindow::RenderableInfo* GeneralGLWindow::addRenderable(GeometryInfo* whatGeometry,const glm::mat4& whereMatrix, ShaderInfo* howShaders, TextureInfo* texture, bool withDepthTest, glm::vec3 bounds)
{
	renderableInfos[currentRenderable].where = whereMatrix;
	renderableInfos[currentRenderable].whatGeometryIndex = whatGeometry;
	renderableInfos[currentRenderable].howShaderIndex = howShaders;
	renderableInfos[currentRenderable].visible = true;
	renderableInfos[currentRenderable].withDepthTest = withDepthTest;
	renderableInfos[currentRenderable].texture = texture;
	renderableInfos[currentRenderable].bounds = bounds;
	return &renderableInfos[currentRenderable++];
}

void GeneralGLWindow::addShaderStreamedParameter(GeometryInfo* geometry,GLuint shaderID,GLuint layoutLocation,GeneralGLWindow::ParameterType parameterType,GLuint bufferOffset,GLuint bufferStride)
{
	shaderID;
	glBindVertexArray(geometry->vertexArrayID);
	glEnableVertexAttribArray(layoutLocation);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->bufferID);
	glVertexAttribPointer(layoutLocation,parameterType/(sizeof(float)),GL_FLOAT, GL_FALSE,bufferStride, (void*)(geometry->streamOffset+bufferOffset));
}

void GeneralGLWindow::addRenderableUniformParameter(RenderableInfo* renderable,const char* name,GeneralGLWindow::ParameterType parameterType,const float* value)
{
	glUseProgram(renderable->howShaderIndex->programID);
	GLuint uniformLocation = glGetUniformLocation(renderable->howShaderIndex->programID, name);
	int index = renderable->numUniforms;
	renderable->uniformParameters[index].type = parameterType;
	renderable->uniformParameters[index].value = value;
	renderable->uniformParameters[index].location = uniformLocation;
	renderable->uniformParameters[index].name = name;
	renderable->numUniforms++;
}

void GeneralGLWindow::updateUniform(RenderableInfo* renderable, const char* name, const float* value)
{
	for(int i=0; i<renderable->numUniforms;i++)
	{
		if(renderable->uniformParameters[i].name == name)
		{
			renderable->uniformParameters[i].value = value;
		}
	}
}

std::string GeneralGLWindow::readShaderCode(const char* fileName)
{
	QString filePath = append+"Shaders/";
	filePath += fileName;
	QByteArray ba = filePath.toUtf8();
	std::ifstream meInput(ba.data());
	std::string result ="";
	if(! meInput.good())
	{
		qDebug() << "File failed to load....";
	}
	else
	{
		result = std::string(
			std::istreambuf_iterator<char>(meInput),
			std::istreambuf_iterator<char>());
	}
	return result;
}

GeneralGLWindow::TextureInfo* GeneralGLWindow::addTexture(const char* fileName, GLuint programID, char* alphaMapName, char* normalMapName, char* aoMap)
{
	int theTex =  currentTexture;//searchTextures(fileName);
	if(theTex == currentTexture)
	{
		createTexture(fileName, 0, programID, &textureInfos[currentTexture].textureID, "png");
		textureInfos[currentTexture].fileName = fileName;
		if(alphaMapName)
		{
			createTexture(alphaMapName, 1, programID, &textureInfos[currentTexture].alphaMapID, "png");
		}
		if(normalMapName)
		{
			createTexture(normalMapName, 2, programID, &textureInfos[currentTexture].normalMapID, "png");
		}
		if(aoMap)
		{
			createTexture(aoMap, 3, programID, &textureInfos[currentTexture].aoMapID, "png");
		}
		currentTexture++;
	}
	return &textureInfos[theTex];
}

int GeneralGLWindow::searchTextures(const char* fileName)
{
	int theTex = currentTexture;
	for(int i=0; i<currentTexture && theTex == currentTexture; i++)
	{
		theTex = (textureInfos[i].fileName == fileName)?i:theTex;
	}
	return theTex;
}

GeneralGLWindow::TextureInfo* GeneralGLWindow::addFrameBufferTexture(GLuint bufferType)
{
	GLuint value = currentPass-1;
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, passInfos[value].framebufferID);

	GLuint xDimensions = passInfos[value].xDimension;
	GLuint yDimensions = passInfos[value].yDimension;
	glViewport(0,0,xDimensions,yDimensions);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureInfos[currentTexture].textureID);
	glBindTexture(GL_TEXTURE_2D, textureInfos[currentTexture].textureID);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if(bufferType == GL_RGBA)
	{
		glTexImage2D(GL_TEXTURE_2D,0,bufferType, xDimensions, yDimensions, 0, bufferType, GL_UNSIGNED_BYTE, 0);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureInfos[currentTexture].textureID, 0);
	}
	else if(bufferType == GL_DEPTH_ATTACHMENT)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, xDimensions, yDimensions, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, textureInfos[currentTexture].textureID,0);
	}
	else
	{
		qDebug() << "Buffer not specified.";
	}
	GLuint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		qDebug() << "Frame buffer not complete...";
	}
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	return &textureInfos[currentTexture++];
}

GeneralGLWindow::TextureInfo* GeneralGLWindow::addCubeMap(const char* folderPath)
{
	QImage posX;
	QImage posY;
	QImage posZ;
	QImage negX;
	QImage negY;
	QImage negZ;
	QString path = folderPath;
	if(!posX.load(path + "/posx.png"))
	{
		qDebug() << (path+"/posx.png");
		qDebug() << "Cube positive x path incorrect...";
		return nullptr;
	}
	if(!posY.load(path + "/posy.png"))
	{
		qDebug() << "Cube positive y path incorrect...";
		return nullptr;
	}
	if(!posZ.load(path + "/posz.png"))
	{
		qDebug() << "Cube positive z path incorrect...";
		return nullptr;
	}
	if(!negX.load(path + "/negx.png"))
	{
		qDebug() << "Cube negative x path incorrect...";
		return nullptr;
	}
	if(!negY.load(path + "/negy.png"))
	{
		qDebug() << "Cube negative y path incorrect...";
		return nullptr;
	}
	if(!negZ.load(path + "/negz.png"))
	{
		qDebug() << "Cube negative z path incorrect...";
		return nullptr;
	}
	posZ = convertToGLFormat(posZ).mirrored(false,true);
	posX = convertToGLFormat(posX).mirrored(false,true);
	posY = convertToGLFormat(posY).mirrored(false,true);
	negZ = convertToGLFormat(negZ).mirrored(false,true);
	negX = convertToGLFormat(negX).mirrored(false,true);
	negY = convertToGLFormat(negY).mirrored(false,true);
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureInfos[currentTexture].cubeMapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureInfos[currentTexture].cubeMapID);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri (GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, posX.width(), posX.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,posX.bits());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, posY.width(), posY.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,posY.bits());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, posZ.width(), posZ.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,posZ.bits());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, negX.width(), negX.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,negX.bits());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, negY.width(), negY.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,negY.bits());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, negZ.width(), negZ.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,negZ.bits());
	
	return &textureInfos[currentTexture++];
}

void GeneralGLWindow::createTexture(const char* name, int textureID, int programID, GLuint* data, char* paramName)
{
	QString filePath = append+"Textures/";
	filePath += name;

	QImage texture;
	if(!texture.load(filePath))
	{
		qDebug() << "Couldn't read the image file.";
		return;
	}

	texture = convertToGLFormat(texture);
	int width = texture.width();
	int height = texture.height();

	qDebug() << "The texture width is " << width << " The texture height is " << height;

	GLint textureLocation = glGetUniformLocation(programID, paramName);
	glUniform1i(textureLocation, textureID);

	glGenTextures(1, data);
	glBindTexture(GL_TEXTURE_2D, *data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture.bits());
}

Camera* GeneralGLWindow::addCamera(glm::vec3 position, glm::vec3 lookAt)
{
	camera[currentCamera].setPosition(position);
	camera[currentCamera].setViewDirection(lookAt);
	return &camera[currentCamera++];
}

Camera* GeneralGLWindow::getMainCamera()
{
	return &camera[0];
}

void GeneralGLWindow::switchMainCameraTo(Camera* cam)
{
	bool found = false;
	if(cam == nullptr)
	{
		mainCamera = 0;
		found = true;
	}

	for(int i=0; i<currentCamera && !found; i++)
	{
		if(&camera[i] == cam)
		{
			mainCamera = i;
			found = true;
		}
	}
}

int GeneralGLWindow::getCurrentRenderable()
{
	return currentRenderable;
}

void GeneralGLWindow::RenderableInfo::draw()
{
	glUseProgram(howShaderIndex->programID);
	glBindVertexArray(whatGeometryIndex->vertexArrayID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->textureID);
	if(texture->cubeMapID)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture->cubeMapID);
	}
	if(texture->alphaMapID)
	{
		glActiveTexture(GL_TEXTURE0+1);
		glBindTexture(GL_TEXTURE_2D, texture->alphaMapID);
	}
	if(texture->normalMapID)
	{
		glActiveTexture(GL_TEXTURE0+2);
		glBindTexture(GL_TEXTURE_2D, texture->normalMapID);
	}
	if(texture->aoMapID)
	{
		glActiveTexture(GL_TEXTURE0+3);
		glBindTexture(GL_TEXTURE_2D, texture->aoMapID);
	}

	for(int i=0; i<numUniforms;i++)
	{
		if(uniformParameters[i].type == PT_FLOAT)
		{
			glUniform1fv(uniformParameters[i].location, 1, uniformParameters[i].value);
		}
		else if(uniformParameters[i].type == PT_VEC2)
		{
			glUniform2fv(uniformParameters[i].location,1,uniformParameters[i].value);
		}
		else if(uniformParameters[i].type == PT_VEC3)
		{
			glUniform3fv(uniformParameters[i].location,1,uniformParameters[i].value);
		}
		else if(uniformParameters[i].type == PT_VEC4)
		{
			glUniform4fv(uniformParameters[i].location,1,uniformParameters[i].value);
		}
		else if(uniformParameters[i].type == PT_MAT3)
		{
			glUniformMatrix3fv(uniformParameters[i].location,1,false,uniformParameters[i].value);
		}
		else if(uniformParameters[i].type == PT_MAT4)
		{
			glUniformMatrix4fv(uniformParameters[i].location,1,false,uniformParameters[i].value);
		}
		else if(uniformParameters[i].type == PT_TEXTURE)
		{
			glUniform1i(uniformParameters[i].location, *uniformParameters[i].value);
		}
	}
	GLuint viewToProjectionLocation = glGetUniformLocation(howShaderIndex->programID, "viewToProjection");
	glUniformMatrix4fv(viewToProjectionLocation, 1, false, &viewToProjection[0][0]);
	GLuint modelToWorldLocation = glGetUniformLocation(howShaderIndex->programID, "modelToWorld");
	glUniformMatrix4fv(modelToWorldLocation, 1, false, &where[0][0]);
	glDrawElements(whatGeometryIndex->indexingMode, whatGeometryIndex->numIndices, GL_UNSIGNED_SHORT, (void*)whatGeometryIndex->indexOffset);
}

glm::vec3 GeneralGLWindow::getCameraPosition()
{
	return cameraPosition;
}

void GeneralGLWindow::createHeightMap(int dimensions, char* name)
{
	module::Perlin myModule;
	myModule.SetSeed(20);
	myModule.SetOctaveCount(2);
	myModule.SetFrequency(2.0);
	myModule.SetPersistence(.5);

	QImage* image = new QImage(dimensions, dimensions, QImage::Format::Format_ARGB32);
	for(int i=0; i<dimensions;i++)
	{
		for(int j=0;j<dimensions;j++)
		{
			/*myModule.SetOctaveCount(3);
			float value0 = getNoiseValueAt(myModule, i, j, dimensions);
			myModule.SetOctaveCount(4);
			float value1 = getNoiseValueAt(myModule, i, j, dimensions);
			myModule.SetOctaveCount(5);
			float value2 = getNoiseValueAt(myModule, i, j, dimensions);
			myModule.SetOctaveCount(6);
			float value3 = getNoiseValueAt(myModule, i, j, dimensions);
			QRgb color = qRgba(value0, value1, value2, value3);
			image->setPixel(i, j, color);*/
		}
	}
	image->save(name);
	delete image;
}

GeneralGLWindow::TextureInfo* GeneralGLWindow::setupTextTexture(QString& text, TextureInfo* swap, glm::vec3 color, int textWidth)
{
	int theTexture = currentTexture;
	if(swap)
	{
		for(int i=0; i<theTexture; i++)
		{
			theTexture = (&textureInfos[i] == swap)?i:theTexture;
		}
	}
	glGenTextures(1, &textureInfos[theTexture].textureID);
	glBindTexture(GL_TEXTURE_2D, textureInfos[theTexture].textureID);
	QFont font("Sans", 45);
	QFontMetrics metric(font);

	int width, height;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &height);
	QRect rect = metric.boundingRect(text);
	width = textWidth;
	height = metric.height()*1.25;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	QImage textImg(width, height, QImage::Format_RGB888);
	{
		QPainter painter(&textImg);
		painter.fillRect(0, 0, width, height, QColor(0,0,0));
		painter.setBrush(QColor(color.x, color.y, color.z));
		painter.setPen(QColor(color.x, color.y, color.z));
		
		painter.setFont(font);
		painter.drawText(5,metric.height()*1.1, text);
	}

	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_IMAGES, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, textImg.bits());
	currentTexture += (theTexture == currentTexture)?1:0;
	return &textureInfos[theTexture];
}

//float GeneralGLWindow::getNoiseValueAt(module::Perlin p,float x, float y, int dimensions)
//{
//	float value = (p.GetValue(x/(float)dimensions,y/(float)dimensions,0)+1)/2;
//	value = (value < 0)?0:value;
//	value = (value > 1)?1.0f:value;
//	value *= 255.0f;
//	return value;
//}

void GeneralGLWindow::myUpdate()
{
	fps = 1/Timer::dt();
	cameraPosition = camera[mainCamera].getPosition();
	Engine::callUpdate();
	if(checkLeKeys)
	{
		checkKeys();
	}
	updateGL();
}

glm::mat4 GeneralGLWindow::getPerspective()
{
	return perspective;
}

void GeneralGLWindow::addLightingUniforms(RenderableComponent* render, Light* light, float* specExp, glm::vec3* ambColor, glm::vec4* dominantColor)
{
	addRenderableUniformParameter(render->graphic, "ambientColor", GeneralGLWindow::PT_VEC3, &(*ambColor)[0]);
	addRenderableUniformParameter(render->graphic, "diffuseColor", GeneralGLWindow::PT_VEC3, &light->diffuseColor[0]);
	addRenderableUniformParameter(render->graphic, "specularColor", GeneralGLWindow::PT_VEC3, &light->diffuseColor[0]);
	addRenderableUniformParameter(render->graphic, "lightPosition", GeneralGLWindow::PT_VEC3, &light->position[0]);
	addRenderableUniformParameter(render->graphic, "cameraPosition", GeneralGLWindow::PT_VEC3, &cameraPosition[0]);
	addRenderableUniformParameter(render->graphic, "specExponent", GeneralGLWindow::PT_FLOAT, specExp);
	float* wDiff = (dominantColor)?&planeColor[2]:&planeColor[0];
	addRenderableUniformParameter(render->graphic, "withDiffuse", GeneralGLWindow::PT_FLOAT, wDiff);
	addRenderableUniformParameter(render->graphic, "withNormalMap", GeneralGLWindow::PT_FLOAT, &planeColor[2]);
	addRenderableUniformParameter(render->graphic, "withOcclusion", GeneralGLWindow::PT_FLOAT, &planeColor[2]);
	addRenderableUniformParameter(render->graphic, "rotation", GeneralGLWindow::PT_MAT4, &render->transform.rotateMat[0][0]);
	addRenderableUniformParameter(render->graphic, "scale", GeneralGLWindow::PT_VEC3, &render->transform.scale[0]);
	if(dominantColor)
	{
		addRenderableUniformParameter(render->graphic, "dominantColor", GeneralGLWindow::PT_VEC4, &(*dominantColor)[0]);
		
	}
}

void GeneralGLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
	glClearColor(0,.2f,0,0);
	glViewport(0, 0, width(), height());
	perspective = glm::perspective(50.0f, (float)width()/height(), .1f, 100.0f);

	for(int i=0; i<currentPass; i++)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, passInfos[i].framebufferID);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, passInfos[i].xDimension, passInfos[i].yDimension);
		/*float midValue = (passInfos[i].cam == 2)?(float)width()/height():1.0f;
		perspective = glm::perspective(60.0f, midValue, .1f, 100.0f);
		viewToProjection = perspective * camera[passInfos[i].cam].getWorldToViewMatrix();*/
		for(int j=0; j<currentRenderable;j++)
		{
			
			if(renderableInfos[j].visible && renderableInfos[j].framebuffers.contains(i))
			{
				if(renderableInfos[j].withDepthTest)
					glEnable(GL_DEPTH_TEST);
				else
					glDisable(GL_DEPTH_TEST);
				renderableInfos[j].draw();
			}
		}
	}
	perspective = glm::perspective(60.0f, (float)width()/height(), .1f, 100.0f);
	glDisable(GL_POLYGON_OFFSET_FILL);
	viewToProjection = perspective * camera[mainCamera].getWorldToViewMatrix();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, width(), height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for(int i=0; i<currentRenderable; i++)
	{
		if(renderableInfos[i].visible)
		{
			if(renderableInfos[i].withDepthTest)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
			renderableInfos[i].draw();
		}
	}
}

void GeneralGLWindow::setVisibility(int renderIndex, bool visibility )
{
	renderableInfos[renderIndex].visible = visibility;
}

void GeneralGLWindow::mouseMoveEvent(QMouseEvent* e)
{
	if(!cameraLocked && QApplication::mouseButtons() == Qt::MouseButton::LeftButton)
	{
		camera[mainCamera].mouseUpdate(glm::vec2(e->x(),e->y()));
	}
}

void GeneralGLWindow::keyPressEvent(QKeyEvent* e)
{
	e;
}

void GeneralGLWindow::shutdown()
{
	for(int i=0; i<files.size(); i)
	{
		delete files[i];
		files.removeAt(i);
	}
}

void GeneralGLWindow::restart()
{
	currentRenderable = 0;
	currentCamera = 1;
	currentGeometry = 0;
	currentPass = 0;
	currentShader = 0;
	currentTexture = 0;
}