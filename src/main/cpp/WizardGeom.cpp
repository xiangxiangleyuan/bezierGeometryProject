#include "BezierBspline.h"

//坐标位置
float baseDataP2[6] = { -0.2, 0.25, 0.8, -0.2, -0.25, 0.8 };

float baseDataPercentP[12] = { 0.1, 0.11, 0.3, 0.4, 0.5, 0.6, 0.7, 0.55, 0.6, 0.7, 0.8, 0.9 };//基础数据
static float baseDataPercentNumP = 7;    //基础数据百分比个数

//精灵集合
WizardGeom *wizardGeomCollec[10];
//精灵数目
int wizardGeomNum = 2;
BezierBspline bezierBspline;
WizardGeomSupple wizardGeomSuppleWizardGeom;


WizardGeom::WizardGeom(float* baseData,float* baseDataPercent,
	int baseDataPercentNum,int degreeSplitNum,int bezierStep,int blineSplitNum, bool isFishBody)
{
	this->baseData = baseData;
	this->baseDataPercent = baseDataPercent;
	this->baseDataPercentNum = baseDataPercentNum;
	this->degreeSplitNum = degreeSplitNum;
	this->bezierStep = bezierStep;
	this->blineSplitNum = blineSplitNum;
	this->isFishBody = isFishBody;
}
WizardGeom::WizardGeom()
{
	
}


WizardGeom::~WizardGeom()
{
	/*delete[] bezierShaderPoints1;
	delete[] bezierShaderPoints2;
	delete[] bezierShaderPoints3;
	delete[] bezierShaderPoints4;
	delete[] bezPointGather;
	delete[] splitPoints;
	delete[] baseDataPercent;
	delete[] blineFactors1;
	delete[] blineFactors2;
	delete[] trueBezierShaderPoints1;
	delete[] trueBezierShaderPoints2;
	delete[] trueBezierShaderPoints3;
	delete[] trueBezierShaderPoints4;
	delete[] trueBlineFactors1;
	delete[] trueBlineFactors2;*/

}



//鱼身
WizardGeom* fishBody = new WizardGeom(baseDataP2, baseDataPercentP,
	baseDataPercentNumP, 40, 17, 5,true);
//鱼头
WizardGeom* fishHeader = new WizardGeom(baseDataP2, baseDataPercentP,
	baseDataPercentNumP, 40, 11, 5,false);


WizardGeom* WizardGeom::getCurrWizardGeom(int wgIndex)
{
	return wizardGeomCollec[wgIndex];
}

void WizardGeom::compWizardGeom()
{
    wizardGeomCollec[0] = fishBody;
    wizardGeomCollec[1] = fishHeader;
	for (int i = 0; i < wizardGeomNum;i++)
	{
		WizardGeom* wgPoint = (WizardGeom*)wizardGeomCollec[i];
		WizardGeom::restructWizardGeom(wgPoint);
		
		bezierBspline.makeUpBezierLine2(i);
		bezierBspline.makeUpBspline(i);
		bezierBspline.blineTextureMap(i);
	}
    //初始化鱼身的贝塞尔曲线（只初始化一次）
    bezierBspline.bindShaderBezierPoints(0);

}


//得到尾部的连接部
float* WizardGeom::getWizardTailJoin()
{
	WizardGeom* wgPoint =WizardGeom::getCurrWizardGeom(1);
	int totalNum = wgPoint->degreeSplitNum * 3 * wgPoint->baseDataPercentNum;
	int lastTwoNum = wgPoint->degreeSplitNum * 3 * (wgPoint->baseDataPercentNum - 2);
	for (int i = lastTwoNum; i < totalNum;i++)
	{
        wgPoint->wizardTailJoin[i - lastTwoNum] = wgPoint->splitPoints[i];
	}
	return wizardTailJoin;

}

void WizardGeom::restructWizardGeom(void* wizardGeomPoint)
{
	WizardGeom* wgPoint = (WizardGeom*)wizardGeomPoint;
	int degreeSplitNum = wgPoint->degreeSplitNum;
	int bezierStep = wgPoint->bezierStep;
	int blineSplitNum = wgPoint->blineSplitNum;

	int bezierSize = bezierStep*degreeSplitNum * 3 + 2;
	wgPoint->bezPointGather = new float[bezierSize];
	if(wgPoint->isFishBody){
        wgPoint->bezPointGatherCache = new float[bezierSize];
	}

	int loopIndex = (degreeSplitNum + 3)* blineSplitNum * 3 * (bezierStep - 1);
	int lastOneIndex = (blineSplitNum - 1) * 3 + blineSplitNum * 3 * (degreeSplitNum + 2) + loopIndex + 2;
	wgPoint->blinesPoints = new float[lastOneIndex];
	wgPoint->bezierShaderPoints1 = new float[lastOneIndex];//tansverSpanNum2 会大一圈
	wgPoint->bezierShaderPoints2 = new float[lastOneIndex];
	wgPoint->bezierShaderPoints3 = new float[lastOneIndex];
	wgPoint->bezierShaderPoints4 = new float[lastOneIndex];
	wgPoint->blineFactors1 = new float[lastOneIndex];
	wgPoint->blineFactors2 = new float[lastOneIndex];

	//每一圈的个数
	int everyCircleNum = blineSplitNum*degreeSplitNum;
	int size = everyCircleNum*bezierStep * 18;
	wgPoint->trueBezierShaderPoints1 = new float[size];
	wgPoint->trueBezierShaderPoints2 = new float[size];
	wgPoint->trueBezierShaderPoints3 = new float[size];
	wgPoint->trueBezierShaderPoints4 = new float[size];
	wgPoint->trueBlineFactors1 = new float[size];
	wgPoint->trueBlineFactors2 = new float[size];

	//连接精灵的贝塞尔控制点
	int joinPointsSize = (wgPoint->degreeSplitNum) * 3 + wgPoint->degreeSplitNum * 3 * (wgPoint->baseDataPercentNum - 1);
	wgPoint->joinPoints = new float[joinPointsSize];
	wgPoint->bsplinePercent = new float[size];
	int g_vertexSize = everyCircleNum*wgPoint->bezierStep * 12 + 20;
	wgPoint->g_vertexTexcoord = new float[g_vertexSize];

	wgPoint->geomIndices = new int[wgPoint->blineSplitNum*wgPoint->degreeSplitNum*(wgPoint->bezierStep - 1) * 6 + 9000];
	
}
