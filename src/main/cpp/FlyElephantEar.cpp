#include "FlyElephantEar.h"

FlyElephantEar::FlyElephantEar(){};
FlyElephantEar::~FlyElephantEar(){};

WizardGeom wizardGeomEar;
WizardGeomSupple wizardGeomSuppleFishEar;
ShaderUtil shaderUtilEar;
FlyElephant flyElephantFlyElephantEar;
FlyElephantEar flyElephantEarSelf;
SeaGrass seaGrassElephantEar;
/*
std::thread threads[1];
float farr[] = { 0.1, 0.2, 0.3 };
threads[0] = std::thread(CuttlefishHandMove::Normalize,farr);
for (auto &thread : threads)
thread.detach();*/

float shaderPoints1[600000];
float shaderPoints2[600000];
float shaderPoints3[600000];
float shaderPoints4[600000];

float trueShaderPoints1[600000];
float trueShaderPoints2[600000];
float trueShaderPoints3[600000];
float trueShaderPoints4[600000];
float blineIndicesFE[30000];
float triangleIndices[30000];
float texcoordGather[400000];
//设置初始的样条控制点
float FlyElephantEar::blpoints[600];
//耳朵根据横穿贝塞尔的向量支隆的角度
float angleAutoIncremCount=0.000001;
float PI=(3.1415926/180.0);
//度数增加或减小的标记
bool angleIncrem=true;
//耳朵向前支隆和向后支隆的标记
bool signTag=true;
int  blineSplitTotal=7;
//垂直与中间线的向量向横穿贝塞尔向量的偏移角度
float angle=0.0;
int turnFrame=0;
int turnFrame2=0;
//耳朵前后扇动幅度的大小
float earFrontBackFlapRange=75.0;
//耳朵下部摆动的幅度
float earBottomWiggleRange=2.2;
//耳朵翻动的仰角角度
float earTurnGoUpAngle=10.0;
float earTurnRotateAngle=4.0;

void FlyElephantEar::makeFishEarThreads(int tag){

    if(tag==1){
        turnFrame++;
    }

    WizardGeom* fishHeader=wizardGeomEar.getCurrWizardGeom(1);
    float* headerBezier=fishHeader->bezPointGather;
    float middleLineVectNor[3];
    middleLineVectNor[0]=BezierAnimationByAngle::middleLineVectNor[0];
    middleLineVectNor[1]=BezierAnimationByAngle::middleLineVectNor[1];
    middleLineVectNor[2]=BezierAnimationByAngle::middleLineVectNor[2];
    //横穿贝塞尔截面的向量
    float vertCrossBezierLineX=BezierAnimationByAngle::vertCrossBezierLineVects[2*3];
    float vertCrossBezierLineY=BezierAnimationByAngle::vertCrossBezierLineVects[2*3+1];
    float vertCrossBezierLineZ=BezierAnimationByAngle::vertCrossBezierLineVects[2*3+2];
    if(tag==1){
        vertCrossBezierLineX=BezierAnimationByAngle::vertCrossBezierLineVects[22*3];
        vertCrossBezierLineY=BezierAnimationByAngle::vertCrossBezierLineVects[22*3+1];
        vertCrossBezierLineZ=BezierAnimationByAngle::vertCrossBezierLineVects[22*3+2];
    }
    float vertCroBezLinVectNor[]={vertCrossBezierLineX,vertCrossBezierLineY,vertCrossBezierLineZ};
    WizardGeomSupple::normalize(vertCroBezLinVectNor);
    //垂直于飞象身体的向量
    float vertBaseLineVectNor[3]={BezierAnimationByAngle::vertBaseLineVects[2*3],
                                  BezierAnimationByAngle::vertBaseLineVects[2*3+1],
                                  BezierAnimationByAngle::vertBaseLineVects[2*3+2]};
    if(tag==1){
        vertBaseLineVectNor[0]=BezierAnimationByAngle::vertBaseLineVects[22*3];
        vertBaseLineVectNor[1]=BezierAnimationByAngle::vertBaseLineVects[22*3+1];
        vertBaseLineVectNor[2]=BezierAnimationByAngle::vertBaseLineVects[22*3+2];
    }
    WizardGeomSupple::normalize(vertBaseLineVectNor);
    int bezierPointIndex=2*fishHeader->bezierStep*3+4*3;
    if(tag==1){
        bezierPointIndex=(22*fishHeader->bezierStep)*3+4*3;
    }

    //函数通过修改垂直于中间线的向量来实现耳朵的前后
    flyElephantEarSelf.FlyElephantEarFan(middleLineVectNor,vertBaseLineVectNor,vertCroBezLinVectNor,tag);
    flyElephantEarSelf.MakeFlyElephantEarForm(headerBezier,vertBaseLineVectNor,middleLineVectNor,bezierPointIndex,tag);
}

//tag标记着哪一侧的耳朵
void FlyElephantEar::MakeFishEar(int tag)
{
    std::thread t(makeFishEarThreads,tag);
    t.join();
//    if(tag==1){
//        turnFrame++;
//    }
//
//    WizardGeom* fishHeader=wizardGeomEar.getCurrWizardGeom(1);
//    float* headerBezier=fishHeader->bezPointGather;
//    float middleLineVectNor[3];
//    middleLineVectNor[0]=BezierAnimationByAngle::middleLineVectNor[0];
//    middleLineVectNor[1]=BezierAnimationByAngle::middleLineVectNor[1];
//    middleLineVectNor[2]=BezierAnimationByAngle::middleLineVectNor[2];
//    //横穿贝塞尔截面的向量
//    float vertCrossBezierLineX=BezierAnimationByAngle::vertCrossBezierLineVects[2*3];
//    float vertCrossBezierLineY=BezierAnimationByAngle::vertCrossBezierLineVects[2*3+1];
//    float vertCrossBezierLineZ=BezierAnimationByAngle::vertCrossBezierLineVects[2*3+2];
//    if(tag==1){
//        vertCrossBezierLineX=BezierAnimationByAngle::vertCrossBezierLineVects[22*3];
//        vertCrossBezierLineY=BezierAnimationByAngle::vertCrossBezierLineVects[22*3+1];
//        vertCrossBezierLineZ=BezierAnimationByAngle::vertCrossBezierLineVects[22*3+2];
//    }
//    float vertCroBezLinVectNor[]={vertCrossBezierLineX,vertCrossBezierLineY,vertCrossBezierLineZ};
//    WizardGeomSupple::normalize(vertCroBezLinVectNor);
//    //垂直于飞象身体的向量
//    float vertBaseLineVectNor[3]={BezierAnimationByAngle::vertBaseLineVects[2*3],
//                                  BezierAnimationByAngle::vertBaseLineVects[2*3+1],
//                                  BezierAnimationByAngle::vertBaseLineVects[2*3+2]};
//    if(tag==1){
//        vertBaseLineVectNor[0]=BezierAnimationByAngle::vertBaseLineVects[22*3];
//        vertBaseLineVectNor[1]=BezierAnimationByAngle::vertBaseLineVects[22*3+1];
//        vertBaseLineVectNor[2]=BezierAnimationByAngle::vertBaseLineVects[22*3+2];
//    }
//    WizardGeomSupple::normalize(vertBaseLineVectNor);
//    int bezierPointIndex=2*fishHeader->bezierStep*3+4*3;
//    if(tag==1){
//        bezierPointIndex=(22*fishHeader->bezierStep)*3+4*3;
//    }
//
//    //函数通过修改垂直于中间线的向量来实现耳朵的前后
//    FlyElephantEar::FlyElephantEarFan(middleLineVectNor,vertBaseLineVectNor,vertCroBezLinVectNor,tag);
//    FlyElephantEar::MakeFlyElephantEarForm(headerBezier,vertBaseLineVectNor,middleLineVectNor,bezierPointIndex,tag);
    FlyElephantEar::MakeEarPoints(blpoints, 2, 14, blineSplitTotal,3);

}
//耳朵 眼睛 嘴巴 都用到这个函数渲染
void FlyElephantEar::MakeEarPoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotalParam,int tag)
{
	//为GPU分解成四分数据
	for (int rowIndex = 0; rowIndex < rowTotal; rowIndex++)
	{
		//当前线段的索引值
		int currCPUIndex = rowIndex*listTotal*3;

		for (int listIndex = 0; listIndex < listTotal - 3; listIndex++)
		{
			for (int pointIndex = 0; pointIndex < blineSplitTotalParam; pointIndex++)
			{
				//GPU渲染点在整条线段的索引值
				int fullLineGPUPointIndex = rowIndex*(listTotal-3)*blineSplitTotalParam;
				//GPU渲染点在当前线段某个区间段的索引值
				int currGPUPointIndex = listIndex * blineSplitTotalParam + pointIndex;
				int currentBlineIndex = (fullLineGPUPointIndex + currGPUPointIndex) * 3;

				shaderPoints1[currentBlineIndex] = blineContPoints[currCPUIndex + listIndex * 3];
				shaderPoints1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + listIndex * 3 + 1];
				shaderPoints1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + listIndex * 3 + 2];

				shaderPoints2[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 1) * 3];
				shaderPoints2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 1];
				shaderPoints2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 2];

				shaderPoints3[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 2) * 3];
				shaderPoints3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 1];
				shaderPoints3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 2];

				shaderPoints4[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 3) * 3];
				shaderPoints4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 1];
				shaderPoints4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 2];

			}
		}

	}

	//在GPU里构建面片
	int currentGPUIndex = 0;
	int evenum = 3;
	int everyFullBlineTotal = blineSplitTotalParam * (listTotal - 3);
	for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
	{
		for (int pointIndex = 0; pointIndex < everyFullBlineTotal - 1; pointIndex++)
		{
			int currPointIndex1th = (rowIndex*everyFullBlineTotal+pointIndex)*3;
			int currPointIndex2th = ((rowIndex+1)*everyFullBlineTotal+pointIndex)*3;
			int currPointIndex3th = (rowIndex*everyFullBlineTotal+(pointIndex+1))*3;
			int currPointIndex4th = ((rowIndex+1)*everyFullBlineTotal+(pointIndex+1))*3;
            int GPUXIndex=currentGPUIndex*evenum;
            int GPUYIndex=GPUXIndex+1;
            int GPUZIndex=GPUXIndex+2;
			trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex1th];
			trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex1th + 1];
			trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex1th + 2];
			trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex1th];
			trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex1th + 1];
			trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex1th + 2];
			trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex1th];
			trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex1th + 1];
			trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex1th + 2];
			trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex1th];
			trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex1th + 1];
			trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex1th + 2];
			blineIndicesFE[GPUXIndex] = float(pointIndex % blineSplitTotalParam);
			blineIndicesFE[GPUYIndex] = float(rowIndex);
			blineIndicesFE[GPUZIndex] = 0.0;

            int texcoordSIndex=currentGPUIndex*2;
            int texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=float(rowIndex)/float(rowTotal-1);
            texcoordGather[texcoordTIndex]=float(pointIndex)/float(everyFullBlineTotal-1);


			currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
			trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex2th];
			trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex2th + 1];
			trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex2th + 2];
			trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex2th];
			trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex2th + 1];
			trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex2th + 2];
			trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex2th];
			trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex2th + 1];
			trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex2th + 2];
			trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex2th];
			trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex2th + 1];
			trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex2th + 2];
			blineIndicesFE[GPUXIndex] = float(pointIndex % blineSplitTotalParam);
			blineIndicesFE[GPUYIndex] = float(rowIndex+1);
			blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=float(rowIndex+1)/float(rowTotal-1);
            texcoordGather[texcoordTIndex]=float(pointIndex)/float(everyFullBlineTotal-1);


			currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
			trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex4th];
			trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex4th + 1];
			trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex4th + 2];
			trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex4th];
			trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex4th + 1];
			trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex4th + 2];
			trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex4th];
			trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex4th + 1];
			trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex4th + 2];
			trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex4th];
			trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex4th + 1];
			trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex4th + 2];
			blineIndicesFE[GPUXIndex] = float((pointIndex + 1) % blineSplitTotalParam);
			blineIndicesFE[GPUYIndex] = float(rowIndex+1);
			blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=float(rowIndex+1)/float(rowTotal-1);
            texcoordGather[texcoordTIndex]=float(pointIndex+1)/float(everyFullBlineTotal-1);


			currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
			trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex1th];
			trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex1th + 1];
			trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex1th + 2];
			trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex1th];
			trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex1th + 1];
			trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex1th + 2];
			trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex1th];
			trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex1th + 1];
			trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex1th + 2];
			trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex1th];
			trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex1th + 1];
			trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex1th + 2];
			blineIndicesFE[GPUXIndex] = float(pointIndex % blineSplitTotalParam);
			blineIndicesFE[GPUYIndex] = float(rowIndex);
			blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=float(rowIndex)/float(rowTotal-1);
            texcoordGather[texcoordTIndex]=float(pointIndex)/float(everyFullBlineTotal-1);


			currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
			trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex4th];
			trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex4th + 1];
			trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex4th + 2];
			trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex4th];
			trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex4th + 1];
			trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex4th + 2];
			trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex4th];
			trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex4th + 1];
			trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex4th + 2];
			trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex4th];
			trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex4th + 1];
			trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex4th + 2];
			blineIndicesFE[GPUXIndex] = float((pointIndex + 1) % blineSplitTotalParam);
			blineIndicesFE[GPUYIndex] = float(rowIndex+1);
			blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=float(rowIndex+1)/float(rowTotal-1);
            texcoordGather[texcoordTIndex]=float(pointIndex+1)/float(everyFullBlineTotal-1);


			currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
			trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex3th];
			trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex3th + 1];
			trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex3th + 2];
			trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex3th];
			trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex3th + 1];
			trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex3th + 2];
			trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex3th];
			trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex3th + 1];
			trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex3th + 2];
			trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex3th];
			trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex3th + 1];
			trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex3th + 2];
			blineIndicesFE[GPUXIndex] = float((pointIndex + 1) % blineSplitTotalParam);
			blineIndicesFE[GPUYIndex] = float(rowIndex);
			blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=float(rowIndex)/float(rowTotal-1);
            texcoordGather[texcoordTIndex]=float(pointIndex+1)/float(everyFullBlineTotal-1);

            currentGPUIndex++;

        }

	}

	if(tag>3&&tag<100){
        FlyElephantEar::drawSeaGrass(blineSplitTotalParam,tag);
    }else{
        FlyElephantEar::DrawFishEarPoints(blineSplitTotalParam,tag);
    }
}

//函数通过修改垂直于中间线的向量来实现耳朵的前后扇动
void FlyElephantEar::FlyElephantEarFan(float* middleLineVectNor,float* vertBaseLineVectNor,float* vertCroBezLinVectNor,int tag){
    float earRange=0.0;
    if(FlyElephantExercise::moveLeng==0.0){
        earRange=0.5;
    }else{
        earRange=2.5;
    }
    //前后扇动的最大度数
    if(angleIncrem){
        angleAutoIncremCount+=earRange;
        if(angleAutoIncremCount>earFrontBackFlapRange){
            angleIncrem=false;
            angleAutoIncremCount=earFrontBackFlapRange;
        }
    }else{
        angleAutoIncremCount-=earRange;
        if(angleAutoIncremCount<0.0){
            angleIncrem=true;
            if(signTag){
                signTag=false;
            }else{
                signTag=true;
            }
            angleAutoIncremCount=0.0;
        }
    }

    WizardGeomSupple::normalize(vertBaseLineVectNor);
    //钝角
    if(angleAutoIncremCount>45.0){
        float moveLeng=tanf(PI*(angleAutoIncremCount-45.0));
        //一侧的耳朵
        if(tag==1){

            if(signTag){
                flyElephantEarSelf.resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, false);
                float vectX=vertBaseLineVectNor[0]+vertCroBezLinVectNor[0];
                float vectY=vertBaseLineVectNor[1]+vertCroBezLinVectNor[1];
                float vectZ=vertBaseLineVectNor[2]+vertCroBezLinVectNor[2];

                vertBaseLineVectNor[0]=vectX-moveLeng*vertBaseLineVectNor[0];
                vertBaseLineVectNor[1]=vectY-moveLeng*vertBaseLineVectNor[1];
                vertBaseLineVectNor[2]=vectZ-moveLeng*vertBaseLineVectNor[2];
            }else{
                flyElephantEarSelf.resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, false);
                float vertX=vertBaseLineVectNor[0]-vertCroBezLinVectNor[0];
                float vertY=vertBaseLineVectNor[1]-vertCroBezLinVectNor[1];
                float vertZ=vertBaseLineVectNor[2]-vertCroBezLinVectNor[2];

                vertBaseLineVectNor[0]=vertX-moveLeng*vertBaseLineVectNor[0];
                vertBaseLineVectNor[1]=vertY-moveLeng*vertBaseLineVectNor[1];
                vertBaseLineVectNor[2]=vertZ-moveLeng*vertBaseLineVectNor[2];
            }
        }else{//另一侧的耳朵

            if(signTag){
                flyElephantEarSelf.resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, true);
                float vertX=vertBaseLineVectNor[0]-vertCroBezLinVectNor[0];
                float vertY=vertBaseLineVectNor[1]-vertCroBezLinVectNor[1];
                float vertZ=vertBaseLineVectNor[2]-vertCroBezLinVectNor[2];

                vertBaseLineVectNor[0]=vertX-moveLeng*vertBaseLineVectNor[0];
                vertBaseLineVectNor[1]=vertY-moveLeng*vertBaseLineVectNor[1];
                vertBaseLineVectNor[2]=vertZ-moveLeng*vertBaseLineVectNor[2];
            }else{
                flyElephantEarSelf.resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, true);
                float vectX=vertBaseLineVectNor[0]+vertCroBezLinVectNor[0];
                float vectY=vertBaseLineVectNor[1]+vertCroBezLinVectNor[1];
                float vectZ=vertBaseLineVectNor[2]+vertCroBezLinVectNor[2];

                vertBaseLineVectNor[0]=vectX-moveLeng*vertBaseLineVectNor[0];
                vertBaseLineVectNor[1]=vectY-moveLeng*vertBaseLineVectNor[1];
                vertBaseLineVectNor[2]=vectZ-moveLeng*vertBaseLineVectNor[2];
            }
        }

        WizardGeomSupple::normalize(vertBaseLineVectNor);
        return;
    }
    //锐角
    float moveLeng=tanf(PI*angleAutoIncremCount);
    //决定那一侧的耳朵
    if(tag==1){
        //决定耳朵隆起方向的正负
		if(signTag){
            FlyElephantEar::resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, false);
			vertBaseLineVectNor[0]+=moveLeng*vertCroBezLinVectNor[0];
			vertBaseLineVectNor[1]+=moveLeng*vertCroBezLinVectNor[1];
			vertBaseLineVectNor[2]+=moveLeng*vertCroBezLinVectNor[2];
		}else{
            FlyElephantEar::resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, false);
			vertBaseLineVectNor[0]-=moveLeng*vertCroBezLinVectNor[0];
			vertBaseLineVectNor[1]-=moveLeng*vertCroBezLinVectNor[1];
			vertBaseLineVectNor[2]-=moveLeng*vertCroBezLinVectNor[2];
		}
    }else{

		if(signTag){
            flyElephantEarSelf.resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, true);
			vertBaseLineVectNor[0]-=moveLeng*vertCroBezLinVectNor[0];
			vertBaseLineVectNor[1]-=moveLeng*vertCroBezLinVectNor[1];
			vertBaseLineVectNor[2]-=moveLeng*vertCroBezLinVectNor[2];
		}else{
            flyElephantEarSelf.resetVertCroBezVect(earTurnGoUpAngle,vertCroBezLinVectNor, true);
			vertBaseLineVectNor[0]+=moveLeng*vertCroBezLinVectNor[0];
			vertBaseLineVectNor[1]+=moveLeng*vertCroBezLinVectNor[1];
			vertBaseLineVectNor[2]+=moveLeng*vertCroBezLinVectNor[2];
		}
    }

    WizardGeomSupple::normalize(vertBaseLineVectNor);

}

//此函数决定了耳朵的形状
void FlyElephantEar::MakeFlyElephantEarForm(float* headerBezier,float* vertBaseLineVectNor,float* middleLineVectNor,int bezierPointIndex,int tag){

    //最底下的点                                                               第1个点
    blpoints[0]=headerBezier[bezierPointIndex]+0.05*vertBaseLineVectNor[0];
    blpoints[1]=headerBezier[bezierPointIndex+1]+0.05*vertBaseLineVectNor[1];
    blpoints[2]=headerBezier[bezierPointIndex+2]+0.05*vertBaseLineVectNor[2];
    //贝塞尔上的点                                                              第2个点
    blpoints[3]=headerBezier[bezierPointIndex];
    blpoints[4]=headerBezier[bezierPointIndex+1];
    blpoints[5]=headerBezier[bezierPointIndex+2];
    //贝塞尔外面的点                                                            第3个点
    blpoints[6]=blpoints[3]-0.03*vertBaseLineVectNor[0];
    blpoints[7]=blpoints[4]-0.03*vertBaseLineVectNor[1];
    blpoints[8]=blpoints[5]-0.03*vertBaseLineVectNor[2];
    //下拐的点                                                                  第4个点
    blpoints[9]=blpoints[0]-0.035*middleLineVectNor[0];
    blpoints[10]=blpoints[1]-0.035*middleLineVectNor[1];
    blpoints[11]=blpoints[2]-0.035*middleLineVectNor[2];
    //下拐后延伸出贝塞尔外部的点
    blpoints[9]-=0.1*vertBaseLineVectNor[0];
    blpoints[10]-=0.1*vertBaseLineVectNor[1];
    blpoints[11]-=0.1*vertBaseLineVectNor[2];
    //下拐的点                                                                  第5个点
    blpoints[12]=blpoints[0]-0.045*middleLineVectNor[0];
    blpoints[13]=blpoints[1]-0.045*middleLineVectNor[1];
    blpoints[14]=blpoints[2]-0.045*middleLineVectNor[2];
    //下拐后延伸出贝塞尔外部的点
    blpoints[12]-=0.15*vertBaseLineVectNor[0];
    blpoints[13]-=0.15*vertBaseLineVectNor[1];
    blpoints[14]-=0.15*vertBaseLineVectNor[2];
    //下拐的点                                                                  第6个点
    blpoints[15]=blpoints[0]-0.05*middleLineVectNor[0];
    blpoints[16]=blpoints[1]-0.05*middleLineVectNor[1];
    blpoints[17]=blpoints[2]-0.05*middleLineVectNor[2];
    //下拐后延伸出贝塞尔外部的点
    blpoints[15]-=0.2*vertBaseLineVectNor[0];
    blpoints[16]-=0.2*vertBaseLineVectNor[1];
    blpoints[17]-=0.2*vertBaseLineVectNor[2];
    //————————————————————————
    //下拐的点                                                                  第7个点
    blpoints[18]=blpoints[0]-0.04*middleLineVectNor[0];
    blpoints[19]=blpoints[1]-0.04*middleLineVectNor[1];
    blpoints[20]=blpoints[2]-0.04*middleLineVectNor[2];
    //下拐后延伸出贝塞尔外部的点
    blpoints[18]-=0.25*vertBaseLineVectNor[0];
    blpoints[19]-=0.25*vertBaseLineVectNor[1];
    blpoints[20]-=0.25*vertBaseLineVectNor[2];

    //下拐的点                                                                  第8个点
    blpoints[21]=blpoints[0]-0.035*middleLineVectNor[0];
    blpoints[22]=blpoints[1]-0.035*middleLineVectNor[1];
    blpoints[23]=blpoints[2]-0.035*middleLineVectNor[2];
    //下拐后延伸出贝塞尔外部的点
    blpoints[21]-=0.3*vertBaseLineVectNor[0];
    blpoints[22]-=0.3*vertBaseLineVectNor[1];
    blpoints[23]-=0.3*vertBaseLineVectNor[2];
    //————————————————————————
    //上拐的点                                                                  第9个点
    blpoints[24]=blpoints[0]+0.01*middleLineVectNor[0];
    blpoints[25]=blpoints[1]+0.01*middleLineVectNor[1];
    blpoints[26]=blpoints[2]+0.01*middleLineVectNor[2];
    //上拐后贝塞尔外部的点
    blpoints[24]-=0.3*vertBaseLineVectNor[0];
    blpoints[25]-=0.3*vertBaseLineVectNor[1];
    blpoints[26]-=0.3*vertBaseLineVectNor[2];

    //上拐的点                                                                  第10个点
    blpoints[27]=blpoints[0]+0.03*middleLineVectNor[0];
    blpoints[28]=blpoints[1]+0.03*middleLineVectNor[1];
    blpoints[29]=blpoints[2]+0.03*middleLineVectNor[2];
    //上拐后贝塞尔外部的点
    blpoints[27]-=0.3*vertBaseLineVectNor[0];
    blpoints[28]-=0.3*vertBaseLineVectNor[1];
    blpoints[29]-=0.3*vertBaseLineVectNor[2];
    //上拐的点                                                                  第11个点
    blpoints[30]=blpoints[0]+0.06*middleLineVectNor[0];
    blpoints[31]=blpoints[1]+0.06*middleLineVectNor[1];
    blpoints[32]=blpoints[2]+0.06*middleLineVectNor[2];
    //上拐后贝塞尔外部的点
    blpoints[30]-=0.2*vertBaseLineVectNor[0];
    blpoints[31]-=0.2*vertBaseLineVectNor[1];
    blpoints[32]-=0.2*vertBaseLineVectNor[2];
    //上拐的点                                                                  第12个点
    blpoints[33]=blpoints[0]+0.04*middleLineVectNor[0];
    blpoints[34]=blpoints[1]+0.04*middleLineVectNor[1];
    blpoints[35]=blpoints[2]+0.04*middleLineVectNor[2];
    //上拐后贝塞尔外部的点
    blpoints[33]-=0.12*vertBaseLineVectNor[0];
    blpoints[34]-=0.12*vertBaseLineVectNor[1];
    blpoints[35]-=0.12*vertBaseLineVectNor[2];
    //上拐的点                                                                  第13个点
    blpoints[36]=blpoints[0]+0.03*middleLineVectNor[0];
    blpoints[37]=blpoints[1]+0.03*middleLineVectNor[1];
    blpoints[38]=blpoints[2]+0.03*middleLineVectNor[2];
    //上拐后贝塞尔外部的点
    blpoints[36]-=0.03*vertBaseLineVectNor[0];
    blpoints[37]-=0.03*vertBaseLineVectNor[1];
    blpoints[38]-=0.03*vertBaseLineVectNor[2];
    //上拐的点                                                                  第14个点
    blpoints[39]=blpoints[0]+0.03*middleLineVectNor[0];
    blpoints[40]=blpoints[1]+0.03*middleLineVectNor[1];
    blpoints[41]=blpoints[2]+0.03*middleLineVectNor[2];
    //上拐后贝塞尔外部的点
    blpoints[39]+=0.1*vertBaseLineVectNor[0];
    blpoints[40]+=0.1*vertBaseLineVectNor[1];
    blpoints[41]+=0.1*vertBaseLineVectNor[2];
    for(int i=42;i<84;i+=3){
		blpoints[i]=headerBezier[bezierPointIndex];
		blpoints[i+1]=headerBezier[bezierPointIndex+1];
		blpoints[i+2]=headerBezier[bezierPointIndex+2];
    }
    /////////////////////////////////////////////////////////////////
    //如果角度在增长(或减小)而且耳朵在这个方向上支隆
    if((angleIncrem&&signTag)||(!signTag&&!angleIncrem)){
        angle+=earBottomWiggleRange;
        if(angle>90.0){
            angle=90.0;
        }

    }else{
        angle-=earBottomWiggleRange;
        if(angle<0.0){
            angle=0.0;
        }
    }
    //正面摆动就逐渐消除冲波逆转了
    if((angleIncrem&&!signTag)&&tag==1){
        turnFrame2++;
    }

    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,9,10,11,angle-50.0,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,12,13,14,angle-30.0,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,15,16,17,angle-10.0,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,18,19,20,angle,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,21,22,23,angle,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,24,25,26,angle,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,27,28,29,angle,tag);
    flyElephantEarSelf.earMoveAloneVect(blpoints,vertBaseLineVectNor,30,31,32,angle,tag);


}

void FlyElephantEar::earMoveAloneVect(float* blpoints,float* vertBaseLineVectNor,int currXIndex,int currYIndex,int currZIndex,float usefulAngle,int tag){
    if(usefulAngle<0.0){
        usefulAngle=0.0;
    }

    ///////////////////////////////
    /////////冲波逆转的代码////////
    /////////////////////////////
    //耳朵回拨时耳朵的这些贝塞尔点可以冲波逆转
    if((currXIndex==15||currXIndex==18||currXIndex==21||currXIndex==24||currXIndex==27)&&((!angleIncrem&&signTag)||(angleIncrem&&!signTag))){

        float turnAngle=0.1;
        if(currXIndex==15){
            turnAngle=0.4;
        }else if(currXIndex==18){
            turnAngle=0.8;
        }else if(currXIndex==21){
            turnAngle=0.9;
        }else if(currXIndex==24){
            turnAngle=1.0;
        }else if(currXIndex==27){
            turnAngle=1.0;
        }
        //耳朵回拨时抵消耳朵的反冲弧度 把角度逐渐减为0
        if((angleIncrem&&!signTag)){

            if(currXIndex==15||currXIndex==18||currXIndex==21||currXIndex==24||currXIndex==27){
                turnAngle-=0.015*turnFrame2;
            }
            if(turnAngle<0.0){
                turnAngle=0.0;
            }
        }
        usefulAngle=usefulAngle-turnFrame*turnAngle;
    }
    //正向运动时就不需要冲波逆转操作 将冲波逆转指针归为零
    if((angleIncrem&&signTag)||(!signTag&&!angleIncrem)){
        turnFrame=0;
        turnFrame2=0;
    }
    //////////////////////////////////////////////////////////////////////////////////////

    float curr2LinePointVectNor[]={blpoints[currXIndex]-blpoints[33],blpoints[currYIndex]-blpoints[34],blpoints[currZIndex]-blpoints[35]};
    //向量夹角余弦值
    float coseValue=(curr2LinePointVectNor[0]*vertBaseLineVectNor[0]+curr2LinePointVectNor[1]*vertBaseLineVectNor[1]+curr2LinePointVectNor[2]*vertBaseLineVectNor[2])/
                    (sqrt(curr2LinePointVectNor[0]*curr2LinePointVectNor[0]+curr2LinePointVectNor[1]*curr2LinePointVectNor[1]+curr2LinePointVectNor[2]*curr2LinePointVectNor[2]))*
                    (sqrt(vertBaseLineVectNor[0]*vertBaseLineVectNor[0]+vertBaseLineVectNor[1]*vertBaseLineVectNor[1]+vertBaseLineVectNor[2]*vertBaseLineVectNor[2]));
    float leng=sqrt((blpoints[currXIndex]-blpoints[33])*(blpoints[currXIndex]-blpoints[33])+(blpoints[currYIndex]-blpoints[34])*(blpoints[currYIndex]-blpoints[34])+
                    (blpoints[currZIndex]-blpoints[35])*(blpoints[currZIndex]-blpoints[35]));
    //得到在支隆直线上的垂点
    float vertLineX=blpoints[33]+coseValue*leng*vertBaseLineVectNor[0];
    float vertLineY=blpoints[34]+coseValue*leng*vertBaseLineVectNor[1];
    float vertLineZ=blpoints[35]+coseValue*leng*vertBaseLineVectNor[2];
    //当前点和直线上垂点间的向量
    float vertLine2currVectNor[]={blpoints[currXIndex]-vertLineX,blpoints[currYIndex]-vertLineY,blpoints[currZIndex]-vertLineZ};
    //当前点和直线上垂点间的距离
    float vertLine2currLeng=sqrt(vertLine2currVectNor[0]*vertLine2currVectNor[0]+vertLine2currVectNor[1]*vertLine2currVectNor[1]+vertLine2currVectNor[2]*vertLine2currVectNor[2]);
    WizardGeomSupple::normalize(vertLine2currVectNor);
    //当前点和直线上垂点间的向量与耳朵支隆起来的方向向量的垂直向量
    float moveVertVectNor[3];
    wizardGeomSuppleFishEar.getVerticalVect(vertLine2currVectNor[0],vertLine2currVectNor[1],vertLine2currVectNor[2],
                                            vertBaseLineVectNor[0],vertBaseLineVectNor[1],vertBaseLineVectNor[2],moveVertVectNor);
    WizardGeomSupple::normalize(moveVertVectNor);
    //是否是反方向
    if(tag==0){
        moveVertVectNor[0]=-moveVertVectNor[0];
        moveVertVectNor[1]=-moveVertVectNor[1];
        moveVertVectNor[2]=-moveVertVectNor[2];
    }
    WizardGeomSupple::normalize(moveVertVectNor);
    //FlyElephantEar::resetMoveVertVect(moveVertVectNor,vertLine2currVectNor,earTurnRotateAngle);
    //样条控制点运动的方向
    float nor[3];
    //钝角的情况
    if(usefulAngle>45.0){
        float moveLeng=tanf(PI*(usefulAngle-45.0));
        nor[0]=-vertLine2currVectNor[0]+moveVertVectNor[0]+moveLeng*vertLine2currVectNor[0];
        nor[1]=-vertLine2currVectNor[1]+moveVertVectNor[1]+moveLeng*vertLine2currVectNor[1];
        nor[2]=-vertLine2currVectNor[2]+moveVertVectNor[2]+moveLeng*vertLine2currVectNor[2];
        WizardGeomSupple::normalize(nor);
        blpoints[currXIndex]=vertLineX-vertLine2currLeng*nor[0];
        blpoints[currYIndex]=vertLineY-vertLine2currLeng*nor[1];
        blpoints[currZIndex]=vertLineZ-vertLine2currLeng*nor[2];

        return;
    }
    //锐角的情况
    float moveLeng=tanf(PI*usefulAngle);
    //当前点和直线上垂点间的向量 + 当前点和直线上垂点间的向量与耳朵支隆起来的方向向量的垂直向量 = 样条控制点运动方向向量
    nor[0]={-vertLine2currVectNor[0]+moveLeng*moveVertVectNor[0]};
    nor[1]={-vertLine2currVectNor[1]+moveLeng*moveVertVectNor[1]};
    nor[2]={-vertLine2currVectNor[2]+moveLeng*moveVertVectNor[2]};
    WizardGeomSupple::normalize(nor);
    blpoints[currXIndex]=vertLineX-vertLine2currLeng*nor[0];
    blpoints[currYIndex]=vertLineY-vertLine2currLeng*nor[1];
    blpoints[currZIndex]=vertLineZ-vertLine2currLeng*nor[2];

}


void FlyElephantEar::DrawFishEarPoints(int blineSplitTotal,int tag)
{

	GLuint flyElephantEarProgram = shaderUtilEar.getFlyElephantEarProgram();
    glUseProgram(flyElephantEarProgram);
    glEnable(GL_DEPTH_TEST);
	GLuint projectionMatrixLocation = glGetUniformLocation(flyElephantEarProgram,"ProjectionMatrix");
	GLuint viewMatrixLocation = glGetUniformLocation(flyElephantEarProgram,"ViewMatrix");
	GLuint modelMatrixLocation = glGetUniformLocation(flyElephantEarProgram,"ModelMatrix");
    GLuint lightPositionLocation = glGetUniformLocation(flyElephantEarProgram,"lightPosition");
    flyElephantFlyElephantEar.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint eyeEarMouthTagLocation = glGetUniformLocation(flyElephantEarProgram,"eyeEarMouthTag");
    glUniform1i(eyeEarMouthTagLocation,tag);

	GLuint blineSplitLocation = glGetUniformLocation(flyElephantEarProgram, "blineSplit");
	glUniform1f(blineSplitLocation,float(blineSplitTotal));
	GLuint blinePoints1Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints1");
	GLuint blinePoints2Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints2");
	GLuint blinePoints3Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints3");
	GLuint blinePoints4Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints4");
	GLuint blinePercentLocation = glGetAttribLocation(flyElephantEarProgram, "blinePercent");


	glVertexAttribPointer(blinePoints1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints1);
	glEnableVertexAttribArray(blinePoints1Location);
	glVertexAttribPointer(blinePoints2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints2);
	glEnableVertexAttribArray(blinePoints2Location);
	glVertexAttribPointer(blinePoints3Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints3);
	glEnableVertexAttribArray(blinePoints3Location);
	glVertexAttribPointer(blinePoints4Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints4);
	glEnableVertexAttribArray(blinePoints4Location);
	glVertexAttribPointer(blinePercentLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blineIndicesFE);
	glEnableVertexAttribArray(blinePercentLocation);
	//glDrawArrays(GL_POINTS, 0, 6000);
	glDrawArrays(GL_TRIANGLES, 0, 6000);
	glUseProgram(0);

    std::memset(shaderPoints1,0,600000*sizeof(float));
    std::memset(shaderPoints2,0,600000*sizeof(float));
    std::memset(shaderPoints3,0,600000*sizeof(float));
    std::memset(shaderPoints4,0,600000*sizeof(float));
    std::memset(trueShaderPoints1,0,600000*sizeof(float));
    std::memset(trueShaderPoints2,0,600000*sizeof(float));
    std::memset(trueShaderPoints3,0,600000*sizeof(float));
    std::memset(trueShaderPoints4,0,600000*sizeof(float));
    std::memset(blineIndicesFE,0,30000*sizeof(float));
    std::memset(triangleIndices,0,30000*sizeof(float));

    //std::memset(blpoints,0,300*sizeof(float));
}

void FlyElephantEar::drawSeaGrass(int blineSplitTotal,int tag)
{

    GLuint seaGrassProgram = shaderUtilEar.getSeaGrassProgram();
    glUseProgram(seaGrassProgram);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);                                                             //开混合模式贴图
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式

    GLuint projectionMatrixLocation = glGetUniformLocation(seaGrassProgram,"ProjectionMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(seaGrassProgram,"ViewMatrix");
    GLuint modelMatrixLocation = glGetUniformLocation(seaGrassProgram,"ModelMatrix");
    flyElephantFlyElephantEar.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint eyeEarMouthTagLocation = glGetUniformLocation(seaGrassProgram,"seaGrassTag");
    glUniform1i(eyeEarMouthTagLocation,tag);

    GLuint blineSplitLocation = glGetUniformLocation(seaGrassProgram, "blineSplit");
    glUniform1f(blineSplitLocation,float(blineSplitTotal));
    GLuint blinePoints1Location = glGetAttribLocation(seaGrassProgram, "blinePoints1");
    GLuint blinePoints2Location = glGetAttribLocation(seaGrassProgram, "blinePoints2");
    GLuint blinePoints3Location = glGetAttribLocation(seaGrassProgram, "blinePoints3");
    GLuint blinePoints4Location = glGetAttribLocation(seaGrassProgram, "blinePoints4");
    GLuint blinePercentLocation = glGetAttribLocation(seaGrassProgram, "blinePercent");


    glVertexAttribPointer(blinePoints1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints1);
    glEnableVertexAttribArray(blinePoints1Location);
    glVertexAttribPointer(blinePoints2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints2);
    glEnableVertexAttribArray(blinePoints2Location);
    glVertexAttribPointer(blinePoints3Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints3);
    glEnableVertexAttribArray(blinePoints3Location);
    glVertexAttribPointer(blinePoints4Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPoints4);
    glEnableVertexAttribArray(blinePoints4Location);
    glVertexAttribPointer(blinePercentLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blineIndicesFE);
    glEnableVertexAttribArray(blinePercentLocation);

    GLuint* seaGrassTextures=getSeaGrassTextureList();
    glActiveTexture(GL_TEXTURE0);
    if(tag==4){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[0]);
    }else if(tag==5){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[2]);
    }else if(tag==6){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[3]);
    }else if(tag==8){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[1]);
    }else if(tag==9){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[13]);
    }else if(tag==10){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[9]);
    }else if(tag==11){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[10]);
    }else if(tag==12){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[7]);
    }else if(tag==13){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[11]);
    }

    glUniform1i(getSeaGrassTextureLocation(), 0);
    glVertexAttribPointer(getSeaGrassTexcoordLocation(), 2, GL_FLOAT, GL_FALSE, 2*4, texcoordGather);
    glEnableVertexAttribArray(getSeaGrassTexcoordLocation());

    //glDrawArrays(GL_POINTS, 0, 6000);
    glDrawArrays(GL_TRIANGLES, 0, 600);
    glDisable(GL_BLEND);
    glUseProgram(0);

    std::memset(shaderPoints1,0,600000*sizeof(float));
    std::memset(shaderPoints2,0,600000*sizeof(float));
    std::memset(shaderPoints3,0,600000*sizeof(float));
    std::memset(shaderPoints4,0,600000*sizeof(float));
    std::memset(trueShaderPoints1,0,600000*sizeof(float));
    std::memset(trueShaderPoints2,0,600000*sizeof(float));
    std::memset(trueShaderPoints3,0,600000*sizeof(float));
    std::memset(trueShaderPoints4,0,600000*sizeof(float));
    std::memset(blineIndicesFE,0,30000*sizeof(float));
    std::memset(triangleIndices,0,30000*sizeof(float));

    //std::memset(blpoints,0,300*sizeof(float));
}



void FlyElephantEar::resetVertCroBezVect(float angle,float* vertCroBezLinVectNor, bool isPlusOrMinu){
    if(isPlusOrMinu){
        float croMoveLeng=tanf(PI*angle);
        vertCroBezLinVectNor[0]=vertCroBezLinVectNor[0]+croMoveLeng*BezierAnimationByAngle::middleLineVectNor[0];
        vertCroBezLinVectNor[1]=vertCroBezLinVectNor[1]+croMoveLeng*BezierAnimationByAngle::middleLineVectNor[1];
        vertCroBezLinVectNor[2]=vertCroBezLinVectNor[2]+croMoveLeng*BezierAnimationByAngle::middleLineVectNor[2];
    }else{
        float croMoveLeng=tanf(PI*angle);
        vertCroBezLinVectNor[0]=vertCroBezLinVectNor[0]-croMoveLeng*BezierAnimationByAngle::middleLineVectNor[0];
        vertCroBezLinVectNor[1]=vertCroBezLinVectNor[1]-croMoveLeng*BezierAnimationByAngle::middleLineVectNor[1];
        vertCroBezLinVectNor[2]=vertCroBezLinVectNor[2]-croMoveLeng*BezierAnimationByAngle::middleLineVectNor[2];
    }

}

void FlyElephantEar::resetMoveVertVect(float* moveVertVectNor,float* vertLine2currVectNor,float angle){
    //翻卷更大的度数
    float moveAngle=tanf(PI*angle);
    moveVertVectNor[0]=moveVertVectNor[0]+moveAngle*vertLine2currVectNor[0];
    moveVertVectNor[1]=moveVertVectNor[1]+moveAngle*vertLine2currVectNor[1];
    moveVertVectNor[2]=moveVertVectNor[2]+moveAngle*vertLine2currVectNor[2];
    WizardGeomSupple::normalize(moveVertVectNor);

}


///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//耳朵 眼睛 嘴巴 都用到这个函数渲染
void FlyElephantEar::MakeEarPoints2(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotalParam,int tag)
{
    //为GPU分解成四分数据
    for (int rowIndex = 0; rowIndex < rowTotal; rowIndex++)
    {
        //当前线段的索引值
        int currCPUIndex = rowIndex*listTotal*3;

        for (int listIndex = 0; listIndex < listTotal - 3; listIndex++)
        {
            for (int pointIndex = 0; pointIndex < blineSplitTotal; pointIndex++)
            {
                //GPU渲染点在整条线段的索引值
                int fullLineGPUPointIndex = rowIndex*(listTotal-3)*blineSplitTotal;
                //GPU渲染点在当前线段某个区间段的索引值
                int currGPUPointIndex = listIndex * blineSplitTotal + pointIndex;
                int currentBlineIndex = (fullLineGPUPointIndex + currGPUPointIndex) * 3;

                shaderPoints1[currentBlineIndex] = blineContPoints[currCPUIndex + listIndex * 3];
                shaderPoints1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + listIndex * 3 + 1];
                shaderPoints1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + listIndex * 3 + 2];

                shaderPoints2[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 1) * 3];
                shaderPoints2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 1];
                shaderPoints2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 2];

                shaderPoints3[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 2) * 3];
                shaderPoints3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 1];
                shaderPoints3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 2];

                shaderPoints4[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 3) * 3];
                shaderPoints4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 1];
                shaderPoints4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 2];

            }
        }

    }

    //在GPU里构建面片
    int currentGPUIndex = 0;
    int evenum = 3;
    int everyFullBlineTotal = blineSplitTotal * (listTotal - 3);
    for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
    {
        for (int pointIndex = 0; pointIndex < everyFullBlineTotal-blineSplitTotal; pointIndex++)
        {
            int currPointIndex1th = (rowIndex*everyFullBlineTotal+pointIndex)*3;
            int currPointIndex2th = ((rowIndex+1)*everyFullBlineTotal+pointIndex)*3;
            int currPointIndex3th = (rowIndex*everyFullBlineTotal+(pointIndex+1))*3;
            int currPointIndex4th = ((rowIndex+1)*everyFullBlineTotal+(pointIndex+1))*3;
            int GPUXIndex=currentGPUIndex*evenum;
            int GPUYIndex=GPUXIndex+1;
            int GPUZIndex=GPUXIndex+2;
            trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex1th];
            trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex1th + 1];
            trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex1th + 2];
            trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex1th];
            trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex1th + 1];
            trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex1th + 2];
            trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex1th];
            trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex1th + 1];
            trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex1th + 2];
            trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex1th];
            trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex1th + 1];
            trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex1th + 2];
            blineIndicesFE[GPUXIndex] = float(pointIndex % blineSplitTotal);
            blineIndicesFE[GPUYIndex] = float(rowIndex);
            blineIndicesFE[GPUZIndex] = 0.0;

            int texcoordSIndex=currentGPUIndex*2;
            int texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=rowIndex/rowTotal;
            texcoordGather[texcoordTIndex]=pointIndex/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex2th];
            trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex2th + 1];
            trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex2th + 2];
            trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex2th];
            trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex2th + 1];
            trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex2th + 2];
            trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex2th];
            trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex2th + 1];
            trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex2th + 2];
            trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex2th];
            trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex2th + 1];
            trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex2th + 2];
            blineIndicesFE[GPUXIndex] = float(pointIndex % blineSplitTotal);
            blineIndicesFE[GPUYIndex] = float(rowIndex+1);
            blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=(rowIndex+1)/rowTotal;
            texcoordGather[texcoordTIndex]=pointIndex/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex4th];
            trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex4th + 1];
            trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex4th + 2];
            trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex4th];
            trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex4th + 1];
            trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex4th + 2];
            trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex4th];
            trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex4th + 1];
            trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex4th + 2];
            trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex4th];
            trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex4th + 1];
            trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex4th + 2];
            blineIndicesFE[GPUXIndex] = float((pointIndex + 1) % blineSplitTotal);
            blineIndicesFE[GPUYIndex] = float(rowIndex+1);
            blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=(rowIndex+1)/rowTotal;
            texcoordGather[texcoordTIndex]=(pointIndex+1)/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex1th];
            trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex1th + 1];
            trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex1th + 2];
            trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex1th];
            trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex1th + 1];
            trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex1th + 2];
            trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex1th];
            trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex1th + 1];
            trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex1th + 2];
            trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex1th];
            trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex1th + 1];
            trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex1th + 2];
            blineIndicesFE[GPUXIndex] = float(pointIndex % blineSplitTotal);
            blineIndicesFE[GPUYIndex] = float(rowIndex);
            blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=(rowIndex)/rowTotal;
            texcoordGather[texcoordTIndex]=(pointIndex)/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex4th];
            trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex4th + 1];
            trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex4th + 2];
            trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex4th];
            trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex4th + 1];
            trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex4th + 2];
            trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex4th];
            trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex4th + 1];
            trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex4th + 2];
            trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex4th];
            trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex4th + 1];
            trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex4th + 2];
            blineIndicesFE[GPUXIndex] = float((pointIndex + 1) % blineSplitTotal);
            blineIndicesFE[GPUYIndex] = float(rowIndex+1);
            blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=(rowIndex+1)/rowTotal;
            texcoordGather[texcoordTIndex]=(pointIndex+1)/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPoints1[GPUXIndex] = shaderPoints1[currPointIndex3th];
            trueShaderPoints1[GPUYIndex] = shaderPoints1[currPointIndex3th + 1];
            trueShaderPoints1[GPUZIndex] = shaderPoints1[currPointIndex3th + 2];
            trueShaderPoints2[GPUXIndex] = shaderPoints2[currPointIndex3th];
            trueShaderPoints2[GPUYIndex] = shaderPoints2[currPointIndex3th + 1];
            trueShaderPoints2[GPUZIndex] = shaderPoints2[currPointIndex3th + 2];
            trueShaderPoints3[GPUXIndex] = shaderPoints3[currPointIndex3th];
            trueShaderPoints3[GPUYIndex] = shaderPoints3[currPointIndex3th + 1];
            trueShaderPoints3[GPUZIndex] = shaderPoints3[currPointIndex3th + 2];
            trueShaderPoints4[GPUXIndex] = shaderPoints4[currPointIndex3th];
            trueShaderPoints4[GPUYIndex] = shaderPoints4[currPointIndex3th + 1];
            trueShaderPoints4[GPUZIndex] = shaderPoints4[currPointIndex3th + 2];
            blineIndicesFE[GPUXIndex] = float((pointIndex + 1) % blineSplitTotal);
            blineIndicesFE[GPUYIndex] = float(rowIndex);
            blineIndicesFE[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGather[texcoordSIndex]=(rowIndex)/rowTotal;
            texcoordGather[texcoordTIndex]=(pointIndex+1)/everyFullBlineTotal;
            currentGPUIndex++;

        }

    }

    FlyElephantEar::DrawFishEarPoints(blineSplitTotalParam,tag);
}



















