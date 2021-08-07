#include "BezierBsplineGeom.h"

ShaderUtil shaderUtilBezierBsplineGeom;
BezierBsplineGeom::BezierBsplineGeom()
{
}

BezierBsplineGeom::~BezierBsplineGeom()
{
}

//float BezierBsplineGeom::windowWidth = 2240/4 + 150 + 100;
//float BezierBsplineGeom::windowHeight = 780/2 + 20 + 100;
float BezierBsplineGeom::windowWidth = 2240;
float BezierBsplineGeom::windowHeight = 780;
GLuint BezierBsplineGeom::texId_0;
GLuint BezierBsplineGeom::texId_1;
GLuint BezierBsplineGeom::texId_2;
GLuint BezierBsplineGeom::texId_3;
GLuint BezierBsplineGeom::texId_4;
GLuint BezierBsplineGeom::texId_5;
GLuint BezierBsplineGeom::texId_6;
GLuint BezierBsplineGeom::texId_7;
GLuint BezierBsplineGeom::texId_8;
GLuint BezierBsplineGeom::texId_9;
void BezierBsplineGeom::makeUpBspline(float* bsplineControlPoints,int blineSplitNum,int bsplineControlNumber,float* bsplinePoints)
{
	
	float f1, f2, f3, f4;
	for (int i = 0; i < blineSplitNum; i++)
	{
		float T = float(i) / float(blineSplitNum);
		f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
		f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
		f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
		f4 = (T*T*T) / 6.0;

		{
			
			for (int j = 0; j < bsplineControlNumber; j++) {
				int currIndex0th = j * 3;
				int currIndex1th = (j+1) * 3;
				int currIndex2th = (j+2) * 3;
				int currIndex3th = (j+3) * 3;

				float x = f1 * bsplineControlPoints[currIndex0th] +
					f2 * bsplineControlPoints[currIndex1th] +
					f3 * bsplineControlPoints[currIndex2th] +
					f4 * bsplineControlPoints[currIndex3th];
				float y = f1 * bsplineControlPoints[currIndex0th+1] +
					f2 * bsplineControlPoints[currIndex1th+1] +
					f3 * bsplineControlPoints[currIndex2th+1] +
					f4 * bsplineControlPoints[currIndex3th+1];
				float z = f1 * bsplineControlPoints[currIndex0th+2] +
					f2 * bsplineControlPoints[currIndex1th+2] +
					f3 * bsplineControlPoints[currIndex2th+2] +
					f4 * bsplineControlPoints[currIndex3th+2];

				int bsplineIndex = (j*blineSplitNum+i)*3;
				bsplinePoints[bsplineIndex] = x;
				bsplinePoints[bsplineIndex+1] = y;
				bsplinePoints[bsplineIndex+2] = z;

			}
		}
	}
}


void BezierBsplineGeom::makeBezierLineByPartTag(float* bezierPoints, float* bezierControlPoints, int sectionNum, int bezierStep, int partTag)
{


	//1 代表是嘴巴
	if (partTag == 1){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::mouhBernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//2 代表是鱼身
	if (partTag == 2){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::bodyBernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//3 代表是鱼尾
	if (partTag == 3){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::tailBernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//4 代表是鱼的背鳍
	if (partTag == 4){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::backSideFinsBernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//5 两侧鱼鳍的骨骼
	if (partTag == 5){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::amboFinsFanBoneBernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}


	//6 鱼的眼睛
	if (partTag == 6){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::eye0BernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//7 鱼的眼睛
	if (partTag == 7){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::eye1BernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//8 鱼的胡须
	if (partTag == 8){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::moustacheBernsteinFactor[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//9 第二个鱼身
	if (partTag == 9){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::bodyBernsteinFactor2[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}

	//10 第二个鱼嘴
	if (partTag == 9){
		int sectionNumber = sectionNum - 1;
		//循环每个点
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			for (int k = 0; k <= sectionNumber; k++)
			{
				float xs = BoneAnimation::mouhBernsteinFactor2[i*(sectionNumber + 1) + k];
				xf = xf + bezierControlPoints[k * 3] * xs;
				yf = yf + bezierControlPoints[k * 3 + 1] * xs;
				zf = zf + bezierControlPoints[k * 3 + 2] * xs;
			}

			bezierPoints[i * 3] = xf;
			bezierPoints[i * 3 + 1] = yf;
			bezierPoints[i * 3 + 2] = zf;

		}

		return;
	}



	int sectionNumber = sectionNum - 1;
	float factResArr[100];//介乘结果的集合
	for (int i = 0; i <= sectionNumber; i++){	//求0到n的阶乘
		factResArr[i] = factrial(i);
	}
	//循环每个点
	for (int i = 0; i <= bezierStep; i++)
	{
		//在bezier曲线上的节点的百分数
		float bezierPercentFractor = float(i) / float(bezierStep);
		if (bezierPercentFractor > 1)
		{
			bezierPercentFractor = 1;
		}

		float tka[100];
		float otka[100];
		for (int j = 0; j <= sectionNumber; j++)
		{
			tka[j] = (float)pow(bezierPercentFractor, j); //计算t的j次幂
			otka[j] = (float)pow(1.0 - bezierPercentFractor, j); //计算1-t的j次幂
		}

		float xf = 0.0;
		float yf = 0.0;
		float zf = 0.0;
		for (int k = 0; k <= sectionNumber; k++)
		{
			float xs = (factResArr[sectionNumber] / (factResArr[k] * factResArr[sectionNumber - k])) * tka[k] * otka[sectionNumber - k];
			xf = xf + bezierControlPoints[k * 3] * xs;
			yf = yf + bezierControlPoints[k * 3 + 1] * xs;
			zf = zf + bezierControlPoints[k * 3 + 2] * xs;
		}

		bezierPoints[i * 3] = xf;
		bezierPoints[i * 3 + 1] = yf;
		bezierPoints[i * 3 + 2] = zf;

	}


}



void BezierBsplineGeom::makeUpBezierLine(float* bezierPoints, float* bezierControlPoints, int sectionNum, int bezierStep)
{

	
	int sectionNumber = sectionNum - 1;
	float factResArr[100];//介乘结果的集合
	for (int i = 0; i <= sectionNumber; i++){	//求0到n的阶乘
		factResArr[i] = factrial(i);
	}
	//循环每个点
	for (int i = 0; i <= bezierStep; i++)
	{
		//在bezier曲线上的节点的百分数
		float bezierPercentFractor = float(i) / float(bezierStep);
		if (bezierPercentFractor > 1)
		{
			bezierPercentFractor = 1;
		}

		float tka[100];
		float otka[100];
		for (int j = 0; j <= sectionNumber; j++)
		{
			tka[j] = (float)pow(bezierPercentFractor, j); //计算t的j次幂
			otka[j] = (float)pow(1.0 - bezierPercentFractor, j); //计算1-t的j次幂
		}

		float xf = 0.0;
		float yf = 0.0;
		float zf = 0.0;
		for (int k = 0; k <= sectionNumber; k++)
		{
			float xs = (factResArr[sectionNumber] / (factResArr[k] * factResArr[sectionNumber - k])) * tka[k] * otka[sectionNumber - k];
			xf = xf + bezierControlPoints[k * 3] * xs;
			yf = yf + bezierControlPoints[k * 3 + 1] * xs;
			zf = zf + bezierControlPoints[k * 3 + 2] * xs;
		}

		bezierPoints[i * 3] = xf;
		bezierPoints[i * 3 + 1] = yf;
		bezierPoints[i * 3 + 2] = zf;

	}


}

//介乘
int BezierBsplineGeom::factrial(int factrialCount)
{
	int factrialResult = 1;	//声明一个long型的变量
	if (factrialCount == 0)			//0的阶乘为1
	{
		return 1;
	}

	for (int i = 2; i <= factrialCount; i++){	//求大于等于2的数的阶乘
		factrialResult = factrialResult*i;
	}

	return factrialResult;	//返回结果

}


void BezierBsplineGeom::makeOthBsplinePoint(float* bsplineControl0th, float* bsplineControl1th, float* bsplineControl2th, float* bsplineControl3th, float* resultPoint)
{

	float f1 = 1.0 / 6.0;
	float f2 = 4.0 / 6.0;
	float f3 = 1.0 / 6.0;
	float x = f1 * bsplineControl0th[0] + f2 * bsplineControl1th[0] + f3 * bsplineControl2th[0];
	float y = f1 * bsplineControl0th[1] + f2 * bsplineControl1th[1] + f3 * bsplineControl2th[1];
	float z = f1 * bsplineControl0th[2] + f2 * bsplineControl1th[2] + f3 * bsplineControl2th[2];
	resultPoint[0] = x;
	resultPoint[1] = y;
	resultPoint[2] = z;

}

float bezierGatherAfter[300000];
void BezierBsplineGeom::buildClosedBsplineGeom(float** bezierPointIndexes, int blineDegreeNum, int bezierStep){

	int pointIndex = 0;
	for (int bezierSectionIndex = 0; bezierSectionIndex<bezierStep; bezierSectionIndex++){

		for (int degreeIndex = 0; degreeIndex<blineDegreeNum; degreeIndex++){

			float* currBezierLine = bezierPointIndexes[degreeIndex];
			//int currPointIndex = degreeIndex*bezierStep * 3 + bezierSectionIndex * 3;
			int currIndex = bezierSectionIndex * 3;
			float x = currBezierLine[currIndex];
			float y = currBezierLine[currIndex + 1];
			float z = currBezierLine[currIndex + 2];

			bezierGatherAfter[pointIndex * 3] = x;
			bezierGatherAfter[pointIndex * 3 + 1] = y;
			bezierGatherAfter[pointIndex * 3 + 2] = z;
			pointIndex++;

		}
		//////////////BLINE闭合曲线需要添加的代码//////////////////////////
		int currPointIndex0 = bezierSectionIndex * 3;
		float x0 = bezierPointIndexes[0][currPointIndex0];
		float y0 = bezierPointIndexes[0][currPointIndex0 + 1];
		float z0 = bezierPointIndexes[0][currPointIndex0 + 2];
		bezierGatherAfter[pointIndex * 3] = x0;
		bezierGatherAfter[pointIndex * 3 + 1] = y0;
		bezierGatherAfter[pointIndex * 3 + 2] = z0;
		pointIndex++;

		int currPointIndex1 = bezierSectionIndex * 3;
		float x1 = bezierPointIndexes[1][currPointIndex1];
		float y1 = bezierPointIndexes[1][currPointIndex1 + 1];
		float z1 = bezierPointIndexes[1][currPointIndex1 + 2];
		bezierGatherAfter[pointIndex * 3] = x1;
		bezierGatherAfter[pointIndex * 3 + 1] = y1;
		bezierGatherAfter[pointIndex * 3 + 2] = z1;
		pointIndex++;

		int currPointIndex2 = bezierSectionIndex * 3;
		float x2 = bezierPointIndexes[2][currPointIndex2];
		float y2 = bezierPointIndexes[2][currPointIndex2 + 1];
		float z2 = bezierPointIndexes[2][currPointIndex2 + 2];
		bezierGatherAfter[pointIndex * 3] = x2;
		bezierGatherAfter[pointIndex * 3 + 1] = y2;
		bezierGatherAfter[pointIndex * 3 + 2] = z2;
		pointIndex++;

		int currPointIndex3 = bezierSectionIndex * 3;
		float x3 = bezierPointIndexes[3][currPointIndex3];
		float y3 = bezierPointIndexes[3][currPointIndex3 + 1];
		float z3 = bezierPointIndexes[3][currPointIndex3 + 2];
		bezierGatherAfter[pointIndex * 3] = x3;
		bezierGatherAfter[pointIndex * 3 + 1] = y3;
		bezierGatherAfter[pointIndex * 3 + 2] = z3;
		pointIndex++;

	}

	makeFishBsplinePoints(bezierGatherAfter, bezierStep, blineDegreeNum + 4, 10, 100);
	int drawNumber = 10 * 6 * (blineDegreeNum+4)* (bezierStep + 4);//样条间隔*方形6个点*样条区间个数*贝塞尔阶数
	drawFishPart(false, 10, 2, drawNumber);
}

float BezierBsplineGeom::shaderPointsBalloonFish1[300000];
float BezierBsplineGeom::shaderPointsBalloonFish2[300000];
float BezierBsplineGeom::shaderPointsBalloonFish3[300000];
float BezierBsplineGeom::shaderPointsBalloonFish4[300000];

float BezierBsplineGeom::trueShaderPointsBalloonFish1[1000000];
float BezierBsplineGeom::trueShaderPointsBalloonFish2[1000000];
float BezierBsplineGeom::trueShaderPointsBalloonFish3[1000000];
float BezierBsplineGeom::trueShaderPointsBalloonFish4[1000000];
float BezierBsplineGeom::blineIndicesFEBalloonFish[1000000];
float BezierBsplineGeom::textureTags[1000000];
float BezierBsplineGeom::texcoordGatherBalloonFish[300000];

//static float* trueShaderPointsBalloonFish1 = new float[600000];
//static float* trueShaderPointsBalloonFish2 = new float[600000];
//static float* trueShaderPointsBalloonFish3 = new float[600000];
//static float* trueShaderPointsBalloonFish4 = new float[600000];
//static float* blineIndicesFEBalloonFish = new float[600000];
//static float* textureTags = new float[600000];
//static float* texcoordGatherBalloonFish = new float[6000000];


void BezierBsplineGeom::makeFishBsplinePoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum2, int tag)
{
	
	int blineSplitNum = 0;
	//为GPU分解成四分数据
	for (int rowIndex = 0; rowIndex < rowTotal; rowIndex++)
	{

		int currCPUIndex = rowIndex*listTotal * 3;
		for (int listIndex = 0; listIndex < listTotal - 3; listIndex++)
		{
			
			blineSplitNum = blineSplitNum2;
			for (int pointIndex = 0; pointIndex < blineSplitNum; pointIndex++)
			{
				//GPU渲染点在整条线段的索引值
				int fullLineGPUPointIndex = rowIndex*(listTotal - 3)*blineSplitNum         ;
				//GPU渲染点在当前线段某个区间段的索引值
				int currGPUPointIndex = listIndex * blineSplitNum + pointIndex;
				int currentBlineIndex = (fullLineGPUPointIndex + currGPUPointIndex) * 3;


				int currListIndex = listIndex * 3;
				shaderPointsBalloonFish1[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 1) * 3;
				shaderPointsBalloonFish2[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 2) * 3;
				shaderPointsBalloonFish3[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 3) * 3;
				shaderPointsBalloonFish4[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];

			}
		}

	}


	//在GPU里构建面片
	int currentGPUIndex = 0;
	int evenum = 3;
	int everyFullBlineTotal = blineSplitNum * (listTotal - 3);
	int backSideBezierTotalNum = 11 * BezierGeom::backSideFinsBezierStep;//11*15
	int amboFinsBezierTotalNum = 18 * BezierGeom::amboFinsFanBoneBezierStep * 2;//360
	for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
	{
		if (tag == 501){
			if ((rowIndex+1) % BezierGeom::amboFinsFanBoneBezierStep == 0){
				continue;
			}
		}
	
		if (tag == 111){
			if (rowIndex == 7 || rowIndex == 15 || rowIndex == 23){
				continue;
			}
		}
		for (int pointIndex = 0; pointIndex < everyFullBlineTotal - blineSplitNum + 1; pointIndex++)
		{

			int currPointIndex1th = (rowIndex*everyFullBlineTotal + pointIndex) * 3;
			int currPointIndex2th = ((rowIndex + 1)*everyFullBlineTotal + pointIndex) * 3;
			int currPointIndex3th = (rowIndex*everyFullBlineTotal + (pointIndex + 1)) * 3;
			int currPointIndex4th = ((rowIndex + 1)*everyFullBlineTotal + (pointIndex + 1)) * 3;
			int GPUXIndex = currentGPUIndex*evenum;
			int GPUYIndex = GPUXIndex + 1;
			int GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex1th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex1th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex1th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex1th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex1th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex1th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex1th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex1th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex1th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex1th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex1th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex1th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex);

			int texcoordSIndex = currentGPUIndex * 2;
			int texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTexcoordSTCoord(tag, rowIndex, texcoordSIndex, texcoordTIndex);
			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);


			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex2th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex2th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex2th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex2th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex2th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex2th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex2th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex2th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex2th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex2th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex2th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex2th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTexcoordSTCoord(tag, rowIndex, texcoordSIndex, texcoordTIndex);
			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);


			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex4th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex4th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex4th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex4th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex4th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex4th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex4th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex4th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex4th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex4th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex4th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex4th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex + 1);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTexcoordSTCoord(tag, rowIndex, texcoordSIndex, texcoordTIndex);
			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);


			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex1th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex1th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex1th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex1th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex1th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex1th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex1th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex1th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex1th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex1th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex1th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex1th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTexcoordSTCoord(tag, rowIndex, texcoordSIndex, texcoordTIndex);
			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);


			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex4th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex4th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex4th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex4th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex4th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex4th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex4th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex4th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex4th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex4th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex4th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex4th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex + 1);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTexcoordSTCoord(tag, rowIndex, texcoordSIndex, texcoordTIndex);
			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);


			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex3th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex3th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex3th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex3th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex3th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex3th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex3th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex3th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex3th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex3th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex3th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex3th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex + 1);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTexcoordSTCoord(tag, rowIndex, texcoordSIndex, texcoordTIndex);
			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

		}

	}


}

void BezierBsplineGeom::setTextureTags(int tag, int rowIndex, int GPUXIndex, int GPUYIndex, int GPUZIndex){

	if (tag == 111){//111代表是鱼的眼睛
		if (rowIndex < 8){
			textureTags[GPUXIndex] = 500.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}
		else if (rowIndex > 7 && rowIndex < 16)
		{
			textureTags[GPUXIndex] = 111.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}
		else if (rowIndex > 15 && rowIndex < 24){
			textureTags[GPUXIndex] = 500.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}
		else{
			textureTags[GPUXIndex] = 111.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}

	}
	else if (tag == 501)
	{
		//背鳍
		if (rowIndex < 11*BezierGeom::backSideFinsBezierStep)
		{
			textureTags[GPUXIndex] = 555.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}
		//两侧的鱼鳍
		else if (rowIndex > 11*BezierGeom::backSideFinsBezierStep-1)
		{
			textureTags[GPUXIndex] = 556.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}

	}
	//嘴巴
	else if (tag == 680)
	{
		textureTags[GPUXIndex] = 680.0;
		textureTags[GPUYIndex] = 0.0;
		textureTags[GPUZIndex] = 0.0;
		
	}

}

void BezierBsplineGeom::setTexcoordSTCoord(int tag, int rowIndex, int texcoordSIndex, int texcoordTIndex){
	int backSideFinsBezierTotalNum = 11 * BezierGeom::backSideFinsBezierStep;
	//501代表背鳍 两侧鱼鳍
	if (tag == 501){
		if (rowIndex < backSideFinsBezierTotalNum){
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex % BezierGeom::backSideFinsBezierStep) / float(BezierGeom::backSideFinsBezierStep);
		}
		else if (rowIndex > 11 * BezierGeom::backSideFinsBezierStep-1){

			texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex - (backSideFinsBezierTotalNum - 1)) %
				BezierGeom::amboFinsFanBoneBezierStep) / float(BezierGeom::amboFinsFanBoneBezierStep);
		}
		

	}
	//111代表两只眼睛的上下两部分 共计4个组件 8个贝塞尔点
	else if (tag==111){
		texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex % 8) / float(8);
	}

}


void BezierBsplineGeom::makeFishBsplinePoints2(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum2, int tag)
{
	int rowBaseNumber = rowTotal / 4;
	int blineSplitNum = 0;
	//为GPU分解成四分数据
	for (int rowIndex = 0; rowIndex < rowTotal; rowIndex++)
	{

		int currCPUIndex = rowIndex*listTotal * 3;
		for (int listIndex = 0; listIndex < listTotal - 3; listIndex++)
		{

			blineSplitNum = blineSplitNum2;
			for (int pointIndex = 0; pointIndex < blineSplitNum; pointIndex++)
			{
				//GPU渲染点在整条线段的索引值
				int fullLineGPUPointIndex = rowIndex*(listTotal - 3)*blineSplitNum;
				//GPU渲染点在当前线段某个区间段的索引值
				int currGPUPointIndex = listIndex * blineSplitNum + pointIndex;
				int currentBlineIndex = (fullLineGPUPointIndex + currGPUPointIndex) * 3;


				int currListIndex = listIndex * 3;
				shaderPointsBalloonFish1[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 1) * 3;
				shaderPointsBalloonFish2[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 2) * 3;
				shaderPointsBalloonFish3[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 3) * 3;
				shaderPointsBalloonFish4[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];

			}
		}

	}


	//在GPU里构建面片
	int currentGPUIndex = 0;
	int evenum = 3;
	int everyFullBlineTotal = blineSplitNum * (listTotal - 3);
	for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
	{
		if (tag == 222){//222代表是鱼鳍背部隆起的鱼鳍，满足下列条件后会与下一个鱼鳍脱离建立面片的关系
			if (rowIndex == 10 || rowIndex == 21 || rowIndex == 32 || rowIndex == 43 || rowIndex == 54 ||
				rowIndex == 65 || rowIndex == 76 || rowIndex == 87 || rowIndex == 98 || rowIndex == 109){
				continue;
			}
		}
		if (tag == 501){//501代表是鱼两侧的鱼鳍骨骼
			if (rowIndex == 9 || rowIndex == 19 || rowIndex == 29 || rowIndex == 39 || rowIndex == 49 ||
				rowIndex == 59 || rowIndex == 69 || rowIndex == 79 || rowIndex == 89 || rowIndex == 99 ||
				rowIndex == 109 || rowIndex == 119 || rowIndex == 129 || rowIndex == 139 || rowIndex == 149 ||
				rowIndex == 159 || rowIndex == 169 || rowIndex == 179 || rowIndex == 189 || rowIndex == 199){
				continue;
			}
		}
		if (tag == 530){//530代表是鱼眼睛的下半部分
			if (rowIndex == 7){
				continue;
			}
		}
		if (tag == 111){//111代表是鱼眼睛的上半部分
			if (rowIndex == 7 || rowIndex == 15 || rowIndex == 23){
				continue;
			}
		}
		if (tag == 520){//520代表是鱼鳍的底座
			if (rowIndex == 5){
				continue;
			}
		}
		for (int pointIndex = 0; pointIndex < everyFullBlineTotal - blineSplitNum + 1; pointIndex++)
		{

			int currPointIndex1th = (rowIndex*everyFullBlineTotal + pointIndex) * 3;
			int currPointIndex2th = ((rowIndex + 1)*everyFullBlineTotal + pointIndex) * 3;
			int currPointIndex3th = (rowIndex*everyFullBlineTotal + (pointIndex + 1)) * 3;
			int currPointIndex4th = ((rowIndex + 1)*everyFullBlineTotal + (pointIndex + 1)) * 3;
			int GPUXIndex = currentGPUIndex*evenum;
			int GPUYIndex = GPUXIndex + 1;
			int GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex1th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex1th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex1th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex1th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex1th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex1th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex1th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex1th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex1th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex1th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex1th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex1th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex);

			int texcoordSIndex = currentGPUIndex * 2;
			int texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex % rowBaseNumber) / float(rowBaseNumber);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal - blineSplitNum + 1);


			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);



			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex2th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex2th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex2th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex2th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex2th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex2th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex2th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex2th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex2th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex2th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex2th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex2th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex + 1) % rowBaseNumber) / float(rowBaseNumber);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal - blineSplitNum + 1);


			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);



			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex4th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex4th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex4th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex4th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex4th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex4th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex4th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex4th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex4th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex4th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex4th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex4th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex + 1);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex + 1) % rowBaseNumber) / float(rowBaseNumber);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal - blineSplitNum + 1);



			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);



			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex1th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex1th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex1th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex1th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex1th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex1th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex1th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex1th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex1th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex1th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex1th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex1th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex % rowBaseNumber) / float(rowBaseNumber);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal - blineSplitNum + 1);


			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);



			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex4th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex4th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex4th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex4th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex4th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex4th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex4th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex4th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex4th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex4th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex4th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex4th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex + 1);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex + 1) % rowBaseNumber) / float(rowBaseNumber);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal - blineSplitNum + 1);


			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);



			currentGPUIndex++;
			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex3th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex3th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex3th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex3th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex3th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex3th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex3th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex3th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex3th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex3th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex3th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex3th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex + 1);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex % rowBaseNumber) / float(rowBaseNumber);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal - blineSplitNum + 1);

			setTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);


			currentGPUIndex++;

		}

	}


}


void BezierBsplineGeom::drawFish0th(bool isDrawPoints,int bsplineNum,int tag){

	UniformData* closedBsplineGeom = shaderUtilBezierBsplineGeom.getClosedBsplineGeomData();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式
	glEnable(GL_BLEND);
	glUseProgram(closedBsplineGeom->m_progHandle);
	int closedBsplineGeomMvpMatrixLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "mvp");
	glUniformMatrix4fv(closedBsplineGeomMvpMatrixLocation, 1, GL_FALSE, Scene::esMatrix.m[0]);


	string sKey_0 = "U_Texture0";
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId_0);
	int location0 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_0.c_str());
	glUniform1i(location0, 0);

	string sKey_1 = "U_Texture1";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texId_1);
	int location1 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_1.c_str());
	glUniform1i(location1, 1);

	string sKey_2 = "U_Texture2";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texId_2);
	int location2 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_2.c_str());
	glUniform1i(location2, 2);

	int noseMouthTagLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "fishPartTag");
	glUniform1i(noseMouthTagLocation, tag);

	GLuint blineSplitLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "blineSplit");
	glUniform1f(blineSplitLocation, float(bsplineNum));
	GLuint blinePoints1Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints1");
	GLuint blinePoints2Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints2");
	GLuint blinePoints3Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints3");
	GLuint blinePoints4Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints4");
	GLuint blinePercentLocation = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePercent");

	int lightPositionLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "lightPosition");
	glUniform3f(lightPositionLocation, 0.0f, 3.1f, 0.0f);

	

	glVertexAttribPointer(blinePoints1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish1);
	glEnableVertexAttribArray(blinePoints1Location);
	glVertexAttribPointer(blinePoints2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish2);
	glEnableVertexAttribArray(blinePoints2Location);
	glVertexAttribPointer(blinePoints3Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish3);
	glEnableVertexAttribArray(blinePoints3Location);
	glVertexAttribPointer(blinePoints4Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish4);
	glEnableVertexAttribArray(blinePoints4Location);
	glVertexAttribPointer(blinePercentLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blineIndicesFEBalloonFish);
	glEnableVertexAttribArray(blinePercentLocation);

	GLuint texcoordLocation = glGetAttribLocation(closedBsplineGeom->m_progHandle, "texcoord");
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 2 * 4, texcoordGatherBalloonFish);
	glEnableVertexAttribArray(texcoordLocation);




	if (isDrawPoints){
		glDrawArrays(GL_POINTS, 0, 10100);
	}else{
		glDrawArrays(GL_TRIANGLES, 0, 10100);
	}
	glDisable(GL_BLEND);
	glUseProgram(0);

	std::memset(BezierBsplineGeom::shaderPointsBalloonFish1, 0, 600000 * sizeof(float));
	std::memset(BezierBsplineGeom::shaderPointsBalloonFish2, 0, 600000 * sizeof(float));
	std::memset(BezierBsplineGeom::shaderPointsBalloonFish3, 0, 600000 * sizeof(float));
	std::memset(BezierBsplineGeom::shaderPointsBalloonFish4, 0, 600000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish1, 0, 300000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish2, 0, 300000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish3, 0, 300000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish4, 0, 300000 * sizeof(float));
	std::memset(blineIndicesFEBalloonFish, 0, 300000 * sizeof(float));

}

void BezierBsplineGeom::drawFishPart(bool isDrawPoints, int bsplineNum, int tag, int drawNumber){

	UniformData* closedBsplineGeom = shaderUtilBezierBsplineGeom.getClosedBsplineGeomData();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式
	glEnable(GL_BLEND);
	glUseProgram(closedBsplineGeom->m_progHandle);
	int closedBsplineGeomMvpMatrixLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "mvp");
	glUniformMatrix4fv(closedBsplineGeomMvpMatrixLocation, 1, GL_FALSE, Scene::esMatrix.m[0]);


	string sKey_0 = "U_Texture0";
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId_0);
	int location0 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_0.c_str());
	glUniform1i(location0, 0);

	string sKey_1 = "U_Texture1";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texId_1);
	int location1 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_1.c_str());
	glUniform1i(location1, 1);

	string sKey_2 = "U_Texture2";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texId_2);
	int location2 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_2.c_str());
	glUniform1i(location2, 2);

	string sKey_3 = "U_Texture3";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texId_3);
	int location3 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_3.c_str());
	glUniform1i(location3, 3);

	string sKey_4 = "U_Texture4";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texId_4);
	int location4 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_4.c_str());
	glUniform1i(location4, 4);

	string sKey_5 = "U_Texture5";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, texId_5);
	int location5 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_5.c_str());
	glUniform1i(location5, 5);

	string sKey_6 = "U_Texture6";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texId_6);
	int location6 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_6.c_str());
	glUniform1i(location6, 6);

	string sKey_7 = "U_Texture7";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, texId_7);
	int location7 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_7.c_str());
	glUniform1i(location7, 7);

	string sKey_8 = "U_Texture8";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, texId_8);
	int location8 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_8.c_str());
	glUniform1i(location8, 8);

	string sKey_9 = "U_Texture9";
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, texId_9);
	int location9 = glGetUniformLocation(closedBsplineGeom->m_progHandle, sKey_9.c_str());
	glUniform1i(location9, 9);


	int noseMouthTagLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "fishPartTag");
	glUniform1i(noseMouthTagLocation, tag);

	GLuint blineSplitLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "blineSplit");
	glUniform1f(blineSplitLocation, float(bsplineNum));
	GLuint blinePoints1Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints1");
	GLuint blinePoints2Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints2");
	GLuint blinePoints3Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints3");
	GLuint blinePoints4Location = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePoints4");
	GLuint blinePercentLocation = glGetAttribLocation(closedBsplineGeom->m_progHandle, "blinePercent");

	int lightPositionLocation = glGetUniformLocation(closedBsplineGeom->m_progHandle, "lightPosition");
	glUniform3f(lightPositionLocation, 0.0f, 3.1f, 0.0f);

	glVertexAttribPointer(blinePoints1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish1);
	glEnableVertexAttribArray(blinePoints1Location);
	glVertexAttribPointer(blinePoints2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish2);
	glEnableVertexAttribArray(blinePoints2Location);
	glVertexAttribPointer(blinePoints3Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish3);
	glEnableVertexAttribArray(blinePoints3Location);
	glVertexAttribPointer(blinePoints4Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFish4);
	glEnableVertexAttribArray(blinePoints4Location);
	glVertexAttribPointer(blinePercentLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blineIndicesFEBalloonFish);
	glEnableVertexAttribArray(blinePercentLocation);

	GLuint textureTagLocation = glGetAttribLocation(closedBsplineGeom->m_progHandle, "textureTag");
	glVertexAttribPointer(textureTagLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, textureTags);
	glEnableVertexAttribArray(textureTagLocation);

	GLuint texcoordLocation = glGetAttribLocation(closedBsplineGeom->m_progHandle, "texcoord");
	glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 2 * 4, texcoordGatherBalloonFish);
	glEnableVertexAttribArray(texcoordLocation);

	if (isDrawPoints){
		glDrawArrays(GL_POINTS, 0, drawNumber);
	}
	else{
		glDrawArrays(GL_TRIANGLES, 0, drawNumber);
	}
	glDisable(GL_BLEND);
	glUseProgram(0);

	std::memset(BezierBsplineGeom::shaderPointsBalloonFish1, 0, 600000 * sizeof(float));
	std::memset(BezierBsplineGeom::shaderPointsBalloonFish2, 0, 600000 * sizeof(float));
	std::memset(BezierBsplineGeom::shaderPointsBalloonFish3, 0, 600000 * sizeof(float));
	std::memset(BezierBsplineGeom::shaderPointsBalloonFish4, 0, 600000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish1, 0, 300000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish2, 0, 300000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish3, 0, 300000 * sizeof(float));
	std::memset(trueShaderPointsBalloonFish4, 0, 300000 * sizeof(float));
	std::memset(blineIndicesFEBalloonFish, 0, 300000 * sizeof(float));

}


void BezierBsplineGeom::makeFishOpenBsplinePoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum2, int tag)
{
	int blineSplitNum = 0;
	//为GPU分解成四分数据
	for (int rowIndex = 0; rowIndex < rowTotal; rowIndex++)
	{
		blineSplitNum = blineSplitNum2;
		
		int currCPUIndex = rowIndex*listTotal * 3;
		for (int listIndex = 0; listIndex < listTotal - 3; listIndex++)
		{

			for (int pointIndex = 0; pointIndex < blineSplitNum; pointIndex++)
			{
				//GPU渲染点在整条线段的索引值
				int fullLineGPUPointIndex = rowIndex*(listTotal - 3)*blineSplitNum;
				//GPU渲染点在当前线段某个区间段的索引值
				int currGPUPointIndex = listIndex * blineSplitNum + pointIndex;
				int currentBlineIndex = (fullLineGPUPointIndex + currGPUPointIndex) * 3;


				int currListIndex = listIndex * 3;
				shaderPointsBalloonFish1[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 1) * 3;
				shaderPointsBalloonFish2[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 2) * 3;
				shaderPointsBalloonFish3[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];
				currListIndex = (listIndex + 3) * 3;
				shaderPointsBalloonFish4[currentBlineIndex] = blineContPoints[currCPUIndex + currListIndex];
				shaderPointsBalloonFish4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + currListIndex + 1];
				shaderPointsBalloonFish4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + currListIndex + 2];

			}
		}

	}

	int everyRowNum = 0;
	//在GPU里构建面片
	int currentGPUIndex = 0;
	int evenum = 3;
	int everyFullBlineTotal = blineSplitNum * (listTotal - 3);
	for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
	{
		

		for (int pointIndex = 0; pointIndex < everyFullBlineTotal - 1; pointIndex++)
		{

			int currPointIndex1th = (rowIndex*everyFullBlineTotal + pointIndex) * 3;
			int currPointIndex2th = ((rowIndex + 1)*everyFullBlineTotal + pointIndex) * 3;
			int currPointIndex3th = (rowIndex*everyFullBlineTotal + (pointIndex + 1)) * 3;
			int currPointIndex4th = ((rowIndex + 1)*everyFullBlineTotal + (pointIndex + 1)) * 3;
			int GPUXIndex = currentGPUIndex*evenum;
			int GPUYIndex = GPUXIndex + 1;
			int GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex1th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex1th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex1th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex1th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex1th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex1th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex1th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex1th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex1th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex1th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex1th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex1th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex % 40);

			int texcoordSIndex = currentGPUIndex * 2;
			int texcoordTIndex = texcoordSIndex + 1;
			if (tag == 525 || tag == 112){
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex%everyRowNum) / float(everyRowNum);
			}
			else{
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			}
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal);
			setOpenTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex2th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex2th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex2th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex2th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex2th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex2th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex2th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex2th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex2th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex2th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex2th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex2th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex % 40);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			if (tag == 525 || tag == 112){
				texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex + 1) % everyRowNum) / float(everyRowNum);

			}
			else{
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);

			}
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal);
			setOpenTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex4th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex4th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex4th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex4th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex4th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex4th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex4th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex4th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex4th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex4th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex4th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex4th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float((pointIndex + 1) % 40);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			if (tag == 525 || tag == 112){
				texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex + 1) % everyRowNum) / float(everyRowNum);

			}
			else{
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);

			}
			//texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal);
			setOpenTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex1th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex1th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex1th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex1th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex1th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex1th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex1th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex1th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex1th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex1th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex1th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex1th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float(pointIndex % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float(pointIndex % 40);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			if (tag == 525 || tag == 112){
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex%everyRowNum) / float(everyRowNum);
			}
			else{
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			}
			//texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex) / float(everyFullBlineTotal);
			setOpenTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex4th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex4th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex4th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex4th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex4th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex4th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex4th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex4th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex4th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex4th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex4th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex4th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex + 1);
			blineIndicesFEBalloonFish[GPUZIndex] = float((pointIndex + 1) % 40);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			if (tag == 525 || tag == 112){
				texcoordGatherBalloonFish[texcoordSIndex] = float((rowIndex + 1) % everyRowNum) / float(everyRowNum);

			}
			else{
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);

			}
			//texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex + 1) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal);
			setOpenTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

			GPUXIndex = currentGPUIndex*evenum;
			GPUYIndex = GPUXIndex + 1;
			GPUZIndex = GPUXIndex + 2;
			trueShaderPointsBalloonFish1[GPUXIndex] = shaderPointsBalloonFish1[currPointIndex3th];
			trueShaderPointsBalloonFish1[GPUYIndex] = shaderPointsBalloonFish1[currPointIndex3th + 1];
			trueShaderPointsBalloonFish1[GPUZIndex] = shaderPointsBalloonFish1[currPointIndex3th + 2];
			trueShaderPointsBalloonFish2[GPUXIndex] = shaderPointsBalloonFish2[currPointIndex3th];
			trueShaderPointsBalloonFish2[GPUYIndex] = shaderPointsBalloonFish2[currPointIndex3th + 1];
			trueShaderPointsBalloonFish2[GPUZIndex] = shaderPointsBalloonFish2[currPointIndex3th + 2];
			trueShaderPointsBalloonFish3[GPUXIndex] = shaderPointsBalloonFish3[currPointIndex3th];
			trueShaderPointsBalloonFish3[GPUYIndex] = shaderPointsBalloonFish3[currPointIndex3th + 1];
			trueShaderPointsBalloonFish3[GPUZIndex] = shaderPointsBalloonFish3[currPointIndex3th + 2];
			trueShaderPointsBalloonFish4[GPUXIndex] = shaderPointsBalloonFish4[currPointIndex3th];
			trueShaderPointsBalloonFish4[GPUYIndex] = shaderPointsBalloonFish4[currPointIndex3th + 1];
			trueShaderPointsBalloonFish4[GPUZIndex] = shaderPointsBalloonFish4[currPointIndex3th + 2];
			blineIndicesFEBalloonFish[GPUXIndex] = float((pointIndex + 1) % blineSplitNum);
			blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex);
			blineIndicesFEBalloonFish[GPUZIndex] = float((pointIndex + 1) % 40);

			texcoordSIndex = currentGPUIndex * 2;
			texcoordTIndex = texcoordSIndex + 1;
			if (tag == 525 || tag == 112){
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex%everyRowNum) / float(everyRowNum);

			}
			else{
				texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);

			}
			//texcoordGatherBalloonFish[texcoordSIndex] = float(rowIndex) / float(rowTotal);
			texcoordGatherBalloonFish[texcoordTIndex] = float(pointIndex + 1) / float(everyFullBlineTotal);
			setOpenTextureTags(tag, rowIndex, GPUXIndex, GPUYIndex, GPUZIndex);

			currentGPUIndex++;

		}

	}

}

void BezierBsplineGeom::setOpenTextureTags(int tag, int rowIndex, int GPUXIndex, int GPUYIndex, int GPUZIndex){

	if (tag == 525){
		if (rowIndex < 21){
			textureTags[GPUXIndex] = 525.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}
		else
		{
			textureTags[GPUXIndex] = 527.0;
			textureTags[GPUYIndex] = 0.0;
			textureTags[GPUZIndex] = 0.0;
		}

	}

}

void BezierBsplineGeom::drawPointLineColorSize(float* points, float r, float g, float b, float size, int number){

	UniformData* colorSizeUniformData = shaderUtilBezierBsplineGeom.getColorSizeUniformData();
	glUseProgram(colorSizeUniformData->m_progHandle);
	int mvpMatrixLocation = glGetUniformLocation(colorSizeUniformData->m_progHandle, "mvp");
	glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, Scene::esMatrix.m[0]);

	int colorLocation = glGetUniformLocation(colorSizeUniformData->m_progHandle, "color");
	int pointSizeLocation = glGetUniformLocation(colorSizeUniformData->m_progHandle, "pointSize");
	GLuint positionLocation = glGetAttribLocation(colorSizeUniformData->m_progHandle, "position");

	glUniform4f(colorLocation, r, g, b, 1.0);
	glUniform1f(pointSizeLocation, size);
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, points);
	glEnableVertexAttribArray(positionLocation);
	glDrawArrays(GL_POINTS, 0, number);

	glUseProgram(0);

}
