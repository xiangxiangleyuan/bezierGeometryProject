#pragma once

#include "scene.h"

class BalloonFlyFishCollisionDetection{

public:
    BalloonFlyFishCollisionDetection();
    ~BalloonFlyFishCollisionDetection();

    static bool isCollisionDetectionAfter;
    static float collDeteAfterBezierPath[3000];
    static int collDeteBezierPathStep;
    static bool isFlyElephantMoveLengZero;
    static bool isInitTempFrontMoveVect;
    static float tempFrontMoveVect[3];
    static bool isCacheFrontMoveVect;

    void checkCollisionDetection();
    void checkBalloonFishFinsCollDete(float* result0th);
    void collisionDetectionAfter(float* colliDetecPoint);
    void rotateBodyByMiddAxis();
    void checkBalloonFishTailCollDete(float* result0th,float* result0th_);
    void checkBalloonFishBodyCollDete(float* result0th,float* result0th_);
    float getBaseLine2FrontVectAngle(float* colliDetecPoint);
    float* makeUpBlinePointTh(float* point0th,float* point1th,float* point2th,float* point3th,int blineSplitNum,int percentNum);


};