#include "BezierGeom.h"


ShaderUtil shaderUtilBezierGeom;
BezierBsplineGeom bezierBsplineGeomBezierGeom;
float paiBezierGeom = 3.1415926 / 180.0;
Scene sceneBezierGeom;
BoneAnimation boneAnimationBezierGeom;
float* BezierGeom::bezierLineIndexes[30];

float bezierLineTransformBezierGather[30000];
int bezierLineTransformPointIndex = 0;
float bezierLineTransformBezierGather2[30000];
int bezierLineTransformPointIndex2 = 0;
float bezierLineTransformOpenBezierGather[30000];
int bezierLineTransformOpenPointIndex = 0;

int BezierGeom::mouthSectionNum = 4;
int BezierGeom::mouthBezierStep = 10;
int BezierGeom::mouthSectionNum2 = 5;
int BezierGeom::mouthBezierStep2 = 6;
int BezierGeom::bodySectionNum = 5;
int BezierGeom::bodyBezierStep = 20;
int BezierGeom::bodySectionNum2 = 6;
int BezierGeom::bodyBezierStep2 = 20;
int BezierGeom::tailSectionNum = 4;
int BezierGeom::tailBezierStep = 6;
int BezierGeom::backSideFinsSectionNum = 4;
int BezierGeom::backSideFinsBezierStep = 10;
int BezierGeom::amboFinsFanBoneSectionNum = 5;
int BezierGeom::amboFinsFanBoneBezierStep = 10;
int BezierGeom::eye0SectionNum = 4;
int BezierGeom::eye0BezierStep = 7;
int BezierGeom::eye1SectionNum = 5;
int BezierGeom::eye1BezierStep = 7;
int BezierGeom::moustacheSectionNum = 6;
int BezierGeom::moustacheBezierStep = 7;

float BezierGeom::amboFinsRoateAngle = 89.0;
float BezierGeom::mouthOpenCloseLeng = 0.0;

BezierGeom::BezierGeom()
{
}

BezierGeom::~BezierGeom()
{
	
}


void BezierGeom::getVerticalVect(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float* resultVect){
	resultVect[0] = v1y * v2z - v2y * v1z;
	resultVect[1] = -(v1x * v2z - v2x * v1z);
	resultVect[2] = v1x * v2y - v2x * v1y;
}

void BezierGeom::normalize(float * vect){

	float length = sqrtf(vect[0] * vect[0] + vect[1] * vect[1] + vect[2] * vect[2]);
	if (length != 0.0f)
	{
		vect[0] = vect[0] / length;
		vect[1] = vect[1] / length;
		vect[2] = vect[2] / length;
	}
}


float BezierGeom::upVect[3] = {0.0,1.0,0.0};
float BezierGeom::innerVect[3] = {0.0,0.0,1.0};
float BezierGeom::leftVect[3] = {1.0,0.0,0.0};
void BezierGeom::makeUpBezierOutline(){
	
	float x0 = -0.04;
	float seaJellyBCP0[30];
	seaJellyBCP0[0] = x0;
	seaJellyBCP0[1] = 0.0;
	seaJellyBCP0[2] = 0.0;
	seaJellyBCP0[3] = x0 - 0.02*upVect[0];
	seaJellyBCP0[4] = 0.0 - 0.02*upVect[1];
	seaJellyBCP0[5] = 0.0 - 0.02*upVect[2];
	seaJellyBCP0[6] = x0 - 0.04*upVect[0];
	seaJellyBCP0[7] = 0.0 - 0.04*upVect[1];
	seaJellyBCP0[8] = 0.0 - 0.04*upVect[2];
	seaJellyBCP0[9] = x0 - 0.05*upVect[0];
	seaJellyBCP0[10] = 0.0 - 0.05*upVect[1];
	seaJellyBCP0[11] = 0.0 - 0.05*upVect[2];
	seaJellyBCP0[12] = x0 - 0.06*upVect[0];
	seaJellyBCP0[13] = 0.0 - 0.06*upVect[1];
	seaJellyBCP0[14] = 0.0 - 0.06*upVect[2];
	float fishBodyBezierLine0[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine0, seaJellyBCP0, bodySectionNum,bodyBezierStep,2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP0,1.0,0.0,0.0,5.0,5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine0, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);

	float x1 = -0.03;
	float seaJellyBCP1[30];
	seaJellyBCP1[0] = x1;
	seaJellyBCP1[1] = 0.0;
	seaJellyBCP1[2] = 0.0;
	seaJellyBCP1[3] = x1 - 0.02*upVect[0];
	seaJellyBCP1[4] = 0.0 - 0.02*upVect[1];
	seaJellyBCP1[5] = 0.0 - 0.02*upVect[2];
	seaJellyBCP1[6] = x1 - 0.04*upVect[0];
	seaJellyBCP1[7] = 0.0 - 0.04*upVect[1];
	seaJellyBCP1[8] = 0.0 - 0.04*upVect[2];
	seaJellyBCP1[9] = x1 - 0.05*upVect[0];
	seaJellyBCP1[10] = 0.0 - 0.05*upVect[1];
	seaJellyBCP1[11] = 0.0 - 0.05*upVect[2];
	seaJellyBCP1[12] = x1 - 0.06*upVect[0];
	seaJellyBCP1[13] = 0.0 - 0.06*upVect[1];
	seaJellyBCP1[14] = 0.0 - 0.06*upVect[2];
	float fishBodyBezierLine1[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine1, seaJellyBCP1, bodySectionNum, bodyBezierStep, 2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP1, 1.0, 0.0, 0.0, 5.0, 5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine1, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);


	float x2 = -0.02;
	float seaJellyBCP2[30];
	seaJellyBCP2[0] = x2 + 0.02*innerVect[0];
	seaJellyBCP2[1] = 0.0 + 0.02*innerVect[1];
	seaJellyBCP2[2] = 0.0 + 0.02*innerVect[2];
	seaJellyBCP2[3] = x2 - 0.02*upVect[0] + 0.03*innerVect[0];
	seaJellyBCP2[4] = 0.0 - 0.02*upVect[1] + 0.03*innerVect[1];
	seaJellyBCP2[5] = 0.0 - 0.02*upVect[2] + 0.03*innerVect[2];
	seaJellyBCP2[6] = x2 - 0.04*upVect[0] + 0.05*innerVect[0];
	seaJellyBCP2[7] = 0.0 - 0.04*upVect[1] + 0.05*innerVect[1];
	seaJellyBCP2[8] = 0.0 - 0.04*upVect[2] + 0.05*innerVect[2];
	seaJellyBCP2[9] = x2 - 0.05*upVect[0] + 0.03*innerVect[0];
	seaJellyBCP2[10] = 0.0 - 0.05*upVect[1] + 0.03*innerVect[1];
	seaJellyBCP2[11] = 0.0 - 0.05*upVect[2] + 0.03*innerVect[2];
	seaJellyBCP2[12] = x2 - 0.06*upVect[0] + 0.02*innerVect[0];
	seaJellyBCP2[13] = 0.0 - 0.06*upVect[1] + 0.02*innerVect[1];
	seaJellyBCP2[14] = 0.0 - 0.06*upVect[2] + 0.02*innerVect[2];
	float fishBodyBezierLine2[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine2, seaJellyBCP2, bodySectionNum, bodyBezierStep, 2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP2, 1.0, 0.0, 0.0, 5.0, 5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine2, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);

	float x3 = -0.01;
	float seaJellyBCP3[30];
	seaJellyBCP3[0] = x3;
	seaJellyBCP3[1] = 0.0;
	seaJellyBCP3[2] = 0.0;
	seaJellyBCP3[3] = x3 - 0.02*upVect[0];
	seaJellyBCP3[4] = 0.0 - 0.02*upVect[1];
	seaJellyBCP3[5] = 0.0 - 0.02*upVect[2];
	seaJellyBCP3[6] = x3 - 0.04*upVect[0];
	seaJellyBCP3[7] = 0.0 - 0.04*upVect[1];
	seaJellyBCP3[8] = 0.0 - 0.04*upVect[2];
	seaJellyBCP3[9] = x3 - 0.05*upVect[0];
	seaJellyBCP3[10] = 0.0 - 0.05*upVect[1];
	seaJellyBCP3[11] = 0.0 - 0.05*upVect[2];
	seaJellyBCP3[12] = x3 - 0.06*upVect[0];
	seaJellyBCP3[13] = 0.0 - 0.06*upVect[1];
	seaJellyBCP3[14] = 0.0 - 0.06*upVect[2];
	float fishBodyBezierLine3[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine3, seaJellyBCP3, bodySectionNum, bodyBezierStep, 2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP3, 1.0, 0.0, 0.0, 5.0, 5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine3, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);

	float x4 = 0.0;
	float seaJellyBCP4[30];
	seaJellyBCP4[0] = x4 + 0.02*innerVect[0];
	seaJellyBCP4[1] = 0.0 + 0.02*innerVect[1];
	seaJellyBCP4[2] = 0.0 + 0.02*innerVect[2];
	seaJellyBCP4[3] = x4 - 0.02*upVect[0] + 0.03*innerVect[0];
	seaJellyBCP4[4] = 0.0 - 0.02*upVect[1] + 0.03*innerVect[1];
	seaJellyBCP4[5] = 0.0 - 0.02*upVect[2] + 0.03*innerVect[2];
	seaJellyBCP4[6] = x4 - 0.04*upVect[0] + 0.05*innerVect[0];
	seaJellyBCP4[7] = 0.0 - 0.04*upVect[1] + 0.05*innerVect[1];
	seaJellyBCP4[8] = 0.0 - 0.04*upVect[2] + 0.05*innerVect[2];
	seaJellyBCP4[9] = x4 - 0.05*upVect[0] + 0.03*innerVect[0];
	seaJellyBCP4[10] = 0.0 - 0.05*upVect[1] + 0.03*innerVect[1];
	seaJellyBCP4[11] = 0.0 - 0.05*upVect[2] + 0.03*innerVect[2];
	seaJellyBCP4[12] = x4 - 0.06*upVect[0] + 0.02*innerVect[0];
	seaJellyBCP4[13] = 0.0 - 0.06*upVect[1] + 0.02*innerVect[1];
	seaJellyBCP4[14] = 0.0 - 0.06*upVect[2] + 0.02*innerVect[2];
	float fishBodyBezierLine4[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine4, seaJellyBCP4, bodySectionNum, bodyBezierStep, 2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP4, 1.0, 0.0, 0.0, 5.0, 5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine4, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);

	float x5 = 0.01;
	float seaJellyBCP5[30];
	seaJellyBCP5[0] = x5;
	seaJellyBCP5[1] = 0.0;
	seaJellyBCP5[2] = 0.0;
	seaJellyBCP5[3] = x5 - 0.02*upVect[0];
	seaJellyBCP5[4] = 0.0 - 0.02*upVect[1];
	seaJellyBCP5[5] = 0.0 - 0.02*upVect[2];
	seaJellyBCP5[6] = x5 - 0.04*upVect[0];
	seaJellyBCP5[7] = 0.0 - 0.04*upVect[1];
	seaJellyBCP5[8] = 0.0 - 0.04*upVect[2];
	seaJellyBCP5[9] = x5 - 0.05*upVect[0];
	seaJellyBCP5[10] = 0.0 - 0.05*upVect[1];
	seaJellyBCP5[11] = 0.0 - 0.05*upVect[2];
	seaJellyBCP5[12] = x5 - 0.06*upVect[0];
	seaJellyBCP5[13] = 0.0 - 0.06*upVect[1];
	seaJellyBCP5[14] = 0.0 - 0.06*upVect[2];
	float fishBodyBezierLine5[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine5, seaJellyBCP5, bodySectionNum, bodyBezierStep, 2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP5, 1.0, 0.0, 0.0, 5.0, 5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine5, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);

	float x6 = 0.02;
	float seaJellyBCP6[30];
	seaJellyBCP6[0] = x6;
	seaJellyBCP6[1] = 0.0;
	seaJellyBCP6[2] = 0.0;
	seaJellyBCP6[3] = x6 - 0.02*upVect[0];
	seaJellyBCP6[4] = 0.0 - 0.02*upVect[1];
	seaJellyBCP6[5] = 0.0 - 0.02*upVect[2];
	seaJellyBCP6[6] = x6 - 0.04*upVect[0];
	seaJellyBCP6[7] = 0.0 - 0.04*upVect[1];
	seaJellyBCP6[8] = 0.0 - 0.04*upVect[2];
	seaJellyBCP6[9] = x6 - 0.05*upVect[0];
	seaJellyBCP6[10] = 0.0 - 0.05*upVect[1];
	seaJellyBCP6[11] = 0.0 - 0.05*upVect[2];
	seaJellyBCP6[12] = x6 - 0.06*upVect[0];
	seaJellyBCP6[13] = 0.0 - 0.06*upVect[1];
	seaJellyBCP6[14] = 0.0 - 0.06*upVect[2];
	float fishBodyBezierLine6[300];
	bezierBsplineGeomBezierGeom.makeBezierLineByPartTag(fishBodyBezierLine6, seaJellyBCP6, bodySectionNum, bodyBezierStep, 2);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(seaJellyBCP6, 1.0, 0.0, 0.0, 5.0, 5);
	bezierBsplineGeomBezierGeom.drawPointLineColorSize(fishBodyBezierLine6, 1.0, 0.5, 0.0, 3.0, bodyBezierStep);

	bezierLineIndexes[0] = fishBodyBezierLine0;
	bezierLineIndexes[1] = fishBodyBezierLine1;
	bezierLineIndexes[2] = fishBodyBezierLine2;
	bezierLineIndexes[3] = fishBodyBezierLine3;
	bezierLineIndexes[4] = fishBodyBezierLine4;
	bezierLineIndexes[5] = fishBodyBezierLine5;
	bezierLineIndexes[6] = fishBodyBezierLine6;


	bezierLineTransformOpenPointIndex = 0;
	bezierLineTransformOpen(bezierLineIndexes, bodyBezierStep, 7, 10, 525, 525);
	bezierBsplineGeomBezierGeom.makeFishOpenBsplinePoints(bezierLineTransformOpenBezierGather, (bodyBezierStep),7, 10, 2);
	//样条控制点之间划分的样条点的个数 * 方形的6个点*一条闭合曲线有几个样条区间*一条贝塞尔线有几个贝塞尔点
	int drawNumber = 10 * 6 * 7 * (bodyBezierStep);
	bezierBsplineGeomBezierGeom.drawFishPart(true, 10, 2, drawNumber);
	std::memset(bezierLineTransformOpenBezierGather, 0, 30000 * sizeof(float));
		

	

}


void BezierGeom::bezierLineTransform(float** bezierLineIndexes, int bezierStep, int degreeNum, int bsplitNum, 
	bool isPointsOrTriangles, int tag0, int tag1){

	for (int bezierSectionIndex = 0; bezierSectionIndex<bezierStep; bezierSectionIndex++){

		for (int degreeIndex = 0; degreeIndex < degreeNum; degreeIndex++){

			float* currBezierLine = bezierLineIndexes[degreeIndex];
			float x = currBezierLine[bezierSectionIndex * 3];
			float y = currBezierLine[bezierSectionIndex * 3 + 1];
			float z = currBezierLine[bezierSectionIndex * 3 + 2];
			int currIndex = bezierLineTransformPointIndex * 3;
			bezierLineTransformBezierGather[currIndex] = x;
			bezierLineTransformBezierGather[currIndex + 1] = y;
			bezierLineTransformBezierGather[currIndex + 2] = z;
			bezierLineTransformPointIndex++;

		}
		//////////////BLINE闭合曲线需要添加的代码//////////////////////////
		int currPointIndex0 = bezierSectionIndex * 3;
		float x0 = bezierLineIndexes[0][currPointIndex0];
		float y0 = bezierLineIndexes[0][currPointIndex0 + 1];
		float z0 = bezierLineIndexes[0][currPointIndex0 + 2];
		int currIndex = bezierLineTransformPointIndex * 3;
		bezierLineTransformBezierGather[currIndex] = x0;
		bezierLineTransformBezierGather[currIndex + 1] = y0;
		bezierLineTransformBezierGather[currIndex + 2] = z0;
		bezierLineTransformPointIndex++;

		currIndex = bezierLineTransformPointIndex * 3;
		int currPointIndex1 = bezierSectionIndex * 3;
		float x1 = bezierLineIndexes[1][currPointIndex1];
		float y1 = bezierLineIndexes[1][currPointIndex1 + 1];
		float z1 = bezierLineIndexes[1][currPointIndex1 + 2];
		bezierLineTransformBezierGather[currIndex] = x1;
		bezierLineTransformBezierGather[currIndex + 1] = y1;
		bezierLineTransformBezierGather[currIndex + 2] = z1;
		bezierLineTransformPointIndex++;

		currIndex = bezierLineTransformPointIndex * 3;
		int currPointIndex2 = bezierSectionIndex * 3;
		float x2 = bezierLineIndexes[2][currPointIndex2];
		float y2 = bezierLineIndexes[2][currPointIndex2 + 1];
		float z2 = bezierLineIndexes[2][currPointIndex2 + 2];
		bezierLineTransformBezierGather[currIndex] = x2;
		bezierLineTransformBezierGather[currIndex + 1] = y2;
		bezierLineTransformBezierGather[currIndex + 2] = z2;
		bezierLineTransformPointIndex++;

		currIndex = bezierLineTransformPointIndex * 3;
		int currPointIndex3 = bezierSectionIndex * 3;
		float x3 = bezierLineIndexes[3][currPointIndex3];
		float y3 = bezierLineIndexes[3][currPointIndex3 + 1];
		float z3 = bezierLineIndexes[3][currPointIndex3 + 2];
		bezierLineTransformBezierGather[currIndex] = x3;
		bezierLineTransformBezierGather[currIndex + 1] = y3;
		bezierLineTransformBezierGather[currIndex + 2] = z3;
		bezierLineTransformPointIndex++;

	}
	
}

void BezierGeom::bezierLineTransformOpen(float** bezierLineIndexes, int bezierStep, 
	int degreeNum, int bsplitNum, int tag0, int tag1){
	//int pointer = 0;
	for (int bezierSectionIndex = 0; bezierSectionIndex<bezierStep; bezierSectionIndex++){

		for (int degreeIndex = 0; degreeIndex < degreeNum; degreeIndex++){

			float* currBezierLine = bezierLineIndexes[degreeIndex];
			float x = currBezierLine[bezierSectionIndex * 3];
			float y = currBezierLine[bezierSectionIndex * 3 + 1];
			float z = currBezierLine[bezierSectionIndex * 3 + 2];
			int currIndex = bezierLineTransformOpenPointIndex * 3;
			
			bezierLineTransformOpenBezierGather[currIndex] = x;
			bezierLineTransformOpenBezierGather[currIndex + 1] = y;
			bezierLineTransformOpenBezierGather[currIndex + 2] = z;
			bezierLineTransformOpenPointIndex++;

		}

	}

}

void BezierGeom::bezierLineTransform2(float** bezierLineIndexes, int bezierStep, int degreeNum, int bsplitNum,
	bool isPointsOrTriangles, int tag0, int tag1){

	for (int bezierSectionIndex = 0; bezierSectionIndex<bezierStep; bezierSectionIndex++){

		for (int degreeIndex = 0; degreeIndex < degreeNum; degreeIndex++){

			float* currBezierLine = bezierLineIndexes[degreeIndex];
			float x = currBezierLine[bezierSectionIndex * 3];
			float y = currBezierLine[bezierSectionIndex * 3 + 1];
			float z = currBezierLine[bezierSectionIndex * 3 + 2];
			int currIndex = bezierLineTransformPointIndex2 * 3;
			bezierLineTransformBezierGather2[currIndex] = x;
			bezierLineTransformBezierGather2[currIndex + 1] = y;
			bezierLineTransformBezierGather2[currIndex + 2] = z;
			bezierLineTransformPointIndex2++;

		}
		//////////////BLINE闭合曲线需要添加的代码//////////////////////////
		int currPointIndex0 = bezierSectionIndex * 3;
		float x0 = bezierLineIndexes[0][currPointIndex0];
		float y0 = bezierLineIndexes[0][currPointIndex0 + 1];
		float z0 = bezierLineIndexes[0][currPointIndex0 + 2];
		int currIndex = bezierLineTransformPointIndex2 * 3;
		bezierLineTransformBezierGather2[currIndex] = x0;
		bezierLineTransformBezierGather2[currIndex + 1] = y0;
		bezierLineTransformBezierGather2[currIndex + 2] = z0;
		bezierLineTransformPointIndex2++;

		currIndex = bezierLineTransformPointIndex2 * 3;
		int currPointIndex1 = bezierSectionIndex * 3;
		float x1 = bezierLineIndexes[1][currPointIndex1];
		float y1 = bezierLineIndexes[1][currPointIndex1 + 1];
		float z1 = bezierLineIndexes[1][currPointIndex1 + 2];
		bezierLineTransformBezierGather2[currIndex] = x1;
		bezierLineTransformBezierGather2[currIndex + 1] = y1;
		bezierLineTransformBezierGather2[currIndex + 2] = z1;
		bezierLineTransformPointIndex2++;

		currIndex = bezierLineTransformPointIndex2 * 3;
		int currPointIndex2 = bezierSectionIndex * 3;
		float x2 = bezierLineIndexes[2][currPointIndex2];
		float y2 = bezierLineIndexes[2][currPointIndex2 + 1];
		float z2 = bezierLineIndexes[2][currPointIndex2 + 2];
		bezierLineTransformBezierGather2[currIndex] = x2;
		bezierLineTransformBezierGather2[currIndex + 1] = y2;
		bezierLineTransformBezierGather2[currIndex + 2] = z2;
		bezierLineTransformPointIndex2++;

		currIndex = bezierLineTransformPointIndex2 * 3;
		int currPointIndex3 = bezierSectionIndex * 3;
		float x3 = bezierLineIndexes[3][currPointIndex3];
		float y3 = bezierLineIndexes[3][currPointIndex3 + 1];
		float z3 = bezierLineIndexes[3][currPointIndex3 + 2];
		bezierLineTransformBezierGather2[currIndex] = x3;
		bezierLineTransformBezierGather2[currIndex + 1] = y3;
		bezierLineTransformBezierGather2[currIndex + 2] = z3;
		bezierLineTransformPointIndex2++;

	}

}


void BezierGeom::point2Line(float* point,float* linePoint0,float* linePoint1){

	//当前点和向量点之间的向量
	float point2LinePointVect[] = { point[0] - linePoint0[0], point[1] - linePoint0[1], point[2] - linePoint0[2] };
	normalize(point2LinePointVect);
	float lineVect[] = { linePoint0[0] - linePoint1[0], linePoint0[1] - linePoint1[1], linePoint0[2] - linePoint1[2] };
	normalize(lineVect);

	float coseValue = (point2LinePointVect[0] * lineVect[0] + point2LinePointVect[1] * lineVect[1] + point2LinePointVect[2] * lineVect[2]) /
		(sqrt(point2LinePointVect[0] * point2LinePointVect[0] + point2LinePointVect[1] * point2LinePointVect[1] + point2LinePointVect[2] * point2LinePointVect[2]))*
		(sqrt(lineVect[0] * lineVect[0] + lineVect[1] * lineVect[1] + lineVect[2] * lineVect[2]));

	//斜边长度
	float bevelLeng = sqrt((point[0] - linePoint0[0])*(point[0] - linePoint0[0]) +
		(point[1] - linePoint0[1])*(point[1] - linePoint0[1]) + (point[2] - linePoint0[2])*(point[2] - linePoint0[2]));

	float dis = bevelLeng * coseValue;
	//中间线顶点沿中间线移动距离后的点
	float purpX = linePoint0[0] + dis*lineVect[0];
	float purpY = linePoint0[1] + dis*lineVect[1];
	float purpZ = linePoint0[2] + dis*lineVect[2];
	float purpPoint[] = { purpX, purpY, purpZ };
	//bezierBsplineGeomBezierGeom.drawPointLineColorSize(purpPoint,1.0,0.0,0.7,5.0,1);
}


void BezierGeom::makeUpBsplineLimitedNum(int blineSplitNum, float* bezierPointCoral0th,
	float* bezierPointCoral1th, float* bezierPointCoral2th, float* bezierPointCoral3th, float* resultBspline,int limitedNum){

	float f1, f2, f3, f4;
	float deltaT = 1.0 / float(blineSplitNum);
	float T;
	for (int i = 0; i < limitedNum; i++)
	{
		T = float(i)*deltaT;
		f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
		f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
		f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
		f4 = (T*T*T) / 6.0;

		float x = f1 * bezierPointCoral0th[0] +
			f2 * bezierPointCoral1th[0] +
			f3 * bezierPointCoral2th[0] +
			f4 * bezierPointCoral3th[0];
		float y = f1 * bezierPointCoral0th[1] +
			f2 * bezierPointCoral1th[1] +
			f3 * bezierPointCoral2th[1] +
			f4 * bezierPointCoral3th[1];
		float z = f1 * bezierPointCoral0th[2] +
			f2 * bezierPointCoral1th[2] +
			f3 * bezierPointCoral2th[2] +
			f4 * bezierPointCoral3th[2];
		int currIndex = i * 3;
		resultBspline[currIndex] = x;
		resultBspline[currIndex + 1] = y;
		resultBspline[currIndex + 2] = z;
	}

}


void BezierGeom::makeUpBspline(int blineSplitNum, float* bezierPointCoral0th, 
	float* bezierPointCoral1th, float* bezierPointCoral2th, float* bezierPointCoral3th, float* resultBspline)
{
	float f1, f2, f3, f4;
	float deltaT = 1.0 / float(blineSplitNum);
	float T;
	for (int i = 0; i < blineSplitNum; i++)
	{
		T = float(i)*deltaT;
		f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
		f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
		f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
		f4 = (T*T*T) / 6.0;

		float x = f1 * bezierPointCoral0th[0] +
			f2 * bezierPointCoral1th[0] +
			f3 * bezierPointCoral2th[0] +
			f4 * bezierPointCoral3th[0];
		float y = f1 * bezierPointCoral0th[1] +
			f2 * bezierPointCoral1th[1] +
			f3 * bezierPointCoral2th[1] +
			f4 * bezierPointCoral3th[1];
		float z = f1 * bezierPointCoral0th[2] +
			f2 * bezierPointCoral1th[2] +
			f3 * bezierPointCoral2th[2] +
			f4 * bezierPointCoral3th[2];
		int currIndex = i * 3;
		resultBspline[currIndex] = x;
		resultBspline[currIndex + 1] = y;
		resultBspline[currIndex + 2] = z;
	}
}

void BezierGeom::makeUpSomeBsplines(int blineSplitNum, int listTotal, float* bezierControlPoints, float* resultBspline)
{
	float f1, f2, f3, f4;
	float deltaT = 1.0 / float(blineSplitNum);
	float T;
	for (int listIndex = 0; listIndex < listTotal; listIndex++){

		for (int i = 0; i < blineSplitNum; i++){
			T = float(i)*deltaT;
			f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
			f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
			f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
			f4 = (T*T*T) / 6.0;

			int currIndex0th = listIndex * 3;
			int currIndex1th = (listIndex+1) * 3;
			int currIndex2th = (listIndex+2) * 3;
			int currIndex3th = (listIndex+3) * 3;

			float x = f1 * bezierControlPoints[currIndex0th] +
				f2 * bezierControlPoints[currIndex1th] +
				f3 * bezierControlPoints[currIndex2th] +
				f4 * bezierControlPoints[currIndex3th];
			float y = f1 * bezierControlPoints[currIndex0th + 1] +
				f2 * bezierControlPoints[currIndex1th + 1] +
				f3 * bezierControlPoints[currIndex2th + 1] +
				f4 * bezierControlPoints[currIndex3th + 1];
			float z = f1 * bezierControlPoints[currIndex0th + 2] +
				f2 * bezierControlPoints[currIndex1th + 2] +
				f3 * bezierControlPoints[currIndex2th + 2] +
				f4 * bezierControlPoints[currIndex3th + 2];

			int currIndex = (listIndex*blineSplitNum + i) * 3;
			resultBspline[currIndex] = x;
			resultBspline[currIndex + 1] = y;
			resultBspline[currIndex + 2] = z;
		}

	}
	
}
