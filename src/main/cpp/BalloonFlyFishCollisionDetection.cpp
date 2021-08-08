#include "BalloonFlyFishCollisionDetection.h"

BalloonFish balloonFishDetection;
WizardGeom wizardGeomDetection;
GameWorld gameWorldCollisionDetection;
BalloonFlyFishCollisionDetection::BalloonFlyFishCollisionDetection() {}
BalloonFlyFishCollisionDetection::~BalloonFlyFishCollisionDetection() {}
float COLLDETEAPARDIST=0.2782633;
//如果为true就说明检测到两者碰撞了
bool BalloonFlyFishCollisionDetection::isCollisionDetectionAfter=false;
void BalloonFlyFishCollisionDetection::checkCollisionDetection(){

    //用来判断碰撞检测的基点
    float baseLinePercentP3th[]={WizardGeomSupple::baseLinePercentPoints[12],WizardGeomSupple::baseLinePercentPoints[13],WizardGeomSupple::baseLinePercentPoints[14]};
    float drawPoints0th0th[3];
    drawPoints0th0th[0]=BalloonFish::bezierGatherBalloonFish[0];
    drawPoints0th0th[1]=BalloonFish::bezierGatherBalloonFish[1];
    drawPoints0th0th[2]=BalloonFish::bezierGatherBalloonFish[2];
    float drawPoints1th0th[3];
    int currIndex1th0th=(BalloonFish::bezierStep)*3;
    drawPoints1th0th[0]=BalloonFish::bezierGatherBalloonFish[currIndex1th0th];
    drawPoints1th0th[1]=BalloonFish::bezierGatherBalloonFish[currIndex1th0th+1];
    drawPoints1th0th[2]=BalloonFish::bezierGatherBalloonFish[currIndex1th0th+2];
    float drawPoints2th0th[3];
    int currIndex2th0th=(2*BalloonFish::bezierStep)*3;
    drawPoints2th0th[0]=BalloonFish::bezierGatherBalloonFish[currIndex2th0th];
    drawPoints2th0th[1]=BalloonFish::bezierGatherBalloonFish[currIndex2th0th+1];
    drawPoints2th0th[2]=BalloonFish::bezierGatherBalloonFish[currIndex2th0th+2];
    float drawPoints3th0th[3];
    int currIndex3th0th=(3*BalloonFish::bezierStep)*3;
    drawPoints3th0th[0]=BalloonFish::bezierGatherBalloonFish[currIndex3th0th];
    drawPoints3th0th[1]=BalloonFish::bezierGatherBalloonFish[currIndex3th0th+1];
    drawPoints3th0th[2]=BalloonFish::bezierGatherBalloonFish[currIndex3th0th+2];
    float result0th[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th0th,drawPoints0th0th,drawPoints1th0th,drawPoints2th0th,result0th);
    float result0th_[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th0th,drawPoints2th0th,drawPoints1th0th,drawPoints0th0th,result0th_);
    float result0th2baseLineVectX=result0th[0]-baseLinePercentP3th[0];
    float result0th2baseLineVectY=result0th[1]-baseLinePercentP3th[1];
    float result0th2baseLineVectZ=result0th[2]-baseLinePercentP3th[2];
    float result0th2baseLineDistance=sqrtf(result0th2baseLineVectX*result0th2baseLineVectX
            +result0th2baseLineVectY*result0th2baseLineVectY+result0th2baseLineVectZ*result0th2baseLineVectZ);

    float result0th2baseLineVectX_=result0th_[0]-baseLinePercentP3th[0];
    float result0th2baseLineVectY_=result0th_[1]-baseLinePercentP3th[1];
    float result0th2baseLineVectZ_=result0th_[2]-baseLinePercentP3th[2];
    float result0th2baseLineDistance_=sqrtf(result0th2baseLineVectX_*result0th2baseLineVectX_
            +result0th2baseLineVectY_*result0th2baseLineVectY_+result0th2baseLineVectZ_*result0th2baseLineVectZ_);
    if(result0th2baseLineDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(result0th2baseLineDistance_<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th_);
    }
    //根据角度判断碰撞检测
    if(result0th2baseLineDistance<2.0*COLLDETEAPARDIST){
        if(getBaseLine2FrontVectAngle(result0th)>50.0){
            balloonFishDetection.bolloonFishSwellUnconditional();
        }
    }
    if(result0th2baseLineDistance_<2.0*COLLDETEAPARDIST){
        if(getBaseLine2FrontVectAngle(result0th)>50.0){
            balloonFishDetection.bolloonFishSwellUnconditional();
        }
    }
//    drawPointLine(BalloonFish::bezierGatherBalloonFish,BalloonFish::bezierStep*2,true,1.0,1.0,0.0,10.0);

    //检测鱼身的碰撞检测
    checkBalloonFishBodyCollDete(result0th,result0th_);
    //检测鱼尾的碰撞检测
    checkBalloonFishTailCollDete(result0th,result0th_);
    //检测鱼鳍碰撞检测
    checkBalloonFishFinsCollDete(result0th);

}

void BalloonFlyFishCollisionDetection::checkBalloonFishBodyCollDete(float *result0th, float *result0th_){
    float baseLinePercentP3th[]={WizardGeomSupple::baseLinePercentPoints[12],WizardGeomSupple::baseLinePercentPoints[13],WizardGeomSupple::baseLinePercentPoints[14]};

    float drawPoints0th4th[3];
    int currIndex0th4th=4*3;
    drawPoints0th4th[0]=BalloonFish::bezierGatherBalloonFish[currIndex0th4th];
    drawPoints0th4th[1]=BalloonFish::bezierGatherBalloonFish[currIndex0th4th+1];
    drawPoints0th4th[2]=BalloonFish::bezierGatherBalloonFish[currIndex0th4th+2];
    float drawPoints1th4th[3];
    int currIndex1th4th=(BalloonFish::bezierStep+4)*3;
    drawPoints1th4th[0]=BalloonFish::bezierGatherBalloonFish[currIndex1th4th];
    drawPoints1th4th[1]=BalloonFish::bezierGatherBalloonFish[currIndex1th4th+1];
    drawPoints1th4th[2]=BalloonFish::bezierGatherBalloonFish[currIndex1th4th+2];
    float drawPoints2th4th[3];
    int currIndex2th4th=(2*BalloonFish::bezierStep+4)*3;
    drawPoints2th4th[0]=BalloonFish::bezierGatherBalloonFish[currIndex2th4th];
    drawPoints2th4th[1]=BalloonFish::bezierGatherBalloonFish[currIndex2th4th+1];
    drawPoints2th4th[2]=BalloonFish::bezierGatherBalloonFish[currIndex2th4th+2];
    float drawPoints3th4th[3];
    int currIndex3th4th=(3*BalloonFish::bezierStep+4)*3;
    drawPoints3th4th[0]=BalloonFish::bezierGatherBalloonFish[currIndex3th4th];
    drawPoints3th4th[1]=BalloonFish::bezierGatherBalloonFish[currIndex3th4th+1];
    drawPoints3th4th[2]=BalloonFish::bezierGatherBalloonFish[currIndex3th4th+2];
    float result4th[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th4th,drawPoints0th4th,drawPoints1th4th,drawPoints2th4th,result4th);
    float result4th_[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th4th,drawPoints2th4th,drawPoints1th4th,drawPoints0th4th,result4th_);
    float result4th2baseLineVectX=result4th[0]-baseLinePercentP3th[0];
    float result4th2baseLineVectY=result4th[1]-baseLinePercentP3th[1];
    float result4th2baseLineVectZ=result4th[2]-baseLinePercentP3th[2];
    float result4th2baseLineDistance=sqrtf(result4th2baseLineVectX*result4th2baseLineVectX
                                           +result4th2baseLineVectY*result4th2baseLineVectY+result4th2baseLineVectZ*result4th2baseLineVectZ);
    float result4th2baseLineVectX_=result4th_[0]-baseLinePercentP3th[0];
    float result4th2baseLineVectY_=result4th_[1]-baseLinePercentP3th[1];
    float result4th2baseLineVectZ_=result4th_[2]-baseLinePercentP3th[2];
    float result4th2baseLineDistance_=sqrtf(result4th2baseLineVectX_*result4th2baseLineVectX_
                                            +result4th2baseLineVectY_*result4th2baseLineVectY_+result4th2baseLineVectZ_*result4th2baseLineVectZ_);
    if(result4th2baseLineDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(result4th2baseLineDistance_<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th_);
    }
//    makeUpBlinePointTh(drawPoints0th4th,drawPoints3th4th,drawPoints2th4th,drawPoints1th4th,10,5);

    /////////////////////////////////////////////////////////
    float drawPoints0th8th[3];
    int currIndex0th8th=8*3;
    drawPoints0th8th[0]=BalloonFish::bezierGatherBalloonFish[currIndex0th8th];
    drawPoints0th8th[1]=BalloonFish::bezierGatherBalloonFish[currIndex0th8th+1];
    drawPoints0th8th[2]=BalloonFish::bezierGatherBalloonFish[currIndex0th8th+2];
    float drawPoints1th8th[3];
    int currIndex1th8th=(BalloonFish::bezierStep+8)*3;
    drawPoints1th8th[0]=BalloonFish::bezierGatherBalloonFish[currIndex1th8th];
    drawPoints1th8th[1]=BalloonFish::bezierGatherBalloonFish[currIndex1th8th+1];
    drawPoints1th8th[2]=BalloonFish::bezierGatherBalloonFish[currIndex1th8th+2];
    float drawPoints2th8th[3];
    int currIndex2th8th=(2*BalloonFish::bezierStep+8)*3;
    drawPoints2th8th[0]=BalloonFish::bezierGatherBalloonFish[currIndex2th8th];
    drawPoints2th8th[1]=BalloonFish::bezierGatherBalloonFish[currIndex2th8th+1];
    drawPoints2th8th[2]=BalloonFish::bezierGatherBalloonFish[currIndex2th8th+2];
    float drawPoints3th8th[3];
    int currIndex3th8th=(3*BalloonFish::bezierStep+8)*3;
    drawPoints3th8th[0]=BalloonFish::bezierGatherBalloonFish[currIndex3th8th];
    drawPoints3th8th[1]=BalloonFish::bezierGatherBalloonFish[currIndex3th8th+1];
    drawPoints3th8th[2]=BalloonFish::bezierGatherBalloonFish[currIndex3th8th+2];
    float result8th[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th8th,drawPoints0th8th,drawPoints1th8th,drawPoints2th8th,result8th);
    float result8th_[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th8th,drawPoints2th8th,drawPoints1th8th,drawPoints0th8th,result8th_);

    float result8th2baseLineVectX=result8th[0]-baseLinePercentP3th[0];
    float result8th2baseLineVectY=result8th[1]-baseLinePercentP3th[1];
    float result8th2baseLineVectZ=result8th[2]-baseLinePercentP3th[2];
    float result8th2baseLineDistance=sqrtf(result8th2baseLineVectX*result8th2baseLineVectX
                                           +result8th2baseLineVectY*result8th2baseLineVectY+result8th2baseLineVectZ*result8th2baseLineVectZ);
    float result8th2baseLineVectX_=result8th_[0]-baseLinePercentP3th[0];
    float result8th2baseLineVectY_=result8th_[1]-baseLinePercentP3th[1];
    float result8th2baseLineVectZ_=result8th_[2]-baseLinePercentP3th[2];
    float result8th2baseLineDistance_=sqrtf(result8th2baseLineVectX_*result8th2baseLineVectX_
                                            +result8th2baseLineVectY_*result8th2baseLineVectY_+result8th2baseLineVectZ_*result8th2baseLineVectZ_);
    if(result8th2baseLineDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(result8th2baseLineDistance_<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th_);
    }
    ///////////////////////////////////////////////////////////////////////////

    float drawPoints0th11th[3];
    int currIndex0th11th=11*3;
    drawPoints0th11th[0]=BalloonFish::bezierGatherBalloonFish[currIndex0th11th];
    drawPoints0th11th[1]=BalloonFish::bezierGatherBalloonFish[currIndex0th11th+1];
    drawPoints0th11th[2]=BalloonFish::bezierGatherBalloonFish[currIndex0th11th+2];
    float drawPoints1th11th[3];
    int currIndex1th11th=(BalloonFish::bezierStep+11)*3;
    drawPoints1th11th[0]=BalloonFish::bezierGatherBalloonFish[currIndex1th11th];
    drawPoints1th11th[1]=BalloonFish::bezierGatherBalloonFish[currIndex1th11th+1];
    drawPoints1th11th[2]=BalloonFish::bezierGatherBalloonFish[currIndex1th11th+2];
    float drawPoints2th11th[3];
    int currIndex2th11th=(2*BalloonFish::bezierStep+11)*3;
    drawPoints2th11th[0]=BalloonFish::bezierGatherBalloonFish[currIndex2th11th];
    drawPoints2th11th[1]=BalloonFish::bezierGatherBalloonFish[currIndex2th11th+1];
    drawPoints2th11th[2]=BalloonFish::bezierGatherBalloonFish[currIndex2th11th+2];
    float drawPoints3th11th[3];
    int currIndex3th11th=(3*BalloonFish::bezierStep+11)*3;
    drawPoints3th11th[0]=BalloonFish::bezierGatherBalloonFish[currIndex3th11th];
    drawPoints3th11th[1]=BalloonFish::bezierGatherBalloonFish[currIndex3th11th+1];
    drawPoints3th11th[2]=BalloonFish::bezierGatherBalloonFish[currIndex3th11th+2];
    float result11th[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th11th,drawPoints0th11th,drawPoints1th11th,drawPoints2th11th,result11th);
    float result11th_[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th11th,drawPoints2th11th,drawPoints1th11th,drawPoints0th11th,result11th_);

    float result11th2baseLineVectX=result11th[0]-baseLinePercentP3th[0];
    float result11th2baseLineVectY=result11th[1]-baseLinePercentP3th[1];
    float result11th2baseLineVectZ=result11th[2]-baseLinePercentP3th[2];
    float result11th2baseLineDistance=sqrtf(result11th2baseLineVectX*result11th2baseLineVectX
                                            +result11th2baseLineVectY*result11th2baseLineVectY+result11th2baseLineVectZ*result11th2baseLineVectZ);
    float result11th2baseLineVectX_=result11th_[0]-baseLinePercentP3th[0];
    float result11th2baseLineVectY_=result11th_[1]-baseLinePercentP3th[1];
    float result11th2baseLineVectZ_=result11th_[2]-baseLinePercentP3th[2];
    float result11th2baseLineDistance_=sqrtf(result11th2baseLineVectX_*result11th2baseLineVectX_
                                             +result11th2baseLineVectY_*result11th2baseLineVectY_+result11th2baseLineVectZ_*result11th2baseLineVectZ_);
    if(result11th2baseLineDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(result11th2baseLineDistance_<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th_);
    }
    /////////////////////////////////////////////////////////////////////////////////

    float drawPoints0th13th[3];
    int currIndex0th13th=13*3;
    drawPoints0th13th[0]=BalloonFish::bezierGatherBalloonFish[currIndex0th13th];
    drawPoints0th13th[1]=BalloonFish::bezierGatherBalloonFish[currIndex0th13th+1];
    drawPoints0th13th[2]=BalloonFish::bezierGatherBalloonFish[currIndex0th13th+2];
    float drawPoints1th13th[3];
    int currIndex1th13th=(BalloonFish::bezierStep+13)*3;
    drawPoints1th13th[0]=BalloonFish::bezierGatherBalloonFish[currIndex1th13th];
    drawPoints1th13th[1]=BalloonFish::bezierGatherBalloonFish[currIndex1th13th+1];
    drawPoints1th13th[2]=BalloonFish::bezierGatherBalloonFish[currIndex1th13th+2];
    float drawPoints2th13th[3];
    int currIndex2th13th=(2*BalloonFish::bezierStep+13)*3;
    drawPoints2th13th[0]=BalloonFish::bezierGatherBalloonFish[currIndex2th13th];
    drawPoints2th13th[1]=BalloonFish::bezierGatherBalloonFish[currIndex2th13th+1];
    drawPoints2th13th[2]=BalloonFish::bezierGatherBalloonFish[currIndex2th13th+2];
    float drawPoints3th13th[3];
    int currIndex3th13th=(3*BalloonFish::bezierStep+13)*3;
    drawPoints3th13th[0]=BalloonFish::bezierGatherBalloonFish[currIndex3th13th];
    drawPoints3th13th[1]=BalloonFish::bezierGatherBalloonFish[currIndex3th13th+1];
    drawPoints3th13th[2]=BalloonFish::bezierGatherBalloonFish[currIndex3th13th+2];
    float result13th[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th13th,drawPoints0th13th,drawPoints1th13th,drawPoints2th13th,result13th);
    float result13th_[3];
    balloonFishDetection.makeOthBsplinePoint(drawPoints3th13th,drawPoints2th13th,drawPoints1th13th,drawPoints0th13th,result13th_);

    float result13th2baseLineVectX=result13th[0]-baseLinePercentP3th[0];
    float result13th2baseLineVectY=result13th[1]-baseLinePercentP3th[1];
    float result13th2baseLineVectZ=result13th[2]-baseLinePercentP3th[2];
    float result13th2baseLineDistance=sqrtf(result13th2baseLineVectX*result13th2baseLineVectX
                                            +result13th2baseLineVectY*result13th2baseLineVectY+result13th2baseLineVectZ*result13th2baseLineVectZ);
    float result13th2baseLineVectX_=result13th_[0]-baseLinePercentP3th[0];
    float result13th2baseLineVectY_=result13th_[1]-baseLinePercentP3th[1];
    float result13th2baseLineVectZ_=result13th_[2]-baseLinePercentP3th[2];
    float result13th2baseLineDistance_=sqrtf(result13th2baseLineVectX_*result13th2baseLineVectX_
                                             +result13th2baseLineVectY_*result13th2baseLineVectY_+result13th2baseLineVectZ_*result13th2baseLineVectZ_);
    if(result13th2baseLineDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(result13th2baseLineDistance_<COLLDETEAPARDIST) {
        collisionDetectionAfter(result0th_);
    }

}

void BalloonFlyFishCollisionDetection::checkBalloonFishTailCollDete(float *result0th, float *result0th_) {
    float baseLinePercentP3th[]={WizardGeomSupple::baseLinePercentPoints[12],WizardGeomSupple::baseLinePercentPoints[13],WizardGeomSupple::baseLinePercentPoints[14]};

    float tailResult0th0[3];
    float tailResult0th1[3];
    //左右
    float tail0thP0[3]={BalloonFish::tailBsplineControlPoints[27],BalloonFish::tailBsplineControlPoints[28],BalloonFish::tailBsplineControlPoints[29]};
    //下部
    float tail0thP1[3]={BalloonFish::tailBsplineControlPoints[30],BalloonFish::tailBsplineControlPoints[31],BalloonFish::tailBsplineControlPoints[32]};
    //左右
    float tail0thP2[3]={BalloonFish::tailBsplineControlPoints[33],BalloonFish::tailBsplineControlPoints[34],BalloonFish::tailBsplineControlPoints[35]};
    //上部
    float tail0thP3[3]={BalloonFish::tailBsplineControlPoints[36],BalloonFish::tailBsplineControlPoints[37],BalloonFish::tailBsplineControlPoints[38]};
    balloonFishDetection.makeOthBsplinePoint(tail0thP1,tail0thP2,tail0thP3,tail0thP0,tailResult0th0);
    balloonFishDetection.makeOthBsplinePoint(tail0thP1,tail0thP0,tail0thP3,tail0thP2,tailResult0th1);
    float tail0th0ToBaseLPercentVectX=tailResult0th0[0]-baseLinePercentP3th[0];
    float tail0th0ToBaseLPercentVectY=tailResult0th0[1]-baseLinePercentP3th[1];
    float tail0th0ToBaseLPercentVectZ=tailResult0th0[2]-baseLinePercentP3th[2];
    float tail0th1ToBaseLPercentVectX=tailResult0th1[0]-baseLinePercentP3th[0];
    float tail0th1ToBaseLPercentVectY=tailResult0th1[1]-baseLinePercentP3th[1];
    float tail0th1ToBaseLPercentVectZ=tailResult0th1[2]-baseLinePercentP3th[2];
    float tail0th0ToBaseLPercentDistance=sqrtf(tail0th0ToBaseLPercentVectX*tail0th0ToBaseLPercentVectX+
                                               tail0th0ToBaseLPercentVectY*tail0th0ToBaseLPercentVectY+tail0th0ToBaseLPercentVectZ*tail0th0ToBaseLPercentVectZ);
    float tail0th1ToBaseLPercentDistance=sqrtf(tail0th1ToBaseLPercentVectX*tail0th1ToBaseLPercentVectX+
                                               tail0th1ToBaseLPercentVectY*tail0th1ToBaseLPercentVectY+tail0th1ToBaseLPercentVectZ*tail0th1ToBaseLPercentVectZ);
    if(tail0th0ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(tail0th1ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th_);
    }
    //////////////////////////////////////////////////////////////////////////////////////
    float tailResult1th0[3];
    float tailResult1th1[3];
    //左右
    float tail1thP0[3]={BalloonFish::tailBsplineControlPoints[54],BalloonFish::tailBsplineControlPoints[55],BalloonFish::tailBsplineControlPoints[56]};
    //下部
    float tail1thP1[3]={BalloonFish::tailBsplineControlPoints[57],BalloonFish::tailBsplineControlPoints[58],BalloonFish::tailBsplineControlPoints[59]};
    //左右
    float tail1thP2[3]={BalloonFish::tailBsplineControlPoints[60],BalloonFish::tailBsplineControlPoints[61],BalloonFish::tailBsplineControlPoints[62]};
    //上部
    float tail1thP3[3]={BalloonFish::tailBsplineControlPoints[63],BalloonFish::tailBsplineControlPoints[64],BalloonFish::tailBsplineControlPoints[65]};
    balloonFishDetection.makeOthBsplinePoint(tail1thP1,tail1thP2,tail1thP3,tail1thP0,tailResult1th0);
    balloonFishDetection.makeOthBsplinePoint(tail1thP1,tail1thP0,tail1thP3,tail1thP2,tailResult1th1);
    float tail1th0ToBaseLPercentVectX=tailResult1th0[0]-baseLinePercentP3th[0];
    float tail1th0ToBaseLPercentVectY=tailResult1th0[1]-baseLinePercentP3th[1];
    float tail1th0ToBaseLPercentVectZ=tailResult1th0[2]-baseLinePercentP3th[2];
    float tail1th1ToBaseLPercentVectX=tailResult1th1[0]-baseLinePercentP3th[0];
    float tail1th1ToBaseLPercentVectY=tailResult1th1[1]-baseLinePercentP3th[1];
    float tail1th1ToBaseLPercentVectZ=tailResult1th1[2]-baseLinePercentP3th[2];
    float tail1th0ToBaseLPercentDistance=sqrtf(tail1th0ToBaseLPercentVectX*tail1th0ToBaseLPercentVectX+
                                               tail1th0ToBaseLPercentVectY*tail1th0ToBaseLPercentVectY+tail1th0ToBaseLPercentVectZ*tail1th0ToBaseLPercentVectZ);
    float tail1th1ToBaseLPercentDistance=sqrtf(tail1th1ToBaseLPercentVectX*tail1th1ToBaseLPercentVectX+
                                               tail1th1ToBaseLPercentVectY*tail1th1ToBaseLPercentVectY+tail1th1ToBaseLPercentVectZ*tail1th1ToBaseLPercentVectZ);
    if(tail1th0ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    if(tail1th1ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th_);
    }
    //////////////////////////////////////////////////////////////////////////////////
    float tailResult3th0[3];
    //左右
    float tail3thP0[3]={BalloonFish::tailBsplineControlPoints[108],BalloonFish::tailBsplineControlPoints[109],BalloonFish::tailBsplineControlPoints[110]};
    //下部
    float tail3thP1[3]={BalloonFish::tailBsplineControlPoints[111],BalloonFish::tailBsplineControlPoints[112],BalloonFish::tailBsplineControlPoints[113]};
    //左右
    float tail3thP2[3]={BalloonFish::tailBsplineControlPoints[114],BalloonFish::tailBsplineControlPoints[115],BalloonFish::tailBsplineControlPoints[116]};
    //上部
    float tail3thP3[3]={BalloonFish::tailBsplineControlPoints[117],BalloonFish::tailBsplineControlPoints[118],BalloonFish::tailBsplineControlPoints[119]};
    balloonFishDetection.makeOthBsplinePoint(tail3thP1,tail3thP2,tail3thP3,tail3thP0,tailResult3th0);
    float tail3th0ToBaseLPercentVectX=tailResult3th0[0]-baseLinePercentP3th[0];
    float tail3th0ToBaseLPercentVectY=tailResult3th0[1]-baseLinePercentP3th[1];
    float tail3th0ToBaseLPercentVectZ=tailResult3th0[2]-baseLinePercentP3th[2];
    float tail3th0ToBaseLPercentDistance=sqrtf(tail3th0ToBaseLPercentVectX*tail3th0ToBaseLPercentVectX+
                                               tail3th0ToBaseLPercentVectY*tail3th0ToBaseLPercentVectY+tail3th0ToBaseLPercentVectZ*tail3th0ToBaseLPercentVectZ);
    if(tail3th0ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    //如果刺豚尾部超过这个距离
    if(tail3th0ToBaseLPercentDistance>1.2*COLLDETEAPARDIST){
        if(BalloonFish::isDrawStab&&BalloonFish::collDeteAfterIndex<1)
        {
            balloonFishDetection.balloonFishSmallUncondition();
        }
    }
}

void BalloonFlyFishCollisionDetection::checkBalloonFishFinsCollDete(float* result0th) {
    float baseLinePercentP3th[]={WizardGeomSupple::baseLinePercentPoints[12],WizardGeomSupple::baseLinePercentPoints[13],WizardGeomSupple::baseLinePercentPoints[14]};
    float* leftFins=BalloonFish::balloonFishLeftFins;

    float leftFins4ToBaseLPercentVectX=leftFins[12]-baseLinePercentP3th[0];
    float leftFins4ToBaseLPercentVectY=leftFins[13]-baseLinePercentP3th[1];
    float leftFins4ToBaseLPercentVectZ=leftFins[14]-baseLinePercentP3th[2];
    float leftFins4ToBaseLPercentDistance=sqrtf(leftFins4ToBaseLPercentVectX*leftFins4ToBaseLPercentVectX+
                                                leftFins4ToBaseLPercentVectY*leftFins4ToBaseLPercentVectY+leftFins4ToBaseLPercentVectZ*leftFins4ToBaseLPercentVectZ);
    if(leftFins4ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }
    float* rightFins=BalloonFish::balloonFishRightFins;
    float rightFins4ToBaseLPercentVectX=rightFins[12]-baseLinePercentP3th[0];
    float rightFins4ToBaseLPercentVectY=rightFins[13]-baseLinePercentP3th[1];
    float rightFins4ToBaseLPercentVectZ=rightFins[14]-baseLinePercentP3th[2];
    float rightFins4ToBaseLPercentDistance=sqrtf(rightFins4ToBaseLPercentVectX*rightFins4ToBaseLPercentVectX+
                                                 rightFins4ToBaseLPercentVectY*rightFins4ToBaseLPercentVectY+rightFins4ToBaseLPercentVectZ*rightFins4ToBaseLPercentVectZ);
    if(rightFins4ToBaseLPercentDistance<COLLDETEAPARDIST){
        collisionDetectionAfter(result0th);
    }

}

float BalloonFlyFishCollisionDetection::collDeteAfterBezierPath[3000];
int BalloonFlyFishCollisionDetection::collDeteBezierPathStep=120;
float BalloonFlyFishCollisionDetection::tempFrontMoveVect[3];
//碰撞检测后执行的函数
void BalloonFlyFishCollisionDetection::collisionDetectionAfter(float* colliDetecPoint){
    float collDeteMoveVect[]={colliDetecPoint[0]-WizardGeomSupple::baseLinePercentPoints[12],
                              colliDetecPoint[1]-WizardGeomSupple::baseLinePercentPoints[13],colliDetecPoint[2]-WizardGeomSupple::baseLinePercentPoints[14]};
    WizardGeomSupple::normalize(collDeteMoveVect);
    tempFrontMoveVect[0]=-collDeteMoveVect[0];
    tempFrontMoveVect[1]=-collDeteMoveVect[1];
    tempFrontMoveVect[2]=-collDeteMoveVect[2];


    {
        //标志着发生了碰撞检测
        isCollisionDetectionAfter=true;
        if(BalloonFish::stabSubstractFactor<0.1){
            FlyElephantExercise::moveLeng=0.003;
            FlyElephantExercise::moveLengSubstracFactor=0.00009;
            BalloonFish::isPrick=true;
            tempFrontMoveVect[0]=-collDeteMoveVect[0];
            tempFrontMoveVect[1]=0.0;
            tempFrontMoveVect[2]=-collDeteMoveVect[2];

//            LOGD("-=-=-=-=-= 刺豚刺到了");
        }


        float collDeteAfterBezierControlP[]={colliDetecPoint[0],colliDetecPoint[1],colliDetecPoint[2],
                                             colliDetecPoint[0]+0.1f*collDeteMoveVect[0],colliDetecPoint[1]+0.1f*collDeteMoveVect[1]+0.1f,colliDetecPoint[2]+0.1f*collDeteMoveVect[2],
                                             colliDetecPoint[0]+0.2f*collDeteMoveVect[0],colliDetecPoint[1]+0.2f*collDeteMoveVect[1]+0.2f,colliDetecPoint[2]+0.2f*collDeteMoveVect[2],
                                             colliDetecPoint[0]+0.3f*collDeteMoveVect[0],colliDetecPoint[1]+0.3f*collDeteMoveVect[1],colliDetecPoint[2]+0.3f*collDeteMoveVect[2]};
        //生成碰撞后沿着运动的bezier路线
        gameWorldCollisionDetection.makeUpBezierLine(collDeteAfterBezierPath,collDeteAfterBezierControlP,4,1,collDeteBezierPathStep);
    }
//    drawPointLine(collDeteAfterBezierPath,100,true,0.0,1.0,0.0,5.0);

}

float BalloonFlyFishCollisionDetection::getBaseLine2FrontVectAngle(float* colliDetecPoint){
    float collDeteMoveVect[]={colliDetecPoint[0]-WizardGeomSupple::baseLinePercentPoints[12],
                              colliDetecPoint[1]-WizardGeomSupple::baseLinePercentPoints[13],colliDetecPoint[2]-WizardGeomSupple::baseLinePercentPoints[14]};
    WizardGeomSupple::normalize(collDeteMoveVect);

    float frontDirect[]={FlyElephantExercise::frontDirectNor[0],0.0,FlyElephantExercise::frontDirectNor[2]};
    //向量夹角的余弦值
    float coseValue=(collDeteMoveVect[0]*frontDirect[0]+collDeteMoveVect[1]*frontDirect[1]+collDeteMoveVect[2]*frontDirect[2])/
                    (sqrtf(collDeteMoveVect[0]*collDeteMoveVect[0]+collDeteMoveVect[1]*collDeteMoveVect[1]+collDeteMoveVect[2]*collDeteMoveVect[2])*
                     sqrtf(frontDirect[0]*frontDirect[0]+frontDirect[1]*frontDirect[1]+frontDirect[2]*frontDirect[2]));
    //返回余弦值对应的弧度
    double angle=acos(double(coseValue));
    //最终旋转的角度值
    float vetorialAngle=float(angle)*180.0/3.14159265;

    return vetorialAngle;
}


void BalloonFlyFishCollisionDetection::rotateBodyByMiddAxis(){

    float midd2TopVect[]={ BalloonFish::topPoint[0]-BalloonFish::middAxisPoints[0],
                           BalloonFish::topPoint[1]-BalloonFish::middAxisPoints[1],BalloonFish::topPoint[2]-BalloonFish::middAxisPoints[2] };
    float middAxisVect[]={ BalloonFish::middAxisPoints[3]-BalloonFish::middAxisPoints[0],
                           BalloonFish::middAxisPoints[4]-BalloonFish::middAxisPoints[1],BalloonFish::middAxisPoints[5]-BalloonFish::middAxisPoints[2] };
    float leftRightVect[3];
    WizardGeomSupple::getVerticalVect(midd2TopVect[0],midd2TopVect[1],midd2TopVect[2],
                                      middAxisVect[0],middAxisVect[1],middAxisVect[2],leftRightVect);
    WizardGeomSupple::normalize(leftRightVect);
    float moveLeng=tanf(0.2*3.1415926/180.0f);
    float movedX=BalloonFish::topPoint[0]+moveLeng*leftRightVect[0];
    float movedY=BalloonFish::topPoint[1]+moveLeng*leftRightVect[1];
    float movedZ=BalloonFish::topPoint[2]+moveLeng*leftRightVect[2];
    float moved2middAxisVect[]={movedX-BalloonFish::middAxisPoints[0],movedY-BalloonFish::middAxisPoints[1],movedZ-BalloonFish::middAxisPoints[2]};
    WizardGeomSupple::normalize(moved2middAxisVect);
    //单位长度是初始的顶点所决定的
    BalloonFish::topPoint[0]=BalloonFish::middAxisPoints[0]+0.1*moved2middAxisVect[0];
    BalloonFish::topPoint[1]=BalloonFish::middAxisPoints[1]+0.1*moved2middAxisVect[1];
    BalloonFish::topPoint[2]=BalloonFish::middAxisPoints[2]+0.1*moved2middAxisVect[2];
    ////////////////////////////////////////////////////////////////
    //碰撞后如果bezier路线角标值大于30 刺豚就开始绕TOP向量旋转
    if(BalloonFish::collDeteAfterIndex>30){

        float midd2TopVect2[]={ BalloonFish::topPoint[0]-BalloonFish::middAxisPoints[0],
                                BalloonFish::topPoint[1]-BalloonFish::middAxisPoints[1],BalloonFish::topPoint[2]-BalloonFish::middAxisPoints[2] };
        float leftRightVect2[3];
        WizardGeomSupple::getVerticalVect(midd2TopVect2[0],midd2TopVect2[1],midd2TopVect2[2],
                                          middAxisVect[0],middAxisVect[1],middAxisVect[2],leftRightVect2);
        WizardGeomSupple::normalize(leftRightVect2);
        float moveLeng2=tanf(0.5*3.1415926/180.0f);

        float pp3thX=BalloonFish::middAxisPoints[9];
        float pp3thY=BalloonFish::middAxisPoints[10];
        float pp3thZ=BalloonFish::middAxisPoints[11];

        float pp0thX=BalloonFish::middAxisPoints[0]-moveLeng2*leftRightVect2[0];
        float pp0thY=BalloonFish::middAxisPoints[1]-moveLeng2*leftRightVect2[1];
        float pp0thZ=BalloonFish::middAxisPoints[2]-moveLeng2*leftRightVect2[2];

        float vect3to0th[]={pp0thX-pp3thX,pp0thY-pp3thY,pp0thZ-pp3thZ};
        WizardGeomSupple::normalize(vect3to0th);
        BalloonFish::middAxisPoints[0]=BalloonFish::middAxisPoints[9]+0.12*vect3to0th[0];
        BalloonFish::middAxisPoints[1]=BalloonFish::middAxisPoints[10]+0.12*vect3to0th[1];
        BalloonFish::middAxisPoints[2]=BalloonFish::middAxisPoints[11]+0.12*vect3to0th[2];

        BalloonFish::middAxisPoints[3]=BalloonFish::middAxisPoints[9]+0.1*vect3to0th[0];
        BalloonFish::middAxisPoints[4]=BalloonFish::middAxisPoints[10]+0.1*vect3to0th[1];
        BalloonFish::middAxisPoints[5]=BalloonFish::middAxisPoints[11]+0.1*vect3to0th[2];

        BalloonFish::middAxisPoints[6]=BalloonFish::middAxisPoints[9]+0.06*vect3to0th[0];
        BalloonFish::middAxisPoints[7]=BalloonFish::middAxisPoints[10]+0.06*vect3to0th[1];
        BalloonFish::middAxisPoints[8]=BalloonFish::middAxisPoints[11]+0.06*vect3to0th[2];

        BalloonFish::middAxisPoints[12]=BalloonFish::middAxisPoints[9]-0.05*vect3to0th[0];
        BalloonFish::middAxisPoints[13]=BalloonFish::middAxisPoints[10]-0.05*vect3to0th[1];
        BalloonFish::middAxisPoints[14]=BalloonFish::middAxisPoints[11]-0.05*vect3to0th[2];

        BalloonFish::middAxisPoints[15]=BalloonFish::middAxisPoints[9]-0.06*vect3to0th[0];
        BalloonFish::middAxisPoints[16]=BalloonFish::middAxisPoints[10]-0.06*vect3to0th[1];
        BalloonFish::middAxisPoints[17]=BalloonFish::middAxisPoints[11]-0.06*vect3to0th[2];

    }
}

////////////////////////////////////////////////////////////////////////////////////
float* BalloonFlyFishCollisionDetection::makeUpBlinePointTh(float* point0th,float* point1th,float* point2th,float* point3th,int blineSplitNum,int percentNum){

    float T = float(percentNum)/float(blineSplitNum);;
    float f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
    float f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
    float f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
    float f4 = (T*T*T) / 6.0;

    float x = f1*point0th[0]+f2*point1th[0]+f3*point2th[0]+f4*point3th[0];
    float y = f1*point0th[1]+f2*point1th[1]+f3*point2th[1]+f4*point3th[1];
    float z = f1*point0th[2]+f2*point1th[2]+f3*point2th[2]+f4*point3th[2];
    float drawPoint[]={x,y,z};
    drawPointLine(drawPoint,1,true,1.0,0.0,0.0,10.0);
    return drawPoint;
}
