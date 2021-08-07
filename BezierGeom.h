#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "BezierBsplineGeom.h"
#include "ShaderUtil.h"
#include "Scene.h"
#include "BoneAnimation.h"
class BezierGeom
{
public:
	BezierGeom();
	~BezierGeom();

	static float* bezierLineIndexes[30];
	static int mouthSectionNum;
	static int mouthBezierStep;
	static int mouthSectionNum2;
	static int mouthBezierStep2;
	static int bodySectionNum;
	static int bodyBezierStep;
	static int bodySectionNum2;
	static int bodyBezierStep2;
	static int tailSectionNum;
	static int tailBezierStep;
	static int backSideFinsSectionNum;
	static int backSideFinsBezierStep;
	static int amboFinsFanBoneSectionNum;
	static int amboFinsFanBoneBezierStep;
	static int eye0SectionNum;
	static int eye0BezierStep;
	static int eye1SectionNum;
	static int eye1BezierStep;
	static int moustacheSectionNum;
	static int moustacheBezierStep;
	//��������������ת�ĽǶ�
	static float amboFinsRoateAngle;
	//���쿪�ϵĸ߶�
	static float mouthOpenCloseLeng;


	static float upVect[3];
	static float innerVect[3];
	static float leftVect[3];

	void makeUpBezierOutline();
	void getVerticalVect(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float* resultVect);
	void normalize(float * vect);
	void makeUpBspline(int blineSplitNum, float* bezierPointCoral0th,
		float* bezierPointCoral1th, float* bezierPointCoral2th, float* bezierPointCoral3th, float* resultBspline);
	//*********
	void makeUpBsplineLimitedNum(int blineSplitNum, float* bezierPointCoral0th,
		float* bezierPointCoral1th, float* bezierPointCoral2th, float* bezierPointCoral3th, float* resultBspline, int limitedNum);
	void makeUpSomeBsplines(int blineSplitNum, int listTotal, float* bezierControlPoints, float* resultBspline);
	//�㵽�ߵĵ�
	void point2Line(float* point, float* linePoint0, float* linePoint1);
	//�������ߵ�����ת��  *********
	void bezierLineTransform(float** bezierLineIndexes, int bezierStep, int degreeNum, int bsplitNum, bool isPointsOrTriangles, int tag0, int tag1);
	void bezierLineTransform2(float** bezierLineIndexes, int bezierStep, int degreeNum, int bsplitNum, bool isPointsOrTriangles, int tag0, int tag1);
	//�������߶�ת��  **********
	void bezierLineTransformOpen(float** bezierLineIndexes, int bezierStep, int degreeNum, int bsplitNum, int tag0, int tag1);


private:

};

