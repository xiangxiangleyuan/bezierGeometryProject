#pragma once

#include "scene.h"

class BalloonFish{

public:
    BalloonFish();
    ~BalloonFish();

    static float bezierGatherBalloonFish[900];
    static const int bezierStep=17;
    static float bezierVertBaseLinePointsBalloonFish[900];
    static float tailBsplineControlPoints[300];
    static float balloonFishLeftFins[90];
    static float balloonFishRightFins[90];
    static float topPoint[3];
    static float middAxisPoints[18];
    static int bezierIndex;
    static float bezierMovePath[3300];
    static float bezierPathControlPoints2[90];
    static bool isCollDeteAfterIndexAdd;
    static int collDeteAfterIndex;
    static float longerRadiu0;
    static float longerRadiu1;
    static float shortRadiu1;
    static float stabSubstractFactor;
    static bool isBecomeSmalling;
    static bool isDrawStab;
    static bool isDrawStabCollDete;
    static bool isPrick;
    static float leftRightVect[3];

    int balloonFishBsplineSplitNum;
    int balloonFishRowNum;
    void initBalloonFish();
    void drawBalloonFish();
    void drawBalloonFishPoints(int blineSplitTotal,int tag);
    void makeBalloonFishBsplinePoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotal,int tag);
    void initBalloonFishBezierControlPoints();
    void point2lineVertPoint(float* bezierPoint, float* baseLineVect, int bezierIndex);
    void makeUpBezierLine(float* bezPointGather,float* splitPoints, int sectionNum,int degreeSplitNum,int bezierStep);
    int factrial(int factrialCount);
    void changeTopPoint();
    //围绕中间轴旋转鱼身
    void rotateBodyByMiddAxis();
    //围绕中间轴垂直线旋转鱼身
    void rotateBodyByVerticalMiddAxis();
    //根据beizer路线前进
    void moveByBezierPath();
    void moveByBezierPathColliDeteAfter();
    void drawBalloonFishSTABPoints(int blineSplitTotal,int tag);
    void makeBalloonFishSTABPoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotal,int tag);
    void addBalloonFishTail();
    void makeOthBsplinePoint(float* bsplineControl0th,float* bsplineControl1th,float* bsplineControl2th,float* bsplineControl3th,float* resultPoint);
    //刺豚开始膨胀
    void bolloonFishSwell();
    //刺豚在缩小
    void balloonFishSmalling();
    //刺豚无条件膨胀
    void bolloonFishSwellUnconditional();
    //刺豚无条件缩小
    void balloonFishSmallUncondition();


};