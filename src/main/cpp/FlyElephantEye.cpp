#include "FlyElephantEye.h"

FlyElephantEye::FlyElephantEye() {};
FlyElephantEye::~FlyElephantEye() {};

FlyElephantEar flyElephantEarFlyElephantEye;
WizardGeom wizardGeomFlyElephantEye;
float drawPoints[60];
float drawPoints2[60];
float drawPoints3[60];
bool isSmileSub=true;
float smileRange=0.05;
float smileDownRange=0.01;
float blinkRange=0.0;
bool isBlinkSub=true;
bool isOutBlinkSub=true;
//眼睛外圈眨眼半径
float shrinkLeng=0.0;
//三个点是指三条贝塞尔线段
void FlyElephantEye::drawFlyElephantEye(int bezierIndex0th,int bezierIndex1th,int bezierIndex2th) {

    WizardGeom* fish=wizardGeomFlyElephantEye.getCurrWizardGeom(1);
    //眼睛的眨眼操作
    if(bezierIndex0th!=10)
    {

        int bezierLine0th=bezierIndex0th,bezierLine1th=bezierIndex1th,bezierLine2th=bezierIndex2th;
        //第8列的第5个点
        int pointIndex0th=(bezierLine0th*fish->bezierStep+5)*3;
        //第10列的第5个点
        int pointIndex1th=(bezierLine1th*fish->bezierStep+5)*3;
        //第12列的第5个点
        int pointIndex2th=(bezierLine2th*fish->bezierStep+5)*3;
        //第12列的第7个点
        int pointIndex4th=(bezierLine2th*fish->bezierStep+7)*3;
        //第10列的第7个点
        int pointIndex5th=(bezierLine1th*fish->bezierStep+7)*3;
        //第8列的第7个点
        int pointIndex6th=(bezierLine0th*fish->bezierStep+7)*3;
        //第8列的第5个点
        int pointIndex7_1th=(bezierLine0th*fish->bezierStep+5)*3;
        //第10列的第5个点
        int pointIndex7_2th=(bezierLine1th*fish->bezierStep+5)*3;
        //第12列的第5个点
        int pointIndex7_3th=(bezierLine2th*fish->bezierStep+5)*3;
        //第12列的第7个点
        int pointIndex7_4th=(bezierLine2th*fish->bezierStep+7)*3;
        //第10列的第6个点
        int pointIndex8th=(bezierLine1th*fish->bezierStep+6)*3;
        float vertBaseLineVectNor10th[]={BezierAnimationByAngle::vertBaseLineVects[bezierLine0th*3],BezierAnimationByAngle::vertBaseLineVects[bezierLine0th*3+1],
                                         BezierAnimationByAngle::vertBaseLineVects[bezierLine0th*3+2]};
        float vertBaseLineVectNor8th[]={BezierAnimationByAngle::vertBaseLineVects[bezierLine1th*3],BezierAnimationByAngle::vertBaseLineVects[bezierLine1th*3+1],
                                        BezierAnimationByAngle::vertBaseLineVects[bezierLine1th*3+2]};
        float vertBaseLineVectNor12th[]={BezierAnimationByAngle::vertBaseLineVects[bezierLine2th*3],BezierAnimationByAngle::vertBaseLineVects[bezierLine2th*3+1],
                                         BezierAnimationByAngle::vertBaseLineVects[bezierLine2th*3+2]};

        WizardGeomSupple::normalize(vertBaseLineVectNor10th);
        //控制点向上伸出一段距离
        float height=0.009;
        float height2=0.04;
        float topPointX=fish->bezPointGather[pointIndex8th]-vertBaseLineVectNor8th[0]*height;
        float topPointY=fish->bezPointGather[pointIndex8th+1]-vertBaseLineVectNor8th[1]*height;
        float topPointZ=fish->bezPointGather[pointIndex8th+2]-vertBaseLineVectNor8th[2]*height;
        float point0thX=fish->bezPointGather[pointIndex0th]-vertBaseLineVectNor10th[0]*height;
        float point0thY=fish->bezPointGather[pointIndex0th+1]-vertBaseLineVectNor10th[1]*height;
        float point0thZ=fish->bezPointGather[pointIndex0th+2]-vertBaseLineVectNor10th[2]*height;
        float point1thX=fish->bezPointGather[pointIndex1th]-vertBaseLineVectNor8th[0]*height;
        float point1thY=fish->bezPointGather[pointIndex1th+1]-vertBaseLineVectNor8th[1]*height;
        float point1thZ=fish->bezPointGather[pointIndex1th+2]-vertBaseLineVectNor8th[2]*height;
        float point2thX=fish->bezPointGather[pointIndex2th]-vertBaseLineVectNor12th[0]*height2;
        float point2thY=fish->bezPointGather[pointIndex2th+1]-vertBaseLineVectNor12th[1]*height2;
        float point2thZ=fish->bezPointGather[pointIndex2th+2]-vertBaseLineVectNor12th[2]*height2;
        float point4thX=fish->bezPointGather[pointIndex4th]-vertBaseLineVectNor12th[0]*height2;
        float point4thY=fish->bezPointGather[pointIndex4th+1]-vertBaseLineVectNor12th[1]*height2;
        float point4thZ=fish->bezPointGather[pointIndex4th+2]-vertBaseLineVectNor12th[2]*height2;
        float point5thX=fish->bezPointGather[pointIndex5th]-vertBaseLineVectNor8th[0]*height;
        float point5thY=fish->bezPointGather[pointIndex5th+1]-vertBaseLineVectNor8th[1]*height;
        float point5thZ=fish->bezPointGather[pointIndex5th+2]-vertBaseLineVectNor8th[2]*height;
        float point6thX=fish->bezPointGather[pointIndex6th]-vertBaseLineVectNor10th[0]*height;
        float point6thY=fish->bezPointGather[pointIndex6th+1]-vertBaseLineVectNor10th[1]*height;
        float point6thZ=fish->bezPointGather[pointIndex6th+2]-vertBaseLineVectNor10th[2]*height;
        float point7_1thX=fish->bezPointGather[pointIndex7_1th]-vertBaseLineVectNor10th[0]*height;
        float point7_1thY=fish->bezPointGather[pointIndex7_1th+1]-vertBaseLineVectNor10th[1]*height;
        float point7_1thZ=fish->bezPointGather[pointIndex7_1th+2]-vertBaseLineVectNor10th[2]*height;
        float point7_2thX=fish->bezPointGather[pointIndex7_2th]-vertBaseLineVectNor8th[0]*height;
        float point7_2thY=fish->bezPointGather[pointIndex7_2th+1]-vertBaseLineVectNor8th[1]*height;
        float point7_2thZ=fish->bezPointGather[pointIndex7_2th+2]-vertBaseLineVectNor8th[2]*height;
        float point7_3thX=fish->bezPointGather[pointIndex7_3th]-vertBaseLineVectNor12th[0]*height2;
        float point7_3thY=fish->bezPointGather[pointIndex7_3th+1]-vertBaseLineVectNor12th[1]*height2;
        float point7_3thZ=fish->bezPointGather[pointIndex7_3th+2]-vertBaseLineVectNor12th[2]*height2;
        float point7_4thX=fish->bezPointGather[pointIndex7_4th]-vertBaseLineVectNor12th[0]*height2;
        float point7_4thY=fish->bezPointGather[pointIndex7_4th+1]-vertBaseLineVectNor12th[1]*height2;
        float point7_4thZ=fish->bezPointGather[pointIndex7_4th+2]-vertBaseLineVectNor12th[2]*height2;
        //第12列的第7个点和第8列的第5个点之间的向量
        float point0th2topVectNor[]={topPointX-point0thX,topPointY-point0thY,topPointZ-point0thZ};
        WizardGeomSupple::normalize(point0th2topVectNor);
        //第12列的第7个点和第10列的第5个点之间的向量
        float point1th2topVectNor[]={topPointX-point1thX,topPointY-point1thY,topPointZ-point1thZ};
        WizardGeomSupple::normalize(point1th2topVectNor);
        //第12列的第7个点和第12列的第5个点之间的向量
        float point2th2topVectNor[]={topPointX-point2thX,topPointY-point2thY,topPointZ-point2thZ};
        WizardGeomSupple::normalize(point2th2topVectNor);
        //第12列的第7个点和第12列的第7个点之间的向量
        float point4th2topVectNor[]={topPointX-point4thX,topPointY-point4thY,topPointZ-point4thZ};
        WizardGeomSupple::normalize(point4th2topVectNor);
        //第12列的第7个点和第10列的第7个点之间的向量
        float point5th2topVectNor[]={topPointX-point5thX,topPointY-point5thY,topPointZ-point5thZ};
        WizardGeomSupple::normalize(point5th2topVectNor);
        //第12列的第7个点和第8列的第7个点之间的向量
        float point6th2topVectNor[]={topPointX-point6thX,topPointY-point6thY,topPointZ-point6thZ};
        WizardGeomSupple::normalize(point6th2topVectNor);

        float nictaLeng0th=0.07;
        float nictaLeng1th=0.01;//数值稍小一些用于中间的小距离位移
        //眼睛外圈眨眼
        if(isOutBlinkSub){
            shrinkLeng+=0.0003;
            if(shrinkLeng>0.07){
                shrinkLeng=0.07;
                isOutBlinkSub=false;
            }
        }else{
            shrinkLeng-=0.0003;
            if(shrinkLeng<0.0){
                shrinkLeng=0.0;
                isOutBlinkSub= true;
            }
        }




        drawPoints[0]=point0thX,drawPoints[1]=point0thY,drawPoints[2]=point0thZ,
        drawPoints[3]=point1thX,drawPoints[4]=point1thY,drawPoints[5]=point1thZ,
        drawPoints[6]=point2thX,drawPoints[7]=point2thY,drawPoints[8]=point2thZ,
        drawPoints[9]=point4thX,drawPoints[10]=point4thY,drawPoints[11]=point4thZ,
        drawPoints[12]=point5thX+shrinkLeng*point5th2topVectNor[0],drawPoints[13]=point5thY+shrinkLeng*point5th2topVectNor[1],drawPoints[14]=point5thZ+shrinkLeng*point5th2topVectNor[2],
        drawPoints[15]=point6thX,drawPoints[16]=point6thY,drawPoints[17]=point6thZ,
        drawPoints[18]=point7_1thX,drawPoints[19]=point7_1thY,drawPoints[20]=point7_1thZ,
        drawPoints[21]=point7_2thX,drawPoints[22]=point7_2thY,drawPoints[23]=point7_2thZ,
        drawPoints[24]=point7_3thX,drawPoints[25]=point7_3thY,drawPoints[26]=point7_3thZ,
        drawPoints[27]=point7_4thX,drawPoints[28]=point7_4thY,drawPoints[29]=point7_4thZ;

        //眼睛内圈眨眼
        if(isBlinkSub){
            blinkRange+=0.0001;
            if(blinkRange>0.03){
                blinkRange=0.03;
                isBlinkSub=false;
            }
        }else{
            blinkRange-=0.0001;
            if(blinkRange<0.0){
                blinkRange=0.0;
                isBlinkSub= true;
            }
        }


        drawPoints[30]=point0thX+nictaLeng0th*point0th2topVectNor[0],drawPoints[31]=point0thY+nictaLeng0th*point0th2topVectNor[1],drawPoints[32]=point0thZ+nictaLeng0th*point0th2topVectNor[2],
        drawPoints[33]=point1thX+nictaLeng1th*point1th2topVectNor[0],drawPoints[34]=point1thY+nictaLeng1th*point1th2topVectNor[1],drawPoints[35]=point1thZ+nictaLeng1th*point1th2topVectNor[2],
        drawPoints[36]=point2thX+nictaLeng0th*point2th2topVectNor[0],drawPoints[37]=point2thY+nictaLeng0th*point2th2topVectNor[1],drawPoints[38]=point2thZ+nictaLeng0th*point2th2topVectNor[2],
        drawPoints[39]=point4thX+nictaLeng0th*point4th2topVectNor[0],drawPoints[40]=point4thY+nictaLeng0th*point4th2topVectNor[1],drawPoints[41]=point4thZ+nictaLeng0th*point4th2topVectNor[2],
        drawPoints[42]=point5thX+(nictaLeng1th+blinkRange)*point5th2topVectNor[0],drawPoints[43]=point5thY+(nictaLeng1th+blinkRange)*point5th2topVectNor[1],drawPoints[44]=point5thZ+(nictaLeng1th+blinkRange)*point5th2topVectNor[2],
        drawPoints[45]=point6thX+nictaLeng0th*point6th2topVectNor[0],drawPoints[46]=point6thY+nictaLeng0th*point6th2topVectNor[1],drawPoints[47]=point6thZ+nictaLeng0th*point6th2topVectNor[2],
        drawPoints[48]=point7_1thX+nictaLeng0th*point0th2topVectNor[0],drawPoints[49]=point7_1thY+nictaLeng0th*point0th2topVectNor[1],drawPoints[50]=point7_1thZ+nictaLeng0th*point0th2topVectNor[2],
        drawPoints[51]=point7_2thX+nictaLeng1th*point1th2topVectNor[0],drawPoints[52]=point7_2thY+nictaLeng1th*point1th2topVectNor[1],drawPoints[53]=point7_2thZ+nictaLeng1th*point1th2topVectNor[2],
        drawPoints[54]=point7_3thX+nictaLeng0th*point2th2topVectNor[0],drawPoints[55]=point7_3thY+nictaLeng0th*point2th2topVectNor[1],drawPoints[56]=point7_3thZ+nictaLeng0th*point2th2topVectNor[2],
        drawPoints[57]=point7_4thX+nictaLeng0th*point4th2topVectNor[0],drawPoints[58]=point7_4thY+nictaLeng0th*point4th2topVectNor[1],drawPoints[59]=point7_4thZ+nictaLeng0th*point4th2topVectNor[2];


        drawPoints2[0]=topPointX,drawPoints2[1]=topPointY,drawPoints2[2]=topPointZ,
        drawPoints2[3]=topPointX,drawPoints2[4]=topPointY,drawPoints2[5]=topPointZ,
        drawPoints2[6]=topPointX,drawPoints2[7]=topPointY,drawPoints2[8]=topPointZ,
        drawPoints2[9]=topPointX,drawPoints2[10]=topPointY,drawPoints2[11]=topPointZ,
        drawPoints2[12]=topPointX,drawPoints2[13]=topPointY,drawPoints2[14]=topPointZ,
        drawPoints2[15]=topPointX,drawPoints2[16]=topPointY,drawPoints2[17]=topPointZ,
        drawPoints2[18]=topPointX,drawPoints2[19]=topPointY,drawPoints2[20]=topPointZ,
        drawPoints2[21]=topPointX,drawPoints2[22]=topPointY,drawPoints2[23]=topPointZ,
        drawPoints2[24]=topPointX,drawPoints2[25]=topPointY,drawPoints2[26]=topPointZ,
        drawPoints2[27]=topPointX,drawPoints2[28]=topPointY,drawPoints2[29]=topPointZ;

        drawPoints2[30]=drawPoints[30],drawPoints2[31]=drawPoints[31],drawPoints2[32]=drawPoints[32],
        drawPoints2[33]=drawPoints[33],drawPoints2[34]=drawPoints[34],drawPoints2[35]=drawPoints[35],
        drawPoints2[36]=drawPoints[36],drawPoints2[37]=drawPoints[37],drawPoints2[38]=drawPoints[38],
        drawPoints2[39]=drawPoints[39],drawPoints2[40]=drawPoints[40],drawPoints2[41]=drawPoints[41],
        drawPoints2[42]=drawPoints[42],drawPoints2[43]=drawPoints[43],drawPoints2[44]=drawPoints[44],
        drawPoints2[45]=drawPoints[45],drawPoints2[46]=drawPoints[46],drawPoints2[47]=drawPoints[47],
        drawPoints2[48]=drawPoints[48],drawPoints2[49]=drawPoints[49],drawPoints2[50]=drawPoints[50],
        drawPoints2[51]=drawPoints[51],drawPoints2[52]=drawPoints[52],drawPoints2[53]=drawPoints[53],
        drawPoints2[54]=drawPoints[54],drawPoints2[55]=drawPoints[55],drawPoints2[56]=drawPoints[56],
        drawPoints2[57]=drawPoints[57],drawPoints2[58]=drawPoints[58],drawPoints2[59]=drawPoints[59];
        //tag 为0 2代表眼睛
        flyElephantEarFlyElephantEye.MakeEarPoints2(drawPoints, 2, 10, 7,0);
        flyElephantEarFlyElephantEye.MakeEarPoints2(drawPoints2, 2, 10, 7,2);

    }else{
        //嘴巴
        int bezierLine0th=bezierIndex0th,bezierLine1th=bezierIndex1th,bezierLine2th=bezierIndex2th;
        //第8列的第5个点
        int pointIndex0th=(bezierLine0th*fish->bezierStep+6)*3;
        //第10列的第5个点
        int pointIndex1th=(bezierLine1th*fish->bezierStep+6)*3;
        //第12列的第5个点
        int pointIndex2th=(bezierLine2th*fish->bezierStep+6)*3;
        //第12列的第7个点
        int pointIndex4th=(bezierLine2th*fish->bezierStep+9)*3;
        //第10列的第7个点
        int pointIndex5th=(bezierLine1th*fish->bezierStep+9)*3;
        //第8列的第7个点
        int pointIndex6th=(bezierLine0th*fish->bezierStep+9)*3;
        //第8列的第5个点
        int pointIndex7_1th=(bezierLine0th*fish->bezierStep+6)*3;
        //第10列的第5个点
        int pointIndex7_2th=(bezierLine1th*fish->bezierStep+6)*3;
        //第12列的第5个点
        int pointIndex7_3th=(bezierLine2th*fish->bezierStep+6)*3;
        //第12列的第7个点
        int pointIndex7_4th=(bezierLine2th*fish->bezierStep+9)*3;
        //第10列的第6个点
        int pointIndex8th=(bezierLine1th*fish->bezierStep+7)*3;
        float vertBaseLineVectNor10th[]={BezierAnimationByAngle::vertBaseLineVects[bezierLine0th*3],BezierAnimationByAngle::vertBaseLineVects[bezierLine0th*3+1],
                                         BezierAnimationByAngle::vertBaseLineVects[bezierLine0th*3+2]};
        float vertBaseLineVectNor8th[]={BezierAnimationByAngle::vertBaseLineVects[bezierLine1th*3],BezierAnimationByAngle::vertBaseLineVects[bezierLine1th*3+1],
                                        BezierAnimationByAngle::vertBaseLineVects[bezierLine1th*3+2]};
        float vertBaseLineVectNor12th[]={BezierAnimationByAngle::vertBaseLineVects[bezierLine2th*3],BezierAnimationByAngle::vertBaseLineVects[bezierLine2th*3+1],
                                         BezierAnimationByAngle::vertBaseLineVects[bezierLine2th*3+2]};

        WizardGeomSupple::normalize(vertBaseLineVectNor10th);
        //控制点向上伸出一段距离
        float height=0.01;
        float height2=0.04;
        float topPointX=fish->bezPointGather[pointIndex8th]-vertBaseLineVectNor8th[0]*height;
        float topPointY=fish->bezPointGather[pointIndex8th+1]-vertBaseLineVectNor8th[1]*height;
        float topPointZ=fish->bezPointGather[pointIndex8th+2]-vertBaseLineVectNor8th[2]*height;
        float point0thX=fish->bezPointGather[pointIndex0th]-vertBaseLineVectNor10th[0]*height;
        float point0thY=fish->bezPointGather[pointIndex0th+1]-vertBaseLineVectNor10th[1]*height;
        float point0thZ=fish->bezPointGather[pointIndex0th+2]-vertBaseLineVectNor10th[2]*height;
        float point1thX=fish->bezPointGather[pointIndex1th]-vertBaseLineVectNor8th[0]*height;
        float point1thY=fish->bezPointGather[pointIndex1th+1]-vertBaseLineVectNor8th[1]*height;
        float point1thZ=fish->bezPointGather[pointIndex1th+2]-vertBaseLineVectNor8th[2]*height;
        float point2thX=fish->bezPointGather[pointIndex2th]-vertBaseLineVectNor12th[0]*height2;
        float point2thY=fish->bezPointGather[pointIndex2th+1]-vertBaseLineVectNor12th[1]*height2;
        float point2thZ=fish->bezPointGather[pointIndex2th+2]-vertBaseLineVectNor12th[2]*height2;
        float point4thX=fish->bezPointGather[pointIndex4th]-vertBaseLineVectNor12th[0]*height2;
        float point4thY=fish->bezPointGather[pointIndex4th+1]-vertBaseLineVectNor12th[1]*height2;
        float point4thZ=fish->bezPointGather[pointIndex4th+2]-vertBaseLineVectNor12th[2]*height2;
        float point5thX=fish->bezPointGather[pointIndex5th]-vertBaseLineVectNor8th[0]*height;
        float point5thY=fish->bezPointGather[pointIndex5th+1]-vertBaseLineVectNor8th[1]*height;
        float point5thZ=fish->bezPointGather[pointIndex5th+2]-vertBaseLineVectNor8th[2]*height;
        float point6thX=fish->bezPointGather[pointIndex6th]-vertBaseLineVectNor10th[0]*height;
        float point6thY=fish->bezPointGather[pointIndex6th+1]-vertBaseLineVectNor10th[1]*height;
        float point6thZ=fish->bezPointGather[pointIndex6th+2]-vertBaseLineVectNor10th[2]*height;
        float point7_1thX=fish->bezPointGather[pointIndex7_1th]-vertBaseLineVectNor10th[0]*height;
        float point7_1thY=fish->bezPointGather[pointIndex7_1th+1]-vertBaseLineVectNor10th[1]*height;
        float point7_1thZ=fish->bezPointGather[pointIndex7_1th+2]-vertBaseLineVectNor10th[2]*height;
        float point7_2thX=fish->bezPointGather[pointIndex7_2th]-vertBaseLineVectNor8th[0]*height;
        float point7_2thY=fish->bezPointGather[pointIndex7_2th+1]-vertBaseLineVectNor8th[1]*height;
        float point7_2thZ=fish->bezPointGather[pointIndex7_2th+2]-vertBaseLineVectNor8th[2]*height;
        float point7_3thX=fish->bezPointGather[pointIndex7_3th]-vertBaseLineVectNor12th[0]*height2;
        float point7_3thY=fish->bezPointGather[pointIndex7_3th+1]-vertBaseLineVectNor12th[1]*height2;
        float point7_3thZ=fish->bezPointGather[pointIndex7_3th+2]-vertBaseLineVectNor12th[2]*height2;
        float point7_4thX=fish->bezPointGather[pointIndex7_4th]-vertBaseLineVectNor12th[0]*height2;
        float point7_4thY=fish->bezPointGather[pointIndex7_4th+1]-vertBaseLineVectNor12th[1]*height2;
        float point7_4thZ=fish->bezPointGather[pointIndex7_4th+2]-vertBaseLineVectNor12th[2]*height2;

        float point1th2topVectNor[]={topPointX-point1thX,topPointY-point1thY,topPointZ-point1thZ};
        WizardGeomSupple::normalize(point1th2topVectNor);
        float point4th2topVectNor[]={topPointX-point4thX,topPointY-point4thY,topPointZ-point4thZ};
        WizardGeomSupple::normalize(point4th2topVectNor);
        float point5th2topVectNor[]={topPointX-point5thX,topPointY-point5thY,topPointZ-point5thZ};
        WizardGeomSupple::normalize(point5th2topVectNor);
        float point6th2topVectNor[]={topPointX-point6thX,topPointY-point6thY,topPointZ-point6thZ};
        WizardGeomSupple::normalize(point6th2topVectNor);

        if(isSmileSub){
            smileRange-=0.001;
            if(smileRange<0.0){
                smileRange=0.0;
                isSmileSub=false;
            }
            smileDownRange-=0.001;
            if(smileDownRange<-0.01){
                smileDownRange=-0.01;
            }
        }else{
            smileRange+=0.001;
            if(smileRange>0.05){
                smileRange=0.05;
                isSmileSub= true;
            }
            smileDownRange+=0.001;
            if(smileDownRange>0.01){
                smileDownRange=0.01;
            }

        }



        drawPoints3[0]=point0thX,drawPoints3[1]=point0thY,drawPoints3[2]=point0thZ,
        drawPoints3[3]=point1thX+smileRange*point1th2topVectNor[0],drawPoints3[4]=point1thY+smileRange*point1th2topVectNor[1],drawPoints3[5]=point1thZ+smileRange*point1th2topVectNor[2],
        drawPoints3[6]=point2thX,drawPoints3[7]=point2thY,drawPoints3[8]=point2thZ,
        drawPoints3[9]=point4thX+0.04*point4th2topVectNor[0],drawPoints3[10]=point4thY+0.04*point4th2topVectNor[1],drawPoints3[11]=point4thZ+0.04*point4th2topVectNor[2],
        drawPoints3[12]=point5thX+smileDownRange*point5th2topVectNor[0],drawPoints3[13]=point5thY+smileDownRange*point5th2topVectNor[1],drawPoints3[14]=point5thZ+smileDownRange*point5th2topVectNor[2],
        drawPoints3[15]=point6thX+0.04*point6th2topVectNor[0],drawPoints3[16]=point6thY+0.04*point6th2topVectNor[1],drawPoints3[17]=point6thZ+0.04*point6th2topVectNor[2],
        drawPoints3[18]=point7_1thX,drawPoints3[19]=point7_1thY,drawPoints3[20]=point7_1thZ,
        drawPoints3[21]=point7_2thX+smileRange*point1th2topVectNor[0],drawPoints3[22]=point7_2thY+smileRange*point1th2topVectNor[1],drawPoints3[23]=point7_2thZ+smileRange*point1th2topVectNor[2],
        drawPoints3[24]=point7_3thX,drawPoints3[25]=point7_3thY,drawPoints3[26]=point7_3thZ,
        drawPoints3[27]=point7_4thX+0.04*point4th2topVectNor[0],drawPoints3[28]=point7_4thY+0.04*point4th2topVectNor[1],drawPoints3[29]=point7_4thZ+0.04*point4th2topVectNor[2],

        drawPoints3[30]=topPointX,drawPoints3[31]=topPointY,drawPoints3[32]=topPointZ,
        drawPoints3[33]=topPointX,drawPoints3[34]=topPointY,drawPoints3[35]=topPointZ,
        drawPoints3[36]=topPointX,drawPoints3[37]=topPointY,drawPoints3[38]=topPointZ,
        drawPoints3[39]=topPointX,drawPoints3[40]=topPointY,drawPoints3[41]=topPointZ,
        drawPoints3[42]=topPointX,drawPoints3[43]=topPointY,drawPoints3[44]=topPointZ,
        drawPoints3[45]=topPointX,drawPoints3[46]=topPointY,drawPoints3[47]=topPointZ,
        drawPoints3[48]=topPointX,drawPoints3[49]=topPointY,drawPoints3[50]=topPointZ,
        drawPoints3[51]=topPointX,drawPoints3[52]=topPointY,drawPoints3[53]=topPointZ,
        drawPoints3[54]=topPointX,drawPoints3[55]=topPointY,drawPoints3[56]=topPointZ,
        drawPoints3[57]=topPointX,drawPoints3[58]=topPointY,drawPoints3[59]=topPointZ;

        //嘴巴不是眼睛
        flyElephantEarFlyElephantEye.MakeEarPoints2(drawPoints3, 2, 10, 5,1);
    }

    std::memset(drawPoints,0, 60*sizeof(float));
    std::memset(drawPoints2,0, 60*sizeof(float));
    std::memset(drawPoints3,0, 60*sizeof(float));

}

float* FlyElephantEye::getDrawPoints(){
    return drawPoints3;
}