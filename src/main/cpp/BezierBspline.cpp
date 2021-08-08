#include "BezierBspline.h"

BezierBspline::BezierBspline(){};
BezierBspline::~BezierBspline(){};
int evenum = 18;//一个四边形 6 个索引
WizardGeom wizardGeomBezierBspline;
WizardGeomSupple wizardGeomSuppleBezierBspline;
BezierBspline self;
BezierAnimationByAngle bezierAnimationByAngleBezierBspline;
FlyElephantExercise flyElephantExerciseBezierBspline;

float* BezierBspline::makeUpBezierLine2(int geomIndex)
{
    WizardGeom* synthPoint = wizardGeomBezierBspline.getCurrWizardGeom(geomIndex);
    wizardGeomSuppleBezierBspline.makeUpCirclePoints(synthPoint);
	float* splitPoints = synthPoint->splitPoints;
	float* bezPointGather = synthPoint->bezPointGather;
	//切面个数
	int cutPlaneNum = synthPoint->baseDataPercentNum;
	//按度数切分圆的个数
	int degSplNum = synthPoint->degreeSplitNum;
	int compBPNum = cutPlaneNum - 1;
	int bezierStep = synthPoint->bezierStep;
	float bezFract = 1.0 / (bezierStep*1.0);
	float factResArr[10000];//介乘结果的集合
	for (int i = 0; i <= compBPNum; i++){	//求0到n的阶乘
		factResArr[i] = self.factrial(i);
	}
	//循环每个点
	for (int row = 0; row < degSplNum; row++)
	{
		for (int i = 0; i <= bezierStep; i++)
		{
			//在bezier曲线上的节点的百分数
			float bezFractValue = i*bezFract;
			if (bezFractValue > 1)
			{
				bezFractValue = 1;
			}
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			float tka[100000];
			float otka[100000];
			for (int j = 0; j <= compBPNum; j++)
			{
				tka[j] = (float)pow(bezFractValue, j); //计算t的j次幂
				otka[j] = (float)pow(1.0 - bezFractValue, j); //计算1-t的j次幂
			}

			for (int k = 0; k <= compBPNum; k++)
			{
				float xs = (factResArr[compBPNum] / (factResArr[k] * factResArr[compBPNum - k])) * tka[k] * otka[compBPNum - k];

				int cutPlaneindex = k*degSplNum * 3;//每个切面的数值个数
				int pointIndex = row * 3;//一个圆的第几个点的角标
				xf = xf + splitPoints[cutPlaneindex + pointIndex] * xs;
				yf = yf + splitPoints[cutPlaneindex + pointIndex + 1] * xs;
				zf = zf + splitPoints[cutPlaneindex + pointIndex + 2] * xs;

			}
			int currIndex = bezierStep*row * 3;//当前bezier线条的角标值

			bezPointGather[currIndex + i * 3] = xf;
			bezPointGather[currIndex + i * 3 + 1] = yf;
			bezPointGather[currIndex + i * 3 + 2] = zf;

		}

	}

	return bezPointGather;
}

//介乘
int BezierBspline::factrial(int factrialCount)
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

////////////////////////////////////////////////////////
///////////  BSPLINE  /////////////////////////////////
///////////////////////////////////////////////////////

void BezierBspline::createBezierShaderPoints(int j, int mIndex1, int blindex, int i, float f1, float f2, float f3, float f4, int wgIndex)
{
	
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	float* bezPointGather = wgPoint->bezPointGather;
	int bezierStep = wgPoint->bezierStep;

	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* blineFactors1 = wgPoint->blineFactors1;
	float* blineFactors2 = wgPoint->blineFactors2;

	bezierShaderPoints1[blindex] = bezPointGather[j * bezierStep * 3 + mIndex1];
	bezierShaderPoints1[blindex + 1] = bezPointGather[j * bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints1[blindex + 2] = bezPointGather[j * bezierStep * 3 + mIndex1 + 2];
	bezierShaderPoints2[blindex] = bezPointGather[(j + 1) * bezierStep * 3 + mIndex1];
	bezierShaderPoints2[blindex + 1] = bezPointGather[(j + 1) * bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints2[blindex + 2] = bezPointGather[(j + 1) * bezierStep * 3 + mIndex1 + 2];
	bezierShaderPoints3[blindex] = bezPointGather[(j + 2) * bezierStep * 3 + mIndex1];
	bezierShaderPoints3[blindex + 1] = bezPointGather[(j + 2) * bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints3[blindex + 2] = bezPointGather[(j + 2) * bezierStep * 3 + mIndex1 + 2];
	bezierShaderPoints4[blindex] = bezPointGather[(j + 3) * bezierStep * 3 + mIndex1];
	bezierShaderPoints4[blindex + 1] = bezPointGather[(j + 3) * bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints4[blindex + 2] = bezPointGather[(j + 3) * bezierStep * 3 + mIndex1 + 2];
	blineFactors1[blindex] = f1;
	blineFactors1[blindex + 1] = f2;
	blineFactors1[blindex + 2] = float(i);
	blineFactors2[blindex] = f3;
	blineFactors2[blindex + 1] = f4;
	blineFactors2[blindex + 2] = float(j);

}

void BezierBspline::createLast3BezierShaderPoints(int mIndex1, int lastThirdIndex, float f1, float f2, float f3, float f4, int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	int blinePointNum = wgPoint->degreeSplitNum - 3;
	float* bezPointGather = wgPoint->bezPointGather;
	int bezierStep = wgPoint->bezierStep;
	int index1 = blinePointNum * bezierStep * 3;
	int index2 = (blinePointNum + 1) * bezierStep * 3;
	int index3 = (blinePointNum + 2) * bezierStep * 3;

	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* blineFactors1 = wgPoint->blineFactors1;
	float* blineFactors2 = wgPoint->blineFactors2;

	bezierShaderPoints1[lastThirdIndex] = bezPointGather[index1 + mIndex1];
	bezierShaderPoints1[lastThirdIndex + 1] = bezPointGather[index1 + mIndex1 + 1];
	bezierShaderPoints1[lastThirdIndex + 2] = bezPointGather[index1 + mIndex1 + 2];
	bezierShaderPoints2[lastThirdIndex] = bezPointGather[index2 + mIndex1];
	bezierShaderPoints2[lastThirdIndex + 1] = bezPointGather[index2 + mIndex1 + 1];
	bezierShaderPoints2[lastThirdIndex + 2] = bezPointGather[index2 + mIndex1 + 2];
	bezierShaderPoints3[lastThirdIndex] = bezPointGather[index3 + mIndex1];
	bezierShaderPoints3[lastThirdIndex + 1] = bezPointGather[index3 + mIndex1 + 1];
	bezierShaderPoints3[lastThirdIndex + 2] = bezPointGather[index3 + mIndex1 + 2];
	bezierShaderPoints4[lastThirdIndex] = bezPointGather[mIndex1];
	bezierShaderPoints4[lastThirdIndex + 1] = bezPointGather[mIndex1 + 1];
	bezierShaderPoints4[lastThirdIndex + 2] = bezPointGather[mIndex1 + 2];

	blineFactors1[lastThirdIndex] = f1;
	blineFactors1[lastThirdIndex + 1] = f2;
	blineFactors1[lastThirdIndex + 2] = 0.0;
	blineFactors2[lastThirdIndex] = f3;
	blineFactors2[lastThirdIndex + 1] = f4;
	blineFactors2[lastThirdIndex + 2] = 0.0;

}

void BezierBspline::createLast2BezierShaderPoints(int mIndex1, int lastSecondIndex, float f1, float f2, float f3, float f4, int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	int blinePointNum = wgPoint->degreeSplitNum - 3;
	float* bezPointGather = wgPoint->bezPointGather;
	int bezierStep = wgPoint->bezierStep;

	int index1 = (blinePointNum + 1) * bezierStep * 3;
	int index2 = (blinePointNum + 2) * bezierStep * 3;

	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* blineFactors1 = wgPoint->blineFactors1;
	float* blineFactors2 = wgPoint->blineFactors2;

	bezierShaderPoints1[lastSecondIndex] = bezPointGather[index1 + mIndex1];
	bezierShaderPoints1[lastSecondIndex + 1] = bezPointGather[index1 + mIndex1 + 1];
	bezierShaderPoints1[lastSecondIndex + 2] = bezPointGather[index1 + mIndex1 + 2];
	bezierShaderPoints2[lastSecondIndex] = bezPointGather[index2 + mIndex1];
	bezierShaderPoints2[lastSecondIndex + 1] = bezPointGather[index2 + mIndex1 + 1];
	bezierShaderPoints2[lastSecondIndex + 2] = bezPointGather[index2 + mIndex1 + 2];
	bezierShaderPoints3[lastSecondIndex] = bezPointGather[mIndex1];
	bezierShaderPoints3[lastSecondIndex + 1] = bezPointGather[mIndex1 + 1];
	bezierShaderPoints3[lastSecondIndex + 2] = bezPointGather[mIndex1 + 2];
	bezierShaderPoints4[lastSecondIndex] = bezPointGather[bezierStep * 3 + mIndex1];
	bezierShaderPoints4[lastSecondIndex + 1] = bezPointGather[bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints4[lastSecondIndex + 2] = bezPointGather[bezierStep * 3 + mIndex1 + 2];

	blineFactors1[lastSecondIndex] = f1;
	blineFactors1[lastSecondIndex + 1] = f2;
	blineFactors1[lastSecondIndex + 2] = 0.0;
	blineFactors2[lastSecondIndex] = f3;
	blineFactors2[lastSecondIndex + 1] = f4;
	blineFactors2[lastSecondIndex + 2] = 0.0;

}

void BezierBspline::createLastBizerShaderPoints(int mIndex1, int lastIndex, float f1, float f2, float f3, float f4, int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	int blinePointNum = wgPoint->degreeSplitNum - 3;
	float* bezPointGather = wgPoint->bezPointGather;
	int bezierStep = wgPoint->bezierStep;
	int index1 = (blinePointNum + 2) * bezierStep * 3;

	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* blineFactors1 = wgPoint->blineFactors1;
	float* blineFactors2 = wgPoint->blineFactors2;

	bezierShaderPoints1[lastIndex] = bezPointGather[index1 + mIndex1];
	bezierShaderPoints1[lastIndex + 1] = bezPointGather[index1 + mIndex1 + 1];
	bezierShaderPoints1[lastIndex + 2] = bezPointGather[index1 + mIndex1 + 2];
	bezierShaderPoints2[lastIndex] = bezPointGather[mIndex1];
	bezierShaderPoints2[lastIndex + 1] = bezPointGather[mIndex1 + 1];
	bezierShaderPoints2[lastIndex + 2] = bezPointGather[mIndex1 + 2];
	bezierShaderPoints3[lastIndex] = bezPointGather[bezierStep * 3 + mIndex1];
	bezierShaderPoints3[lastIndex + 1] = bezPointGather[bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints3[lastIndex + 2] = bezPointGather[bezierStep * 3 + mIndex1 + 2];
	bezierShaderPoints4[lastIndex] = bezPointGather[2 * bezierStep * 3 + mIndex1];
	bezierShaderPoints4[lastIndex + 1] = bezPointGather[2 * bezierStep * 3 + mIndex1 + 1];
	bezierShaderPoints4[lastIndex + 2] = bezPointGather[2 * bezierStep * 3 + mIndex1 + 2];
	
	blineFactors1[lastIndex] = f1;
	blineFactors1[lastIndex + 1] = f2;
	blineFactors1[lastIndex + 2] = 0.0;
	blineFactors2[lastIndex] = f3;
	blineFactors2[lastIndex + 1] = f4;
	blineFactors2[lastIndex + 2] = 0.0;

}

void BezierBspline::makeUpBspline(int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	int blineSplitNum = wgPoint->blineSplitNum;
	float f1, f2, f3, f4;
	float deltaT = 1.0 / blineSplitNum;
	float T;
	for (int i = 0; i < blineSplitNum; i++)
	{
		T = i*deltaT;
		f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
		f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
		f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
		f4 = (T*T*T) / 6.0;

		BezierBspline::makeUpPoints(f1, f2, f3, f4, i, wgIndex);

	}

}

void BezierBspline::makeUpPoints(float f1, float f2, float f3, float f4, int i,int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	int bezierStep = wgPoint->bezierStep;
	int blineSplitNum = wgPoint->blineSplitNum;
	int degreeSplitNum = wgPoint->degreeSplitNum - 3;
	float* bezierGatherPoint = wgPoint->bezPointGather;
	float* blinesPoints = wgPoint->blinesPoints;
	for (int m = 0; m < bezierStep; m++) //每条贝塞尔线段上拥有的点数  贝塞尔线段上的第m个点
	{
		//每个闭环包含的段数 * 每个曲线段包含的点个数 * 3 * 第m个闭合圈   每个闭合圈所包含的数值个数   +3是加的3条线段
		int loopIndex = (degreeSplitNum + 3)* blineSplitNum * 3 * m;
		int mIndex1 = m * 3; //贝塞尔线段上的第 m 个点的索引
		int mIndex2 = mIndex1 + 1;
		int mIndex3 = mIndex2 + 1;
		for (int j = 0; j < degreeSplitNum; j++)
		{
			//j * steps * 3  横截面的第j个点
			float x = f1*bezierGatherPoint[j * bezierStep * 3 + mIndex1] + f2*bezierGatherPoint[(j + 1) * bezierStep * 3 + mIndex1] + f3*bezierGatherPoint[(j + 2) * bezierStep * 3 + mIndex1] + f4*bezierGatherPoint[(j + 3) * bezierStep * 3 + mIndex1];
			float y = f1*bezierGatherPoint[j * bezierStep * 3 + mIndex2] + f2*bezierGatherPoint[(j + 1) * bezierStep * 3 + mIndex2] + f3*bezierGatherPoint[(j + 2) * bezierStep * 3 + mIndex2] + f4*bezierGatherPoint[(j + 3) * bezierStep * 3 + mIndex2];
			float z = f1*bezierGatherPoint[j * bezierStep * 3 + mIndex3] + f2*bezierGatherPoint[(j + 1) * bezierStep * 3 + mIndex3] + f3*bezierGatherPoint[(j + 2) * bezierStep * 3 + mIndex3] + f4*bezierGatherPoint[(j + 3) * bezierStep * 3 + mIndex3];
			int secNum = blineSplitNum * 3 * j;//到第 j 个点时，当下的索引值
			int blindex = secNum + i * 3 + loopIndex;
			blinesPoints[blindex] = x;
			blinesPoints[blindex + 1] = y;
			blinesPoints[blindex + 2] = z;
			
			BezierBspline::createBezierShaderPoints(j, mIndex1, blindex, i, f1, f2, f3, f4, wgIndex);

		}
		//横截面的最后三个点
		float x4 = f1*bezierGatherPoint[degreeSplitNum * bezierStep * 3 + mIndex1] + f2*bezierGatherPoint[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1] + f3*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1] + f4*bezierGatherPoint[mIndex1];
		float y4 = f1*bezierGatherPoint[degreeSplitNum * bezierStep * 3 + mIndex2] + f2*bezierGatherPoint[(degreeSplitNum + 1) * bezierStep * 3 + mIndex2] + f3*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2] + f4*bezierGatherPoint[mIndex2];
		float z4 = f1*bezierGatherPoint[degreeSplitNum * bezierStep * 3 + mIndex3] + f2*bezierGatherPoint[(degreeSplitNum + 1) * bezierStep * 3 + mIndex3] + f3*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3] + f4*bezierGatherPoint[mIndex3];

		float x5 = f1*bezierGatherPoint[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1] + f2*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1] + f3*bezierGatherPoint[mIndex1] + f4*bezierGatherPoint[bezierStep * 3 + mIndex1];
		float y5 = f1*bezierGatherPoint[(degreeSplitNum + 1) * bezierStep * 3 + mIndex2] + f2*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2] + f3*bezierGatherPoint[mIndex2] + f4*bezierGatherPoint[bezierStep * 3 + mIndex2];
		float z5 = f1*bezierGatherPoint[(degreeSplitNum + 1) * bezierStep * 3 + mIndex3] + f2*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3] + f3*bezierGatherPoint[mIndex3] + f4*bezierGatherPoint[bezierStep * 3 + mIndex3];

		float x6 = f1*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1] + f2*bezierGatherPoint[mIndex1] + f3*bezierGatherPoint[bezierStep * 3 + mIndex1] + f4*bezierGatherPoint[2 * bezierStep * 3 + mIndex1];
		float y6 = f1*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2] + f2*bezierGatherPoint[mIndex2] + f3*bezierGatherPoint[bezierStep * 3 + mIndex2] + f4*bezierGatherPoint[2 * bezierStep * 3 + mIndex2];
		float z6 = f1*bezierGatherPoint[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3] + f2*bezierGatherPoint[mIndex3] + f3*bezierGatherPoint[bezierStep * 3 + mIndex3] + f4*bezierGatherPoint[2 * bezierStep * 3 + mIndex3];
		int lastThirdIndex = i * 3 + blineSplitNum * 3 * degreeSplitNum + loopIndex;
		blinesPoints[lastThirdIndex] = x4;
		blinesPoints[lastThirdIndex + 1] = y4;
		blinesPoints[lastThirdIndex + 2] = z4;
		BezierBspline::createLast3BezierShaderPoints(mIndex1, lastThirdIndex, f1, f2, f3, f4, wgIndex);

		int lastSecondIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 1) + loopIndex;
		blinesPoints[lastSecondIndex] = x5;
		blinesPoints[lastSecondIndex + 1] = y5;
		blinesPoints[lastSecondIndex + 2] = z5;
		BezierBspline::createLast2BezierShaderPoints(mIndex1, lastSecondIndex, f1, f2, f3, f4, wgIndex);

		int lastOneIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 2) + loopIndex;
		blinesPoints[lastOneIndex] = x6;
		blinesPoints[lastOneIndex + 1] = y6;
		blinesPoints[lastOneIndex + 2] = z6;
		BezierBspline::createLastBizerShaderPoints(mIndex1, lastOneIndex, f1, f2, f3, f4, wgIndex);

	}

}

void BezierBspline::blineTextureMap(int wgIndex)
{
	////每一圈包含的点数
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	int bezierStep = wgPoint->bezierStep;
	int everyCircleNum = wgPoint->blineSplitNum*wgPoint->degreeSplitNum;
	//横向跨度
	for (int j = 0; j < bezierStep; j++)
	{
		
		int tansverSpanNum1 = j * everyCircleNum * 3;
		int tansverSpanNum2 = (j + 1) * everyCircleNum * 3;
		float textureCoord1 = j * 1.0 / bezierStep;
		float textureCoord2 = (j + 1.0) / bezierStep;

		for (int i = 0; i < everyCircleNum - 1; i++)//在一个闭合圈内跳跃几个点
		{
			float fv1 = i*1.0 / everyCircleNum;
			float fv2 = (i + 1)*1.0 / everyCircleNum;
			//每个闭合圈点的个数 * 第几个横向跨度 + 当前闭合圈点里的第几个点
			int m = everyCircleNum * j + i;
			
			//把贝塞尔曲线上的点的点绑定到shader里的样条曲线上
			BezierBspline::getAllShaderParams(tansverSpanNum1, tansverSpanNum2, textureCoord1, textureCoord2, fv1, fv2, m, i, j, wgIndex);

		}

		for (int i = everyCircleNum - 1; i < everyCircleNum; i++)//在一个闭合圈内跳跃几个点
		{
			float fv1 = i*1.0 / everyCircleNum;
			float fv2 = (i + 1)*1.0 / everyCircleNum;
			int m = everyCircleNum * j + i;
			//把贝塞尔曲线上的最后一个闭合圈上的点绑定到shader里的样条曲线上
			BezierBspline::getCloseAllShaderParams(tansverSpanNum1, tansverSpanNum2, textureCoord1, textureCoord2, fv1, fv2, m, i, j, wgIndex);

		}

	}

}

void BezierBspline::getBsplinePercent(int i, float* bsplinePercent, int blineSplitNum, int m, int mIndex)
{
	float linePercent = (float)(i%blineSplitNum) / (float)blineSplitNum;
	bsplinePercent[m*evenum + mIndex] = linePercent;
	bsplinePercent[m*evenum + mIndex + 1] = float(i%blineSplitNum);
	bsplinePercent[m*evenum + mIndex + 2] = float(i);

}

void BezierBspline::makeUpClosedQuadFace(int m, int mIndex, int i, int j, int tansverSpanNum1,
	float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4,
	float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
	float* trueBlineFactors1, float* trueBlineFactors2, 
	float* blineFactors1, float* blineFactors2, float* bsplinePercent, int blineSplitNum)
{
	
	trueBezierShaderPoints1[m * evenum + mIndex] = bezierShaderPoints1[i * 3 + tansverSpanNum1];
	trueBezierShaderPoints1[m * evenum + mIndex + 1] = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum1];
	trueBezierShaderPoints1[m * evenum + mIndex + 2] = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum1];
	trueBezierShaderPoints2[m * evenum + mIndex] = bezierShaderPoints2[i * 3 + tansverSpanNum1];
	trueBezierShaderPoints2[m * evenum + mIndex + 1] = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum1];
	trueBezierShaderPoints2[m * evenum + mIndex + 2] = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum1];
	trueBezierShaderPoints3[m * evenum + mIndex] = bezierShaderPoints3[i * 3 + tansverSpanNum1];
	trueBezierShaderPoints3[m * evenum + mIndex + 1] = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum1];
	trueBezierShaderPoints3[m * evenum + mIndex + 2] = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum1];
	trueBezierShaderPoints4[m * evenum + mIndex] = bezierShaderPoints4[i * 3 + tansverSpanNum1];
	trueBezierShaderPoints4[m * evenum + mIndex + 1] = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum1];
	trueBezierShaderPoints4[m * evenum + mIndex + 2] = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum1];
	trueBlineFactors1[m * evenum + mIndex] = blineFactors1[i * 3 + tansverSpanNum1];
	trueBlineFactors1[m * evenum + mIndex + 1] = blineFactors1[i * 3 + tansverSpanNum1 + 1];
	trueBlineFactors1[m * evenum + mIndex + 2] = (float)j;
	trueBlineFactors2[m * evenum + mIndex] = blineFactors2[i * 3 + tansverSpanNum1];
	trueBlineFactors2[m * evenum + mIndex + 1] = blineFactors2[i * 3 + tansverSpanNum1 + 1];
	trueBlineFactors2[m * evenum + mIndex + 2] = (float)i;
	
	BezierBspline::getBsplinePercent(i, bsplinePercent, blineSplitNum, m, mIndex);

}



void BezierBspline::getCloseAllShaderParams(int tansverSpanNum1, int tansverSpanNum2, float textureCoord1,
	float textureCoord2, float fv1, float fv2, int m, int i, int j, int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	float* blinesPoints = wgPoint->blinesPoints;
	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* blineFactors1 = wgPoint->blineFactors1;
	float* blineFactors2 = wgPoint->blineFactors2;
	float* trueBezierShaderPoints1 = wgPoint->trueBezierShaderPoints1;
	float* trueBezierShaderPoints2 = wgPoint->trueBezierShaderPoints2;
	float* trueBezierShaderPoints3 = wgPoint->trueBezierShaderPoints3;
	float* trueBezierShaderPoints4 = wgPoint->trueBezierShaderPoints4;
	float* trueBlineFactors1 = wgPoint->trueBlineFactors1;
	float* trueBlineFactors2 = wgPoint->trueBlineFactors2;
	float* g_vertexTexcoord = wgPoint->g_vertexTexcoord;

	float* bsplinePercent = wgPoint->bsplinePercent;
	int blineSplitNum = wgPoint->blineSplitNum;

	BezierBspline::makeUpClosedQuadFace(m, 0, i, j, tansverSpanNum1,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);

	BezierBspline::makeUpClosedQuadFace(m, 3, 0, j, tansverSpanNum1,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);
	
	BezierBspline::makeUpClosedQuadFace(m, 6, i, j, tansverSpanNum2,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);
	
	BezierBspline::makeUpClosedQuadFace(m, 9, i, j, tansverSpanNum2,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);
	
	BezierBspline::makeUpClosedQuadFace(m, 12, 0, j, tansverSpanNum2,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);

	BezierBspline::makeUpClosedQuadFace(m, 15, 0, j, tansverSpanNum1,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);
	
	BezierBspline::saveClosedBsplinePoints(m, i, tansverSpanNum1, tansverSpanNum2, blinesPoints,wgIndex);
	g_vertexTexcoord[m * 12 + 0] = textureCoord1;//textureCoord1
	g_vertexTexcoord[m * 12 + 1] = fv1;
	g_vertexTexcoord[m * 12 + 2] = textureCoord1;//textureCoord2
	g_vertexTexcoord[m * 12 + 3] = fv2;
	g_vertexTexcoord[m * 12 + 4] = textureCoord2;//textureCoord1
	g_vertexTexcoord[m * 12 + 5] = fv1;

	g_vertexTexcoord[m * 12 + 6] = textureCoord2;//textureCoord1
	g_vertexTexcoord[m * 12 + 7] = fv1;
	g_vertexTexcoord[m * 12 + 8] = textureCoord2;//textureCoord2
	g_vertexTexcoord[m * 12 + 9] = fv2;
	g_vertexTexcoord[m * 12 + 10] = textureCoord1;//textureCoord2
	g_vertexTexcoord[m * 12 + 11] = fv2;
}

void BezierBspline::getAllShaderParams(int tansverSpanNum1, int tansverSpanNum2, float textureCoord1,
	float textureCoord2, float fv1, float fv2, int m, int i, int j, int wgIndex)
{

	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	float* blinesPoints = wgPoint->blinesPoints;
	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* blineFactors1 = wgPoint->blineFactors1;
	float* blineFactors2 = wgPoint->blineFactors2;
	float* trueBezierShaderPoints1 = wgPoint->trueBezierShaderPoints1;
	float* trueBezierShaderPoints2 = wgPoint->trueBezierShaderPoints2;
	float* trueBezierShaderPoints3 = wgPoint->trueBezierShaderPoints3;
	float* trueBezierShaderPoints4 = wgPoint->trueBezierShaderPoints4;
	float* trueBlineFactors1 = wgPoint->trueBlineFactors1;
	float* trueBlineFactors2 = wgPoint->trueBlineFactors2;
	//用来存放样条曲线百分比的集合
	float* bsplinePercent = wgPoint->bsplinePercent;
	int blineSplitNum = wgPoint->blineSplitNum;
	float* g_vertexTexcoord = wgPoint->g_vertexTexcoord;

	BezierBspline::makeUpClosedQuadFace(m, 0, i, j, tansverSpanNum1,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);

	BezierBspline::makeUpClosedQuadFace(m, 3, i + 1, j, tansverSpanNum1,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);
	
	BezierBspline::makeUpClosedQuadFace(m, 6, i, j, tansverSpanNum2,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);

	BezierBspline::makeUpClosedQuadFace(m, 9, i, j, tansverSpanNum2,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);

	BezierBspline::makeUpClosedQuadFace(m, 12, i+1, j, tansverSpanNum2,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);

	BezierBspline::makeUpClosedQuadFace(m, 15, i + 1, j, tansverSpanNum1,
		trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4,
		bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
		trueBlineFactors1, trueBlineFactors2, 
		blineFactors1, blineFactors2, bsplinePercent, blineSplitNum);
	
	BezierBspline::saveBsplinePoints(m, i, tansverSpanNum1, tansverSpanNum2, blinesPoints,wgIndex);
	
	g_vertexTexcoord[m * 12 + 0] = textureCoord1;//textureCoord1
	g_vertexTexcoord[m * 12 + 1] = fv1;
	g_vertexTexcoord[m * 12 + 2] = textureCoord1;//textureCoord2
	g_vertexTexcoord[m * 12 + 3] = fv2;
	g_vertexTexcoord[m * 12 + 4] = textureCoord2;//textureCoord1
	g_vertexTexcoord[m * 12 + 5] = fv1;

	g_vertexTexcoord[m * 12 + 6] = textureCoord2;//textureCoord1
	g_vertexTexcoord[m * 12 + 7] = fv1;
	g_vertexTexcoord[m * 12 + 8] = textureCoord2;//textureCoord2
	g_vertexTexcoord[m * 12 + 9] = fv2;
	g_vertexTexcoord[m * 12 + 10] = textureCoord1;//textureCoord2
	g_vertexTexcoord[m * 12 + 11] = fv2;
}

void BezierBspline::saveBsplinePoints(int m, int i, int tansverSpanNum1, int tansverSpanNum2,float* blinesPoints,int wgIndex)
{
	
	WizardGeom* wg = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	wg->geomIndices[m * 6 + 0] = (6 * m);
	wg->geomIndices[m * 6 + 1] = (6 * m + 1);
	wg->geomIndices[m * 6 + 2] = (6 * m + 2);
	wg->geomIndices[m * 6 + 3] = (6 * m + 3);
	wg->geomIndices[m * 6 + 4] = (6 * m + 4);
	wg->geomIndices[m * 6 + 5] = (6 * m + 5);

}

void BezierBspline::saveClosedBsplinePoints(int m, int i, int tansverSpanNum1, int tansverSpanNum2, float* blinesPoints,int wgIndex)
{
	WizardGeom* wg = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	wg->geomIndices[m * 6 + 0] = (6 * m);
	wg->geomIndices[m * 6 + 1] = (6 * m + 1);
	wg->geomIndices[m * 6 + 2] = (6 * m + 2);
	wg->geomIndices[m * 6 + 3] = (6 * m + 3);
	wg->geomIndices[m * 6 + 4] = (6 * m + 4);
	wg->geomIndices[m * 6 + 5] = (6 * m + 5);

}

void BezierBspline::bindShaderBezierPoints(int wgIndex)
{
	//wgIndex为0的精灵做为连接部，连接到wgIndex为1的精灵上
	//if (wgIndex==0)
	{
		WizardGeom* synthPointZero = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
       wizardGeomSuppleBezierBspline.joinWizardGeom();
		float* splitPoints = wizardGeomBezierBspline.getCurrWizardGeom(1)->joinPoints;
		float* bezPointGatherZero = synthPointZero->bezPointGather;
		//按度数切分圆的个数
		int degreeSplitNumZero = synthPointZero->degreeSplitNum;
		int bezierLoopTimeZero = synthPointZero->baseDataPercentNum - 1;
		int bezierStepZero = synthPointZero->bezierStep;
		float bezierPercent = 1.0f / (float(bezierStepZero));
		float factorialResult[30000];//介乘结果的集合
		for (int i = 0; i <= bezierLoopTimeZero; i++){	//求0到n的阶乘
            factorialResult[i] = BezierBspline::factrial(i);
		}
		//循环每个点
		for (int row = 0; row < degreeSplitNumZero; row++)
		{
			for (int i = 0; i <= bezierStepZero; i++)
			{

				float xf = 0.0f;
				float yf = 0.0f;
				float zf = 0.0f;
				float tka[30000];
				float otka[30000];


				//在bezier曲线上的节点的百分数
				float bezFractValue = float(i)*bezierPercent;
				if (bezFractValue > 1)
				{
						bezFractValue = 1;
				}
				for (int j = 0; j <= bezierLoopTimeZero; j++)
				{
				    tka[j] = float(pow(bezFractValue, j)); //计算t的j次幂
				    otka[j] = float(pow(1.0f - bezFractValue, j)); //计算1-t的j次幂
				}

				for (int k = 0; k <= bezierLoopTimeZero; k++)
				{
				    float xs = (factorialResult[bezierLoopTimeZero] / (factorialResult[k] * factorialResult[bezierLoopTimeZero - k])) * tka[k] * otka[bezierLoopTimeZero - k];
					int cutPlaneindex = k*degreeSplitNumZero * 3;//每个切面的数值个数
					int pointIndex = row * 3;//一个圆的第几个点的角标
					xf = xf + splitPoints[cutPlaneindex + pointIndex] * xs;
					yf = yf + splitPoints[cutPlaneindex + pointIndex + 1] * xs;
					zf = zf + splitPoints[cutPlaneindex + pointIndex + 2] * xs;
				}

				int currIndex = bezierStepZero*row * 3;//当前bezier线条的角标值
                bezPointGatherZero[currIndex + i * 3] = xf;
                bezPointGatherZero[currIndex + i * 3 + 1] = yf;
                bezPointGatherZero[currIndex + i * 3 + 2] = zf;
                synthPointZero->bezPointGatherCache[currIndex + i * 3] = xf;
                synthPointZero->bezPointGatherCache[currIndex + i * 3 + 1] = yf;
                synthPointZero->bezPointGatherCache[currIndex + i * 3 + 2] = zf;

            }

		}
	}

}


void BezierBspline::bindShaderBezier2Bline(int wgIndex)
{
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	
	int blineSplitNum = wgPoint->blineSplitNum;
	int bezierStep = wgPoint->bezierStep;
	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;
	float* bezPointGather = wgPoint->bezPointGather;

	for (int i = 0; i < blineSplitNum; i++)
	{
		
		int degreeSplitNum = wgPoint->degreeSplitNum - 3;
		for (int m = 0; m < bezierStep; m++) //每条贝塞尔线段上拥有的点数  贝塞尔线段上的第m个点
		{
			//每个闭环包含的段数 * 每个曲线段包含的点个数 * 3 * 第m个闭合圈   每个闭合圈所包含的数值个数   +3是加的3条线段
			int loopIndex = (degreeSplitNum + 3)* blineSplitNum * 3 * m;
			int mIndex1 = m * 3; //贝塞尔线段上的第 m 个点的索引
			for (int j = 0; j < degreeSplitNum; j++)
			{
				//j * steps * 3  横截面的第j个点
				int secNum = blineSplitNum * 3 * j;//到第 j 个点时，当下的索引值
				int blindex = secNum + i * 3 + loopIndex;

				bezierShaderPoints1[blindex] = bezPointGather[j * bezierStep * 3 + mIndex1];
				bezierShaderPoints1[blindex + 1] = bezPointGather[j * bezierStep * 3 + mIndex1 + 1];
				bezierShaderPoints1[blindex + 2] = bezPointGather[j * bezierStep * 3 + mIndex1 + 2];
				bezierShaderPoints2[blindex] = bezPointGather[(j + 1) * bezierStep * 3 + mIndex1];
				bezierShaderPoints2[blindex + 1] = bezPointGather[(j + 1) * bezierStep * 3 + mIndex1 + 1];
				bezierShaderPoints2[blindex + 2] = bezPointGather[(j + 1) * bezierStep * 3 + mIndex1 + 2];
				bezierShaderPoints3[blindex] = bezPointGather[(j + 2) * bezierStep * 3 + mIndex1];
				bezierShaderPoints3[blindex + 1] = bezPointGather[(j + 2) * bezierStep * 3 + mIndex1 + 1];
				bezierShaderPoints3[blindex + 2] = bezPointGather[(j + 2) * bezierStep * 3 + mIndex1 + 2];
				bezierShaderPoints4[blindex] = bezPointGather[(j + 3) * bezierStep * 3 + mIndex1];
				bezierShaderPoints4[blindex + 1] = bezPointGather[(j + 3) * bezierStep * 3 + mIndex1 + 1];
				bezierShaderPoints4[blindex + 2] = bezPointGather[(j + 3) * bezierStep * 3 + mIndex1 + 2];

			}

			int blinePointNum = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex)->degreeSplitNum - 3;
			int index1 = blinePointNum * bezierStep * 3;
			int index2 = (blinePointNum + 1) * bezierStep * 3;
			int index3 = (blinePointNum + 2) * bezierStep * 3;
			int lastThirdIndex = i * 3 + blineSplitNum * 3 * degreeSplitNum + loopIndex;

			bezierShaderPoints1[lastThirdIndex] = bezPointGather[index1 + mIndex1];
			bezierShaderPoints1[lastThirdIndex + 1] = bezPointGather[index1 + mIndex1 + 1];
			bezierShaderPoints1[lastThirdIndex + 2] = bezPointGather[index1 + mIndex1 + 2];
			bezierShaderPoints2[lastThirdIndex] = bezPointGather[index2 + mIndex1];
			bezierShaderPoints2[lastThirdIndex + 1] = bezPointGather[index2 + mIndex1 + 1];
			bezierShaderPoints2[lastThirdIndex + 2] = bezPointGather[index2 + mIndex1 + 2];
			bezierShaderPoints3[lastThirdIndex] = bezPointGather[index3 + mIndex1];
			bezierShaderPoints3[lastThirdIndex + 1] = bezPointGather[index3 + mIndex1 + 1];
			bezierShaderPoints3[lastThirdIndex + 2] = bezPointGather[index3 + mIndex1 + 2];
			bezierShaderPoints4[lastThirdIndex] = bezPointGather[mIndex1];
			bezierShaderPoints4[lastThirdIndex + 1] = bezPointGather[mIndex1 + 1];
			bezierShaderPoints4[lastThirdIndex + 2] = bezPointGather[mIndex1 + 2];

			int last2Index1 = (blinePointNum + 1) * bezierStep * 3;
			int last2Index2 = (blinePointNum + 2) * bezierStep * 3;
			int lastSecondIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 1) + loopIndex;
			bezierShaderPoints1[lastSecondIndex] = bezPointGather[last2Index1 + mIndex1];
			bezierShaderPoints1[lastSecondIndex + 1] = bezPointGather[last2Index1 + mIndex1 + 1];
			bezierShaderPoints1[lastSecondIndex + 2] = bezPointGather[last2Index1 + mIndex1 + 2];
			bezierShaderPoints2[lastSecondIndex] = bezPointGather[last2Index2 + mIndex1];
			bezierShaderPoints2[lastSecondIndex + 1] = bezPointGather[last2Index2 + mIndex1 + 1];
			bezierShaderPoints2[lastSecondIndex + 2] = bezPointGather[last2Index2 + mIndex1 + 2];
			bezierShaderPoints3[lastSecondIndex] = bezPointGather[mIndex1];
			bezierShaderPoints3[lastSecondIndex + 1] = bezPointGather[mIndex1 + 1];
			bezierShaderPoints3[lastSecondIndex + 2] = bezPointGather[mIndex1 + 2];
			bezierShaderPoints4[lastSecondIndex] = bezPointGather[bezierStep * 3 + mIndex1];
			bezierShaderPoints4[lastSecondIndex + 1] = bezPointGather[bezierStep * 3 + mIndex1 + 1];
			bezierShaderPoints4[lastSecondIndex + 2] = bezPointGather[bezierStep * 3 + mIndex1 + 2];


			int lastIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 2) + loopIndex;
			int lasIndex1 = (blinePointNum + 2) * bezierStep * 3;
			bezierShaderPoints1[lastIndex] = bezPointGather[lasIndex1 + mIndex1];
			bezierShaderPoints1[lastIndex + 1] = bezPointGather[lasIndex1 + mIndex1 + 1];
			bezierShaderPoints1[lastIndex + 2] = bezPointGather[lasIndex1 + mIndex1 + 2];
			bezierShaderPoints2[lastIndex] = bezPointGather[mIndex1];
			bezierShaderPoints2[lastIndex + 1] = bezPointGather[mIndex1 + 1];
			bezierShaderPoints2[lastIndex + 2] = bezPointGather[mIndex1 + 2];
			bezierShaderPoints3[lastIndex] = bezPointGather[bezierStep * 3 + mIndex1];
			bezierShaderPoints3[lastIndex + 1] = bezPointGather[bezierStep * 3 + mIndex1 + 1];
			bezierShaderPoints3[lastIndex + 2] = bezPointGather[bezierStep * 3 + mIndex1 + 2];
			bezierShaderPoints4[lastIndex] = bezPointGather[2 * bezierStep * 3 + mIndex1];
			bezierShaderPoints4[lastIndex + 1] = bezPointGather[2 * bezierStep * 3 + mIndex1 + 1];
			bezierShaderPoints4[lastIndex + 2] = bezPointGather[2 * bezierStep * 3 + mIndex1 + 2];

		}
	}

}

void BezierBspline::makeUpShaderQuadFace(int i, int mIndex, int j, int tansverSpanNum1, int m,
	float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
	float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4)
{

	float bezierShaderPointX1_1 = bezierShaderPoints1[i * 3 + tansverSpanNum1];
	float bezierShaderPointY1_1 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum1];
	float bezierShaderPointZ1_1 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum1];
	float bezierShaderPointX2_1 = bezierShaderPoints2[i * 3 + tansverSpanNum1];
	float bezierShaderPointY2_1 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum1];
	float bezierShaderPointZ2_1 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum1];
	float bezierShaderPointX3_1 = bezierShaderPoints3[i * 3 + tansverSpanNum1];
	float bezierShaderPointY3_1 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum1];
	float bezierShaderPointZ3_1 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum1];
	float bezierShaderPointX4_1 = bezierShaderPoints4[i * 3 + tansverSpanNum1];
	float bezierShaderPointY4_1 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum1];
	float bezierShaderPointZ4_1 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum1];

	trueBezierShaderPoints1[m * evenum + mIndex] = bezierShaderPointX1_1;
	trueBezierShaderPoints1[m * evenum + mIndex + 1] = bezierShaderPointY1_1;
	trueBezierShaderPoints1[m * evenum + mIndex + 2] = bezierShaderPointZ1_1;
	trueBezierShaderPoints2[m * evenum + mIndex] = bezierShaderPointX2_1;
	trueBezierShaderPoints2[m * evenum + mIndex + 1] = bezierShaderPointY2_1;
	trueBezierShaderPoints2[m * evenum + mIndex + 2] = bezierShaderPointZ2_1;
	trueBezierShaderPoints3[m * evenum + mIndex] = bezierShaderPointX3_1;
	trueBezierShaderPoints3[m * evenum + mIndex + 1] = bezierShaderPointY3_1;
	trueBezierShaderPoints3[m * evenum + mIndex + 2] = bezierShaderPointZ3_1;
	trueBezierShaderPoints4[m * evenum + mIndex] = bezierShaderPointX4_1;
	trueBezierShaderPoints4[m * evenum + mIndex + 1] = bezierShaderPointY4_1;
	trueBezierShaderPoints4[m * evenum + mIndex + 2] = bezierShaderPointZ4_1;


}



void BezierBspline::makeUpShaderQuadFaceBezier(int i, int mIndex, int j, int bezierStep, int tansverSpanNum2, int m,
	float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
	float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4)
{
	float bezierShaderPointX1_3 = bezierShaderPoints1[i * 3 + tansverSpanNum2];
	float bezierShaderPointY1_3 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ1_3 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum2];
	float bezierShaderPointX2_3 = bezierShaderPoints2[i * 3 + tansverSpanNum2];
	float bezierShaderPointY2_3 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ2_3 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum2];
	float bezierShaderPointX3_3 = bezierShaderPoints3[i * 3 + tansverSpanNum2];
	float bezierShaderPointY3_3 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ3_3 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum2];
	float bezierShaderPointX4_3 = bezierShaderPoints4[i * 3 + tansverSpanNum2];
	float bezierShaderPointY4_3 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ4_3 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum2];

	trueBezierShaderPoints1[m * evenum + mIndex] = bezierShaderPointX1_3;
	trueBezierShaderPoints1[m * evenum + mIndex + 1] = bezierShaderPointY1_3;
	trueBezierShaderPoints1[m * evenum + mIndex + 2] = bezierShaderPointZ1_3;
	trueBezierShaderPoints2[m * evenum + mIndex] = bezierShaderPointX2_3;
	trueBezierShaderPoints2[m * evenum + mIndex + 1] = bezierShaderPointY2_3;
	trueBezierShaderPoints2[m * evenum + mIndex + 2] = bezierShaderPointZ2_3;
	trueBezierShaderPoints3[m * evenum + mIndex] = bezierShaderPointX3_3;
	trueBezierShaderPoints3[m * evenum + mIndex + 1] = bezierShaderPointY3_3;
	trueBezierShaderPoints3[m * evenum + mIndex + 2] = bezierShaderPointZ3_3;
	trueBezierShaderPoints4[m * evenum + mIndex] = bezierShaderPointX4_3;
	trueBezierShaderPoints4[m * evenum + mIndex + 1] = bezierShaderPointY4_3;
	trueBezierShaderPoints4[m * evenum + mIndex + 2] = bezierShaderPointZ4_3;

}

void BezierBspline::makeUpShaderQuadFace5(int i, int j, int bezierStep, int tansverSpanNum2, int m,
	float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
	float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4)
{
	float bezierShaderPointX1_5 = bezierShaderPoints1[(i + 1) * 3 + tansverSpanNum2];
	float bezierShaderPointY1_5 = bezierShaderPoints1[(i + 1) * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ1_5 = bezierShaderPoints1[(i + 1) * 3 + 2 + tansverSpanNum2];
	float bezierShaderPointX2_5 = bezierShaderPoints2[(i + 1) * 3 + tansverSpanNum2];
	float bezierShaderPointY2_5 = bezierShaderPoints2[(i + 1) * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ2_5 = bezierShaderPoints2[(i + 1) * 3 + 2 + tansverSpanNum2];
	float bezierShaderPointX3_5 = bezierShaderPoints3[(i + 1) * 3 + tansverSpanNum2];
	float bezierShaderPointY3_5 = bezierShaderPoints3[(i + 1) * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ3_5 = bezierShaderPoints3[(i + 1) * 3 + 2 + tansverSpanNum2];
	float bezierShaderPointX4_5 = bezierShaderPoints4[(i + 1) * 3 + tansverSpanNum2];
	float bezierShaderPointY4_5 = bezierShaderPoints4[(i + 1) * 3 + 1 + tansverSpanNum2];
	float bezierShaderPointZ4_5 = bezierShaderPoints4[(i + 1) * 3 + 2 + tansverSpanNum2];

	trueBezierShaderPoints1[m * evenum + 12] = bezierShaderPointX1_5;
	trueBezierShaderPoints1[m * evenum + 13] = bezierShaderPointY1_5;
	trueBezierShaderPoints1[m * evenum + 14] = bezierShaderPointZ1_5;
	trueBezierShaderPoints2[m * evenum + 12] = bezierShaderPointX2_5;
	trueBezierShaderPoints2[m * evenum + 13] = bezierShaderPointY2_5;
	trueBezierShaderPoints2[m * evenum + 14] = bezierShaderPointZ2_5;
	trueBezierShaderPoints3[m * evenum + 12] = bezierShaderPointX3_5;
	trueBezierShaderPoints3[m * evenum + 13] = bezierShaderPointY3_5;
	trueBezierShaderPoints3[m * evenum + 14] = bezierShaderPointZ3_5;
	trueBezierShaderPoints4[m * evenum + 12] = bezierShaderPointX4_5;
	trueBezierShaderPoints4[m * evenum + 13] = bezierShaderPointY4_5;
	trueBezierShaderPoints4[m * evenum + 14] = bezierShaderPointZ4_5;

}

void BezierBspline::makeUpClosedShaderQuadFace5(int i, int j, int bezierStep, int tansverSpanNum2, int m,
	float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
	float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4)
{
	float bezierShaderPointX1_5 = bezierShaderPoints1[tansverSpanNum2];
	float bezierShaderPointY1_5 = bezierShaderPoints1[1 + tansverSpanNum2];
	float bezierShaderPointZ1_5 = bezierShaderPoints1[2 + tansverSpanNum2];
	float bezierShaderPointX2_5 = bezierShaderPoints2[tansverSpanNum2];
	float bezierShaderPointY2_5 = bezierShaderPoints2[1 + tansverSpanNum2];
	float bezierShaderPointZ2_5 = bezierShaderPoints2[2 + tansverSpanNum2];
	float bezierShaderPointX3_5 = bezierShaderPoints3[tansverSpanNum2];
	float bezierShaderPointY3_5 = bezierShaderPoints3[1 + tansverSpanNum2];
	float bezierShaderPointZ3_5 = bezierShaderPoints3[2 + tansverSpanNum2];
	float bezierShaderPointX4_5 = bezierShaderPoints4[tansverSpanNum2];
	float bezierShaderPointY4_5 = bezierShaderPoints4[1 + tansverSpanNum2];
	float bezierShaderPointZ4_5 = bezierShaderPoints4[2 + tansverSpanNum2];

	trueBezierShaderPoints1[m * evenum + 12] = bezierShaderPointX1_5;
	trueBezierShaderPoints1[m * evenum + 13] = bezierShaderPointY1_5;
	trueBezierShaderPoints1[m * evenum + 14] = bezierShaderPointZ1_5;
	trueBezierShaderPoints2[m * evenum + 12] = bezierShaderPointX2_5;
	trueBezierShaderPoints2[m * evenum + 13] = bezierShaderPointY2_5;
	trueBezierShaderPoints2[m * evenum + 14] = bezierShaderPointZ2_5;
	trueBezierShaderPoints3[m * evenum + 12] = bezierShaderPointX3_5;
	trueBezierShaderPoints3[m * evenum + 13] = bezierShaderPointY3_5;
	trueBezierShaderPoints3[m * evenum + 14] = bezierShaderPointZ3_5;
	trueBezierShaderPoints4[m * evenum + 12] = bezierShaderPointX4_5;
	trueBezierShaderPoints4[m * evenum + 13] = bezierShaderPointY4_5;
	trueBezierShaderPoints4[m * evenum + 14] = bezierShaderPointZ4_5;


}

void BezierBspline::bindTrueShaderPoints(int wgIndex)
{
	
	WizardGeom* wgPoint = wizardGeomBezierBspline.getCurrWizardGeom(wgIndex);
	float* blinesPoints = wgPoint->blinesPoints;
	float* bezierShaderPoints1 = wgPoint->bezierShaderPoints1;
	float* bezierShaderPoints2 = wgPoint->bezierShaderPoints2;
	float* bezierShaderPoints3 = wgPoint->bezierShaderPoints3;
	float* bezierShaderPoints4 = wgPoint->bezierShaderPoints4;

	float* trueBezierShaderPoints1 = wgPoint->trueBezierShaderPoints1;
	float* trueBezierShaderPoints2 = wgPoint->trueBezierShaderPoints2;
	float* trueBezierShaderPoints3 = wgPoint->trueBezierShaderPoints3;
	float* trueBezierShaderPoints4 = wgPoint->trueBezierShaderPoints4;
	int bezierStep = wgPoint->bezierStep;

	int everyCircleNum = wgPoint->blineSplitNum*wgPoint->degreeSplitNum;
	int evenum = 18;//一个四边形 6 个索引
	//横向跨度
	for (int j = 0; j < bezierStep; j++)
	{
		int tansverSpanNum1 = j * everyCircleNum * 3;
		int tansverSpanNum2 = (j + 1) * everyCircleNum * 3;
		float textureCoord1 = j * 1.0 / bezierStep;
		float textureCoord2 = (j + 1.0) / bezierStep;

		for (int i = 0; i < everyCircleNum - 1; i++)//在一个闭合圈内跳跃几个点
		{
			//float remainder = (i%wgPoint->blineSplitNum) / (wgPoint->blineSplitNum*1.0);
			float fv1 = i*1.0 / everyCircleNum;
			float fv2 = (i + 1)*1.0 / everyCircleNum;
			//每个闭合圈点的个数 * 第几个横向跨度 + 当前闭合圈点里的第几个点
			int m = everyCircleNum * j + i;
			//四个集合对应四个控制点
			//六个函数对应两个三角形的六个点
			self.makeUpShaderQuadFace(i, 0, j, tansverSpanNum1, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);
		
			self.makeUpShaderQuadFace(i+1, 3, j, tansverSpanNum1, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);
			
			self.makeUpShaderQuadFaceBezier(i, 6, j, bezierStep, tansverSpanNum2, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);

			self.makeUpShaderQuadFaceBezier(i, 9, j, bezierStep, tansverSpanNum2, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);


			self.makeUpShaderQuadFace5(i, j, bezierStep, tansverSpanNum2, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);

			self.makeUpShaderQuadFace(i + 1, 15, j, tansverSpanNum1, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);

		}

		for (int i = everyCircleNum - 1; i < everyCircleNum; i++)//在一个闭合圈内跳跃几个点
		{

			float fv1 = i*1.0 / everyCircleNum;
			float fv2 = (i + 1)*1.0 / everyCircleNum;
			int m = everyCircleNum * j + i;

			self.makeUpShaderQuadFace(i, 0, j, tansverSpanNum1, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);
			
			self.makeUpShaderQuadFace(0, 3, j, tansverSpanNum1, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);

			self.makeUpShaderQuadFaceBezier(i, 6, j, bezierStep, tansverSpanNum2, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);

			self.makeUpShaderQuadFaceBezier(i, 9, j, bezierStep, tansverSpanNum2, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);
			
			self.makeUpClosedShaderQuadFace5(i, j, bezierStep, tansverSpanNum2, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);

			self.makeUpShaderQuadFace(0, 15, j, tansverSpanNum1, m,
				bezierShaderPoints1, bezierShaderPoints2, bezierShaderPoints3, bezierShaderPoints4,
				trueBezierShaderPoints1, trueBezierShaderPoints2, trueBezierShaderPoints3, trueBezierShaderPoints4);
			
		}

	}
}


void BezierBspline::boneAnimation(int wgIndex)
{
    //BezierBspline::bindShaderBezierPoints(wgIndex);
    //bezierAnimationByAngleBezierBspline.bezierAnimation2(wgIndex);
    std::thread t1(calElephant2,wgIndex);
    t1.join();
    std::thread t2(calElephant1,wgIndex);
    t2.join();
//    BezierBspline::bindShaderBezier2Bline(wgIndex);
//    BezierBspline::bindTrueShaderPoints(wgIndex);

}

void BezierBspline::calElephant1(int geomIndex){
    flyElephantExerciseBezierBspline.rotateByBaseLine(ControlPanel::rotateBodyAngle);//0.1
    flyElephantExerciseBezierBspline.frontMove();
    //flyElephantExerciseBezierBspline.moveUpDown();
    BezierBspline::bindShaderBezier2Bline(geomIndex);
    BezierBspline::bindTrueShaderPoints(geomIndex);
}

void BezierBspline::calElephant2(int geomIndex){
    bezierAnimationByAngleBezierBspline.bezierAnimation2(geomIndex);
}
