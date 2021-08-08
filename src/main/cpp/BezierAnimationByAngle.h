#pragma once

#include "scene.h"

class BezierAnimationByAngle{

public:
    BezierAnimationByAngle();
    ~BezierAnimationByAngle();

    void bezierAnimation2(int wgIndex);
    float setPrev2currLengthValueByBezierIndex(int bezierLineIndex,int bezierIndex,float prev2currLengthS);
    void bendAndSkirtHemlineAnima(int bezierLineIndex,int bezierIndex,float alonePrev2th2prevX,
            float alonePrev2th2prevY,float alonePrev2th2prevZ,float moveLeng,float* moveVerticalVectNor,
            float* movedPoint,float prev2currLengthS,float* prevPoint,float prev2currLength,float* vertCrossBezierLineVector);
    float setBendAngle1thValueByBezierIndex(int bezierLineIndex,int bezierIndex);
    float getBezierMoveAngle(int bezierLineIndex,int bezierIndex);
    void bezierAnimFirst(WizardGeom* fishBodyGeom,int bezierLineIndex,int bezierIndex,float* vertCrossBezierLineVector,
            float vertBaseLineVectX,float vertBaseLineVectY,float vertBaseLineVectZ);
    void bezierAnimOrthers(WizardGeom* fishBodyGeom,int bezierLineIndex,int bezierIndex,float* vertCrossBezierLineVector);
    void meetStopCondition(int bezierIndex,int bezierLineIndex);
    bool meetReturnCondition(int bezierIndex,int bezierLineIndex);
    float getTrueBendAngle(int bezierIndex,int bezierLineIndex,float trueBendAngle1th);
    void skirtHemlineAndBend(int bezierLineIndex,int bezierIndex,float prev2currLength,float* prevPoint,
            float bendAngle,float* vertCrossBezierLineVector,float* prev2movedVectNor,float* directVectNor,float* movedPoint);
    void getSkirtHemlineVect(float* moveCrossVectNor,float* moveDirectVectNor,int bezierLineIndex,int bezierIndex);
    float substractWaverAngle(float waverAngle);
    float substractBendAngle(float bendAngle);
    void setStratchHeadValue(int bezierLineIndex,int bezierIndex,float alonePrev2th2prevX,
            float alonePrev2th2prevY,float alonePrev2th2prevZ,float moveLeng,float* moveVerticalVectNor,
            float* movedPoint,float prev2currLengthS,float* prevPoint,float prev2currLength,float* vertCrossBezierLineVector);
    bool meetStratchHead();
    float getBendAnimaAngle(int bezierIndex,int bezierLineIndex);
    bool meetBendAndSkirtHemline(int bezierIndex,int bezierLineIndex);


    static float vertBaseLineVects[300];
    static float vertCrossBezierLineVects[300];
    static float middleLineVectNor[3];


    };
