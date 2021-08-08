#pragma once

#include "scene.h"

class FlyElephant
{
public:
    FlyElephant();
    ~FlyElephant();
    static float lightPosition[3];
    static float cameraPosition[3];
    void initFlyElephantLocation();
    void drawFlyElephant();
    void SetMatrixByLocation(GLuint modelMatrixLocation,GLuint viewMatrixLocation,GLuint projectionMatrixLocation);
    glm::mat4 getViewMatrix();

};