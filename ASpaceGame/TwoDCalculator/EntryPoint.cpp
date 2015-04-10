#include "RenderUI.h"
#include "Engine.h"
#include "CallbackVariables.h"
#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>

void MyMatrixTransformCallback2D(const MatrixTransformData2D& data)
{
	glm::vec2 myVec;
	glm::mat3 temp =
		Scale (data.scaleX, data.scaleY) *
		Rotate (data.rotate) *
		Translate (data.translateX, data.translateY);

	matrices[data.selectedMatrix] = temp;

	currentTransform = glm::mat3();
	for(int i=0; i<numMatrices; i++)
	{
		currentTransform =  matrices[i] * currentTransform;
	}
}

void MyBasicVectorEquationCallback(const BasicVectorEquationInfo& info)
{
	left = glm::vec2(info.x1, info.y1);
	left = left*info.scalar1;
	right = glm::vec2(info.x2, info.y2);
	right = right*info.scalar2;
	if(info.add)
	{
		result = left + right;
	}
	else
	{
		result = left - right;
	}
}

void MyPerpendicularDataCallback(const PerpendicularData& info)
{
	original = glm::vec2(info.x, info.y);
	normal = glm::normalize(original);
	cwPerpendicular = glm::vec2(original.y, -original.x);
	ccwPerpendicular = glm::vec2(-original.y,original.x);
}

void MyDotProductDataCallback(const DotProductData& data)
{
	if(data.projectOntoLeftVector)
	{
		first = glm::vec2(data.v1i, data.v1j);
		second = glm::vec2(data.v2i, data.v2j);
		projection = glm::normalize(first) * (glm::dot(first, second) / first.length());
		rejection = glm::vec2(second.x - projection.x, second.y - projection.y);
	}
	else
	{
		second = glm::vec2(data.v1i, data.v1j);
		first = glm::vec2(data.v2i, data.v2j);
		projection = glm::normalize(first) * (glm::dot(first, second) / first.length());
		rejection = glm::vec2(second.x - projection.x, second.y - projection.y);
	}
}

void MyLerpDataCallback(const LerpData& data)
{
	a = glm::vec2(data.a_i, data.a_j);
	b = glm::vec2(data.b_i, data.b_j);
	aMinusb = b- a;
	lerpResult = glm::vec2(((1-data.beta)*a.x + data.beta*b.x),((1-data.beta)*a.y + data.beta*b.y));
	aLerpPortion = glm::vec2((1-data.beta)*a.x, (1-data.beta)*a.y);
	bLerpPortion = glm::vec2((data.beta)*b.x, (data.beta)*b.y);
}

void MyLinearTransformationCallback(const LinearTransformationData& data)
{
	glm::vec2 plain(data.v0, data.v1);
	glm::mat2 op(glm::vec2(data.m00, data.m10), glm::vec2(data.m01, data.m11));
	result2 = op*plain;
}

void MyAffineTransformationCallback(const AffineTransformationData& data)
{
	glm::mat3 bases(
		glm::vec3(data.data[0], data.data[3], data.data[6]), 
		glm::vec3(data.data[1], data.data[4], data.data[7]),
		glm::vec3(data.data[2], data.data[5], data.data[8]));

	for(int i=0; i<5; i++)
	{
		affineResults[i].x = data.data[9 + 3*i];
		affineResults[i].y = data.data[10 + 3*i];
		affineResults[i].z = data.data[11 + 3*i];
		affineResults[i] = bases * affineResults[i];
	}
}

void MyMatrixTransformCallback3D(const MatrixTransformData3D& data)
{
	glm::mat4 temp =
		glm::scale(glm::mat4(1.0f), glm::vec3(data.scaleX, data.scaleY, data.scaleZ)) *
		glm::rotate(glm::mat4(1.0f), glm::degrees(data.rotateX), glm::vec3(1,0,0))*
		glm::rotate(glm::mat4(1.0f), glm::degrees(data.rotateY), glm::vec3(0,1,0))*
		glm::rotate(glm::mat4(1.0f), glm::degrees(data.rotateZ), glm::vec3(0,0,1))*
		glm::translate(glm::mat4(1.0f), glm::vec3(data.translateX, data.translateY, data.translateZ));
		

	matrices3D[data.selectedMatrix] = temp;

	fullTransform = glm::mat4();

	for(int i=0; i<numMatrices; i++)
	{
		fullTransform = fullTransform * matrices3D[i];
	}
}

int main(int argc, char* argv[])
{
	Engine::Init();

	RenderUI renderUI;

	renderUI.setBasicVectorEquationData(
		MyBasicVectorEquationCallback,
		&left.x, &right.x, &result.x);

	renderUI.setPerpendicularData(
		&original.x, &normal.x, 
		&cwPerpendicular.x, &ccwPerpendicular.x,
		MyPerpendicularDataCallback);

	renderUI.setDotProductData(
		&first.x, &second.x, &projection.x, &rejection.x,
		MyDotProductDataCallback);

	renderUI.setLerpData(
		&a.x, &b.x, &aMinusb.x, &aLerpPortion.x, &bLerpPortion.x,
		&lerpResult.x, MyLerpDataCallback);

	renderUI.setLinearTransformationData(&result2.x, MyLinearTransformationCallback);

	renderUI.setAffineTransformationData(&affineResults[0].x, MyAffineTransformationCallback);

	renderUI.set2DMatrixVerticesTransformData(&lines[0].x, numLines, reinterpret_cast<float*>(&matrices), 
		reinterpret_cast<float*>(&currentTransform), MyMatrixTransformCallback2D);

	renderUI.set3DMatrixCallback(reinterpret_cast<float*>(&matrices3D), reinterpret_cast<float*>(&fullTransform), MyMatrixTransformCallback3D);

	if( ! renderUI.initialize(argc, argv))
		return -1;

	return renderUI.run();
}