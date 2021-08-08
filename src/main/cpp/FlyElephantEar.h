#pragma once

#include "scene.h"

class FlyElephantEar
{
public:
    FlyElephantEar();
    ~FlyElephantEar();

    static float blpoints[600];
    void MakeFishEar(int tag);
    void MakeEarPoints(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotal,int tag);//tag为0时指眼睛 为1时指嘴巴 为2时指耳朵
    void DrawFishEarPoints(int blineSplitTotal,int tag);
    void FlyElephantEarFan(float* middleLineVectNor,float* vertBaseLineVectNor,float* vertCroBezLinVectNor,int tag);
    void MakeFlyElephantEarForm(float* headerBezier,float* vertBaseLineVectNor,float* middleLineVectNor,int bezierPointIndex,int tag);
    void earMoveAloneVect(float* blpoints,float* vertBaseLineVectNor,int currXIndex,int currYIndex,int currZIndex,float angle,int tag);
    void resetVertCroBezVect(float angle,float* vertCroBezLinVectNor, bool isPlusOrMinu);
    void resetMoveVertVect(float* moveVertVectNor,float* vertLine2currVectNor,float angle);

    void MakeEarPoints2(float* blineContPoints, int rowTotal, int listTotal, int blineSplitTotalParam,int tag);
    void drawSeaGrass(int blineSplitTotal,int tag);

    static void makeFishEarThreads(int tag);

};


