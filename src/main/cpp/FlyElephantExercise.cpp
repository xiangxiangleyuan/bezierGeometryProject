#include "FlyElephantExercise.h"


WizardGeom wizardGeomFlyElephantExercise;
WizardGeomSupple wizardGeomSuppleFlyElephantExercise;
FlyElephantExercise flyElephantExerciseSelf;
float FlyElephantExercise::bezierVertBaseLinePoints[150];
BezierBspline bezierBsplineFlyElephantExercise;


FlyElephantExercise::FlyElephantExercise() {};
FlyElephantExercise::~FlyElephantExercise() {};
float FlyElephantExercise::frontLine[6];
float FlyElephantExercise::frontDirectNor[3];
//需要旋转的总次数
int FlyElephantExercise::rotateCountTotal=0;
//飞象章鱼旋转的次数指针
int FlyElephantExercise::flyElephantCount=0;
bool FlyElephantExercise::isInverseRotate=false;
////////飞象前进幅度的控制////////////////////
float FlyElephantExercise::moveLeng=0.001;
float FlyElephantExercise::moveUpDownLeng=0.0;
bool FlyElephantExercise::isMoveUp=true;
float FlyElephantExercise::moveLengSubstracFactor=0.00002;
//////////////////////////

void FlyElephantExercise::getFrontDirectVect(){
    WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(1);
    float* bezPointGather = synthPoint->bezPointGather;
    float* baseData = synthPoint->baseData;
    float baseVect[] = { baseData[0] - baseData[3], baseData[1] - baseData[4], baseData[2] - baseData[5] };
    WizardGeomSupple::normalize(baseVect);

    int bezierPointIndex = 5;
    float point[] = { bezPointGather[bezierPointIndex * 3], bezPointGather[bezierPointIndex * 3 + 1], bezPointGather[bezierPointIndex * 3 + 2] };
    point2lineVertPoint(point, baseVect, bezierPointIndex);

    int degreeIndex = 12;
    int bezierPIndex = (degreeIndex * synthPoint->bezierStep + bezierPointIndex) * 3;
    int currBezierPointIndex = bezierPointIndex * 3;
    //中间线上的垂点
    float vertX = bezierVertBaseLinePoints[currBezierPointIndex];
    float vertY = bezierVertBaseLinePoints[currBezierPointIndex + 1];
    float vertZ = bezierVertBaseLinePoints[currBezierPointIndex + 2];

    float currX = bezPointGather[bezierPIndex];
    float currY = bezPointGather[bezierPIndex + 1];
    float currZ = bezPointGather[bezierPIndex + 2];

    frontDirectNor[0]=currX-vertX;
    frontDirectNor[1]=currY-vertY;
    frontDirectNor[2]=currZ-vertZ;
    WizardGeomSupple::normalize(frontDirectNor);
//    LOGD("-=-=-=-=-=-=%f %f %f ...",frontDirectNor[0],frontDirectNor[1],frontDirectNor[2]);

}


void FlyElephantExercise::rotateByBaseLine(float rotateAngle)
{
    if(flyElephantCount++>rotateCountTotal){
        flyElephantCount=0;
        rotateCountTotal=0;
        return;
    }

    if(rotateCountTotal==0){
        flyElephantCount=0;
        return;
    }

    for(int i=0;i<2;i++){
        WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(i);
        float* bezPointGather = synthPoint->bezPointGather;
        float* baseData = synthPoint->baseData;
        float baseVect[] = { baseData[0] - baseData[3], baseData[1] - baseData[4], baseData[2] - baseData[5] };
        WizardGeomSupple::normalize(baseVect);

        for (int i = 0; i < synthPoint->bezierStep; i++)
        {
            float point[] = { bezPointGather[i * 3], bezPointGather[i * 3 + 1], bezPointGather[i * 3 + 2] };
            point2lineVertPoint(point, baseVect, i);
        }

        for (int degreeIndex = 0; degreeIndex < synthPoint->degreeSplitNum; degreeIndex++)
        {
            for (int bezierPointIndex = 1; bezierPointIndex < synthPoint->bezierStep; bezierPointIndex++)
            {
                int bezierPIndex = (degreeIndex * synthPoint->bezierStep + bezierPointIndex) * 3;
                int currBezierPointIndex = bezierPointIndex * 3;
                //中间线上的垂点
                float vertX = bezierVertBaseLinePoints[currBezierPointIndex];
                float vertY = bezierVertBaseLinePoints[currBezierPointIndex + 1];
                float vertZ = bezierVertBaseLinePoints[currBezierPointIndex + 2];

                float currX = bezPointGather[bezierPIndex];
                float currY = bezPointGather[bezierPIndex + 1];
                float currZ = bezPointGather[bezierPIndex + 2];

                //中间线上的垂直向量
                float bezier2vertX = currX - vertX;
                float bezier2vertY = currY - vertY;
                float bezier2vertZ = currZ - vertZ;
                //中间线上的垂点到当前点的距离
                float bezier2vertLeng = sqrt(bezier2vertX*bezier2vertX + bezier2vertY*bezier2vertY + bezier2vertZ*bezier2vertZ);


                float* rotateResult = flyElephantExerciseSelf.rotateByBaseLine(currX, currY, currZ, vertX, vertY, vertZ, rotateAngle, isInverseRotate);
                bezPointGather[bezierPIndex] = rotateResult[0];
                bezPointGather[bezierPIndex + 1] = rotateResult[1];
                bezPointGather[bezierPIndex + 2] = rotateResult[2];

                if(i==1&&degreeIndex==12&&bezierPointIndex==5){
                    frontDirectNor[0]=currX-vertX;
                    frontDirectNor[1]=currY-vertY;
                    frontDirectNor[2]=currZ-vertZ;
                    WizardGeomSupple::normalize(frontDirectNor);
                    frontLine[0]=vertX;frontLine[1]=vertY;frontLine[2]=vertZ;
                    frontLine[3]=currX+0.3*frontDirectNor[0];
                    frontLine[4]=currY+0.3*frontDirectNor[1];
                    frontLine[5]=currZ+0.3*frontDirectNor[2];
                }

            }

        }

    }
    //贝塞尔控制点的旋转
    WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(1);
    float* splitPoints = synthPoint->splitPoints;
    for (int baseIndex = 0; baseIndex < synthPoint->baseDataPercentNum; baseIndex++)
    {
        for (int degreeIndex = 0; degreeIndex < synthPoint->degreeSplitNum; degreeIndex++)
        {
            int everyCircleIndex = (baseIndex * synthPoint->degreeSplitNum + degreeIndex) * 3;
            float currX = splitPoints[everyCircleIndex];
            float currY = splitPoints[everyCircleIndex + 1];
            float currZ = splitPoints[everyCircleIndex + 2];

            float vertX = WizardGeomSupple::baseLinePercentPoints[baseIndex * 3];
            float vertY = WizardGeomSupple::baseLinePercentPoints[baseIndex * 3 + 1];
            float vertZ = WizardGeomSupple::baseLinePercentPoints[baseIndex * 3 + 2];
            float* rotateResult = flyElephantExerciseSelf.rotateByBaseLine(currX, currY, currZ, vertX, vertY, vertZ, rotateAngle, isInverseRotate);
            splitPoints[everyCircleIndex] = rotateResult[0];
            splitPoints[everyCircleIndex + 1] = rotateResult[1];
            splitPoints[everyCircleIndex + 2] = rotateResult[2];

        }

    }


}

void FlyElephantExercise::frontMove(){
    WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(1);
    float moveVectNor[]={frontDirectNor[0],frontDirectNor[1],frontDirectNor[2]};

    //说明还在转动
    if(rotateCountTotal>0||moveLeng==0.0){
        return;
    }
    //如果检测到两者碰撞就不再位移
    if(BalloonFlyFishCollisionDetection::isCollisionDetectionAfter&&
    (BalloonFish::isCollDeteAfterIndexAdd&&BalloonFish::collDeteAfterIndex<30)&&
    BalloonFish::stabSubstractFactor>0.1){
        moveLeng=0.0;
    }

    moveLeng-=moveLengSubstracFactor;
    if(moveLeng<0.0){
        moveLeng=0.0;
    }

    //如果被刺豚刺到了
    if(BalloonFish::isPrick){
        //刺到后还在运动中
        if(moveLeng>0.0){
//            moveVectNor[0]=-moveVectNor[0];
//            moveVectNor[1]=-moveVectNor[1];
//            moveVectNor[2]=-moveVectNor[2];
            moveVectNor[0]=BalloonFlyFishCollisionDetection::tempFrontMoveVect[0];
            moveVectNor[1]=BalloonFlyFishCollisionDetection::tempFrontMoveVect[1];
            moveVectNor[2]=BalloonFlyFishCollisionDetection::tempFrontMoveVect[2];

        }else{
            //刺豚刺到后运动结束
            BalloonFish::isPrick=false;
            moveLengSubstracFactor=0.00002;
        }


    }
    //飞象章鱼活动的界限
    if(synthPoint->baseData[5]>2.0||synthPoint->baseData[5]<0.3){
        moveLeng=-moveLeng;
    }
    FlyElephantExercise::moveByPrickVect(moveVectNor);

//    FlyElephantExercise::moveByPrickVect(moveVectNor);


//    for(int i=0;i<2;i++){
//        WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(i);
//        float* bezPointGather = synthPoint->bezPointGather;
//        for (int degreeIndex = 0; degreeIndex < synthPoint->degreeSplitNum; degreeIndex++)
//        {
//            for (int bezierPointIndex = 0; bezierPointIndex < synthPoint->bezierStep; bezierPointIndex++)
//            {
//                int bezierPIndex = (degreeIndex * synthPoint->bezierStep + bezierPointIndex) * 3;
//                bezPointGather[bezierPIndex]+=(moveLeng*moveVectNor[0]);
//                bezPointGather[bezierPIndex + 1]+=(moveLeng*moveVectNor[1]);
//                bezPointGather[bezierPIndex + 2]+=(moveLeng*moveVectNor[2]);
//
//            }
//
//        }
//    }
//
//    float* splitPoints = synthPoint->splitPoints;
//    for (int baseIndex = 0; baseIndex < synthPoint->baseDataPercentNum; baseIndex++)
//    {
//        for (int degreeIndex = 0; degreeIndex < synthPoint->degreeSplitNum; degreeIndex++)
//        {
//            int everyCircleIndex = (baseIndex * synthPoint->degreeSplitNum + degreeIndex) * 3;
//
//            splitPoints[everyCircleIndex]+=(moveLeng*moveVectNor[0]);
//            splitPoints[everyCircleIndex + 1]+=(moveLeng*moveVectNor[1]);
//            splitPoints[everyCircleIndex + 2]+=(moveLeng*moveVectNor[2]);
//
//        }
//
//    }
//    {
//        synthPoint->baseData[0]+=(moveLeng*moveVectNor[0]);
//        synthPoint->baseData[1]+=(moveLeng*moveVectNor[1]);
//        synthPoint->baseData[2]+=(moveLeng*moveVectNor[2]);
//        synthPoint->baseData[3]+=(moveLeng*moveVectNor[0]);
//        synthPoint->baseData[4]+=(moveLeng*moveVectNor[1]);
//        synthPoint->baseData[5]+=(moveLeng*moveVectNor[2]);
//
//        FlyElephant::lightPosition[0]+=(moveLeng*moveVectNor[0]);
//        FlyElephant::lightPosition[1]+=(moveLeng*moveVectNor[1]);
//        FlyElephant::lightPosition[2]+=(moveLeng*moveVectNor[2]);
//
//    }
//
//    for(int i=0;i<8;i++){
//        WizardGeomSupple::baseLinePercentPoints[i*3]+=(moveLeng*moveVectNor[0]);
//        WizardGeomSupple::baseLinePercentPoints[i*3+1]+=(moveLeng*moveVectNor[1]);
//        WizardGeomSupple::baseLinePercentPoints[i*3+2]+=(moveLeng*moveVectNor[2]);
//    }

}

void FlyElephantExercise::moveByPrickVect(float* moveVectNor){
    WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(1);

    for(int i=0;i<2;i++){
        WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(i);
        float* bezPointGather = synthPoint->bezPointGather;
        for (int degreeIndex = 0; degreeIndex < synthPoint->degreeSplitNum; degreeIndex++)
        {
            for (int bezierPointIndex = 0; bezierPointIndex < synthPoint->bezierStep; bezierPointIndex++)
            {
                int bezierPIndex = (degreeIndex * synthPoint->bezierStep + bezierPointIndex) * 3;
                bezPointGather[bezierPIndex]+=(moveLeng*moveVectNor[0]);
                bezPointGather[bezierPIndex + 1]+=(moveLeng*moveVectNor[1]);
                bezPointGather[bezierPIndex + 2]+=(moveLeng*moveVectNor[2]);

            }

        }
    }

    float* splitPoints = synthPoint->splitPoints;
    for (int baseIndex = 0; baseIndex < synthPoint->baseDataPercentNum; baseIndex++)
    {
        for (int degreeIndex = 0; degreeIndex < synthPoint->degreeSplitNum; degreeIndex++)
        {
            int everyCircleIndex = (baseIndex * synthPoint->degreeSplitNum + degreeIndex) * 3;

            splitPoints[everyCircleIndex]+=(moveLeng*moveVectNor[0]);
            splitPoints[everyCircleIndex + 1]+=(moveLeng*moveVectNor[1]);
            splitPoints[everyCircleIndex + 2]+=(moveLeng*moveVectNor[2]);

        }

    }
    {
        synthPoint->baseData[0]+=(moveLeng*moveVectNor[0]);
        synthPoint->baseData[1]+=(moveLeng*moveVectNor[1]);
        synthPoint->baseData[2]+=(moveLeng*moveVectNor[2]);
        synthPoint->baseData[3]+=(moveLeng*moveVectNor[0]);
        synthPoint->baseData[4]+=(moveLeng*moveVectNor[1]);
        synthPoint->baseData[5]+=(moveLeng*moveVectNor[2]);

        FlyElephant::lightPosition[0]+=(moveLeng*moveVectNor[0]);
        FlyElephant::lightPosition[1]+=(moveLeng*moveVectNor[1]);
        FlyElephant::lightPosition[2]+=(moveLeng*moveVectNor[2]);

    }

    for(int i=0;i<8;i++){
        WizardGeomSupple::baseLinePercentPoints[i*3]+=(moveLeng*moveVectNor[0]);
        WizardGeomSupple::baseLinePercentPoints[i*3+1]+=(moveLeng*moveVectNor[1]);
        WizardGeomSupple::baseLinePercentPoints[i*3+2]+=(moveLeng*moveVectNor[2]);
    }
}

void FlyElephantExercise::point2lineVertPoint(float* bezierPoint, float* baseLineVect, int bezierIndex)
{
    WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(1);
    float* baseData = synthPoint->baseData;
    //当前贝塞尔的点到中间轴顶点的斜边向量
    float pointVect[] = {bezierPoint[0]-baseData[3], bezierPoint[1]-baseData[4],bezierPoint[2]-baseData[5]};
    WizardGeomSupple::normalize(pointVect);
    //斜边和中间线之间的向量夹角余弦值
    float coseValue = (baseLineVect[0] * pointVect[0] + baseLineVect[1] * pointVect[1] + baseLineVect[2] * pointVect[2]) /
                      (sqrt(baseLineVect[0] * baseLineVect[0] + baseLineVect[1] * baseLineVect[1] + baseLineVect[2] * baseLineVect[2]))*
                      (sqrt(pointVect[0] * pointVect[0] + pointVect[1] * pointVect[1] + pointVect[2] * pointVect[2]));
    //斜边长度
    float bevelLeng = sqrt((baseData[3] - bezierPoint[0])*(baseData[3] - bezierPoint[0]) +
                           (baseData[4] - bezierPoint[1])*(baseData[4] - bezierPoint[1]) +
                           (baseData[5] - bezierPoint[2])*(baseData[5] - bezierPoint[2]));
    float dis = bevelLeng * coseValue;
    //中间线顶点沿中间线移动距离后的点
    float purpX=baseData[3]+dis*baseLineVect[0];
    float purpY=baseData[4]+dis*baseLineVect[1];
    float purpZ=baseData[5]+dis*baseLineVect[2];
    bezierVertBaseLinePoints[bezierIndex*3]=purpX;
    bezierVertBaseLinePoints[bezierIndex*3+1]=purpY;
    bezierVertBaseLinePoints[bezierIndex*3+2]=purpZ;
}

float result[3];
float* FlyElephantExercise::rotateByBaseLine(float currX, float currY, float currZ, float vertX, float vertY, float vertZ, float rotateAngle, bool isInverse)
{
    WizardGeom* synthPoint = wizardGeomFlyElephantExercise.getCurrWizardGeom(1);
    float* baseData = synthPoint->baseData;
    float baseVect[] = { baseData[0] - baseData[3], baseData[1] - baseData[4], baseData[2] - baseData[5] };
    WizardGeomSupple::normalize(baseVect);

    //中间线上的垂直向量
    float bezier2vertX = currX - vertX;
    float bezier2vertY = currY - vertY;
    float bezier2vertZ = currZ - vertZ;
    //中间线上的垂点到当前点的距离
    float bezier2vertLeng = sqrt(bezier2vertX*bezier2vertX + bezier2vertY*bezier2vertY + bezier2vertZ*bezier2vertZ);
    //移动的向量
    float verticalVect[3];
    wizardGeomSuppleFlyElephantExercise.getVerticalVect(baseVect[0], baseVect[1], baseVect[2], bezier2vertX, bezier2vertY, bezier2vertZ,verticalVect);
    float verticalVectNor[] = { verticalVect[0], verticalVect[1], verticalVect[2] };
    if (isInverse)
    {
        verticalVectNor[0] = -verticalVectNor[0];
        verticalVectNor[1] = -verticalVectNor[1];
        verticalVectNor[2] = -verticalVectNor[2];
    }
    WizardGeomSupple::normalize(verticalVectNor);

    float angle = rotateAngle * 3.1415926 / 180.0f;
    float moveLeng = tanf(angle)*bezier2vertLeng;
    float ppX = currX - moveLeng*verticalVectNor[0];
    float ppY = currY - moveLeng*verticalVectNor[1];
    float ppZ = currZ - moveLeng*verticalVectNor[2];
    //中间线的垂点到位移后点的向量
    float finalVectX = vertX - ppX;
    float finalVectY = vertY - ppY;
    float finalVectZ = vertZ - ppZ;
    float finalVectNor[] = { finalVectX, finalVectY, finalVectZ };
    WizardGeomSupple::normalize(finalVectNor);

    float resultX = vertX - bezier2vertLeng*finalVectNor[0];
    float resultY = vertY - bezier2vertLeng*finalVectNor[1];
    float resultZ = vertZ - bezier2vertLeng*finalVectNor[2];
    //float result[] = {resultX, resultY, resultZ};
    result[0]=resultX;result[1]=resultY;result[2]=resultZ;
    return result;
}


