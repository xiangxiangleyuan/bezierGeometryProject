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
	//�������
	int baseDataPercentNum;
	//���������зֵĸ���
	int blineSplitNum;
	//bezier ���߲�����
	int bezierStep;	//�ܵò�����
	int degreeSplitNum;//���Ƕ��з�Բ�ĸ���

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

	//�õ������β�����ӵ�
	float* wizardTailJoin = new float[300];
	float* getWizardTailJoin();
	//���Ӿ���ı��������Ƶ�
	float* joinPoints = new float;
	//�������ߵİٷֱ�
	float* bsplinePercent = new float;
	float* g_vertexTexcoord = new float;
	//�ع�������Ĳ���
	void restructWizardGeom(void* wgPoint);
    void compWizardGeom();
	//�õ����鼯��
	WizardGeom* getCurrWizardGeom(int wgIndex);

private:

};

