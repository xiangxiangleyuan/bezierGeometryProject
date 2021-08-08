#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "scene.h"

class WizardGeomSupple
{
public:
	WizardGeomSupple();
	~WizardGeomSupple();
	static float baseLinePercentPoints[90];
	static float currentPoint[3];
	void averageCircle(float percent, int perNum,float splitRadius,void* wgPoint);
	void getCurrentPoint(float percent,int perNum, void* wgPoint);
	float* makeUpCirclePoints(void* wgPoint);
	//Æ´½Ó¾«Áé
	void joinWizardGeom();

	float* GetVerticalPointByVect(float baseX, float baseY, float baseZ,
		float middLineX, float middLineY, float middLineZ, float leng, float splitRadius);
	static void normalize(float * vect);
	static void getVerticalVect(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float* verticalVect);


};
