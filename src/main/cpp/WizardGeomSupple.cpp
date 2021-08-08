#include "WizardGeomSupple.h"


WizardGeom wizardGeomWizardGeomSupple;
ShaderUtil shaderUtilWizardGeomSupple;
//切分时绕转的半径
float WizardGeomSupple::currentPoint[3];
float WizardGeomSupple::baseLinePercentPoints[90];
float point[3];
WizardGeomSupple::WizardGeomSupple(){}

WizardGeomSupple::~WizardGeomSupple(){}
       
void WizardGeomSupple::averageCircle(float percent, int perNum, float splitRadius, void* wgPoint)
{
	WizardGeom* synthPoint = (WizardGeom*)wgPoint;
	float* splitPoints = synthPoint->splitPoints;
	float* baseData = synthPoint->baseData;
	int degreeSplitNum = synthPoint->degreeSplitNum;
	int currIndex = perNum * degreeSplitNum * 3;

	//顶部的那个点
	if (perNum == 0)
	{
		splitPoints[0] = currentPoint[0]; splitPoints[1] = currentPoint[1]; splitPoints[2] = currentPoint[2];
		for (int i = 0; i < degreeSplitNum - 1; i++)
		{
			splitPoints[currIndex + (i + 1) * 3] = currentPoint[0];
			splitPoints[currIndex + (i + 1) * 3 + 1] = currentPoint[1];
			splitPoints[currIndex + (i + 1) * 3 + 2] = currentPoint[2];
		}

		return;
	}

	float middLineX = baseData[3] - baseData[0];
	float middLineY = baseData[4] - baseData[1];
	float middLineZ = baseData[5] - baseData[2];
	//中间线和y轴共面的垂线
	float verticalVect[3];
    WizardGeomSupple::getVerticalVect(middLineX, middLineY, middLineZ, 0.0, 0.0, -1.0,verticalVect);

	float radiusRatio = sqrt(splitRadius*splitRadius / (verticalVect[0] * verticalVect[0] +
		verticalVect[1]*verticalVect[1] + verticalVect[2]*verticalVect[2]));
	//生成的基点
	float baseX = currentPoint[0] - radiusRatio*verticalVect[0];
	float baseY = currentPoint[1] - radiusRatio*verticalVect[1];
	float baseZ = currentPoint[2] - radiusRatio*verticalVect[2];
	splitPoints[0 + currIndex] = baseX; splitPoints[1 + currIndex] = baseY; splitPoints[2 + currIndex] = baseZ;
	
	for (int i = 0; i < degreeSplitNum - 1; i++)
	{

		float splitRadian = (3.1415926 / 180.0)*(360.0 / degreeSplitNum);
		float newMoveL = tan(splitRadian)*splitRadius;
		float radius=splitRadius;
//        if(i>2&&i<22&&perNum==1){
//            radius=splitRadius+0.12;
//        }else{
//            radius=splitRadius-0.006;
//        }
		float* finalPoint = WizardGeomSupple::GetVerticalPointByVect(baseX, baseY, baseZ, middLineX, middLineY, middLineZ, newMoveL,radius);

		splitPoints[currIndex + (i + 1) * 3] = finalPoint[0];
		splitPoints[currIndex + (i + 1) * 3 + 1] = finalPoint[1];
		splitPoints[currIndex + (i + 1) * 3 + 2] = finalPoint[2];
		//产生新的基点
		baseX = finalPoint[0];
		baseY = finalPoint[1];
		baseZ = finalPoint[2];
	}

}
//基线的百分比上的点
void WizardGeomSupple::getCurrentPoint(float percent,int perNum, void* wgPoint)
{
	
	WizardGeom* synthPoint = (WizardGeom*)wgPoint;
	float* baseData = synthPoint->baseData;
	float middLineX = baseData[3] - baseData[0];
	float middLineY = baseData[4] - baseData[1];
	float middLineZ = baseData[5] - baseData[2];
	float length = sqrt(middLineX*middLineX + middLineY*middLineY + middLineZ*middLineZ)*percent;
	float ratio = sqrt(length*length / (middLineX*middLineX + middLineY*middLineY + middLineZ*middLineZ));
	currentPoint[0] = baseData[0] + ratio*middLineX;
	currentPoint[1] = baseData[1] + ratio*middLineY;
	currentPoint[2] = baseData[2] + ratio*middLineZ;

	baseLinePercentPoints[perNum * 3] = currentPoint[0];
	baseLinePercentPoints[perNum * 3 + 1] = currentPoint[1];
	baseLinePercentPoints[perNum * 3 + 2] = currentPoint[2];
	
}

float* WizardGeomSupple::makeUpCirclePoints(void* wgPoint)
{
	WizardGeom* syntheticalUtilPoint = (WizardGeom*)wgPoint;
	int size = syntheticalUtilPoint->baseDataPercentNum;
	float* baseDataPercent = syntheticalUtilPoint->baseDataPercent;
	for (int i = 0; i < size; i++)
	{
		WizardGeomSupple::getCurrentPoint(baseDataPercent[i], i, syntheticalUtilPoint);
		if (i == 0)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.1, syntheticalUtilPoint);
		}
		else if (i == 1)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
		else if (i== 2)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
		else if (i == 3)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.3, syntheticalUtilPoint);
		}
		else if (i == 4)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.3, syntheticalUtilPoint);
		}
		else if (i == 5)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
		else if (i == 6)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
		else if (i == 7)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
		else if (i == 8)
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
		else
		{
			WizardGeomSupple::averageCircle(baseDataPercent[i], i, 0.25, syntheticalUtilPoint);
		}
	}

	float* splitPoints = syntheticalUtilPoint->splitPoints;
	return splitPoints;
}



void WizardGeomSupple::joinWizardGeom()
{
	WizardGeom* wgPoint = wizardGeomWizardGeomSupple.getCurrWizardGeom(1);
	wgPoint->getWizardTailJoin();

	//贝塞尔控制点的一个切面的数值个数
	int everyNum = wgPoint->degreeSplitNum * 3;
	for (int j = 0; j < wgPoint->baseDataPercentNum; j++)
	{
		//第几排下的坐标
		int currNum = everyNum*j;
		for (int i = 0; i < wgPoint->degreeSplitNum; i++)
		{
			//每排下的第几个坐标
			int currIndex = i * 3;
			//贝塞尔控制点的第一圈
			float x1 = wgPoint->wizardTailJoin[currIndex];
			float y1 = wgPoint->wizardTailJoin[currIndex + 1];
			float z1 = wgPoint->wizardTailJoin[currIndex + 2];
			//贝塞尔控制点的第二圈
			float x2 = wgPoint->wizardTailJoin[currIndex + everyNum];
			float y2 = wgPoint->wizardTailJoin[currIndex + 1 + everyNum];
			float z2 = wgPoint->wizardTailJoin[currIndex + 2 + everyNum];
			//几何体尾部两个控制点的向量
			float tailVectX = x2 - x1;
			float tailVectY = y2 - y1;
			float tailVectZ = z2 - z1;

			//根据尾部向量要移动的距离
			float radius = float(j)*0.05f;
            if(j==0){
                radius = float(j)*0.04f;
            }
			//贝塞尔控制点的最后一排作为连接点的起点
			float tailVectRatio = sqrt(radius*radius / (tailVectX*tailVectX + tailVectY*tailVectY + tailVectZ*tailVectZ));
			//两个模型在此拟合
            float joinPx = x1 + tailVectRatio*tailVectX;
            float joinPy = y1 + tailVectRatio*tailVectY;
            float joinPz = z1 + tailVectRatio*tailVectZ;

            wgPoint->joinPoints[currIndex + currNum] = joinPx;
            wgPoint->joinPoints[currIndex + 1 + currNum] = joinPy;
            wgPoint->joinPoints[currIndex + 2 + currNum] = joinPz;

		}
	}

}



float* WizardGeomSupple::GetVerticalPointByVect(float baseX, float baseY, float baseZ,
	float middLineX, float middLineY, float middLineZ, float leng, float splitRadius)
{
	float newVectX = baseX - currentPoint[0];
	float newVectY = baseY - currentPoint[1];
	float newVectZ = baseZ - currentPoint[2];
    float newMoveVect[3];
    WizardGeomSupple::getVerticalVect(middLineX, middLineY, middLineZ, newVectX, newVectY, newVectZ, newMoveVect);
	float newRatio = sqrt(leng*leng / (newMoveVect[0] * newMoveVect[0] + newMoveVect[1] * newMoveVect[1] + newMoveVect[2] * newMoveVect[2]));
	float newX = baseX + newRatio*newMoveVect[0];
	float newY = baseY + newRatio*newMoveVect[1];
	float newZ = baseZ + newRatio*newMoveVect[2];
	float finalVectX = newX - currentPoint[0];
	float finalVectY = newY - currentPoint[1];
	float finalVectZ = newZ - currentPoint[2];
	float finalRatio = sqrt(splitRadius*splitRadius / (finalVectX*finalVectX + finalVectY*finalVectY + finalVectZ*finalVectZ));
	float finalX = currentPoint[0] + finalRatio*finalVectX;
	float finalY = currentPoint[1] + finalRatio*finalVectY;
	float finalZ = currentPoint[2] + finalRatio*finalVectZ;
	point[0] = finalX;
    point[1] = finalY;
    point[2] = finalZ;
	return point;
}

void WizardGeomSupple::normalize(float * vect)
{
    float length = sqrtf(vect[0] * vect[0] + vect[1] * vect[1] + vect[2] * vect[2]);

    if (length != 0.0f)
    {
        vect[0] = vect[0] / length;
        vect[1] = vect[1] / length;
        vect[2] = vect[2] / length;
    }
}


void WizardGeomSupple::getVerticalVect(float v1x, float v1y, float v1z, float v2x, float v2y, float v2z, float* verticalVect)
{
    verticalVect[0] = v1y * v2z - v2y * v1z;
    verticalVect[1] = -(v1x * v2z - v2x * v1z);
    verticalVect[2] = v1x * v2y - v2x * v1y;

}

