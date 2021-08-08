#pragma once

#include "scene.h"

class FlyElephantExercise{

public:
    FlyElephantExercise();
    ~FlyElephantExercise();

    static float bezierVertBaseLinePoints[150];
    static float frontLine[6];
    static float frontDirectNor[3];
    static int rotateCountTotal;
    static bool isInverseRotate;
    static int flyElephantCount;
    static float moveLeng;
    static float moveUpDownLeng;
    static bool isMoveUp;
    static float moveLengSubstracFactor;

    void point2lineVertPoint(float* point, float* baseVect, int bezierIndex);
    static float* rotateByBaseLine(float currX, float currY, float currZ, float vertX, float vertY, float vertZ, float rotateAngle, bool isInverse);
    void rotateByBaseLine(float rotateAngle);
    void getFrontDirectVect();
    void frontMove();
    void moveUpDown();
    void moveByPrickVect(float* moveVectNor);
    };

