#include "BalloonFish.h"

float shaderPointsBalloonFish1[600000];
float shaderPointsBalloonFish2[600000];
float shaderPointsBalloonFish3[600000];
float shaderPointsBalloonFish4[600000];

float trueShaderPointsBalloonFish1[600000];
float trueShaderPointsBalloonFish2[600000];
float trueShaderPointsBalloonFish3[600000];
float trueShaderPointsBalloonFish4[600000];
float blineIndicesFEBalloonFish[30000];
float texcoordGatherBalloonFish[400000];

float shaderPointsBalloonFishSTAB1[600000];
float shaderPointsBalloonFishSTAB2[600000];
float shaderPointsBalloonFishSTAB3[600000];
float shaderPointsBalloonFishSTAB4[600000];

float trueShaderPointsBalloonFishSTAB1[600000];
float trueShaderPointsBalloonFishSTAB2[600000];
float trueShaderPointsBalloonFishSTAB3[600000];
float trueShaderPointsBalloonFishSTAB4[600000];
float blineIndicesFEBalloonFishSTAB[90000];
float texcoordGatherBalloonFishSTAB[90000];
float balloonFishSTABMiddPoints[90000];


GameWorld gameWorldBalloonFish;
FlyElephantEar flyElephantEarBalloonFish;
ShaderUtil shaderUtilBalloonFish;
FlyElephant flyElephantBalloonFish;
WizardGeom wizardGeomBalloonFish;
BalloonFlyFishCollisionDetection collisionDetectionBalloonFish;
BalloonFish::BalloonFish() {};
BalloonFish::~BalloonFish() {};

float BalloonFish::bezierGatherBalloonFish[900];
float bezierGatherBalloonFish_After[900];
float bezierGatherBalloonFishSTAB[900];

float BalloonFish::topPoint[3];

//刺豚bezier点的集合
float bezierControlPoints3[900];
float BalloonFish::bezierVertBaseLinePointsBalloonFish[900];
int bezierDegreeSplitNum=4;
int bezierSectionNum=6;
int blineSplitNum=5;
float BalloonFish::middAxisPoints[18];
float factResArr[10000];//介乘结果的集合
float BalloonFish::stabSubstractFactor=0.18;
//在缩小的时候设置为false不绘制刺 在膨胀的时候设置为true绘制刺
bool BalloonFish::isDrawStab=false;
bool BalloonFish::isPrick=false;
void BalloonFish::initBalloonFish() {
    topPoint[0]=0.0;
    topPoint[1]=0.1;
    topPoint[2]=0.0;
    middAxisPoints[0]=0.3;
    middAxisPoints[1]=0.0;
    middAxisPoints[2]=0.0;
    middAxisPoints[3]=0.35;
    middAxisPoints[4]=0.0;
    middAxisPoints[5]=0.0;
    middAxisPoints[6]=0.4;
    middAxisPoints[7]=0.0;
    middAxisPoints[8]=0.0;
    middAxisPoints[9]=0.45;
    middAxisPoints[10]=0.0;
    middAxisPoints[11]=0.0;
    middAxisPoints[12]=0.5;
    middAxisPoints[13]=0.0;
    middAxisPoints[14]=0.0;
    middAxisPoints[15]=0.55;
    middAxisPoints[16]=0.0;
    middAxisPoints[17]=0.0;

    for (int i = 0; i < bezierSectionNum; i++){	//求0到n的阶乘
        factResArr[i] = factrial(i);
    }

}

void BalloonFish::drawBalloonFish(){
    //初始化刺豚beizer轮廓的bezier控制点
    changeTopPoint();
    initBalloonFishBezierControlPoints();
    //加上刺豚的尾巴
    addBalloonFishTail();
    /////////////初始化刺豚的bezier轮廓曲线//////////////////////////////
    makeUpBezierLine(bezierGatherBalloonFish,bezierControlPoints3,bezierSectionNum,bezierDegreeSplitNum,bezierStep);


    float baseVect[3];
    baseVect[0]=middAxisPoints[0]-middAxisPoints[3];
    baseVect[1]=middAxisPoints[1]-middAxisPoints[4];
    baseVect[2]=middAxisPoints[2]-middAxisPoints[5];
    WizardGeomSupple::normalize(baseVect);
    for (int i = 0; i < bezierStep; i++)
    {
        float point[] = { bezierGatherBalloonFish[i * 3], bezierGatherBalloonFish[i * 3 + 1], bezierGatherBalloonFish[i * 3 + 2] };
        point2lineVertPoint(point, baseVect, i);
    }
    int pointSTABIndex=0;
    for(int bezierSectionIndex=0;bezierSectionIndex<bezierStep;bezierSectionIndex++){

        for(int degreeIndex=0;degreeIndex<bezierDegreeSplitNum;degreeIndex++){

            int currPointIndex=degreeIndex*bezierStep*3+bezierSectionIndex*3;

            float x = bezierGatherBalloonFish[currPointIndex];
            float y = bezierGatherBalloonFish[currPointIndex+1];
            float z = bezierGatherBalloonFish[currPointIndex+2];

            bezierGatherBalloonFishSTAB[pointSTABIndex*3]=x;
            bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=y;
            bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=z;
            pointSTABIndex++;

        }
        //////////////BLINE闭合曲线需要添加的代码//////////////////////////
        int currPointIndex0=bezierSectionIndex*3;
        float x0 = bezierGatherBalloonFish[currPointIndex0];
        float y0 = bezierGatherBalloonFish[currPointIndex0+1];
        float z0 = bezierGatherBalloonFish[currPointIndex0+2];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=x0;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=y0;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=z0;
        pointSTABIndex++;

        int currPointIndex1=bezierStep*3+bezierSectionIndex*3;
        float x1 = bezierGatherBalloonFish[currPointIndex1];
        float y1 = bezierGatherBalloonFish[currPointIndex1+1];
        float z1 = bezierGatherBalloonFish[currPointIndex1+2];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=x1;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=y1;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=z1;
        pointSTABIndex++;

        int currPointIndex2=2*bezierStep*3+bezierSectionIndex*3;
        float x2 = bezierGatherBalloonFish[currPointIndex2];
        float y2 = bezierGatherBalloonFish[currPointIndex2+1];
        float z2 = bezierGatherBalloonFish[currPointIndex2+2];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=x2;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=y2;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=z2;
        pointSTABIndex++;

        int currPointIndex3=3*bezierStep*3+bezierSectionIndex*3;
        float x3 = bezierGatherBalloonFish[currPointIndex3];
        float y3 = bezierGatherBalloonFish[currPointIndex3+1];
        float z3 = bezierGatherBalloonFish[currPointIndex3+2];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=x3;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=y3;
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=z3;
        pointSTABIndex++;

        ///////////////////////////////////////////////////////////////
        int currIndex=(bezierSectionIndex)*3;
        for(int degreeIndex=0;degreeIndex<bezierDegreeSplitNum;degreeIndex++){
            bezierGatherBalloonFishSTAB[pointSTABIndex*3]=bezierVertBaseLinePointsBalloonFish[currIndex];
            bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=bezierVertBaseLinePointsBalloonFish[currIndex+1];
            bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=bezierVertBaseLinePointsBalloonFish[currIndex+2];
            pointSTABIndex++;

        }
        //////////////BLINE闭合曲线需要添加的代码//////////////////////////
        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=bezierVertBaseLinePointsBalloonFish[currIndex];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=bezierVertBaseLinePointsBalloonFish[currIndex+1];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=bezierVertBaseLinePointsBalloonFish[currIndex+2];
        pointSTABIndex++;


        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=bezierVertBaseLinePointsBalloonFish[currIndex];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=bezierVertBaseLinePointsBalloonFish[currIndex+1];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=bezierVertBaseLinePointsBalloonFish[currIndex+2];
        pointSTABIndex++;

        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=bezierVertBaseLinePointsBalloonFish[currIndex];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=bezierVertBaseLinePointsBalloonFish[currIndex+1];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=bezierVertBaseLinePointsBalloonFish[currIndex+2];
        pointSTABIndex++;

        bezierGatherBalloonFishSTAB[pointSTABIndex*3]=bezierVertBaseLinePointsBalloonFish[currIndex];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+1]=bezierVertBaseLinePointsBalloonFish[currIndex+1];
        bezierGatherBalloonFishSTAB[pointSTABIndex*3+2]=bezierVertBaseLinePointsBalloonFish[currIndex+2];
        pointSTABIndex++;
    }
    if(isDrawStab){
        makeBalloonFishSTABPoints(bezierGatherBalloonFishSTAB,bezierStep*2,8,10,10);
    }
    //////////////////////////////////////////////////////////////////////////////////////////

    int pointIndex=0;
    for(int bezierSectionIndex=0;bezierSectionIndex<bezierStep;bezierSectionIndex++){

        for(int degreeIndex=0;degreeIndex<bezierDegreeSplitNum;degreeIndex++){

            int currPointIndex=degreeIndex*bezierStep*3+bezierSectionIndex*3;

            float x = bezierGatherBalloonFish[currPointIndex];
            float y = bezierGatherBalloonFish[currPointIndex+1];
            float z = bezierGatherBalloonFish[currPointIndex+2];

            bezierGatherBalloonFish_After[pointIndex*3]=x;
            bezierGatherBalloonFish_After[pointIndex*3+1]=y;
            bezierGatherBalloonFish_After[pointIndex*3+2]=z;
            pointIndex++;

        }
        //////////////BLINE闭合曲线需要添加的代码//////////////////////////
        int currPointIndex0=bezierSectionIndex*3;
        float x0 = bezierGatherBalloonFish[currPointIndex0];
        float y0 = bezierGatherBalloonFish[currPointIndex0+1];
        float z0 = bezierGatherBalloonFish[currPointIndex0+2];
        bezierGatherBalloonFish_After[pointIndex*3]=x0;
        bezierGatherBalloonFish_After[pointIndex*3+1]=y0;
        bezierGatherBalloonFish_After[pointIndex*3+2]=z0;
        pointIndex++;

        int currPointIndex1=bezierStep*3+bezierSectionIndex*3;
        float x1 = bezierGatherBalloonFish[currPointIndex1];
        float y1 = bezierGatherBalloonFish[currPointIndex1+1];
        float z1 = bezierGatherBalloonFish[currPointIndex1+2];
        bezierGatherBalloonFish_After[pointIndex*3]=x1;
        bezierGatherBalloonFish_After[pointIndex*3+1]=y1;
        bezierGatherBalloonFish_After[pointIndex*3+2]=z1;
        pointIndex++;

        int currPointIndex2=2*bezierStep*3+bezierSectionIndex*3;
        float x2 = bezierGatherBalloonFish[currPointIndex2];
        float y2 = bezierGatherBalloonFish[currPointIndex2+1];
        float z2 = bezierGatherBalloonFish[currPointIndex2+2];
        bezierGatherBalloonFish_After[pointIndex*3]=x2;
        bezierGatherBalloonFish_After[pointIndex*3+1]=y2;
        bezierGatherBalloonFish_After[pointIndex*3+2]=z2;
        pointIndex++;

        int currPointIndex3=3*bezierStep*3+bezierSectionIndex*3;
        float x3 = bezierGatherBalloonFish[currPointIndex3];
        float y3 = bezierGatherBalloonFish[currPointIndex3+1];
        float z3 = bezierGatherBalloonFish[currPointIndex3+2];
        bezierGatherBalloonFish_After[pointIndex*3]=x3;
        bezierGatherBalloonFish_After[pointIndex*3+1]=y3;
        bezierGatherBalloonFish_After[pointIndex*3+2]=z3;
        pointIndex++;

        int currPointIndex4=4*bezierStep*3+bezierSectionIndex*3;
        float x4 = bezierGatherBalloonFish[currPointIndex4];
        float y4 = bezierGatherBalloonFish[currPointIndex4+1];
        float z4 = bezierGatherBalloonFish[currPointIndex4+2];
        bezierGatherBalloonFish_After[pointIndex*3]=x4;
        bezierGatherBalloonFish_After[pointIndex*3+1]=y4;
        bezierGatherBalloonFish_After[pointIndex*3+2]=z4;
        pointIndex++;
    }
    makeBalloonFishBsplinePoints(bezierGatherBalloonFish_After,bezierStep,bezierDegreeSplitNum+5,blineSplitNum,100);
    /////////////////////////////////////////////////////////////

}


void BalloonFish::makeBalloonFishBsplinePoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitNum,int tag)
{
    //为GPU分解成四分数据
    for (int rowIndex = 0; rowIndex < rowTotal; rowIndex++)
    {
        //当前线段的索引值
        int currCPUIndex = rowIndex*listTotal*3;

        for (int listIndex = 0; listIndex < listTotal - 3; listIndex++)
        {
            for (int pointIndex = 0; pointIndex < blineSplitNum; pointIndex++)
            {
                //GPU渲染点在整条线段的索引值
                int fullLineGPUPointIndex = rowIndex*(listTotal-3)*blineSplitNum;
                //GPU渲染点在当前线段某个区间段的索引值
                int currGPUPointIndex = listIndex * blineSplitNum + pointIndex;
                int currentBlineIndex = (fullLineGPUPointIndex + currGPUPointIndex) * 3;

                shaderPointsBalloonFish1[currentBlineIndex] = blineContPoints[currCPUIndex + listIndex * 3];
                shaderPointsBalloonFish1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + listIndex * 3 + 1];
                shaderPointsBalloonFish1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + listIndex * 3 + 2];

                shaderPointsBalloonFish2[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 1) * 3];
                shaderPointsBalloonFish2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 1];
                shaderPointsBalloonFish2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 2];

                shaderPointsBalloonFish3[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 2) * 3];
                shaderPointsBalloonFish3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 1];
                shaderPointsBalloonFish3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 2];

                shaderPointsBalloonFish4[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 3) * 3];
                shaderPointsBalloonFish4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 1];
                shaderPointsBalloonFish4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 2];

            }
        }

    }

    //在GPU里构建面片
    int currentGPUIndex = 0;
    int evenum = 3;
    int everyFullBlineTotal = blineSplitNum * (listTotal - 3);
    for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
    {
        for (int pointIndex = 0; pointIndex < everyFullBlineTotal-blineSplitNum; pointIndex++)
        {
            int currPointIndex1th = (rowIndex*everyFullBlineTotal+pointIndex)*3;
            int currPointIndex2th = ((rowIndex+1)*everyFullBlineTotal+pointIndex)*3;
            int currPointIndex3th = (rowIndex*everyFullBlineTotal+(pointIndex+1))*3;
            int currPointIndex4th = ((rowIndex+1)*everyFullBlineTotal+(pointIndex+1))*3;
            int GPUXIndex=currentGPUIndex*evenum;
            int GPUYIndex=GPUXIndex+1;
            int GPUZIndex=GPUXIndex+2;
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
            blineIndicesFEBalloonFish[GPUZIndex] = 0.0;

            int texcoordSIndex=currentGPUIndex*2;
            int texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFish[texcoordSIndex]=float(rowIndex)/float(rowTotal);
            texcoordGatherBalloonFish[texcoordTIndex]=float(pointIndex)/float(everyFullBlineTotal-blineSplitNum-blineSplitNum);


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
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
            blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex+1);
            blineIndicesFEBalloonFish[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFish[texcoordSIndex]=float(rowIndex+1)/float(rowTotal);
            texcoordGatherBalloonFish[texcoordTIndex]=float(pointIndex)/float(everyFullBlineTotal-blineSplitNum-blineSplitNum);


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
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
            blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex+1);
            blineIndicesFEBalloonFish[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFish[texcoordSIndex]=float(rowIndex+1)/float(rowTotal);
            texcoordGatherBalloonFish[texcoordTIndex]=float(pointIndex+1)/float(everyFullBlineTotal-blineSplitNum-blineSplitNum);


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
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
            blineIndicesFEBalloonFish[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFish[texcoordSIndex]=float(rowIndex)/float(rowTotal);
            texcoordGatherBalloonFish[texcoordTIndex]=float(pointIndex)/float(everyFullBlineTotal-blineSplitNum-blineSplitNum);


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
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
            blineIndicesFEBalloonFish[GPUYIndex] = float(rowIndex+1);
            blineIndicesFEBalloonFish[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFish[texcoordSIndex]=float(rowIndex+1)/float(rowTotal);
            texcoordGatherBalloonFish[texcoordTIndex]=float(pointIndex+1)/float(everyFullBlineTotal-blineSplitNum-blineSplitNum);


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
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
            blineIndicesFEBalloonFish[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFish[texcoordSIndex]=float(rowIndex)/float(rowTotal);
            texcoordGatherBalloonFish[texcoordTIndex]=float(pointIndex+1)/float(everyFullBlineTotal-blineSplitNum-blineSplitNum);

            currentGPUIndex++;


        }

    }

    BalloonFish::drawBalloonFishPoints(blineSplitNum,tag);
}

bool isBecomeSmallingEnd0=false;
bool isBecomeSmallingEnd1=false;
bool isBecomeSmallingEnd2=false;
bool isBecomeSmallingEnd3=false;
void BalloonFish::balloonFishSmalling(){
    if(isBecomeSmalling){
        longerRadiu0-=0.001;
        if(longerRadiu0<0.08){
            isBecomeSmallingEnd0=true;
            longerRadiu0=0.08;
        }
        longerRadiu1-=0.001;
        if(longerRadiu1<0.08){
            isBecomeSmallingEnd1=true;
            longerRadiu1=0.08;
        }
        shortRadiu1-=0.0008;
        if(shortRadiu1<0.05){
            isBecomeSmallingEnd2=true;
            shortRadiu1=0.05;
        }
        stabSubstractFactor+=0.0015;
        if(stabSubstractFactor>0.18){
            isBecomeSmallingEnd3=true;
            stabSubstractFactor=0.18;
            isDrawStab= false;
        }
        //所有的初始值恢复完毕
        if(isBecomeSmallingEnd0&&isBecomeSmallingEnd1&&isBecomeSmallingEnd2&&isBecomeSmallingEnd3){
            isBecomeSmallingEnd0=false;
            isBecomeSmallingEnd1=false;
            isBecomeSmallingEnd2=false;
            isBecomeSmallingEnd3=false;
            isBecomeSmalling=false;
        }
    }
}


void BalloonFish::balloonFishSmallUncondition(){

    longerRadiu0-=0.001;
    if(longerRadiu0<0.08){
        longerRadiu0=0.08;
    }
    longerRadiu1-=0.001;
    if(longerRadiu1<0.08){
        longerRadiu1=0.08;
    }
    shortRadiu1-=0.0008;
    if(shortRadiu1<0.05){
        shortRadiu1=0.05;
    }
    stabSubstractFactor+=0.0015;
    if(stabSubstractFactor>0.18){
        stabSubstractFactor=0.18;
        isDrawStab= false;
    }
}

void BalloonFish::changeTopPoint(){

    //如果检测到两者碰撞刺豚就按指定路线运动
    if(BalloonFlyFishCollisionDetection::isCollisionDetectionAfter){
        moveByBezierPathColliDeteAfter();
        return;
    }
    //刺豚在缩小
    balloonFishSmalling();

    rotateBodyByMiddAxis();
    moveByBezierPath();
    rotateBodyByVerticalMiddAxis();
}

bool rotatePointer= false;
float BalloonFish::leftRightVect[3];
void BalloonFish::rotateBodyByMiddAxis(){
    if(rotatePointer)
    {
        return;
    }
    float midd2TopVect[]={ topPoint[0]-middAxisPoints[0],topPoint[1]-middAxisPoints[1],topPoint[2]-middAxisPoints[2] };
    float middAxisVect[]={ middAxisPoints[3]-middAxisPoints[0],middAxisPoints[4]-middAxisPoints[1],middAxisPoints[5]-middAxisPoints[2] };

    WizardGeomSupple::getVerticalVect(midd2TopVect[0],midd2TopVect[1],midd2TopVect[2],
                                      middAxisVect[0],middAxisVect[1],middAxisVect[2],leftRightVect);
    WizardGeomSupple::normalize(leftRightVect);
    float moveLeng=tanf(60.0*3.1415926/180.0f);
    //float moveLeng=0.005236;
    float movedX=topPoint[0]+moveLeng*leftRightVect[0];
    float movedY=topPoint[1]+moveLeng*leftRightVect[1];
    float movedZ=topPoint[2]+moveLeng*leftRightVect[2];
    float moved2middAxisVect[]={movedX-middAxisPoints[0],movedY-middAxisPoints[1],movedZ-middAxisPoints[2]};
    WizardGeomSupple::normalize(moved2middAxisVect);
    //单位长度是初始的顶点所决定的
    topPoint[0]=middAxisPoints[0]+0.1*moved2middAxisVect[0];
    topPoint[1]=middAxisPoints[1]+0.1*moved2middAxisVect[1];
    topPoint[2]=middAxisPoints[2]+0.1*moved2middAxisVect[2];
    rotatePointer=true;
}


//当前bezier路线上的点的索引值
int BalloonFish::bezierIndex=0;
int frameCount=0;
bool isInitP2PDistance=false;
float distance=0.0;
float BalloonFish::bezierPathControlPoints2[90];
//////bezier路线/////////
float BalloonFish::bezierMovePath[3300];
bool isGenerateBezierPath=false;
float bezierPathBasePoint[]={-0.2,0.0,1.0};
bool isNeedInitBezierPath=true;
int bezierPathStep=150;
bool BalloonFish::isDrawStabCollDete=false;
void BalloonFish::moveByBezierPath(){

    if(!isGenerateBezierPath){
        bezierPathControlPoints2[0]=bezierPathBasePoint[0]-1.5;
        bezierPathControlPoints2[1]=bezierPathBasePoint[1];
        bezierPathControlPoints2[2]=bezierPathBasePoint[2];
        bezierPathControlPoints2[3]=bezierPathBasePoint[0]-0.8;
        bezierPathControlPoints2[4]=bezierPathBasePoint[1];
        bezierPathControlPoints2[5]=bezierPathBasePoint[2]-0.1;
        bezierPathControlPoints2[6]=bezierPathBasePoint[0]-0.6;
        bezierPathControlPoints2[7]=bezierPathBasePoint[1];
        bezierPathControlPoints2[8]=bezierPathBasePoint[2]-0.3;
        bezierPathControlPoints2[9]=bezierPathBasePoint[0]-0.4;
        bezierPathControlPoints2[10]=bezierPathBasePoint[1];
        bezierPathControlPoints2[11]=bezierPathBasePoint[2]-0.5;
        bezierPathControlPoints2[12]=bezierPathBasePoint[0]-0.2;
        bezierPathControlPoints2[13]=bezierPathBasePoint[1];
        bezierPathControlPoints2[14]=bezierPathBasePoint[2]-0.7;

        bezierPathControlPoints2[15]=bezierPathBasePoint[0];
        bezierPathControlPoints2[16]=bezierPathBasePoint[1];
        bezierPathControlPoints2[17]=bezierPathBasePoint[2]-0.6;

        bezierPathControlPoints2[18]=bezierPathBasePoint[0]+0.2;
        bezierPathControlPoints2[19]=bezierPathBasePoint[1];
        bezierPathControlPoints2[20]=bezierPathBasePoint[2]-0.7;
        bezierPathControlPoints2[21]=bezierPathBasePoint[0]+0.4;
        bezierPathControlPoints2[22]=bezierPathBasePoint[1];
        bezierPathControlPoints2[23]=bezierPathBasePoint[2]-0.5;
        bezierPathControlPoints2[24]=bezierPathBasePoint[0]+0.6;
        bezierPathControlPoints2[25]=bezierPathBasePoint[1];
        bezierPathControlPoints2[26]=bezierPathBasePoint[2]-0.3;
        bezierPathControlPoints2[27]=bezierPathBasePoint[0]+0.8;
        bezierPathControlPoints2[28]=bezierPathBasePoint[1];
        bezierPathControlPoints2[29]=bezierPathBasePoint[2]-0.1;
        bezierPathControlPoints2[30]=bezierPathBasePoint[0]+1.5;
        bezierPathControlPoints2[31]=bezierPathBasePoint[1];
        bezierPathControlPoints2[32]=bezierPathBasePoint[2];

        gameWorldBalloonFish.makeUpBezierLine(bezierMovePath,bezierPathControlPoints2,11,1,bezierPathStep);
        isGenerateBezierPath=true;
    }

    {
        if(bezierIndex>bezierPathStep-1){
            if(!isNeedInitBezierPath){
                //重新生成bezier路线
                bezierPathControlPoints2[0]=bezierPathBasePoint[0]-1.5;
                bezierPathControlPoints2[1]=bezierPathBasePoint[1];
                bezierPathControlPoints2[2]=bezierPathBasePoint[2];
                bezierPathControlPoints2[3]=bezierPathBasePoint[0]-0.8;
                bezierPathControlPoints2[4]=bezierPathBasePoint[1];
                bezierPathControlPoints2[5]=bezierPathBasePoint[2]-0.1;
                bezierPathControlPoints2[6]=bezierPathBasePoint[0]-0.6;
                bezierPathControlPoints2[7]=bezierPathBasePoint[1];
                bezierPathControlPoints2[8]=bezierPathBasePoint[2]-0.3;
                bezierPathControlPoints2[9]=bezierPathBasePoint[0]-0.4;
                bezierPathControlPoints2[10]=bezierPathBasePoint[1];
                bezierPathControlPoints2[11]=bezierPathBasePoint[2]-0.5;
                bezierPathControlPoints2[12]=bezierPathBasePoint[0]-0.2;
                bezierPathControlPoints2[13]=bezierPathBasePoint[1];
                bezierPathControlPoints2[14]=bezierPathBasePoint[2]-0.7;

                bezierPathControlPoints2[15]=bezierPathBasePoint[0];
                bezierPathControlPoints2[16]=bezierPathBasePoint[1];
                bezierPathControlPoints2[17]=bezierPathBasePoint[2]-0.6;

                bezierPathControlPoints2[18]=bezierPathBasePoint[0]+0.2;
                bezierPathControlPoints2[19]=bezierPathBasePoint[1];
                bezierPathControlPoints2[20]=bezierPathBasePoint[2]-0.7;
                bezierPathControlPoints2[21]=bezierPathBasePoint[0]+0.4;
                bezierPathControlPoints2[22]=bezierPathBasePoint[1];
                bezierPathControlPoints2[23]=bezierPathBasePoint[2]-0.5;
                bezierPathControlPoints2[24]=bezierPathBasePoint[0]+0.6;
                bezierPathControlPoints2[25]=bezierPathBasePoint[1];
                bezierPathControlPoints2[26]=bezierPathBasePoint[2]-0.3;
                bezierPathControlPoints2[27]=bezierPathBasePoint[0]+0.8;
                bezierPathControlPoints2[28]=bezierPathBasePoint[1];
                bezierPathControlPoints2[29]=bezierPathBasePoint[2]-0.1;
                bezierPathControlPoints2[30]=bezierPathBasePoint[0]+1.5;
                bezierPathControlPoints2[31]=bezierPathBasePoint[1];
                bezierPathControlPoints2[32]=bezierPathBasePoint[2];

                isNeedInitBezierPath= true;
            }else{
                //重新生成bezier路线
                bezierPathControlPoints2[0]=bezierPathBasePoint[0]+1.5;
                bezierPathControlPoints2[1]=bezierPathBasePoint[1];
                bezierPathControlPoints2[2]=bezierPathBasePoint[2];
                bezierPathControlPoints2[3]=bezierPathBasePoint[0]+0.8;
                bezierPathControlPoints2[4]=bezierPathBasePoint[1];
                bezierPathControlPoints2[5]=bezierPathBasePoint[2]-0.1;
                bezierPathControlPoints2[6]=bezierPathBasePoint[0]+0.6;
                bezierPathControlPoints2[7]=bezierPathBasePoint[1];
                bezierPathControlPoints2[8]=bezierPathBasePoint[2]-0.3;
                bezierPathControlPoints2[9]=bezierPathBasePoint[0]+0.4;
                bezierPathControlPoints2[10]=bezierPathBasePoint[1];
                bezierPathControlPoints2[11]=bezierPathBasePoint[2]-0.5;
                bezierPathControlPoints2[12]=bezierPathBasePoint[0]+0.2;
                bezierPathControlPoints2[13]=bezierPathBasePoint[1];
                bezierPathControlPoints2[14]=bezierPathBasePoint[2]-0.7;

                bezierPathControlPoints2[15]=bezierPathBasePoint[0];
                bezierPathControlPoints2[16]=bezierPathBasePoint[1];
                bezierPathControlPoints2[17]=bezierPathBasePoint[2]-0.6;

                bezierPathControlPoints2[18]=bezierPathBasePoint[0]-0.2;
                bezierPathControlPoints2[19]=bezierPathBasePoint[1];
                bezierPathControlPoints2[20]=bezierPathBasePoint[2]-0.7;
                bezierPathControlPoints2[21]=bezierPathBasePoint[0]-0.4;
                bezierPathControlPoints2[22]=bezierPathBasePoint[1];
                bezierPathControlPoints2[23]=bezierPathBasePoint[2]-0.5;
                bezierPathControlPoints2[24]=bezierPathBasePoint[0]-0.6;
                bezierPathControlPoints2[25]=bezierPathBasePoint[1];
                bezierPathControlPoints2[26]=bezierPathBasePoint[2]-0.3;
                bezierPathControlPoints2[27]=bezierPathBasePoint[0]-0.8;
                bezierPathControlPoints2[28]=bezierPathBasePoint[1];
                bezierPathControlPoints2[29]=bezierPathBasePoint[2]-0.1;
                bezierPathControlPoints2[30]=bezierPathBasePoint[0]-1.5;
                bezierPathControlPoints2[31]=bezierPathBasePoint[1];
                bezierPathControlPoints2[32]=bezierPathBasePoint[2];

                isNeedInitBezierPath= false;
            }

            gameWorldBalloonFish.makeUpBezierLine(bezierMovePath,bezierPathControlPoints2,11,1,bezierPathStep);
            bezierIndex=0;
            return;
        }

//        drawPointLine(bezierMovePath,110,true,1.0,0.0,0.0,10.0);

        int currIndex=bezierIndex*3;
        float lengX=bezierMovePath[currIndex]-middAxisPoints[0];
        float lengY=bezierMovePath[currIndex+1]-middAxisPoints[1];
        float lengZ=bezierMovePath[currIndex+2]-middAxisPoints[2];

        if(!isInitP2PDistance){
            distance=sqrt(lengX*lengX+lengY*lengY+lengZ*lengZ)/5.0;
            isInitP2PDistance=true;
        }

        if(frameCount++>4)
        {
            //需要重新初始化距离
            isInitP2PDistance=false;
            frameCount=0;
            //向下一个路线上bezier点的进发
            bezierIndex++;
            return;
        }
        //bezier路线上的点和刺豚点的向量
        float p2pVect[]={bezierMovePath[currIndex]-middAxisPoints[0],bezierMovePath[currIndex+1]-middAxisPoints[1],bezierMovePath[currIndex+2]-middAxisPoints[2]};
        WizardGeomSupple::normalize(p2pVect);
        //按照向量位移
        for(int i=0;i<6;i++){
            int currIndex=i*3;
            middAxisPoints[currIndex]+=distance*p2pVect[0];
            middAxisPoints[currIndex+1]+=distance*p2pVect[1];
            middAxisPoints[currIndex+2]+=distance*p2pVect[2];
        }
        topPoint[0]+=distance*p2pVect[0];
        topPoint[1]+=distance*p2pVect[1];
        topPoint[2]+=distance*p2pVect[2];

    }

}

void BalloonFish::rotateBodyByVerticalMiddAxis(){
    float middVect[3];
    int currIndex=bezierIndex*3;
    float moveVect[]={-bezierMovePath[currIndex]+middAxisPoints[0],-bezierMovePath[currIndex+1]+middAxisPoints[1],-bezierMovePath[currIndex+2]+middAxisPoints[2]};
    float middAxisVect[]={ middAxisPoints[15]-middAxisPoints[0],middAxisPoints[16]-middAxisPoints[1],middAxisPoints[17]-middAxisPoints[2] };
    //前进方向的向量
    middVect[0]=moveVect[0]+middAxisVect[0];
    middVect[1]=moveVect[1]+middAxisVect[1];
    middVect[2]=moveVect[2]+middAxisVect[2];
//    middVect[0]+=middAxisVect[0];
//    middVect[1]+=middAxisVect[1];
//    middVect[2]+=middAxisVect[2];

    WizardGeomSupple::normalize(middVect);


    middAxisPoints[3]=middAxisPoints[0]+0.02*middVect[0];
    middAxisPoints[4]=middAxisPoints[1]+0.02*middVect[1];
    middAxisPoints[5]=middAxisPoints[2]+0.02*middVect[2];
    middAxisPoints[6]=middAxisPoints[0]+0.06*middVect[0];
    middAxisPoints[7]=middAxisPoints[1]+0.06*middVect[1];
    middAxisPoints[8]=middAxisPoints[2]+0.06*middVect[2];
    middAxisPoints[9]=middAxisPoints[0]+0.12*middVect[0];
    middAxisPoints[10]=middAxisPoints[1]+0.12*middVect[1];
    middAxisPoints[11]=middAxisPoints[2]+0.12*middVect[2];
    middAxisPoints[12]=middAxisPoints[0]+0.17*middVect[0];
    middAxisPoints[13]=middAxisPoints[1]+0.17*middVect[1];
    middAxisPoints[14]=middAxisPoints[2]+0.17*middVect[2];
    middAxisPoints[15]=middAxisPoints[0]+0.18*middVect[0];
    middAxisPoints[16]=middAxisPoints[1]+0.18*middVect[1];
    middAxisPoints[17]=middAxisPoints[2]+0.18*middVect[2];

    //重新设置垂直的向量
    float midd2TopVect2[]={ topPoint[0]-middAxisPoints[0],topPoint[1]-middAxisPoints[1],topPoint[2]-middAxisPoints[2] };
    float middAxisVect2[]={ middAxisPoints[3]-middAxisPoints[0],middAxisPoints[4]-middAxisPoints[1],middAxisPoints[5]-middAxisPoints[2] };
    float vertVect2[3]={0.0,-1.0,0.0};
//    WizardGeomSupple::getVerticalVect(midd2TopVect2[0],midd2TopVect2[1],midd2TopVect2[2],middAxisVect2[0],middAxisVect2[1],middAxisVect2[2],vertVect2);
    float vertVect3[3];
    WizardGeomSupple::getVerticalVect(middAxisVect2[0],middAxisVect2[1],middAxisVect2[2],vertVect2[0],vertVect2[1],vertVect2[2],vertVect3);
    WizardGeomSupple::normalize(vertVect3);
    topPoint[0]=middAxisPoints[0]+0.1*vertVect3[0];
    topPoint[1]=middAxisPoints[1]+0.1*vertVect3[1];
    topPoint[2]=middAxisPoints[2]+0.1*vertVect3[2];

    return;

}
//碰撞后bezier路线上的角标值
int BalloonFish::collDeteAfterIndex=0;
//碰撞后bezier路线上的角标值增加还是减小
bool BalloonFish::isCollDeteAfterIndexAdd= true;
//刺豚缩小的开关
bool BalloonFish::isBecomeSmalling=false;
void BalloonFish::moveByBezierPathColliDeteAfter(){

    if(collDeteAfterIndex>BalloonFlyFishCollisionDetection::collDeteBezierPathStep-1){
        isCollDeteAfterIndexAdd= false;
    }else if(collDeteAfterIndex<1){
        isCollDeteAfterIndexAdd= true;
    }
    if(isCollDeteAfterIndexAdd){
        collDeteAfterIndex++;
    }else{
        collDeteAfterIndex--;
    }
    int currIndex=collDeteAfterIndex*3;
    float lengX=BalloonFlyFishCollisionDetection::collDeteAfterBezierPath[currIndex]-middAxisPoints[0];
    float lengY=BalloonFlyFishCollisionDetection::collDeteAfterBezierPath[currIndex+1]-middAxisPoints[1];
    float lengZ=BalloonFlyFishCollisionDetection::collDeteAfterBezierPath[currIndex+2]-middAxisPoints[2];
    float distance=sqrtf(lengX*lengX+lengY*lengY+lengZ*lengZ);
    //bezier路线上的点和刺豚点的向量
    float p2pVect[]={lengX,lengY,lengZ};
    WizardGeomSupple::normalize(p2pVect);
    //按照向量位移
    for(int i=0;i<6;i++){
        int currIndex=i*3;
        middAxisPoints[currIndex]+=distance*p2pVect[0];
        middAxisPoints[currIndex+1]+=distance*p2pVect[1];
        middAxisPoints[currIndex+2]+=distance*p2pVect[2];
    }
    topPoint[0]+=distance*p2pVect[0];
    topPoint[1]+=distance*p2pVect[1];
    topPoint[2]+=distance*p2pVect[2];
    //碰撞后刺豚执行的反转特效动作
    collisionDetectionBalloonFish.rotateBodyByMiddAxis();
    //刺豚开始膨胀
    bolloonFishSwell();
    //碰撞后生成的bezier路线回退到了第一个开始缩小恢复到初始大小
    if(!isCollDeteAfterIndexAdd&&collDeteAfterIndex==0){
        //碰撞结束按bezier路线继续位移
        BalloonFlyFishCollisionDetection::isCollisionDetectionAfter=false;
        isBecomeSmalling=true;
//        BalloonFlyFishCollisionDetection::isInitTempFrontMoveVect=false;
    }

}
//刺豚开始膨胀
void BalloonFish::bolloonFishSwell(){
    //刺豚碰撞bezier路线生成后角标值在增加而且角标值大于10
    if(isCollDeteAfterIndexAdd&&collDeteAfterIndex>10){
        longerRadiu0+=0.001;
        if(longerRadiu0>0.16){
            longerRadiu0=0.16;
        }
        longerRadiu1+=0.001;
        if(longerRadiu1>0.13){
            longerRadiu1=0.13;
        }
        shortRadiu1+=0.0008;
        if(shortRadiu1>0.13){
            shortRadiu1=0.13;
        }
        isDrawStab=true;
        stabSubstractFactor-=0.002;
        if(stabSubstractFactor<0.0){
            stabSubstractFactor=0.0;
        }
    }
}

void BalloonFish::bolloonFishSwellUnconditional(){
    longerRadiu0+=0.001;
    if(longerRadiu0>0.16){
        longerRadiu0=0.16;
    }
    longerRadiu1+=0.001;
    if(longerRadiu1>0.13){
        longerRadiu1=0.13;
    }
    shortRadiu1+=0.0008;
    if(shortRadiu1>0.13){
        shortRadiu1=0.13;
    }
    isDrawStab=true;
    stabSubstractFactor-=0.002;
    if(stabSubstractFactor<0.0){
        stabSubstractFactor=0.0;
    }
}

float BalloonFish::longerRadiu0=0.08;
float BalloonFish::longerRadiu1=0.08;//底部下垂
float BalloonFish::shortRadiu1=0.05;//背部弓起
//初始化刺豚beizer轮廓的bezier控制点
void BalloonFish::initBalloonFishBezierControlPoints(){

    float midd2TopVect[]={
            topPoint[0]-middAxisPoints[0],
            topPoint[1]-middAxisPoints[1],
            topPoint[2]-middAxisPoints[2]};
    WizardGeomSupple::normalize(midd2TopVect);
    float middAxisVect[]={middAxisPoints[3]-middAxisPoints[0],
                          middAxisPoints[4]-middAxisPoints[1],
                          middAxisPoints[5]-middAxisPoints[2]};
    float leftRightVect[3];
    WizardGeomSupple::getVerticalVect(midd2TopVect[0],midd2TopVect[1],midd2TopVect[2],
                                      middAxisVect[0],middAxisVect[1],middAxisVect[2],leftRightVect);
    WizardGeomSupple::normalize(leftRightVect);
    float bezierControlVect0[]={midd2TopVect[0],midd2TopVect[1],midd2TopVect[2]};
    float bezierControlVect1[]={leftRightVect[0],leftRightVect[1],leftRightVect[2]};
    float bezierControlVect2[]={-midd2TopVect[0],-midd2TopVect[1],-midd2TopVect[2]};
    float bezierControlVect3[]={-leftRightVect[0],-leftRightVect[1],-leftRightVect[2]};

    bezierControlPoints3[0]=middAxisPoints[0]+0.025*bezierControlVect0[0];
    bezierControlPoints3[1]=middAxisPoints[1]+0.025*bezierControlVect0[1];
    bezierControlPoints3[2]=middAxisPoints[2]+0.025*bezierControlVect0[2];
    bezierControlPoints3[3]=middAxisPoints[0]+0.001*bezierControlVect1[0];
    bezierControlPoints3[4]=middAxisPoints[1]+0.001*bezierControlVect1[1];
    bezierControlPoints3[5]=middAxisPoints[2]+0.001*bezierControlVect1[2];
    bezierControlPoints3[6]=middAxisPoints[0]+0.025*bezierControlVect2[0];
    bezierControlPoints3[7]=middAxisPoints[1]+0.025*bezierControlVect2[1];
    bezierControlPoints3[8]=middAxisPoints[2]+0.025*bezierControlVect2[2];
    bezierControlPoints3[9]=middAxisPoints[0]+0.001*bezierControlVect3[0];
    bezierControlPoints3[10]=middAxisPoints[1]+0.001*bezierControlVect3[1];
    bezierControlPoints3[11]=middAxisPoints[2]+0.001*bezierControlVect3[2];

    bezierControlPoints3[12]=middAxisPoints[3]+longerRadiu0*bezierControlVect0[0];
    bezierControlPoints3[13]=middAxisPoints[4]+longerRadiu0*bezierControlVect0[1];
    bezierControlPoints3[14]=middAxisPoints[5]+longerRadiu0*bezierControlVect0[2];
    //准备画上眼睛的头部突兀的部位
    bezierControlPoints3[15]=middAxisPoints[3]+longerRadiu1*bezierControlVect1[0];
    bezierControlPoints3[16]=middAxisPoints[4]+longerRadiu1*bezierControlVect1[1];
    bezierControlPoints3[17]=middAxisPoints[5]+longerRadiu1*bezierControlVect1[2];
    bezierControlPoints3[18]=middAxisPoints[3]+longerRadiu0*bezierControlVect2[0];
    bezierControlPoints3[19]=middAxisPoints[4]+longerRadiu0*bezierControlVect2[1];
    bezierControlPoints3[20]=middAxisPoints[5]+longerRadiu0*bezierControlVect2[2];
    bezierControlPoints3[21]=middAxisPoints[3]+shortRadiu1*bezierControlVect3[0];
    bezierControlPoints3[22]=middAxisPoints[4]+shortRadiu1*bezierControlVect3[1];
    bezierControlPoints3[23]=middAxisPoints[5]+shortRadiu1*bezierControlVect3[2];

    bezierControlPoints3[24]=middAxisPoints[6]+longerRadiu0*bezierControlVect0[0];
    bezierControlPoints3[25]=middAxisPoints[7]+longerRadiu0*bezierControlVect0[1];
    bezierControlPoints3[26]=middAxisPoints[8]+longerRadiu0*bezierControlVect0[2];
    bezierControlPoints3[27]=middAxisPoints[6]+longerRadiu1*bezierControlVect1[0];
    bezierControlPoints3[28]=middAxisPoints[7]+longerRadiu1*bezierControlVect1[1];
    bezierControlPoints3[29]=middAxisPoints[8]+longerRadiu1*bezierControlVect1[2];
    bezierControlPoints3[30]=middAxisPoints[6]+longerRadiu0*bezierControlVect2[0];
    bezierControlPoints3[31]=middAxisPoints[7]+longerRadiu0*bezierControlVect2[1];
    bezierControlPoints3[32]=middAxisPoints[8]+longerRadiu0*bezierControlVect2[2];
    bezierControlPoints3[33]=middAxisPoints[6]+shortRadiu1*bezierControlVect3[0];
    bezierControlPoints3[34]=middAxisPoints[7]+shortRadiu1*bezierControlVect3[1];
    bezierControlPoints3[35]=middAxisPoints[8]+shortRadiu1*bezierControlVect3[2];

    bezierControlPoints3[36]=middAxisPoints[9]+longerRadiu0*bezierControlVect0[0];
    bezierControlPoints3[37]=middAxisPoints[10]+longerRadiu0*bezierControlVect0[1];
    bezierControlPoints3[38]=middAxisPoints[11]+longerRadiu0*bezierControlVect0[2];
    bezierControlPoints3[39]=middAxisPoints[9]+longerRadiu1*bezierControlVect1[0];
    bezierControlPoints3[40]=middAxisPoints[10]+longerRadiu1*bezierControlVect1[1];
    bezierControlPoints3[41]=middAxisPoints[11]+longerRadiu1*bezierControlVect1[2];
    bezierControlPoints3[42]=middAxisPoints[9]+longerRadiu0*bezierControlVect2[0];
    bezierControlPoints3[43]=middAxisPoints[10]+longerRadiu0*bezierControlVect2[1];
    bezierControlPoints3[44]=middAxisPoints[11]+longerRadiu0*bezierControlVect2[2];
    bezierControlPoints3[45]=middAxisPoints[9]+shortRadiu1*bezierControlVect3[0];
    bezierControlPoints3[46]=middAxisPoints[10]+shortRadiu1*bezierControlVect3[1];
    bezierControlPoints3[47]=middAxisPoints[11]+shortRadiu1*bezierControlVect3[2];

    bezierControlPoints3[48]=middAxisPoints[12]+0.03*bezierControlVect0[0];
    bezierControlPoints3[49]=middAxisPoints[13]+0.03*bezierControlVect0[1];
    bezierControlPoints3[50]=middAxisPoints[14]+0.03*bezierControlVect0[2];
    bezierControlPoints3[51]=middAxisPoints[12]+0.03*bezierControlVect1[0];
    bezierControlPoints3[52]=middAxisPoints[13]+0.03*bezierControlVect1[1];
    bezierControlPoints3[53]=middAxisPoints[14]+0.03*bezierControlVect1[2];
    bezierControlPoints3[54]=middAxisPoints[12]+0.03*bezierControlVect2[0];
    bezierControlPoints3[55]=middAxisPoints[13]+0.03*bezierControlVect2[1];
    bezierControlPoints3[56]=middAxisPoints[14]+0.03*bezierControlVect2[2];
    bezierControlPoints3[57]=middAxisPoints[12]+0.03*bezierControlVect3[0];
    bezierControlPoints3[58]=middAxisPoints[13]+0.03*bezierControlVect3[1];
    bezierControlPoints3[59]=middAxisPoints[14]+0.03*bezierControlVect3[2];

    bezierControlPoints3[60]=middAxisPoints[15]+0.03*bezierControlVect0[0];
    bezierControlPoints3[61]=middAxisPoints[16]+0.03*bezierControlVect0[1];
    bezierControlPoints3[62]=middAxisPoints[17]+0.03*bezierControlVect0[2];
    bezierControlPoints3[63]=middAxisPoints[15]+0.03*bezierControlVect1[0];
    bezierControlPoints3[64]=middAxisPoints[16]+0.03*bezierControlVect1[1];
    bezierControlPoints3[65]=middAxisPoints[17]+0.03*bezierControlVect1[2];
    bezierControlPoints3[66]=middAxisPoints[15]+0.03*bezierControlVect2[0];
    bezierControlPoints3[67]=middAxisPoints[16]+0.03*bezierControlVect2[1];
    bezierControlPoints3[68]=middAxisPoints[17]+0.03*bezierControlVect2[2];
    bezierControlPoints3[69]=middAxisPoints[15]+0.03*bezierControlVect3[0];
    bezierControlPoints3[70]=middAxisPoints[16]+0.03*bezierControlVect3[1];
    bezierControlPoints3[71]=middAxisPoints[17]+0.03*bezierControlVect3[2];

}


int fishFinsPointer=0;
bool fishFinsPointerAdd=true;
int tailPointer=0;
bool tailPointerAdd=true;
float BalloonFish::tailBsplineControlPoints[300];
float BalloonFish::balloonFishLeftFins[90];
float BalloonFish::balloonFishRightFins[90];
void BalloonFish::addBalloonFishTail(){

    if(fishFinsPointerAdd){
        fishFinsPointer++;
    }else{
        fishFinsPointer--;
    }
    float angle=fishFinsPointer*1.6;
    if(angle>45.0){
        fishFinsPointerAdd=false;
    }
    if(angle<-45.0){
        fishFinsPointerAdd=true;
    }



    float midd2TopVect[]={
            topPoint[0]-middAxisPoints[0],
            topPoint[1]-middAxisPoints[1],
            topPoint[2]-middAxisPoints[2]};
    WizardGeomSupple::normalize(midd2TopVect);
    float middAxisVect[]={middAxisPoints[3]-middAxisPoints[0],
                          middAxisPoints[4]-middAxisPoints[1],
                          middAxisPoints[5]-middAxisPoints[2]};
    WizardGeomSupple::normalize(middAxisVect);
    float leftRightVect[3];
    WizardGeomSupple::getVerticalVect(midd2TopVect[0],midd2TopVect[1],midd2TopVect[2],
                                      middAxisVect[0],middAxisVect[1],middAxisVect[2],leftRightVect);
    WizardGeomSupple::normalize(leftRightVect);
    float bezierControlVect0[]={midd2TopVect[0],midd2TopVect[1],midd2TopVect[2]};
    float bezierControlVect1[]={leftRightVect[0],leftRightVect[1],leftRightVect[2]};
    float bezierControlVect2[]={-midd2TopVect[0],-midd2TopVect[1],-midd2TopVect[2]};
    float bezierControlVect3[]={-leftRightVect[0],-leftRightVect[1],-leftRightVect[2]};


    if(tailPointerAdd){
        tailPointer++;
    }else{
        tailPointer--;
    }
    float tailAngle=tailPointer*1.5;
    if(tailAngle>20.0){
        tailPointerAdd=false;
    }
    if(tailAngle<-20.0){
        tailPointerAdd=true;
    }

    float tailAngle2=tailPointer*1.8;
    if(tailAngle2>40.0){
        tailAngle2=40.0;
    }
    if(tailAngle2<-40.0){
        tailAngle2=-40.0;
    }


    float fishFinsMoveAngle=tanf((3.1415926/180.0)*tailAngle);
    float fishFinsMoveAngle2=tanf((3.1415926/180.0)*tailAngle2);
    float tailMoveVect[]={middAxisVect[0]+tanf(fishFinsMoveAngle)*midd2TopVect[0],
                          middAxisVect[1]+tanf(fishFinsMoveAngle)*midd2TopVect[1],
                          middAxisVect[2]+tanf(fishFinsMoveAngle)*midd2TopVect[2]};
    WizardGeomSupple::normalize(tailMoveVect);
    float tailMoveVect2[]={middAxisVect[0]+tanf(fishFinsMoveAngle2)*midd2TopVect[0],
                          middAxisVect[1]+tanf(fishFinsMoveAngle2)*midd2TopVect[1],
                          middAxisVect[2]+tanf(fishFinsMoveAngle2)*midd2TopVect[2]};
    WizardGeomSupple::normalize(tailMoveVect2);


    tailBsplineControlPoints[0]=bezierControlPoints3[48];
    tailBsplineControlPoints[1]=bezierControlPoints3[49];
    tailBsplineControlPoints[2]=bezierControlPoints3[50];
    tailBsplineControlPoints[3]=bezierControlPoints3[51];
    tailBsplineControlPoints[4]=bezierControlPoints3[52];
    tailBsplineControlPoints[5]=bezierControlPoints3[53];
    tailBsplineControlPoints[6]=bezierControlPoints3[54];
    tailBsplineControlPoints[7]=bezierControlPoints3[55];
    tailBsplineControlPoints[8]=bezierControlPoints3[56];
    tailBsplineControlPoints[9]=bezierControlPoints3[57];
    tailBsplineControlPoints[10]=bezierControlPoints3[58];
    tailBsplineControlPoints[11]=bezierControlPoints3[59];

    tailBsplineControlPoints[12]=tailBsplineControlPoints[0];
    tailBsplineControlPoints[13]=tailBsplineControlPoints[1];
    tailBsplineControlPoints[14]=tailBsplineControlPoints[2];
    tailBsplineControlPoints[15]=tailBsplineControlPoints[3];
    tailBsplineControlPoints[16]=tailBsplineControlPoints[4];
    tailBsplineControlPoints[17]=tailBsplineControlPoints[5];
    tailBsplineControlPoints[18]=tailBsplineControlPoints[6];
    tailBsplineControlPoints[19]=tailBsplineControlPoints[7];
    tailBsplineControlPoints[20]=tailBsplineControlPoints[8];
    tailBsplineControlPoints[21]=tailBsplineControlPoints[9];
    tailBsplineControlPoints[22]=tailBsplineControlPoints[10];
    tailBsplineControlPoints[23]=tailBsplineControlPoints[11];
    tailBsplineControlPoints[24]=tailBsplineControlPoints[0];
    tailBsplineControlPoints[25]=tailBsplineControlPoints[1];
    tailBsplineControlPoints[26]=tailBsplineControlPoints[2];

    tailBsplineControlPoints[27]=bezierControlPoints3[60]+0.01*tailMoveVect[0];
    tailBsplineControlPoints[28]=bezierControlPoints3[61]+0.01*tailMoveVect[1];
    tailBsplineControlPoints[29]=bezierControlPoints3[62]+0.01*tailMoveVect[2];
    tailBsplineControlPoints[30]=bezierControlPoints3[63]+0.02*tailMoveVect[0];
    tailBsplineControlPoints[31]=bezierControlPoints3[64]+0.02*tailMoveVect[1];
    tailBsplineControlPoints[32]=bezierControlPoints3[65]+0.02*tailMoveVect[2];
    tailBsplineControlPoints[33]=bezierControlPoints3[66]+0.01*tailMoveVect[0];
    tailBsplineControlPoints[34]=bezierControlPoints3[67]+0.01*tailMoveVect[1];
    tailBsplineControlPoints[35]=bezierControlPoints3[68]+0.01*tailMoveVect[2];
    tailBsplineControlPoints[36]=bezierControlPoints3[69]+0.02*tailMoveVect[0];
    tailBsplineControlPoints[37]=bezierControlPoints3[70]+0.02*tailMoveVect[1];
    tailBsplineControlPoints[38]=bezierControlPoints3[71]+0.02*tailMoveVect[2];

    tailBsplineControlPoints[39]=tailBsplineControlPoints[27];
    tailBsplineControlPoints[40]=tailBsplineControlPoints[28];
    tailBsplineControlPoints[41]=tailBsplineControlPoints[29];
    tailBsplineControlPoints[42]=tailBsplineControlPoints[30];
    tailBsplineControlPoints[43]=tailBsplineControlPoints[31];
    tailBsplineControlPoints[44]=tailBsplineControlPoints[32];
    tailBsplineControlPoints[45]=tailBsplineControlPoints[33];
    tailBsplineControlPoints[46]=tailBsplineControlPoints[34];
    tailBsplineControlPoints[47]=tailBsplineControlPoints[35];
    tailBsplineControlPoints[48]=tailBsplineControlPoints[36];
    tailBsplineControlPoints[49]=tailBsplineControlPoints[37];
    tailBsplineControlPoints[50]=tailBsplineControlPoints[38];
    tailBsplineControlPoints[51]=tailBsplineControlPoints[27];
    tailBsplineControlPoints[52]=tailBsplineControlPoints[28];
    tailBsplineControlPoints[53]=tailBsplineControlPoints[29];


    tailBsplineControlPoints[54]=bezierControlPoints3[60]+0.04*tailMoveVect[0]-0.015*bezierControlVect0[0];
    tailBsplineControlPoints[55]=bezierControlPoints3[61]+0.04*tailMoveVect[1]-0.015*bezierControlVect0[1];
    tailBsplineControlPoints[56]=bezierControlPoints3[62]+0.04*tailMoveVect[2]-0.015*bezierControlVect0[2];
    tailBsplineControlPoints[57]=bezierControlPoints3[63]+0.04*tailMoveVect[0]-0.01*bezierControlVect1[0];
    tailBsplineControlPoints[58]=bezierControlPoints3[64]+0.04*tailMoveVect[1]-0.01*bezierControlVect1[1];
    tailBsplineControlPoints[59]=bezierControlPoints3[65]+0.04*tailMoveVect[2]-0.01*bezierControlVect1[2];
    tailBsplineControlPoints[60]=bezierControlPoints3[66]+0.04*tailMoveVect[0]-0.015*bezierControlVect2[0];
    tailBsplineControlPoints[61]=bezierControlPoints3[67]+0.04*tailMoveVect[1]-0.015*bezierControlVect2[1];
    tailBsplineControlPoints[62]=bezierControlPoints3[68]+0.04*tailMoveVect[2]-0.015*bezierControlVect2[2];
    tailBsplineControlPoints[63]=bezierControlPoints3[69]+0.04*tailMoveVect[0]-0.01*bezierControlVect3[0];
    tailBsplineControlPoints[64]=bezierControlPoints3[70]+0.04*tailMoveVect[1]-0.01*bezierControlVect3[1];
    tailBsplineControlPoints[65]=bezierControlPoints3[71]+0.04*tailMoveVect[2]-0.01*bezierControlVect3[2];

    tailBsplineControlPoints[66]=tailBsplineControlPoints[54];
    tailBsplineControlPoints[67]=tailBsplineControlPoints[55];
    tailBsplineControlPoints[68]=tailBsplineControlPoints[56];
    tailBsplineControlPoints[69]=tailBsplineControlPoints[57];
    tailBsplineControlPoints[70]=tailBsplineControlPoints[58];
    tailBsplineControlPoints[71]=tailBsplineControlPoints[59];
    tailBsplineControlPoints[72]=tailBsplineControlPoints[60];
    tailBsplineControlPoints[73]=tailBsplineControlPoints[61];
    tailBsplineControlPoints[74]=tailBsplineControlPoints[62];
    tailBsplineControlPoints[75]=tailBsplineControlPoints[63];
    tailBsplineControlPoints[76]=tailBsplineControlPoints[64];
    tailBsplineControlPoints[77]=tailBsplineControlPoints[65];
    tailBsplineControlPoints[78]=tailBsplineControlPoints[54];
    tailBsplineControlPoints[79]=tailBsplineControlPoints[55];
    tailBsplineControlPoints[80]=tailBsplineControlPoints[56];


    tailBsplineControlPoints[81]=bezierControlPoints3[60]+0.06*tailMoveVect2[0]-0.02*bezierControlVect0[0];
    tailBsplineControlPoints[82]=bezierControlPoints3[61]+0.06*tailMoveVect2[1]-0.02*bezierControlVect0[1];
    tailBsplineControlPoints[83]=bezierControlPoints3[62]+0.06*tailMoveVect2[2]-0.02*bezierControlVect0[2];
    tailBsplineControlPoints[84]=bezierControlPoints3[63]+0.06*tailMoveVect2[0]+0.015*bezierControlVect1[0];
    tailBsplineControlPoints[85]=bezierControlPoints3[64]+0.06*tailMoveVect2[1]+0.015*bezierControlVect1[1];
    tailBsplineControlPoints[86]=bezierControlPoints3[65]+0.06*tailMoveVect2[2]+0.015*bezierControlVect1[2];
    tailBsplineControlPoints[87]=bezierControlPoints3[66]+0.06*tailMoveVect2[0]-0.02*bezierControlVect2[0];
    tailBsplineControlPoints[88]=bezierControlPoints3[67]+0.06*tailMoveVect2[1]-0.02*bezierControlVect2[1];
    tailBsplineControlPoints[89]=bezierControlPoints3[68]+0.06*tailMoveVect2[2]-0.02*bezierControlVect2[2];
    tailBsplineControlPoints[90]=bezierControlPoints3[69]+0.06*tailMoveVect2[0]+0.015*bezierControlVect3[0];
    tailBsplineControlPoints[91]=bezierControlPoints3[70]+0.06*tailMoveVect2[1]+0.015*bezierControlVect3[1];
    tailBsplineControlPoints[92]=bezierControlPoints3[71]+0.06*tailMoveVect2[2]+0.015*bezierControlVect3[2];

    tailBsplineControlPoints[93]=tailBsplineControlPoints[81];
    tailBsplineControlPoints[94]=tailBsplineControlPoints[82];
    tailBsplineControlPoints[95]=tailBsplineControlPoints[83];
    tailBsplineControlPoints[96]=tailBsplineControlPoints[84];
    tailBsplineControlPoints[97]=tailBsplineControlPoints[85];
    tailBsplineControlPoints[98]=tailBsplineControlPoints[86];
    tailBsplineControlPoints[99]=tailBsplineControlPoints[87];
    tailBsplineControlPoints[100]=tailBsplineControlPoints[88];
    tailBsplineControlPoints[101]=tailBsplineControlPoints[89];
    tailBsplineControlPoints[102]=tailBsplineControlPoints[90];
    tailBsplineControlPoints[103]=tailBsplineControlPoints[91];
    tailBsplineControlPoints[104]=tailBsplineControlPoints[92];
    tailBsplineControlPoints[105]=tailBsplineControlPoints[81];
    tailBsplineControlPoints[106]=tailBsplineControlPoints[82];
    tailBsplineControlPoints[107]=tailBsplineControlPoints[83];


    tailBsplineControlPoints[108]=bezierControlPoints3[60]+0.08*tailMoveVect2[0]-0.028*bezierControlVect0[0];
    tailBsplineControlPoints[109]=bezierControlPoints3[61]+0.08*tailMoveVect2[1]-0.028*bezierControlVect0[1];
    tailBsplineControlPoints[110]=bezierControlPoints3[62]+0.08*tailMoveVect2[2]-0.028*bezierControlVect0[2];
    tailBsplineControlPoints[111]=bezierControlPoints3[63]+0.08*tailMoveVect2[0]+0.02*bezierControlVect1[0];
    tailBsplineControlPoints[112]=bezierControlPoints3[64]+0.08*tailMoveVect2[1]+0.02*bezierControlVect1[1];
    tailBsplineControlPoints[113]=bezierControlPoints3[65]+0.08*tailMoveVect2[2]+0.02*bezierControlVect1[2];
    tailBsplineControlPoints[114]=bezierControlPoints3[66]+0.08*tailMoveVect2[0]-0.028*bezierControlVect2[0];
    tailBsplineControlPoints[115]=bezierControlPoints3[67]+0.08*tailMoveVect2[1]-0.028*bezierControlVect2[1];
    tailBsplineControlPoints[116]=bezierControlPoints3[68]+0.08*tailMoveVect2[2]-0.028*bezierControlVect2[2];
    tailBsplineControlPoints[117]=bezierControlPoints3[69]+0.08*tailMoveVect2[0]+0.02*bezierControlVect3[0];
    tailBsplineControlPoints[118]=bezierControlPoints3[70]+0.08*tailMoveVect2[1]+0.02*bezierControlVect3[1];
    tailBsplineControlPoints[119]=bezierControlPoints3[71]+0.08*tailMoveVect2[2]+0.02*bezierControlVect3[2];

    tailBsplineControlPoints[120]=tailBsplineControlPoints[108];
    tailBsplineControlPoints[121]=tailBsplineControlPoints[109];
    tailBsplineControlPoints[122]=tailBsplineControlPoints[110];
    tailBsplineControlPoints[123]=tailBsplineControlPoints[111];
    tailBsplineControlPoints[124]=tailBsplineControlPoints[112];
    tailBsplineControlPoints[125]=tailBsplineControlPoints[113];
    tailBsplineControlPoints[126]=tailBsplineControlPoints[114];
    tailBsplineControlPoints[127]=tailBsplineControlPoints[115];
    tailBsplineControlPoints[128]=tailBsplineControlPoints[116];
    tailBsplineControlPoints[129]=tailBsplineControlPoints[117];
    tailBsplineControlPoints[130]=tailBsplineControlPoints[118];
    tailBsplineControlPoints[131]=tailBsplineControlPoints[119];
    tailBsplineControlPoints[132]=tailBsplineControlPoints[108];
    tailBsplineControlPoints[133]=tailBsplineControlPoints[109];
    tailBsplineControlPoints[134]=tailBsplineControlPoints[110];

    makeBalloonFishBsplinePoints(tailBsplineControlPoints,5,bezierDegreeSplitNum+5,5,200);
    ////////////////////////////////////////////////
    ////////////左右鱼鳍//////////////////
    ///////////////////////////////////////////////
    float bsplineControl3th4th[3];
    float bsplineControl0th4th[3];
    float bsplineControl1th4th[3];
    float bsplineControl2th4th[3];

    int bezier3thIndex=3*bezierStep*3;
    int bezier1thIndex=bezierStep*3;
    int bezier2thIndex=2*bezierStep*3;

    bsplineControl3th4th[0]=bezierGatherBalloonFish[bezier3thIndex+12];
    bsplineControl3th4th[1]=bezierGatherBalloonFish[bezier3thIndex+13];
    bsplineControl3th4th[2]=bezierGatherBalloonFish[bezier3thIndex+14];
    bsplineControl0th4th[0]=bezierGatherBalloonFish[12];
    bsplineControl0th4th[1]=bezierGatherBalloonFish[13];
    bsplineControl0th4th[2]=bezierGatherBalloonFish[14];
    bsplineControl1th4th[0]=bezierGatherBalloonFish[bezier1thIndex+12];
    bsplineControl1th4th[1]=bezierGatherBalloonFish[bezier1thIndex+13];
    bsplineControl1th4th[2]=bezierGatherBalloonFish[bezier1thIndex+14];
    bsplineControl2th4th[0]=bezierGatherBalloonFish[bezier2thIndex+12];
    bsplineControl2th4th[1]=bezierGatherBalloonFish[bezier2thIndex+13];
    bsplineControl2th4th[2]=bezierGatherBalloonFish[bezier2thIndex+14];
    float resultPoint3012th[3];
    makeOthBsplinePoint(bsplineControl3th4th,bsplineControl0th4th,bsplineControl1th4th,bsplineControl2th4th,resultPoint3012th);
    float resultPoint1230th[3];
    makeOthBsplinePoint(bsplineControl1th4th,bsplineControl2th4th,bsplineControl3th4th,bsplineControl0th4th,resultPoint1230th);

    for(int i=0;i<9;i++){
        int currIndex=27+i*3;
        balloonFishLeftFins[currIndex]=resultPoint3012th[0];
        balloonFishLeftFins[currIndex+1]=resultPoint3012th[1];
        balloonFishLeftFins[currIndex+2]=resultPoint3012th[2];
    }
    for(int i=0;i<9;i++){
        int currIndex=27+i*3;
        balloonFishRightFins[currIndex]=resultPoint1230th[0];
        balloonFishRightFins[currIndex+1]=resultPoint1230th[1];
        balloonFishRightFins[currIndex+2]=resultPoint1230th[2];
    }



    float leftFinsVect[]={resultPoint3012th[0]-bezierVertBaseLinePointsBalloonFish[12],
                          resultPoint3012th[1]-bezierVertBaseLinePointsBalloonFish[13],resultPoint3012th[2]-bezierVertBaseLinePointsBalloonFish[14]};
    WizardGeomSupple::normalize(leftFinsVect);
    //鱼鳍运动的方向
    float leftFinsMoveVect[3];
    leftFinsMoveVect[0]=leftFinsVect[0]-fishFinsMoveAngle*middAxisVect[0];
    leftFinsMoveVect[1]=leftFinsVect[1]-fishFinsMoveAngle*middAxisVect[1];
    leftFinsMoveVect[2]=leftFinsVect[2]-fishFinsMoveAngle*middAxisVect[2];
    WizardGeomSupple::normalize(leftFinsMoveVect);

    balloonFishLeftFins[0]=resultPoint3012th[0]+0.01*leftFinsMoveVect[0]+0.02*leftRightVect[0];
    balloonFishLeftFins[1]=resultPoint3012th[1]+0.01*leftFinsMoveVect[1]+0.02*leftRightVect[1];
    balloonFishLeftFins[2]=resultPoint3012th[2]+0.01*leftFinsMoveVect[2]+0.02*leftRightVect[2];
    balloonFishLeftFins[3]=resultPoint3012th[0]+0.015*leftFinsMoveVect[0]+0.03*leftRightVect[0];
    balloonFishLeftFins[4]=resultPoint3012th[1]+0.015*leftFinsMoveVect[1]+0.03*leftRightVect[1];
    balloonFishLeftFins[5]=resultPoint3012th[2]+0.015*leftFinsMoveVect[2]+0.03*leftRightVect[2];
    balloonFishLeftFins[6]=resultPoint3012th[0]+0.02*leftFinsMoveVect[0]+0.05*leftRightVect[0];
    balloonFishLeftFins[7]=resultPoint3012th[1]+0.02*leftFinsMoveVect[1]+0.05*leftRightVect[1];
    balloonFishLeftFins[8]=resultPoint3012th[2]+0.02*leftFinsMoveVect[2]+0.05*leftRightVect[2];

    balloonFishLeftFins[9]=resultPoint3012th[0]+0.03*leftFinsMoveVect[0]+0.03*leftRightVect[0];
    balloonFishLeftFins[10]=resultPoint3012th[1]+0.03*leftFinsMoveVect[1]+0.03*leftRightVect[1];
    balloonFishLeftFins[11]=resultPoint3012th[2]+0.03*leftFinsMoveVect[2]+0.03*leftRightVect[2];
    balloonFishLeftFins[12]=resultPoint3012th[0]+0.03*leftFinsMoveVect[0]+0.02*leftRightVect[0];
    balloonFishLeftFins[13]=resultPoint3012th[1]+0.03*leftFinsMoveVect[1]+0.02*leftRightVect[1];
    balloonFishLeftFins[14]=resultPoint3012th[2]+0.03*leftFinsMoveVect[2]+0.02*leftRightVect[2];
    balloonFishLeftFins[15]=resultPoint3012th[0]+0.03*leftFinsMoveVect[0];
    balloonFishLeftFins[16]=resultPoint3012th[1]+0.03*leftFinsMoveVect[1];
    balloonFishLeftFins[17]=resultPoint3012th[2]+0.03*leftFinsMoveVect[2];

    balloonFishLeftFins[18]=resultPoint3012th[0]+0.02*leftFinsMoveVect[0]-0.02*leftRightVect[0];
    balloonFishLeftFins[19]=resultPoint3012th[1]+0.02*leftFinsMoveVect[1]-0.02*leftRightVect[1];
    balloonFishLeftFins[20]=resultPoint3012th[2]+0.02*leftFinsMoveVect[2]-0.02*leftRightVect[2];
    balloonFishLeftFins[21]=resultPoint3012th[0]+0.015*leftFinsMoveVect[0];
    balloonFishLeftFins[22]=resultPoint3012th[1]+0.015*leftFinsMoveVect[1];
    balloonFishLeftFins[23]=resultPoint3012th[2]+0.015*leftFinsMoveVect[2];
    balloonFishLeftFins[24]=resultPoint3012th[0]+0.01*leftFinsMoveVect[0]+0.02*leftRightVect[0];
    balloonFishLeftFins[25]=resultPoint3012th[1]+0.01*leftFinsMoveVect[1]+0.02*leftRightVect[1];
    balloonFishLeftFins[26]=resultPoint3012th[2]+0.01*leftFinsMoveVect[2]+0.02*leftRightVect[2];
    flyElephantEarBalloonFish.MakeEarPoints(balloonFishLeftFins,2,9,5,101);
//    drawPointLine(balloonFishLeftFins,9,true,1.0,0.0,1.0,10.0);

    float rightFinsVect[]={resultPoint1230th[0]-bezierVertBaseLinePointsBalloonFish[12],
                           resultPoint1230th[1]-bezierVertBaseLinePointsBalloonFish[13],resultPoint1230th[2]-bezierVertBaseLinePointsBalloonFish[14]};
    WizardGeomSupple::normalize(rightFinsVect);
    float rightFinsMoveVect[3];//鱼鳍外凸的向量
    rightFinsMoveVect[0]=rightFinsVect[0]-fishFinsMoveAngle*middAxisVect[0];
    rightFinsMoveVect[1]=rightFinsVect[1]-fishFinsMoveAngle*middAxisVect[1];
    rightFinsMoveVect[2]=rightFinsVect[2]-fishFinsMoveAngle*middAxisVect[2];
    WizardGeomSupple::normalize(rightFinsMoveVect);

    balloonFishRightFins[0]=resultPoint1230th[0]+0.01*rightFinsMoveVect[0]+0.02*leftRightVect[0];
    balloonFishRightFins[1]=resultPoint1230th[1]+0.01*rightFinsMoveVect[1]+0.02*leftRightVect[1];
    balloonFishRightFins[2]=resultPoint1230th[2]+0.01*rightFinsMoveVect[2]+0.02*leftRightVect[2];
    balloonFishRightFins[3]=resultPoint1230th[0]+0.015*rightFinsMoveVect[0]+0.03*leftRightVect[0];
    balloonFishRightFins[4]=resultPoint1230th[1]+0.015*rightFinsMoveVect[1]+0.03*leftRightVect[1];
    balloonFishRightFins[5]=resultPoint1230th[2]+0.015*rightFinsMoveVect[2]+0.03*leftRightVect[2];
    balloonFishRightFins[6]=resultPoint1230th[0]+0.02*rightFinsMoveVect[0]+0.05*leftRightVect[0];
    balloonFishRightFins[7]=resultPoint1230th[1]+0.02*rightFinsMoveVect[1]+0.05*leftRightVect[1];
    balloonFishRightFins[8]=resultPoint1230th[2]+0.02*rightFinsMoveVect[2]+0.05*leftRightVect[2];

    balloonFishRightFins[9]=resultPoint1230th[0]+0.03*rightFinsMoveVect[0]+0.03*leftRightVect[0];
    balloonFishRightFins[10]=resultPoint1230th[1]+0.03*rightFinsMoveVect[1]+0.03*leftRightVect[1];
    balloonFishRightFins[11]=resultPoint1230th[2]+0.03*rightFinsMoveVect[2]+0.03*leftRightVect[2];
    balloonFishRightFins[12]=resultPoint1230th[0]+0.03*rightFinsMoveVect[0]+0.02*leftRightVect[0];
    balloonFishRightFins[13]=resultPoint1230th[1]+0.03*rightFinsMoveVect[1]+0.02*leftRightVect[1];
    balloonFishRightFins[14]=resultPoint1230th[2]+0.03*rightFinsMoveVect[2]+0.02*leftRightVect[2];
    balloonFishRightFins[15]=resultPoint1230th[0]+0.03*rightFinsMoveVect[0];
    balloonFishRightFins[16]=resultPoint1230th[1]+0.03*rightFinsMoveVect[1];
    balloonFishRightFins[17]=resultPoint1230th[2]+0.03*rightFinsMoveVect[2];

    balloonFishRightFins[18]=resultPoint1230th[0]+0.02*rightFinsMoveVect[0]-0.01*leftRightVect[0];
    balloonFishRightFins[19]=resultPoint1230th[1]+0.02*rightFinsMoveVect[1]-0.01*leftRightVect[1];
    balloonFishRightFins[20]=resultPoint1230th[2]+0.02*rightFinsMoveVect[2]-0.01*leftRightVect[2];
    balloonFishRightFins[21]=resultPoint1230th[0]+0.015*rightFinsMoveVect[0];
    balloonFishRightFins[22]=resultPoint1230th[1]+0.015*rightFinsMoveVect[1];
    balloonFishRightFins[23]=resultPoint1230th[2]+0.015*rightFinsMoveVect[2];
    balloonFishRightFins[24]=resultPoint1230th[0]+0.01*rightFinsMoveVect[0]+0.01*leftRightVect[0];
    balloonFishRightFins[25]=resultPoint1230th[1]+0.01*rightFinsMoveVect[1]+0.01*leftRightVect[1];
    balloonFishRightFins[26]=resultPoint1230th[2]+0.01*rightFinsMoveVect[2]+0.01*leftRightVect[2];
    flyElephantEarBalloonFish.MakeEarPoints(balloonFishRightFins,2,9,5,101);
    ////////////////////////////////////////////////////////////////////////
    //**上下的鱼鳍
    ///////////////////////////////////////////////////////////////////////
    float bsplineControl0th12th[3];
    float bsplineControl1th12th[3];
    float bsplineControl2th12th[3];
    float bsplineControl3th12th[3];

    bsplineControl0th12th[0]=bezierGatherBalloonFish[36];
    bsplineControl0th12th[1]=bezierGatherBalloonFish[37];
    bsplineControl0th12th[2]=bezierGatherBalloonFish[38];
    bsplineControl1th12th[0]=bezierGatherBalloonFish[bezier1thIndex+36];
    bsplineControl1th12th[1]=bezierGatherBalloonFish[bezier1thIndex+37];
    bsplineControl1th12th[2]=bezierGatherBalloonFish[bezier1thIndex+38];
    bsplineControl2th12th[0]=bezierGatherBalloonFish[bezier2thIndex+36];
    bsplineControl2th12th[1]=bezierGatherBalloonFish[bezier2thIndex+37];
    bsplineControl2th12th[2]=bezierGatherBalloonFish[bezier2thIndex+38];
    bsplineControl3th12th[0]=bezierGatherBalloonFish[bezier3thIndex+36];
    bsplineControl3th12th[1]=bezierGatherBalloonFish[bezier3thIndex+37];
    bsplineControl3th12th[2]=bezierGatherBalloonFish[bezier3thIndex+38];
    float resultPoint0123th[3];
    makeOthBsplinePoint(bsplineControl0th12th,bsplineControl1th12th,bsplineControl2th12th,bsplineControl3th12th,resultPoint0123th);
    float resultPoint2301th[3];
    makeOthBsplinePoint(bsplineControl2th12th,bsplineControl3th12th,bsplineControl0th12th,bsplineControl1th12th,resultPoint2301th);
    float balloonFishTopFins[90];
    float balloonFishBottomFins[90];

    float topFinsVect[]={resultPoint0123th[0]-bezierVertBaseLinePointsBalloonFish[36],
                         resultPoint0123th[1]-bezierVertBaseLinePointsBalloonFish[37],resultPoint0123th[2]-bezierVertBaseLinePointsBalloonFish[38]};
    WizardGeomSupple::normalize(topFinsVect);

    for(int i=0;i<5;i++){
        int currIndex=15+i*3;
        balloonFishTopFins[currIndex]=resultPoint0123th[0]-0.01*topFinsVect[0];
        balloonFishTopFins[currIndex+1]=resultPoint0123th[1]-0.01*topFinsVect[1];
        balloonFishTopFins[currIndex+2]=resultPoint0123th[2]-0.01*topFinsVect[2];
    }
    for(int i=0;i<5;i++){
        int currIndex=15+i*3;
        balloonFishBottomFins[currIndex]=resultPoint2301th[0]+0.015*topFinsVect[0];
        balloonFishBottomFins[currIndex+1]=resultPoint2301th[1]+0.015*topFinsVect[1];
        balloonFishBottomFins[currIndex+2]=resultPoint2301th[2]+0.015*topFinsVect[2];
    }

    balloonFishTopFins[0]=resultPoint0123th[0]-0.03*topFinsVect[0]+0.03*middAxisVect[0];
    balloonFishTopFins[1]=resultPoint0123th[1]-0.03*topFinsVect[1]+0.03*middAxisVect[1];
    balloonFishTopFins[2]=resultPoint0123th[2]-0.03*topFinsVect[2]+0.03*middAxisVect[2];
    balloonFishTopFins[3]=resultPoint0123th[0]-0.02*topFinsVect[0]+0.02*middAxisVect[0];
    balloonFishTopFins[4]=resultPoint0123th[1]-0.02*topFinsVect[1]+0.02*middAxisVect[1];
    balloonFishTopFins[5]=resultPoint0123th[2]-0.02*topFinsVect[2]+0.02*middAxisVect[2];
    balloonFishTopFins[6]=resultPoint0123th[0]+0.05*topFinsVect[0];
    balloonFishTopFins[7]=resultPoint0123th[1]+0.05*topFinsVect[1];
    balloonFishTopFins[8]=resultPoint0123th[2]+0.05*topFinsVect[2];
    balloonFishTopFins[9]=resultPoint0123th[0]-0.02*topFinsVect[0]-0.02*middAxisVect[0];
    balloonFishTopFins[10]=resultPoint0123th[1]-0.02*topFinsVect[1]-0.02*middAxisVect[1];
    balloonFishTopFins[11]=resultPoint0123th[2]-0.02*topFinsVect[2]-0.02*middAxisVect[2];
    balloonFishTopFins[12]=resultPoint0123th[0]-0.03*topFinsVect[0]-0.03*middAxisVect[0];
    balloonFishTopFins[13]=resultPoint0123th[1]-0.03*topFinsVect[1]-0.03*middAxisVect[1];
    balloonFishTopFins[14]=resultPoint0123th[2]-0.03*topFinsVect[2]-0.03*middAxisVect[2];
    flyElephantEarBalloonFish.MakeEarPoints(balloonFishTopFins,2,5,5,101);


    balloonFishBottomFins[0]=resultPoint2301th[0]+0.03*topFinsVect[0]+0.03*middAxisVect[0];
    balloonFishBottomFins[1]=resultPoint2301th[1]+0.03*topFinsVect[1]+0.03*middAxisVect[1];
    balloonFishBottomFins[2]=resultPoint2301th[2]+0.03*topFinsVect[2]+0.03*middAxisVect[2];
    balloonFishBottomFins[3]=resultPoint2301th[0]+0.02*topFinsVect[0]+0.02*middAxisVect[0];
    balloonFishBottomFins[4]=resultPoint2301th[1]+0.02*topFinsVect[1]+0.02*middAxisVect[1];
    balloonFishBottomFins[5]=resultPoint2301th[2]+0.02*topFinsVect[2]+0.02*middAxisVect[2];
    balloonFishBottomFins[6]=resultPoint2301th[0]-0.05*topFinsVect[0];
    balloonFishBottomFins[7]=resultPoint2301th[1]-0.05*topFinsVect[1];
    balloonFishBottomFins[8]=resultPoint2301th[2]-0.05*topFinsVect[2];
    balloonFishBottomFins[9]=resultPoint2301th[0]+0.02*topFinsVect[0]-0.02*middAxisVect[0];
    balloonFishBottomFins[10]=resultPoint2301th[1]+0.02*topFinsVect[1]-0.02*middAxisVect[1];
    balloonFishBottomFins[11]=resultPoint2301th[2]+0.02*topFinsVect[2]-0.02*middAxisVect[2];
    balloonFishBottomFins[12]=resultPoint2301th[0]+0.03*topFinsVect[0]-0.03*middAxisVect[0];
    balloonFishBottomFins[13]=resultPoint2301th[1]+0.03*topFinsVect[1]-0.03*middAxisVect[1];
    balloonFishBottomFins[14]=resultPoint2301th[2]+0.03*topFinsVect[2]-0.03*middAxisVect[2];
    flyElephantEarBalloonFish.MakeEarPoints(balloonFishBottomFins,2,5,5,101);

}


void BalloonFish::makeOthBsplinePoint(float* bsplineControl0th,float* bsplineControl1th,float* bsplineControl2th,float* bsplineControl3th,float* resultPoint)
{

    float f1 = 1.0/6.0;
    float f2 = 4.0/6.0;
    float f3 = 1.0/6.0;
    float x = f1 * bsplineControl0th[0] + f2 * bsplineControl1th[0] + f3 * bsplineControl2th[0];
    float y = f1 * bsplineControl0th[1] + f2 * bsplineControl1th[1] + f3 * bsplineControl2th[1];
    float z = f1 * bsplineControl0th[2] + f2 * bsplineControl1th[2] + f3 * bsplineControl2th[2];
    resultPoint[0] = x;
    resultPoint[1] = y;
    resultPoint[2] = z;

}

void BalloonFish::point2lineVertPoint(float* bezierPoint, float* baseLineVect, int bezierIndex)
{
    //当前贝塞尔的点到中间轴顶点的斜边向量
    float pointVect[] = {bezierPoint[0]-middAxisPoints[3], bezierPoint[1]-middAxisPoints[4],bezierPoint[2]-middAxisPoints[5]};
    WizardGeomSupple::normalize(pointVect);
    //斜边和中间线之间的向量夹角余弦值
    float coseValue = (baseLineVect[0] * pointVect[0] + baseLineVect[1] * pointVect[1] + baseLineVect[2] * pointVect[2]) /
                      (sqrt(baseLineVect[0] * baseLineVect[0] + baseLineVect[1] * baseLineVect[1] + baseLineVect[2] * baseLineVect[2]))*
                      (sqrt(pointVect[0] * pointVect[0] + pointVect[1] * pointVect[1] + pointVect[2] * pointVect[2]));
    //斜边长度
    float bevelLeng = sqrt((middAxisPoints[3] - bezierPoint[0])*(middAxisPoints[3] - bezierPoint[0]) +
                           (middAxisPoints[4] - bezierPoint[1])*(middAxisPoints[4] - bezierPoint[1]) +
                           (middAxisPoints[5] - bezierPoint[2])*(middAxisPoints[5] - bezierPoint[2]));
    float dis = bevelLeng * coseValue;
    //中间线顶点沿中间线移动距离后的点
    float purpX=middAxisPoints[3]+dis*baseLineVect[0];
    float purpY=middAxisPoints[4]+dis*baseLineVect[1];
    float purpZ=middAxisPoints[5]+dis*baseLineVect[2];
    bezierVertBaseLinePointsBalloonFish[bezierIndex*3]=purpX;
    bezierVertBaseLinePointsBalloonFish[bezierIndex*3+1]=purpY;
    bezierVertBaseLinePointsBalloonFish[bezierIndex*3+2]=purpZ;
}

void BalloonFish::makeUpBezierLine(float* bezPointGather,float* splitPoints, int sectionNum,int degreeSplitNum,int bezierStep)
{

    //按度数切分圆的个数
    int degSplNum = degreeSplitNum;
    int compBPNum = sectionNum - 1;
    float bezFract = 1.0 / (bezierStep*1.0);
    //循环每个点
    for (int row = 0; row < degSplNum; row++)
    {
        for (int i = 0; i <= bezierStep; i++)
        {
            //在bezier曲线上的节点的百分数
            float bezFractValue = i*bezFract;
            if (bezFractValue > 1){
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


}

//介乘
int BalloonFish::factrial(int factrialCount)
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



void BalloonFish::drawBalloonFishPoints(int blineSplitNum,int tag)
{

    GLuint flyElephantEarProgram = shaderUtilBalloonFish.getBalloonFishProgram();
    glUseProgram(flyElephantEarProgram);
    glEnable(GL_DEPTH_TEST);
    GLuint projectionMatrixLocation = glGetUniformLocation(flyElephantEarProgram,"ProjectionMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(flyElephantEarProgram,"ViewMatrix");
    GLuint modelMatrixLocation = glGetUniformLocation(flyElephantEarProgram,"ModelMatrix");
    GLuint lightPositionLocation = glGetUniformLocation(flyElephantEarProgram,"lightPosition");
    flyElephantBalloonFish.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint eyeEarMouthTagLocation = glGetUniformLocation(flyElephantEarProgram,"eyeEarMouthTag");
    glUniform1i(eyeEarMouthTagLocation,tag);
    GLuint blineSplitLocation = glGetUniformLocation(flyElephantEarProgram, "blineSplit");
    glUniform1f(blineSplitLocation,float(blineSplitNum));
    GLuint blinePoints1Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints1");
    GLuint blinePoints2Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints2");
    GLuint blinePoints3Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints3");
    GLuint blinePoints4Location = glGetAttribLocation(flyElephantEarProgram, "blinePoints4");
    GLuint blinePercentLocation = glGetAttribLocation(flyElephantEarProgram, "blinePercent");


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

    GLuint texcoordLocation=glGetAttribLocation(flyElephantEarProgram,"texcoord");
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoordGatherBalloonFish);
    glEnableVertexAttribArray(texcoordLocation);


    GLuint balloonFishTextureLocation=glGetUniformLocation(flyElephantEarProgram,"U_Texture");//U_Texture
    glActiveTexture(GL_TEXTURE0);
    if(tag==100){
        glBindTexture(GL_TEXTURE_2D, getCoralTextureList()[6]);
    }else{
        glBindTexture(GL_TEXTURE_2D, getCoralTextureList()[7]);
    }
    glUniform1i(balloonFishTextureLocation, 0);


    //glDrawArrays(GL_POINTS, 0, 300);
    glDrawArrays(GL_TRIANGLES, 0, blineSplitNum*(bezierDegreeSplitNum+1)*bezierStep*6);
    glUseProgram(0);

    std::memset(shaderPointsBalloonFish1,0,600000*sizeof(float));
    std::memset(shaderPointsBalloonFish2,0,600000*sizeof(float));
    std::memset(shaderPointsBalloonFish3,0,600000*sizeof(float));
    std::memset(shaderPointsBalloonFish4,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFish1,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFish2,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFish3,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFish4,0,600000*sizeof(float));
    std::memset(blineIndicesFEBalloonFish,0,30000*sizeof(float));
    //std::memset(blpoints,0,300*sizeof(float));
}

////////////////////////////////////////////////////////////////////////
/////////刺豚的刺/////////////
void BalloonFish::makeBalloonFishSTABPoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotal,int tag)
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

                shaderPointsBalloonFishSTAB1[currentBlineIndex] = blineContPoints[currCPUIndex + listIndex * 3];
                shaderPointsBalloonFishSTAB1[currentBlineIndex + 1] = blineContPoints[currCPUIndex + listIndex * 3 + 1];
                shaderPointsBalloonFishSTAB1[currentBlineIndex + 2] = blineContPoints[currCPUIndex + listIndex * 3 + 2];

                shaderPointsBalloonFishSTAB2[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 1) * 3];
                shaderPointsBalloonFishSTAB2[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 1];
                shaderPointsBalloonFishSTAB2[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 1) * 3 + 2];

                shaderPointsBalloonFishSTAB3[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 2) * 3];
                shaderPointsBalloonFishSTAB3[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 1];
                shaderPointsBalloonFishSTAB3[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 2) * 3 + 2];

                shaderPointsBalloonFishSTAB4[currentBlineIndex] = blineContPoints[currCPUIndex + (listIndex + 3) * 3];
                shaderPointsBalloonFishSTAB4[currentBlineIndex + 1] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 1];
                shaderPointsBalloonFishSTAB4[currentBlineIndex + 2] = blineContPoints[currCPUIndex + (listIndex + 3) * 3 + 2];

            }
        }

    }

    //在GPU里构建面片
    int currentGPUIndex = 0;
    int evenum = 3;
    int everyFullBlineTotal = blineSplitTotal * (listTotal - 3);
    for (int rowIndex = 0; rowIndex < rowTotal - 1; rowIndex++)
    {
        if(rowIndex%2==1){
            continue;
        }
        for (int pointIndex = 0; pointIndex < everyFullBlineTotal-blineSplitTotal; pointIndex++)
        {
            int currPointIndex1th = (rowIndex*everyFullBlineTotal+pointIndex)*3;
            int currPointIndex2th = ((rowIndex+1)*everyFullBlineTotal+pointIndex)*3;
            int currPointIndex3th = (rowIndex*everyFullBlineTotal+(pointIndex+1))*3;
            int currPointIndex4th = ((rowIndex+1)*everyFullBlineTotal+(pointIndex+1))*3;
            int GPUXIndex=currentGPUIndex*evenum;
            int GPUYIndex=GPUXIndex+1;
            int GPUZIndex=GPUXIndex+2;
            trueShaderPointsBalloonFishSTAB1[GPUXIndex] = shaderPointsBalloonFishSTAB1[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB1[GPUYIndex] = shaderPointsBalloonFishSTAB1[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB1[GPUZIndex] = shaderPointsBalloonFishSTAB1[currPointIndex1th + 2];
            trueShaderPointsBalloonFishSTAB2[GPUXIndex] = shaderPointsBalloonFishSTAB2[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB2[GPUYIndex] = shaderPointsBalloonFishSTAB2[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB2[GPUZIndex] = shaderPointsBalloonFishSTAB2[currPointIndex1th + 2];
            trueShaderPointsBalloonFishSTAB3[GPUXIndex] = shaderPointsBalloonFishSTAB3[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB3[GPUYIndex] = shaderPointsBalloonFishSTAB3[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB3[GPUZIndex] = shaderPointsBalloonFishSTAB3[currPointIndex1th + 2];
            trueShaderPointsBalloonFishSTAB4[GPUXIndex] = shaderPointsBalloonFishSTAB4[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB4[GPUYIndex] = shaderPointsBalloonFishSTAB4[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB4[GPUZIndex] = shaderPointsBalloonFishSTAB4[currPointIndex1th + 2];
            blineIndicesFEBalloonFishSTAB[GPUXIndex] = float(pointIndex % blineSplitTotal);
            blineIndicesFEBalloonFishSTAB[GPUYIndex] = float(rowIndex);
            blineIndicesFEBalloonFishSTAB[GPUZIndex] = 0.0;

            int texcoordSIndex=currentGPUIndex*2;
            int texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFishSTAB[texcoordSIndex]=rowIndex/rowTotal;
            texcoordGatherBalloonFishSTAB[texcoordTIndex]=pointIndex/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPointsBalloonFishSTAB1[GPUXIndex] = shaderPointsBalloonFishSTAB1[currPointIndex2th];
            trueShaderPointsBalloonFishSTAB1[GPUYIndex] = shaderPointsBalloonFishSTAB1[currPointIndex2th + 1];
            trueShaderPointsBalloonFishSTAB1[GPUZIndex] = shaderPointsBalloonFishSTAB1[currPointIndex2th + 2];
            trueShaderPointsBalloonFishSTAB2[GPUXIndex] = shaderPointsBalloonFishSTAB2[currPointIndex2th];
            trueShaderPointsBalloonFishSTAB2[GPUYIndex] = shaderPointsBalloonFishSTAB2[currPointIndex2th + 1];
            trueShaderPointsBalloonFishSTAB2[GPUZIndex] = shaderPointsBalloonFishSTAB2[currPointIndex2th + 2];
            trueShaderPointsBalloonFishSTAB3[GPUXIndex] = shaderPointsBalloonFishSTAB3[currPointIndex2th];
            trueShaderPointsBalloonFishSTAB3[GPUYIndex] = shaderPointsBalloonFishSTAB3[currPointIndex2th + 1];
            trueShaderPointsBalloonFishSTAB3[GPUZIndex] = shaderPointsBalloonFishSTAB3[currPointIndex2th + 2];
            trueShaderPointsBalloonFishSTAB4[GPUXIndex] = shaderPointsBalloonFishSTAB4[currPointIndex2th];
            trueShaderPointsBalloonFishSTAB4[GPUYIndex] = shaderPointsBalloonFishSTAB4[currPointIndex2th + 1];
            trueShaderPointsBalloonFishSTAB4[GPUZIndex] = shaderPointsBalloonFishSTAB4[currPointIndex2th + 2];
            blineIndicesFEBalloonFishSTAB[GPUXIndex] = float(pointIndex % blineSplitTotal);
            blineIndicesFEBalloonFishSTAB[GPUYIndex] = float(rowIndex+1);
            blineIndicesFEBalloonFishSTAB[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFishSTAB[texcoordSIndex]=(rowIndex+1)/rowTotal;
            texcoordGatherBalloonFishSTAB[texcoordTIndex]=pointIndex/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPointsBalloonFishSTAB1[GPUXIndex] = shaderPointsBalloonFishSTAB1[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB1[GPUYIndex] = shaderPointsBalloonFishSTAB1[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB1[GPUZIndex] = shaderPointsBalloonFishSTAB1[currPointIndex4th + 2];
            trueShaderPointsBalloonFishSTAB2[GPUXIndex] = shaderPointsBalloonFishSTAB2[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB2[GPUYIndex] = shaderPointsBalloonFishSTAB2[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB2[GPUZIndex] = shaderPointsBalloonFishSTAB2[currPointIndex4th + 2];
            trueShaderPointsBalloonFishSTAB3[GPUXIndex] = shaderPointsBalloonFishSTAB3[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB3[GPUYIndex] = shaderPointsBalloonFishSTAB3[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB3[GPUZIndex] = shaderPointsBalloonFishSTAB3[currPointIndex4th + 2];
            trueShaderPointsBalloonFishSTAB4[GPUXIndex] = shaderPointsBalloonFishSTAB4[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB4[GPUYIndex] = shaderPointsBalloonFishSTAB4[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB4[GPUZIndex] = shaderPointsBalloonFishSTAB4[currPointIndex4th + 2];
            blineIndicesFEBalloonFishSTAB[GPUXIndex] = float((pointIndex + 1) % blineSplitTotal);
            blineIndicesFEBalloonFishSTAB[GPUYIndex] = float(rowIndex+1);
            blineIndicesFEBalloonFishSTAB[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFishSTAB[texcoordSIndex]=(rowIndex+1)/rowTotal;
            texcoordGatherBalloonFishSTAB[texcoordTIndex]=(pointIndex+1)/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPointsBalloonFishSTAB1[GPUXIndex] = shaderPointsBalloonFishSTAB1[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB1[GPUYIndex] = shaderPointsBalloonFishSTAB1[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB1[GPUZIndex] = shaderPointsBalloonFishSTAB1[currPointIndex1th + 2];
            trueShaderPointsBalloonFishSTAB2[GPUXIndex] = shaderPointsBalloonFishSTAB2[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB2[GPUYIndex] = shaderPointsBalloonFishSTAB2[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB2[GPUZIndex] = shaderPointsBalloonFishSTAB2[currPointIndex1th + 2];
            trueShaderPointsBalloonFishSTAB3[GPUXIndex] = shaderPointsBalloonFishSTAB3[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB3[GPUYIndex] = shaderPointsBalloonFishSTAB3[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB3[GPUZIndex] = shaderPointsBalloonFishSTAB3[currPointIndex1th + 2];
            trueShaderPointsBalloonFishSTAB4[GPUXIndex] = shaderPointsBalloonFishSTAB4[currPointIndex1th];
            trueShaderPointsBalloonFishSTAB4[GPUYIndex] = shaderPointsBalloonFishSTAB4[currPointIndex1th + 1];
            trueShaderPointsBalloonFishSTAB4[GPUZIndex] = shaderPointsBalloonFishSTAB4[currPointIndex1th + 2];
            blineIndicesFEBalloonFishSTAB[GPUXIndex] = float(pointIndex % blineSplitTotal);
            blineIndicesFEBalloonFishSTAB[GPUYIndex] = float(rowIndex);
            blineIndicesFEBalloonFishSTAB[GPUZIndex] = float(rowIndex)/2.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFishSTAB[texcoordSIndex]=(rowIndex)/rowTotal;
            texcoordGatherBalloonFishSTAB[texcoordTIndex]=(pointIndex)/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPointsBalloonFishSTAB1[GPUXIndex] = shaderPointsBalloonFishSTAB1[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB1[GPUYIndex] = shaderPointsBalloonFishSTAB1[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB1[GPUZIndex] = shaderPointsBalloonFishSTAB1[currPointIndex4th + 2];
            trueShaderPointsBalloonFishSTAB2[GPUXIndex] = shaderPointsBalloonFishSTAB2[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB2[GPUYIndex] = shaderPointsBalloonFishSTAB2[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB2[GPUZIndex] = shaderPointsBalloonFishSTAB2[currPointIndex4th + 2];
            trueShaderPointsBalloonFishSTAB3[GPUXIndex] = shaderPointsBalloonFishSTAB3[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB3[GPUYIndex] = shaderPointsBalloonFishSTAB3[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB3[GPUZIndex] = shaderPointsBalloonFishSTAB3[currPointIndex4th + 2];
            trueShaderPointsBalloonFishSTAB4[GPUXIndex] = shaderPointsBalloonFishSTAB4[currPointIndex4th];
            trueShaderPointsBalloonFishSTAB4[GPUYIndex] = shaderPointsBalloonFishSTAB4[currPointIndex4th + 1];
            trueShaderPointsBalloonFishSTAB4[GPUZIndex] = shaderPointsBalloonFishSTAB4[currPointIndex4th + 2];
            blineIndicesFEBalloonFishSTAB[GPUXIndex] = float((pointIndex + 1) % blineSplitTotal);
            blineIndicesFEBalloonFishSTAB[GPUYIndex] = float(rowIndex+1);
            blineIndicesFEBalloonFishSTAB[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFishSTAB[texcoordSIndex]=(rowIndex+1)/rowTotal;
            texcoordGatherBalloonFishSTAB[texcoordTIndex]=(pointIndex+1)/everyFullBlineTotal;


            currentGPUIndex++;
            GPUXIndex=currentGPUIndex*evenum;
            GPUYIndex=GPUXIndex+1;
            GPUZIndex=GPUXIndex+2;
            trueShaderPointsBalloonFishSTAB1[GPUXIndex] = shaderPointsBalloonFishSTAB1[currPointIndex3th];
            trueShaderPointsBalloonFishSTAB1[GPUYIndex] = shaderPointsBalloonFishSTAB1[currPointIndex3th + 1];
            trueShaderPointsBalloonFishSTAB1[GPUZIndex] = shaderPointsBalloonFishSTAB1[currPointIndex3th + 2];
            trueShaderPointsBalloonFishSTAB2[GPUXIndex] = shaderPointsBalloonFishSTAB2[currPointIndex3th];
            trueShaderPointsBalloonFishSTAB2[GPUYIndex] = shaderPointsBalloonFishSTAB2[currPointIndex3th + 1];
            trueShaderPointsBalloonFishSTAB2[GPUZIndex] = shaderPointsBalloonFishSTAB2[currPointIndex3th + 2];
            trueShaderPointsBalloonFishSTAB3[GPUXIndex] = shaderPointsBalloonFishSTAB3[currPointIndex3th];
            trueShaderPointsBalloonFishSTAB3[GPUYIndex] = shaderPointsBalloonFishSTAB3[currPointIndex3th + 1];
            trueShaderPointsBalloonFishSTAB3[GPUZIndex] = shaderPointsBalloonFishSTAB3[currPointIndex3th + 2];
            trueShaderPointsBalloonFishSTAB4[GPUXIndex] = shaderPointsBalloonFishSTAB4[currPointIndex3th];
            trueShaderPointsBalloonFishSTAB4[GPUYIndex] = shaderPointsBalloonFishSTAB4[currPointIndex3th + 1];
            trueShaderPointsBalloonFishSTAB4[GPUZIndex] = shaderPointsBalloonFishSTAB4[currPointIndex3th + 2];
            blineIndicesFEBalloonFishSTAB[GPUXIndex] = float((pointIndex + 1) % blineSplitTotal);
            blineIndicesFEBalloonFishSTAB[GPUYIndex] = float(rowIndex);
            blineIndicesFEBalloonFishSTAB[GPUZIndex] = 0.0;

            texcoordSIndex=currentGPUIndex*2;
            texcoordTIndex=texcoordSIndex+1;
            texcoordGatherBalloonFishSTAB[texcoordSIndex]=(rowIndex)/rowTotal;
            texcoordGatherBalloonFishSTAB[texcoordTIndex]=(pointIndex+1)/everyFullBlineTotal;
            currentGPUIndex++;

        }

    }

    BalloonFish::drawBalloonFishSTABPoints(blineSplitTotal,tag);
}


void BalloonFish::drawBalloonFishSTABPoints(int blineSplitTotal,int tag)
{

    GLuint balloonFishSTABProgram = shaderUtilBalloonFish.getBalloonFishSTABProgram();
    glUseProgram(balloonFishSTABProgram);
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式
    GLuint projectionMatrixLocation = glGetUniformLocation(balloonFishSTABProgram,"ProjectionMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(balloonFishSTABProgram,"ViewMatrix");
    GLuint modelMatrixLocation = glGetUniformLocation(balloonFishSTABProgram,"ModelMatrix");
    GLuint lightPositionLocation = glGetUniformLocation(balloonFishSTABProgram,"lightPosition");
    flyElephantBalloonFish.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint eyeEarMouthTagLocation = glGetUniformLocation(balloonFishSTABProgram,"eyeEarMouthTag");
    glUniform1i(eyeEarMouthTagLocation,tag);
    GLuint  substractFactorLocation=glGetUniformLocation(balloonFishSTABProgram,"substractFactor");
    glUniform1f(substractFactorLocation,float(stabSubstractFactor));

    GLuint blineSplitLocation = glGetUniformLocation(balloonFishSTABProgram, "blineSplit");
    glUniform1f(blineSplitLocation,float(blineSplitTotal));
    GLuint blinePoints1Location = glGetAttribLocation(balloonFishSTABProgram, "blinePoints1");
    GLuint blinePoints2Location = glGetAttribLocation(balloonFishSTABProgram, "blinePoints2");
    GLuint blinePoints3Location = glGetAttribLocation(balloonFishSTABProgram, "blinePoints3");
    GLuint blinePoints4Location = glGetAttribLocation(balloonFishSTABProgram, "blinePoints4");
    GLuint blinePercentLocation = glGetAttribLocation(balloonFishSTABProgram, "blinePercent");


    glVertexAttribPointer(blinePoints1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFishSTAB1);
    glEnableVertexAttribArray(blinePoints1Location);
    glVertexAttribPointer(blinePoints2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFishSTAB2);
    glEnableVertexAttribArray(blinePoints2Location);
    glVertexAttribPointer(blinePoints3Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFishSTAB3);
    glEnableVertexAttribArray(blinePoints3Location);
    glVertexAttribPointer(blinePoints4Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, trueShaderPointsBalloonFishSTAB4);
    glEnableVertexAttribArray(blinePoints4Location);
    glVertexAttribPointer(blinePercentLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blineIndicesFEBalloonFishSTAB);
    glEnableVertexAttribArray(blinePercentLocation);
    //glDrawArrays(GL_POINTS, 0, 6000);
    glDrawArrays(GL_TRIANGLES, 0, 100*(4+1)*20*6/2);
    //glDisable(GL_BLEND);
    glUseProgram(0);

    std::memset(shaderPointsBalloonFishSTAB1,0,600000*sizeof(float));
    std::memset(shaderPointsBalloonFishSTAB2,0,600000*sizeof(float));
    std::memset(shaderPointsBalloonFishSTAB3,0,600000*sizeof(float));
    std::memset(shaderPointsBalloonFishSTAB4,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFishSTAB1,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFishSTAB2,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFishSTAB3,0,600000*sizeof(float));
    std::memset(trueShaderPointsBalloonFishSTAB4,0,600000*sizeof(float));
    std::memset(blineIndicesFEBalloonFishSTAB,0,30000*sizeof(float));
    //std::memset(blpoints,0,300*sizeof(float));
}