#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "esUtil.h"
#include "ShaderUtil.h"
#include "Scene.h"
class BezierBsplineGeom
{
public:
	BezierBsplineGeom();
	~BezierBsplineGeom();

	static float windowWidth;
	static float windowHeight;

	static float shaderPointsBalloonFish1[300000];
	static float shaderPointsBalloonFish2[300000];
	static float shaderPointsBalloonFish3[300000];
	static float shaderPointsBalloonFish4[300000];

	static float trueShaderPointsBalloonFish1[1000000];
	static float trueShaderPointsBalloonFish2[1000000];
	static float trueShaderPointsBalloonFish3[1000000];
	static float trueShaderPointsBalloonFish4[1000000];
	static float blineIndicesFEBalloonFish[1000000];
	static float textureTags[1000000];
	static float texcoordGatherBalloonFish[300000];

	//����ID
	static GLuint texId_0;
	static GLuint texId_1;
	static GLuint texId_2;
	static GLuint texId_3;
	static GLuint texId_4;
	static GLuint texId_5;
	static GLuint texId_6;
	static GLuint texId_7;
	static GLuint texId_8;
	static GLuint texId_9;


	void makeUpBspline(float* bsplineControlPoints, int blineSplitNum, int bsplineControlNumber, float* bsplinePoints);
	void makeUpBezierLine(float* bezierPoints, float* bezierControlPoints, int sectionNum, int bezierStep);
	int factrial(int factrialCount);
	void makeOthBsplinePoint(float* bsplineControl0th, float* bsplineControl1th, 
		float* bsplineControl2th, float* bsplineControl3th, float* resultPoint);
	void buildClosedBsplineGeom(float** bezierPointIndexes, int blineDegreeNum, int bezierStep);
	void makeFishBsplinePoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum, int tag);
	void makeFishBsplinePoints2(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum, int tag);
	//���㿪��ʽ����������
	void makeFishOpenBsplinePoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum2, int tag);
	void drawFish0th(bool isDrawPoints, int bsplineNum, int tag);
	void drawFishPart(bool isDrawPoints, int bsplineNum, int tag, int drawNumber);
	//���Ƶ����
	void drawPointLineColorSize(float* points, float r, float g, float b, float size, int number);
	//���ݱ�����������������ֵ
	void setTextureTags(int tag, int rowIndex, int GPUXIndex, int GPUYIndex, int GPUZIndex);
	void setOpenTextureTags(int tag, int rowIndex, int GPUXIndex, int GPUYIndex, int GPUZIndex);

	void setTexcoordSTCoord(int tag, int rowIndex, int texcoordSIndex, int texcoordTIndex);
	//�������첿�ֵı������߶�(������)
	void makeUpMouthBezierLine(float* bezierPoints, float* bezierControlPoints, int sectionNum, int bezierStep);
	//���ݱ�Ǽ��㱴�����߶�
	void makeBezierLineByPartTag(float* bezierPoints, float* bezierControlPoints, int sectionNum, int bezierStep, int partTag);

private:

};

