#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "scene.h"

class BezierBspline
{
public:
    BezierBspline();
    ~BezierBspline();

    static float* makeUpBezierLine2(int geomIndex);       //生成bezier曲线函数

    int factrial(int factrialCount); //介乘函数

    //构造B样条曲线
    void makeUpBspline(int wgIndex);
    void makeUpPoints(float f1, float f2, float f3, float f4, int i, int wgIndex);
    void blineTextureMap(int wgIndex);


    void createBezierShaderPoints(int j, int mIndex1, int blindex, int i, float f1, float f2, float f3, float f4, int wgIndex);
    void createLast3BezierShaderPoints(int mIndex1, int lastThirdIndex, float f1, float f2, float f3, float f4, int wgIndex);
    void createLast2BezierShaderPoints(int mIndex1, int lastSecondIndex, float f1, float f2, float f3, float f4, int wgIndex);
    void createLastBizerShaderPoints(int mIndex1, int lastSecondIndex, float f1, float f2, float f3, float f4, int wgIndex);
    void boneAnimation(int wgIndex);//骨骼动画
    void getAllShaderParams(int tansverSpanNum1, int tansverSpanNum2, float textureCoord1, float textureCoord2, float fv1, float fv2, int m, int i, int j, int wgIndex);
    void getCloseAllShaderParams(int tansverSpanNum1, int tansverSpanNum2, float textureCoord1, float textureCoord2, float fv1, float fv2, int m, int i, int j, int wgIndex);
    void bindShaderBezierPoints(int wgIndex);
    static void bindShaderBezier2Bline(int wgIndex);
    static void bindTrueShaderPoints(int wgIndex);
    //保存样条曲线的点
    void saveBsplinePoints(int m, int i, int tansverSpanNum1, int tansverSpanNum2, float* blinesPoints,int wgIndex);
    void saveClosedBsplinePoints(int m, int i, int tansverSpanNum1, int tansverSpanNum2, float* blinesPoints, int wgIndex);
    //得到B样条的百分数
    void getBsplinePercent(int i, float* bsplinePercent, int blineSplitNum, int m, int mIndex);


    void makeUpClosedQuadFace(int m, int mIndex, int i, int j, int tansverSpanNum1,
                              float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4,
                              float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
                              float* trueBlineFactors1, float* trueBlineFactors2,/* float* wgHeadFactors1, float* wgHeadFactors2,*/
                              float* blineFactors1, float* blineFactors2, float* bsplinePercent, int blineSplitNum);

    void makeUpShaderQuadFace(int i, int mIndex, int j, int tansverSpanNum1, int m,
                              float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
                              float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4/*,
																																	  float* wizardGeomHead1, float* wizardGeomHead2, float* wizardGeomHead3, float* wizardGeomHead4*/);
    void makeUpShaderQuadFaceBezier(int i, int mIndex, int j, int bezierStep, int tansverSpanNum, int m,
                                    float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
                                    float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4/*,
																																	  float* wizardGeomHead1, float* wizardGeomHead2, float* wizardGeomHead3, float* wizardGeomHead4*/);
    void makeUpShaderQuadFace5(int i, int j, int bezierStep, int tansverSpanNum, int m,
                               float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
                               float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4/*,
																																	  float* wizardGeomHead1, float* wizardGeomHead2, float* wizardGeomHead3, float* wizardGeomHead4*/);
    void makeUpClosedShaderQuadFace5(int i, int j, int bezierStep, int tansverSpanNum, int m,
                                     float* bezierShaderPoints1, float* bezierShaderPoints2, float* bezierShaderPoints3, float* bezierShaderPoints4,
                                     float* trueBezierShaderPoints1, float* trueBezierShaderPoints2, float* trueBezierShaderPoints3, float* trueBezierShaderPoints4/*,
																																	  float* wizardGeomTail1, float* wizardGeomTail2, float* wizardGeomTail3, float* wizardGeomTail4*/);

private:
    //制作四边形面片
    static void calElephant1(int geomIndex);
    static void calElephant2(int geomIndex);
};



