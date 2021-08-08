#pragma once

#include "scene.h"

class GameWorld{

public:
    GameWorld();
    ~GameWorld();
    static float flowerPosition0[3];
    static float flowerPosition1[3];
    static float flowerPosition2[3];
    static float flowerPosition3[3];
    static float flowerPosition4[3];
    static float flowerPosition5[3];
    static float flowerPosition6[3];

    void makeUpBezierLine(float* bezPointGather,float* splitPoints, int sectionNum,int degreeSplitNum,int bezierStep);
    int factrial(int factrialCount);
    void initGameWorld();
    void makeUpBspline(int blineSplitNum,int bezierStep,int degreeSplitNum,
                       float* blinesPoints_coralGroup,float* blinesPointsNormal_coral,float* bezierPointCoral,float* texcoord_coral);
    void initCoralReef();

    void drawCoral(GLuint textureCoralReefLocation,GLuint texcoordCoralReefLocation);
    void textureMapping(GLuint texture,GLuint textureLocation,GLuint light_wavesTexture,
            GLuint textureFloorLightWavesLocation,GLuint texcoordLocation,GLuint longLatitudeFloorLocation);

    float* getBezPointGather_floor();
    float* getBezierControlPointsMap();

    };