#pragma once

#include "scene.h"

class FlyElephantEye{

public:
    FlyElephantEye();
    ~FlyElephantEye();
    void drawFlyElephantEye(int bezierIndex0th,int bezierIndex1th,int bezierIndex2th);
    float* getDrawPoints();

};
