#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "ggl.h"

class WizardGeom
{
public:
	WizardGeom(float* baseData, float* baseDataPercent,
		int baseDataPercentNum, int degreeSplitNum, int bezierStep, int blineSplitNum,bool isFishBody);
	WizardGeom();
	~WizardGeom();

	////////////////////////////////////////////////////////////////////////
    bool isFishBody;
    GLuint blinePoints1Location;
    GLuint blinePoints2Location;
    GLuint blinePoints3Location;
    GLuint blinePoints4Location;
    GLuint blindex1Location;
    GLuint blindex2Location;
    GLuint blinePercentLocation;
    GLuint projectionMatrixLocation;
    GLuint viewMatrixLocation;
    GLuint modelMatrixLocation;
	GLuint lightPositionLocation;
	GLuint modelInverseTransposeMatrixLocation;
	GLuint cameraPositionLocation;
	GLuint wizardGeomIndexLocation;


    float* baseData = new float[6];
	float* splitPoints = new float[500000];
	float* baseDataPercent = new float[500];
	int* geomIndices = new int;

	float* blinesPoints = new float;
	//切面个数
	int baseDataPercentNum;
	//样条曲线切分的个数
	int blineSplitNum;
	//bezier 曲线步进数
	int bezierStep;	//总得步进数
	int degreeSplitNum;//按角度切分圆的个数

	float* bezPointGather = new float;
    float* bezPointGatherCache = new float;

    float* bezierShaderPoints1 = new float;
	float* bezierShaderPoints2 = new float;
	float* bezierShaderPoints3 = new float;
	float* bezierShaderPoints4 = new float;
	float* blineFactors1 = new float;
	float* blineFactors2 = new float;
	float* trueBezierShaderPoints1 = new float;
	float* trueBezierShaderPoints2 = new float;
	float* trueBezierShaderPoints3 = new float;
	float* trueBezierShaderPoints4 = new float;
	float* trueBlineFactors1 = new float;
	float* trueBlineFactors2 = new float;

	//得到精灵的尾部连接点
	float* wizardTailJoin = new float[300];
	float* getWizardTailJoin();
	//连接精灵的贝塞尔控制点
	float* joinPoints = new float;
	//样条曲线的百分比
	float* bsplinePercent = new float;
	float* g_vertexTexcoord = new float;
	//重构精灵体的参数
	void restructWizardGeom(void* wgPoint);
    void compWizardGeom();
	//得到精灵集合
	WizardGeom* getCurrWizardGeom(int wgIndex);

private:

};

