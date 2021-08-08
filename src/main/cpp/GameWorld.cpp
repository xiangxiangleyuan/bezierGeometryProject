#include "GameWorld.h"

GameWorld::GameWorld() {};
GameWorld::~GameWorld() {};

ShaderUtil shaderUtilGameWorld;
FlyElephant flyElephantGameWorld;
float bezierControlPointsMap[3000];

float PI_GAMEWORLD=(3.1415926/180.0);
///////珊瑚的集合////////////
float blinesPoints_coralGroup0th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral0th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral0th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral0th[60000];
float blinesPoints_coralGroup1th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral1th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral1th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral1th[60000];
float blinesPoints_coralGroup2th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral2th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral2th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral2th[60000];
float blinesPoints_coralGroup3th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral3th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral3th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral3th[60000];
float blinesPoints_coralGroup4th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral4th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral4th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral4th[60000];
float blinesPoints_coralGroup5th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral5th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral5th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral5th[60000];
float blinesPoints_coralGroup6th[60000];//珊瑚的样条曲线点的集合
float blinesPointsNormal_coral6th[60000];//珊瑚的样条曲线法线的点
float bezierPointCoral6th[6000];//珊瑚的样条曲线点的集合
float texcoord_coral6th[60000];
//////地板的集合////////////
//地面坐标点的集合
float bezPointGather_floor[6000];
//地面坐标点重新组合后的集合
float bezPointGather_floorGroup[18000];
//地面的纹理坐标集合
float texcoord_floor[12000];
//地板经纬数值的集合
float longLatitudecGather[12000];
/////////////////////////////////
float GameWorld::flowerPosition0[3];
float GameWorld::flowerPosition1[3];
float GameWorld::flowerPosition2[3];
float GameWorld::flowerPosition3[3];
float GameWorld::flowerPosition4[3];
float GameWorld::flowerPosition5[3];

void GameWorld::makeUpBezierLine(float* bezPointGather,float* splitPoints, int sectionNum,int degreeSplitNum,int bezierStep)
{

    //切面个数
    int cutPlaneNum = sectionNum;
    //按度数切分圆的个数
    int degSplNum = degreeSplitNum;
    int compBPNum = cutPlaneNum - 1;
    float bezFract = 1.0 / (bezierStep*1.0);
    float factResArr[10000];//介乘结果的集合
    for (int i = 0; i <= compBPNum; i++){	//求0到n的阶乘
        factResArr[i] = GameWorld::factrial(i);
    }
    //循环每个点
    for (int row = 0; row < degSplNum; row++)
    {
        for (int i = 0; i <= bezierStep; i++)
        {
            //在bezier曲线上的节点的百分数
            float bezFractValue = i*bezFract;
            if (bezFractValue > 1)
            {
                bezFractValue = 1;
            }
            float xf = 0.0;
            float yf = 0.0;
            float zf = 0.0;
            float tka[100000];
            float otka[100000];
            for (int j = 0; j <= compBPNum; j++)
            {
                tka[j] = (float)pow(bezFractValue, j); //计算t的j次幂
                otka[j] = (float)pow(1.0 - bezFractValue, j); //计算1-t的j次幂
            }

            for (int k = 0; k <= compBPNum; k++)
            {
                float xs = (factResArr[compBPNum] / (factResArr[k] * factResArr[compBPNum - k])) * tka[k] * otka[compBPNum - k];

                int cutPlaneindex = k*degSplNum * 3;//每个切面的数值个数
                int pointIndex = row * 3;//一个圆的第几个点的角标
                xf = xf + splitPoints[cutPlaneindex + pointIndex] * xs;
                yf = yf + splitPoints[cutPlaneindex + pointIndex + 1] * xs;
                zf = zf + splitPoints[cutPlaneindex + pointIndex + 2] * xs;

            }
            int currIndex = bezierStep*row * 3;//当前bezier线条的角标值

            bezPointGather[currIndex + i * 3] = xf;
            bezPointGather[currIndex + i * 3 + 1] = yf;
            bezPointGather[currIndex + i * 3 + 2] = zf;

        }

    }


}

//介乘
int GameWorld::factrial(int factrialCount)
{
    int factrialResult = 1;	//声明一个long型的变量
    if (factrialCount == 0)			//0的阶乘为1
    {
        return 1;
    }

    for (int i = 2; i <= factrialCount; i++){	//求大于等于2的数的阶乘
        factrialResult = factrialResult*i;
    }

    return factrialResult;	//返回结果

}

//初始化地面
void GameWorld::initGameWorld() {
    float floorHeight=-9.0;
    float splitPoints[150]={50.0,floorHeight,32.0,    43.0,floorHeight,26.0,     35.0,floorHeight,22.0,     29.0,floorHeight,18.0,      27.0,floorHeight,16.0,      25.0,floorHeight,15.0,      23.0,floorHeight,14.0,     //8.0,-2.0,5.0,
                            36.0,floorHeight,32.0,    30.0,floorHeight,26.0,     26.0,floorHeight,22.0,     23.0,floorHeight,18.0,       21.0,floorHeight,16.0,       17.0,floorHeight,15.0,      10.0,floorHeight,14.0,     //4.0,-2.0,5.0,
                            8.0,floorHeight+7.0f,32.0,    8.0,floorHeight+4.0f,26.0,     8.0,floorHeight,22.0,     8.0,floorHeight,18.0,       8.0,floorHeight,16.0,        8.0,floorHeight,15.0,       8.0,floorHeight,14.0,      //0.0,-2.0,5.0,
                            -8.0,floorHeight-3.0f,32.0,     -8.0,floorHeight-1.0f,26.0,      -8.0,floorHeight,22.0,     -8.0,floorHeight,18.0,        -8.0,floorHeight,16.0,       -8.0,floorHeight,15.0,      -8.0,floorHeight,14.0,    //-4.0,-2.0,5.0,
                            -36.0,floorHeight,32.0,   -30.0,floorHeight,26.0,    -26.0,floorHeight,22.0,    -23.0,floorHeight,18.0,      -21.0,floorHeight,16.0,      -17.0,floorHeight,15.0,     -10.0,floorHeight,14.0,    //-8.0,-2.0,5.0
                            -54.0,floorHeight,32.0,   -44.0,floorHeight,26.0,    -37.0,floorHeight,22.0,    -32.0,floorHeight,18.0,      -29.0,floorHeight,16.0,      -27.0,floorHeight,15.0,     -25.0,floorHeight,14.0};    //-13.0,-2.0,5.0};
//    for(int i=0;i<42;i++){
//        splitPoints[i*3+1]-=9.6;
//    }
    int sectionNum=6;
    int bezierStep=30;
    int rowTotal=6;
    GameWorld::makeUpBezierLine(bezPointGather_floor,splitPoints,sectionNum,rowTotal+1,bezierStep);
    for(int rowIndex=0;rowIndex<rowTotal;rowIndex++)
    {
        for(int i=0;i<bezierStep-1;i++){
            int bezierStep1=(rowIndex*bezierStep+i)*3;
            int bezierStep2=((rowIndex+1)*bezierStep+i)*3;

            float x1=bezPointGather_floor[bezierStep1];
            float y1=bezPointGather_floor[bezierStep1+1];
            float z1=bezPointGather_floor[bezierStep1+2];

            float x2=bezPointGather_floor[bezierStep2];
            float y2=bezPointGather_floor[bezierStep2+1];
            float z2=bezPointGather_floor[bezierStep2+2];

            float x3=bezPointGather_floor[bezierStep2+3];
            float y3=bezPointGather_floor[bezierStep2+4];
            float z3=bezPointGather_floor[bezierStep2+5];

            float x1_=bezPointGather_floor[bezierStep2+3];
            float y1_=bezPointGather_floor[bezierStep2+4];
            float z1_=bezPointGather_floor[bezierStep2+5];

            float x2_=bezPointGather_floor[bezierStep1];
            float y2_=bezPointGather_floor[bezierStep1+1];
            float z2_=bezPointGather_floor[bezierStep1+2];

            float x3_=bezPointGather_floor[bezierStep1+3];
            float y3_=bezPointGather_floor[bezierStep1+4];
            float z3_=bezPointGather_floor[bezierStep1+5];

            int pointBaseIndex=i*18+bezierStep*18*rowIndex;
            bezPointGather_floorGroup[pointBaseIndex]=x1;
            bezPointGather_floorGroup[pointBaseIndex+1]=y1;
            bezPointGather_floorGroup[pointBaseIndex+2]=z1;
            bezPointGather_floorGroup[pointBaseIndex+3]=x2;
            bezPointGather_floorGroup[pointBaseIndex+4]=y2;
            bezPointGather_floorGroup[pointBaseIndex+5]=z2;
            bezPointGather_floorGroup[pointBaseIndex+6]=x3;
            bezPointGather_floorGroup[pointBaseIndex+7]=y3;
            bezPointGather_floorGroup[pointBaseIndex+8]=z3;
            bezPointGather_floorGroup[pointBaseIndex+9]=x1_;
            bezPointGather_floorGroup[pointBaseIndex+10]=y1_;
            bezPointGather_floorGroup[pointBaseIndex+11]=z1_;
            bezPointGather_floorGroup[pointBaseIndex+12]=x2_;
            bezPointGather_floorGroup[pointBaseIndex+13]=y2_;
            bezPointGather_floorGroup[pointBaseIndex+14]=z2_;
            bezPointGather_floorGroup[pointBaseIndex+15]=x3_;
            bezPointGather_floorGroup[pointBaseIndex+16]=y3_;
            bezPointGather_floorGroup[pointBaseIndex+17]=z3_;

            int textureIndex=12*i+bezierStep*12*rowIndex;
            texcoord_floor[textureIndex]=float(i)/float(bezierStep);
            texcoord_floor[textureIndex+1]=float(rowIndex)/float(rowTotal);
            texcoord_floor[textureIndex+2]=float(i)/float(bezierStep);
            texcoord_floor[textureIndex+3]=float(rowIndex+1)/float(rowTotal);
            texcoord_floor[textureIndex+4]=float(i+1)/float(bezierStep);
            texcoord_floor[textureIndex+5]=float(rowIndex+1)/float(rowTotal);

            texcoord_floor[textureIndex+6]=float(i+1)/float(bezierStep);
            texcoord_floor[textureIndex+7]=float(rowIndex+1)/float(rowTotal);
            texcoord_floor[textureIndex+8]=float(i)/float(bezierStep);
            texcoord_floor[textureIndex+9]=float(rowIndex)/float(rowTotal);
            texcoord_floor[textureIndex+10]=float(i+1)/float(bezierStep);
            texcoord_floor[textureIndex+11]=float(rowIndex)/float(rowTotal);

            longLatitudecGather[textureIndex]=i;
            longLatitudecGather[textureIndex+1]=rowIndex;
            longLatitudecGather[textureIndex+2]=i;
            longLatitudecGather[textureIndex+3]=rowIndex+1;
            longLatitudecGather[textureIndex+4]=i+1;
            longLatitudecGather[textureIndex+5]=rowIndex+1;
            longLatitudecGather[textureIndex+6]=i+1;
            longLatitudecGather[textureIndex+7]=rowIndex+1;
            longLatitudecGather[textureIndex+8]=i;
            longLatitudecGather[textureIndex+9]=rowIndex;
            longLatitudecGather[textureIndex+10]=i+1;
            longLatitudecGather[textureIndex+11]=rowIndex;

        }

    }


}


void GameWorld::makeUpBspline(int blineSplitNum,int bezierStep,int degreeSplitNum,
        float* blinesPoints_coralGroup,float* blinesPointsNormal_coral,float* bezierPointCoral,float* texcoord_coral)
{
    float blinesPointsGather[6000];
    float blinesPointsNormalGather[6000];
    float f1, f2, f3, f4;
    float deltaT = 1.0 / float(blineSplitNum);
    float T;
    for (int i = 0; i < blineSplitNum; i++)
    {
        T = float(i)*deltaT;
        f1 = (-T*T*T + 3 * T*T - 3 * T + 1) / 6.0;
        f2 = (3 * T*T*T - 6 * T*T + 4) / 6.0;
        f3 = (-3 * T*T*T + 3 * T*T + 3 * T + 1) / 6.0;
        f4 = (T*T*T) / 6.0;

        for (int m = 0; m < bezierStep; m++) //每条贝塞尔线段上拥有的点数  贝塞尔线段上的第m个点
        {
            //每个闭环包含的段数 * 每个曲线段包含的点个数 * 3 * 第m个闭合圈   每个闭合圈所包含的数值个数   +3是加的3条线段
            int loopIndex = (degreeSplitNum + 3) * blineSplitNum * 3 * m;
            int mIndex1 = m * 3; //贝塞尔线段上的第 m 个点的索引
            int mIndex2 = mIndex1 + 1;
            int mIndex3 = mIndex2 + 1;
            for (int j = 0; j < degreeSplitNum; j++) {
                //j * steps * 3  横截面的第j个点
                float x = f1 * bezierPointCoral[j * bezierStep * 3 + mIndex1] +
                          f2 * bezierPointCoral[(j + 1) * bezierStep * 3 + mIndex1] +
                          f3 * bezierPointCoral[(j + 2) * bezierStep * 3 + mIndex1] +
                          f4 * bezierPointCoral[(j + 3) * bezierStep * 3 + mIndex1];
                float y = f1 * bezierPointCoral[j * bezierStep * 3 + mIndex2] +
                          f2 * bezierPointCoral[(j + 1) * bezierStep * 3 + mIndex2] +
                          f3 * bezierPointCoral[(j + 2) * bezierStep * 3 + mIndex2] +
                          f4 * bezierPointCoral[(j + 3) * bezierStep * 3 + mIndex2];
                float z = f1 * bezierPointCoral[j * bezierStep * 3 + mIndex3] +
                          f2 * bezierPointCoral[(j + 1) * bezierStep * 3 + mIndex3] +
                          f3 * bezierPointCoral[(j + 2) * bezierStep * 3 + mIndex3] +
                          f4 * bezierPointCoral[(j + 3) * bezierStep * 3 + mIndex3];
                int secNum = blineSplitNum * 3 * j;//到第 j 个点时，当下的索引值
                int blindex = secNum + i * 3 + loopIndex;

                blinesPointsGather[blindex] = x;
                blinesPointsGather[blindex + 1] = y;
                blinesPointsGather[blindex + 2] = z;


                float blinePoints1X=bezierPointCoral[j * bezierStep * 3 + mIndex1];
                float blinePoints2X=bezierPointCoral[(j + 1) * bezierStep * 3 + mIndex1];
                float blinePoints3X=bezierPointCoral[(j + 2) * bezierStep * 3 + mIndex1];
                float blinePoints4X=bezierPointCoral[(j + 3) * bezierStep * 3 + mIndex1];
                float blinePoints1Y=bezierPointCoral[j * bezierStep * 3 + mIndex2];
                float blinePoints2Y=bezierPointCoral[(j + 1) * bezierStep * 3 + mIndex2];
                float blinePoints3Y=bezierPointCoral[(j + 2) * bezierStep * 3 + mIndex2];
                float blinePoints4Y=bezierPointCoral[(j + 3) * bezierStep * 3 + mIndex2];
                float blinePoints1Z=bezierPointCoral[j * bezierStep * 3 + mIndex3];
                float blinePoints2Z=bezierPointCoral[(j + 1) * bezierStep * 3 + mIndex3];
                float blinePoints3Z=bezierPointCoral[(j + 2) * bezierStep * 3 + mIndex3];
                float blinePoints4Z=bezierPointCoral[(j + 3) * bezierStep * 3 + mIndex3];

                float normalX=blinePoints1X-2.0*blinePoints2X+blinePoints3X+T*(3.0*blinePoints2X-blinePoints1X-3.0*blinePoints3X+blinePoints4X);
                float normalY=blinePoints1Y-2.0*blinePoints2Y+blinePoints3Y+T*(3.0*blinePoints2Y-blinePoints1Y-3.0*blinePoints3Y+blinePoints4Y);
                float normalZ=blinePoints1Z-2.0*blinePoints2Z+blinePoints3Z+T*(3.0*blinePoints2Z-blinePoints1Z-3.0*blinePoints3Z+blinePoints4Z);

                blinesPointsNormalGather[blindex] = normalX;
                blinesPointsNormalGather[blindex + 1] = normalY;
                blinesPointsNormalGather[blindex + 2] = normalZ;
            }

            //横截面的最后三个点
            float x4 = f1*bezierPointCoral[degreeSplitNum * bezierStep * 3 + mIndex1] + f2*bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1] + f3*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1] + f4*bezierPointCoral[mIndex1];
            float y4 = f1*bezierPointCoral[degreeSplitNum * bezierStep * 3 + mIndex2] + f2*bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex2] + f3*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2] + f4*bezierPointCoral[mIndex2];
            float z4 = f1*bezierPointCoral[degreeSplitNum * bezierStep * 3 + mIndex3] + f2*bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex3] + f3*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3] + f4*bezierPointCoral[mIndex3];

            float blinePoints1X_4=bezierPointCoral[degreeSplitNum * bezierStep * 3 + mIndex1];
            float blinePoints2X_4=bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1];
            float blinePoints3X_4=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1];
            float blinePoints4X_4=bezierPointCoral[mIndex1];
            float blinePoints1Y_4=bezierPointCoral[degreeSplitNum * bezierStep * 3 + mIndex2];
            float blinePoints2Y_4=bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex2];
            float blinePoints3Y_4=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2];
            float blinePoints4Y_4=bezierPointCoral[mIndex2];
            float blinePoints1Z_4=bezierPointCoral[degreeSplitNum * bezierStep * 3 + mIndex3];
            float blinePoints2Z_4=bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex3];
            float blinePoints3Z_4=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3];
            float blinePoints4Z_4=bezierPointCoral[mIndex3];

            float normalX4=blinePoints1X_4-2.0*blinePoints2X_4+blinePoints3X_4+T*(3.0*blinePoints2X_4-blinePoints1X_4-3.0*blinePoints3X_4+blinePoints4X_4);
            float normalY4=blinePoints1Y_4-2.0*blinePoints2Y_4+blinePoints3Y_4+T*(3.0*blinePoints2Y_4-blinePoints1Y_4-3.0*blinePoints3Y_4+blinePoints4Y_4);
            float normalZ4=blinePoints1Z_4-2.0*blinePoints2Z_4+blinePoints3Z_4+T*(3.0*blinePoints2Z_4-blinePoints1Z_4-3.0*blinePoints3Z_4+blinePoints4Z_4);

            float x5 = f1*bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1] + f2*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1] + f3*bezierPointCoral[mIndex1] + f4*bezierPointCoral[bezierStep * 3 + mIndex1];
            float y5 = f1*bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex2] + f2*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2] + f3*bezierPointCoral[mIndex2] + f4*bezierPointCoral[bezierStep * 3 + mIndex2];
            float z5 = f1*bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex3] + f2*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3] + f3*bezierPointCoral[mIndex3] + f4*bezierPointCoral[bezierStep * 3 + mIndex3];

            float blinePoints1X_5=bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1];
            float blinePoints2X_5=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1];
            float blinePoints3X_5=bezierPointCoral[mIndex1];
            float blinePoints4X_5=bezierPointCoral[bezierStep * 3 + mIndex1];
            float blinePoints1Y_5=bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1];
            float blinePoints2Y_5=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1];
            float blinePoints3Y_5=bezierPointCoral[mIndex1];
            float blinePoints4Y_5=bezierPointCoral[bezierStep * 3 + mIndex1];
            float blinePoints1Z_5=bezierPointCoral[(degreeSplitNum + 1) * bezierStep * 3 + mIndex1];
            float blinePoints2Z_5=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1];
            float blinePoints3Z_5=bezierPointCoral[mIndex1];
            float blinePoints4Z_5=bezierPointCoral[bezierStep * 3 + mIndex1];

            float normalX5=blinePoints1X_5-2.0*blinePoints2X_5+blinePoints3X_5+T*(3.0*blinePoints2X_5-blinePoints1X_5-3.0*blinePoints3X_5+blinePoints4X_5);
            float normalY5=blinePoints1Y_5-2.0*blinePoints2Y_5+blinePoints3Y_5+T*(3.0*blinePoints2Y_5-blinePoints1Y_5-3.0*blinePoints3Y_5+blinePoints4Y_5);
            float normalZ5=blinePoints1Z_5-2.0*blinePoints2Z_5+blinePoints3Z_5+T*(3.0*blinePoints2Z_5-blinePoints1Z_5-3.0*blinePoints3Z_5+blinePoints4Z_5);

            float x6 = f1*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1] + f2*bezierPointCoral[mIndex1] + f3*bezierPointCoral[bezierStep * 3 + mIndex1] + f4*bezierPointCoral[2 * bezierStep * 3 + mIndex1];
            float y6 = f1*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2] + f2*bezierPointCoral[mIndex2] + f3*bezierPointCoral[bezierStep * 3 + mIndex2] + f4*bezierPointCoral[2 * bezierStep * 3 + mIndex2];
            float z6 = f1*bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3] + f2*bezierPointCoral[mIndex3] + f3*bezierPointCoral[bezierStep * 3 + mIndex3] + f4*bezierPointCoral[2 * bezierStep * 3 + mIndex3];
            int lastThirdIndex = i * 3 + blineSplitNum * 3 * degreeSplitNum + loopIndex;

            float blinePoints1X_6=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex1];
            float blinePoints2X_6=bezierPointCoral[mIndex1];
            float blinePoints3X_6=bezierPointCoral[bezierStep * 3 + mIndex1];
            float blinePoints4X_6=bezierPointCoral[2 * bezierStep * 3 + mIndex1];
            float blinePoints1Y_6=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex2];
            float blinePoints2Y_6=bezierPointCoral[mIndex2];
            float blinePoints3Y_6=bezierPointCoral[bezierStep * 3 + mIndex2];
            float blinePoints4Y_6=bezierPointCoral[2 * bezierStep * 3 + mIndex2];
            float blinePoints1Z_6=bezierPointCoral[(degreeSplitNum + 2) * bezierStep * 3 + mIndex3];
            float blinePoints2Z_6=bezierPointCoral[mIndex3];
            float blinePoints3Z_6=bezierPointCoral[bezierStep * 3 + mIndex3];
            float blinePoints4Z_6=bezierPointCoral[2 * bezierStep * 3 + mIndex3];

            float normalX6=blinePoints1X_6-2.0*blinePoints2X_6+blinePoints3X_6+T*(3.0*blinePoints2X_6-blinePoints1X_6-3.0*blinePoints3X_6+blinePoints4X_6);
            float normalY6=blinePoints1Y_6-2.0*blinePoints2Y_6+blinePoints3Y_6+T*(3.0*blinePoints2Y_6-blinePoints1Y_6-3.0*blinePoints3Y_6+blinePoints4Y_6);
            float normalZ6=blinePoints1Z_6-2.0*blinePoints2Z_6+blinePoints3Z_6+T*(3.0*blinePoints2Z_6-blinePoints1Z_6-3.0*blinePoints3Z_6+blinePoints4Z_6);

            blinesPointsGather[lastThirdIndex] = x4;
            blinesPointsGather[lastThirdIndex + 1] = y4;
            blinesPointsGather[lastThirdIndex + 2] = z4;

            blinesPointsNormalGather[lastThirdIndex]=normalX4;
            blinesPointsNormalGather[lastThirdIndex+1]=normalY4;
            blinesPointsNormalGather[lastThirdIndex+2]=normalZ4;

            int lastSecondIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 1) + loopIndex;

            blinesPointsGather[lastSecondIndex] = x5;
            blinesPointsGather[lastSecondIndex + 1] = y5;
            blinesPointsGather[lastSecondIndex + 2] = z5;

            blinesPointsNormalGather[lastSecondIndex]=normalX5;
            blinesPointsNormalGather[lastSecondIndex+1]=normalY5;
            blinesPointsNormalGather[lastSecondIndex+2]=normalZ5;

            int lastOneIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 2) + loopIndex;

            blinesPointsGather[lastOneIndex] = x6;
            blinesPointsGather[lastOneIndex + 1] = y6;
            blinesPointsGather[lastOneIndex + 2] = z6;

            blinesPointsNormalGather[lastOneIndex]=normalX6;
            blinesPointsNormalGather[lastOneIndex+1]=normalY6;
            blinesPointsNormalGather[lastOneIndex+2]=normalZ6;

            float x7 = f1*bezierPointCoral[mIndex1] + f2*bezierPointCoral[bezierStep * 3 + mIndex1] + f3*bezierPointCoral[2 * bezierStep * 3 + mIndex1]+ f4*bezierPointCoral[3 * bezierStep * 3 + mIndex1];
            float y7 = f1*bezierPointCoral[mIndex2] + f2*bezierPointCoral[bezierStep * 3 + mIndex2] + f3*bezierPointCoral[2 * bezierStep * 3 + mIndex2]+ f4*bezierPointCoral[3 * bezierStep * 3 + mIndex2];
            float z7 = f1*bezierPointCoral[mIndex3] + f2*bezierPointCoral[bezierStep * 3 + mIndex3] + f3*bezierPointCoral[2 * bezierStep * 3 + mIndex3]+ f4*bezierPointCoral[3 * bezierStep * 3 + mIndex3];
            int lastIndex = i * 3 + blineSplitNum * 3 * (degreeSplitNum + 3) + loopIndex;

            blinesPointsGather[lastIndex] = x7;
            blinesPointsGather[lastIndex + 1] = y7;
            blinesPointsGather[lastIndex + 2] = z7;

            float blinePoints1X_7=bezierPointCoral[mIndex1];
            float blinePoints2X_7=bezierPointCoral[bezierStep * 3 + mIndex1];
            float blinePoints3X_7=bezierPointCoral[2 * bezierStep * 3 + mIndex1];
            float blinePoints4X_7=bezierPointCoral[3 * bezierStep * 3 + mIndex1];
            float blinePoints1Y_7=bezierPointCoral[mIndex2];
            float blinePoints2Y_7=bezierPointCoral[bezierStep * 3 + mIndex2];
            float blinePoints3Y_7=bezierPointCoral[2 * bezierStep * 3 + mIndex2];
            float blinePoints4Y_7=bezierPointCoral[3 * bezierStep * 3 + mIndex2];
            float blinePoints1Z_7=bezierPointCoral[mIndex3];
            float blinePoints2Z_7=bezierPointCoral[bezierStep * 3 + mIndex3];
            float blinePoints3Z_7=bezierPointCoral[2 * bezierStep * 3 + mIndex3];
            float blinePoints4Z_7=bezierPointCoral[3 * bezierStep * 3 + mIndex3];

            float normalX7=blinePoints1X_7-2.0*blinePoints2X_7+blinePoints3X_7+T*(3.0*blinePoints2X_7-blinePoints1X_7-3.0*blinePoints3X_7+blinePoints4X_7);
            float normalY7=blinePoints1Y_7-2.0*blinePoints2Y_7+blinePoints3Y_7+T*(3.0*blinePoints2Y_7-blinePoints1Y_7-3.0*blinePoints3Y_7+blinePoints4Y_7);
            float normalZ7=blinePoints1Z_7-2.0*blinePoints2Z_7+blinePoints3Z_7+T*(3.0*blinePoints2Z_7-blinePoints1Z_7-3.0*blinePoints3Z_7+blinePoints4Z_7);


            blinesPointsNormalGather[lastIndex]=normalX7;
            blinesPointsNormalGather[lastIndex+1]=normalY7;
            blinesPointsNormalGather[lastIndex+2]=normalZ7;
        }
    }

    int count=0;
    int everyCircleNum=(degreeSplitNum+3)*blineSplitNum;
    for(int bezierStepIndex=0;bezierStepIndex<bezierStep-1;bezierStepIndex++){
        for(int rowIndex=0;rowIndex<everyCircleNum;rowIndex++){

            float x1=blinesPointsGather[(bezierStepIndex*everyCircleNum+rowIndex)*3];
            float y1=blinesPointsGather[(bezierStepIndex*everyCircleNum+rowIndex)*3+1];
            float z1=blinesPointsGather[(bezierStepIndex*everyCircleNum+rowIndex)*3+2];


            float x2=blinesPointsGather[((bezierStepIndex+1)*everyCircleNum+rowIndex)*3];
            float y2=blinesPointsGather[((bezierStepIndex+1)*everyCircleNum+rowIndex)*3+1];
            float z2=blinesPointsGather[((bezierStepIndex+1)*everyCircleNum+rowIndex)*3+2];

            float x3=blinesPointsGather[((bezierStepIndex+1)*everyCircleNum+(rowIndex+1))*3];
            float y3=blinesPointsGather[((bezierStepIndex+1)*everyCircleNum+(rowIndex+1))*3+1];
            float z3=blinesPointsGather[((bezierStepIndex+1)*everyCircleNum+(rowIndex+1))*3+2];

            float x1_=x3;
            float y1_=y3;
            float z1_=z3;

            float x2_=x1;
            float y2_=y1;
            float z2_=z1;

            float x3_=blinesPointsGather[(bezierStepIndex*everyCircleNum+(rowIndex+1))*3];
            float y3_=blinesPointsGather[(bezierStepIndex*everyCircleNum+(rowIndex+1))*3+1];
            float z3_=blinesPointsGather[(bezierStepIndex*everyCircleNum+(rowIndex+1))*3+2];

            int pointBaseIndex=18*count;
            blinesPoints_coralGroup[pointBaseIndex]=x1;
            blinesPoints_coralGroup[pointBaseIndex+1]=y1;
            blinesPoints_coralGroup[pointBaseIndex+2]=z1;
            blinesPoints_coralGroup[pointBaseIndex+3]=x2;
            blinesPoints_coralGroup[pointBaseIndex+4]=y2;
            blinesPoints_coralGroup[pointBaseIndex+5]=z2;
            blinesPoints_coralGroup[pointBaseIndex+6]=x3;
            blinesPoints_coralGroup[pointBaseIndex+7]=y3;
            blinesPoints_coralGroup[pointBaseIndex+8]=z3;
            blinesPoints_coralGroup[pointBaseIndex+9]=x1_;
            blinesPoints_coralGroup[pointBaseIndex+10]=y1_;
            blinesPoints_coralGroup[pointBaseIndex+11]=z1_;
            blinesPoints_coralGroup[pointBaseIndex+12]=x2_;
            blinesPoints_coralGroup[pointBaseIndex+13]=y2_;
            blinesPoints_coralGroup[pointBaseIndex+14]=z2_;
            blinesPoints_coralGroup[pointBaseIndex+15]=x3_;
            blinesPoints_coralGroup[pointBaseIndex+16]=y3_;
            blinesPoints_coralGroup[pointBaseIndex+17]=z3_;

//            int textureIndex=12*rowIndex+everyCircleNum*12*bezierStepIndex;
            int textureIndex=12*count;
            texcoord_coral[textureIndex]=float(bezierStepIndex)/float(bezierStep);
            texcoord_coral[textureIndex+1]=float(rowIndex)/float(everyCircleNum+1);
            texcoord_coral[textureIndex+2]=float(bezierStepIndex+1)/float(bezierStep);
            texcoord_coral[textureIndex+3]=float(rowIndex)/float(everyCircleNum+1);
            texcoord_coral[textureIndex+4]=float(bezierStepIndex+1)/float(bezierStep);
            texcoord_coral[textureIndex+5]=float(rowIndex+1)/float(everyCircleNum+1);
            texcoord_coral[textureIndex+6]=float(bezierStepIndex+1)/float(bezierStep);
            texcoord_coral[textureIndex+7]=float(rowIndex+1)/float(everyCircleNum+1);
            texcoord_coral[textureIndex+8]=float(bezierStepIndex)/float(bezierStep);
            texcoord_coral[textureIndex+9]=float(rowIndex)/float(everyCircleNum+1);
            texcoord_coral[textureIndex+10]=float(bezierStepIndex)/float(bezierStep);
            texcoord_coral[textureIndex+11]=float(rowIndex+1)/float(everyCircleNum+1);


            float normalx1=blinesPointsNormalGather[(bezierStepIndex*everyCircleNum+rowIndex)*3];
            float normaly1=blinesPointsNormalGather[(bezierStepIndex*everyCircleNum+rowIndex)*3+1];
            float normalz1=blinesPointsNormalGather[(bezierStepIndex*everyCircleNum+rowIndex)*3+2];

            float normalx2=blinesPointsNormalGather[((bezierStepIndex+1)*everyCircleNum+rowIndex)*3];
            float normaly2=blinesPointsNormalGather[((bezierStepIndex+1)*everyCircleNum+rowIndex)*3+1];
            float normalz2=blinesPointsNormalGather[((bezierStepIndex+1)*everyCircleNum+rowIndex)*3+2];

            float normalx3=blinesPointsNormalGather[((bezierStepIndex+1)*everyCircleNum+(rowIndex+1))*3];
            float normaly3=blinesPointsNormalGather[((bezierStepIndex+1)*everyCircleNum+(rowIndex+1))*3+1];
            float normalz3=blinesPointsNormalGather[((bezierStepIndex+1)*everyCircleNum+(rowIndex+1))*3+2];

            float normalx1_=normalx3;
            float normaly1_=normaly3;
            float normalz1_=normalz3;

            float normalx2_=normalx1;
            float normaly2_=normaly1;
            float normalz2_=normalz1;

            float normalx3_=blinesPointsNormalGather[(bezierStepIndex*everyCircleNum+(rowIndex+1))*3];
            float normaly3_=blinesPointsNormalGather[(bezierStepIndex*everyCircleNum+(rowIndex+1))*3+1];
            float normalz3_=blinesPointsNormalGather[(bezierStepIndex*everyCircleNum+(rowIndex+1))*3+2];

            blinesPointsNormal_coral[pointBaseIndex]=normalx1;
            blinesPointsNormal_coral[pointBaseIndex+1]=normaly1;
            blinesPointsNormal_coral[pointBaseIndex+2]=normalz1;
            blinesPointsNormal_coral[pointBaseIndex+3]=normalx2;
            blinesPointsNormal_coral[pointBaseIndex+4]=normaly2;
            blinesPointsNormal_coral[pointBaseIndex+5]=normalz2;
            blinesPointsNormal_coral[pointBaseIndex+6]=normalx3;
            blinesPointsNormal_coral[pointBaseIndex+7]=normaly3;
            blinesPointsNormal_coral[pointBaseIndex+8]=normalz3;
            blinesPointsNormal_coral[pointBaseIndex+9]=normalx1_;
            blinesPointsNormal_coral[pointBaseIndex+10]=normaly1_;
            blinesPointsNormal_coral[pointBaseIndex+11]=normalz1_;
            blinesPointsNormal_coral[pointBaseIndex+12]=normalx2_;
            blinesPointsNormal_coral[pointBaseIndex+13]=normaly2_;
            blinesPointsNormal_coral[pointBaseIndex+14]=normalz2_;
            blinesPointsNormal_coral[pointBaseIndex+15]=normalx3_;
            blinesPointsNormal_coral[pointBaseIndex+16]=normaly3_;
            blinesPointsNormal_coral[pointBaseIndex+17]=normalz3_;
            count++;
        }

    }

}

void GameWorld::initCoralReef(){
    ////////////////////扁的珊瑚////////////////
    float baseX=bezPointGather_floor[10*3]+6.0;
    float baseY=bezPointGather_floor[10*3+1]+2.0;
    float baseZ=bezPointGather_floor[10*3+2]-2.0;
    float aloneYMoveLeng=tanf(PI_GAMEWORLD*8.0f);
    float oppoAngleVectNor1[]={1.0,0.0,0.0};
    oppoAngleVectNor1[1]+=aloneYMoveLeng;
    WizardGeomSupple::normalize(oppoAngleVectNor1);
    float oppoAngleVectNor2[]={1.0,0.0,-1.0};
    WizardGeomSupple::normalize(oppoAngleVectNor2);
    float oppoAngleVectNor3[]={0.0,0.0,-1.0};
    oppoAngleVectNor3[1]-=aloneYMoveLeng;
    WizardGeomSupple::normalize(oppoAngleVectNor3);
    float oppoAngleVectNor4[]={-1.0,0.0,-1.0};
    WizardGeomSupple::normalize(oppoAngleVectNor4);
    oppoAngleVectNor4[1]-=aloneYMoveLeng;
    WizardGeomSupple::normalize(oppoAngleVectNor4);
    float oppoAngleVectNor5[]={-1.0,0.0,0.0};
    WizardGeomSupple::normalize(oppoAngleVectNor5);
    float oppoAngleVectNor6[]={0.0,0.0,1.0};
    oppoAngleVectNor6[1]+=aloneYMoveLeng;
    WizardGeomSupple::normalize(oppoAngleVectNor6);

    float radius2=1.5;
    float radius3=2.0;
    float radius4=5.0;
    float radius5=13.0;
    float radius6=9.0;
    float radius7=5.0;
    float radius8=2.0;


    float height2=6.0;
    float height3=6.5;
    float height4=7.0;
    float height5=5.0;
    float height6=5.0;
    float height7=4.0;

    float bezierControlPoints[]={
            baseX+radius8*oppoAngleVectNor1[0],baseY+radius8*oppoAngleVectNor1[1]+height7,baseZ+radius8*oppoAngleVectNor1[2],
            baseX+radius8*oppoAngleVectNor2[0],baseY+radius8*oppoAngleVectNor2[1]+height7,baseZ+radius8*oppoAngleVectNor2[2],
            baseX+radius8*oppoAngleVectNor3[0],baseY+radius8*oppoAngleVectNor3[1]+height7,baseZ+radius8*oppoAngleVectNor3[2],
            baseX+radius8*oppoAngleVectNor4[0],baseY+radius8*oppoAngleVectNor4[1]+height7,baseZ+radius8*oppoAngleVectNor4[2],
            baseX+radius8*oppoAngleVectNor5[0],baseY+radius8*oppoAngleVectNor5[1]+height7,baseZ+radius8*oppoAngleVectNor5[2],
            baseX+radius8*oppoAngleVectNor6[0],baseY+radius8*oppoAngleVectNor6[1]+height7,baseZ+radius8*oppoAngleVectNor6[2],

            baseX+radius7*oppoAngleVectNor1[0],baseY+radius7*oppoAngleVectNor1[1]+height7,baseZ+radius7*oppoAngleVectNor1[2],
            baseX+radius7*oppoAngleVectNor2[0],baseY+radius7*oppoAngleVectNor2[1]+height7,baseZ+radius7*oppoAngleVectNor2[2],
            baseX+radius7*oppoAngleVectNor3[0],baseY+radius7*oppoAngleVectNor3[1]+height7,baseZ+radius7*oppoAngleVectNor3[2],
            baseX+radius7*oppoAngleVectNor4[0],baseY+radius7*oppoAngleVectNor4[1]+height7,baseZ+radius7*oppoAngleVectNor4[2],
            baseX+radius7*oppoAngleVectNor5[0],baseY+radius7*oppoAngleVectNor5[1]+height7,baseZ+radius7*oppoAngleVectNor5[2],
            baseX+radius7*oppoAngleVectNor6[0],baseY+radius7*oppoAngleVectNor6[1]+height7,baseZ+radius7*oppoAngleVectNor6[2],

            baseX+radius6*oppoAngleVectNor1[0],baseY+radius6*oppoAngleVectNor1[1]+height6,baseZ+radius6*oppoAngleVectNor1[2],
            baseX+radius6*oppoAngleVectNor2[0],baseY+radius6*oppoAngleVectNor2[1]+height6,baseZ+radius6*oppoAngleVectNor2[2],
            baseX+radius6*oppoAngleVectNor3[0],baseY+radius6*oppoAngleVectNor3[1]+height6,baseZ+radius6*oppoAngleVectNor3[2],
            baseX+radius6*oppoAngleVectNor4[0],baseY+radius6*oppoAngleVectNor4[1]+height6,baseZ+radius6*oppoAngleVectNor4[2],
            baseX+radius6*oppoAngleVectNor5[0],baseY+radius6*oppoAngleVectNor5[1]+height6,baseZ+radius6*oppoAngleVectNor5[2],
            baseX+radius6*oppoAngleVectNor6[0],baseY+radius6*oppoAngleVectNor6[1]+height6,baseZ+radius6*oppoAngleVectNor6[2],

            baseX+radius5*oppoAngleVectNor1[0],baseY+radius5*oppoAngleVectNor1[1]+height5,baseZ+radius5*oppoAngleVectNor1[2],
            baseX+radius5*oppoAngleVectNor2[0],baseY+radius5*oppoAngleVectNor2[1]+height5,baseZ+radius5*oppoAngleVectNor2[2],
            baseX+radius5*oppoAngleVectNor3[0],baseY+radius5*oppoAngleVectNor3[1]+height5,baseZ+radius5*oppoAngleVectNor3[2],
            baseX+radius5*oppoAngleVectNor4[0],baseY+radius5*oppoAngleVectNor4[1]+height5,baseZ+radius5*oppoAngleVectNor4[2],
            baseX+radius5*oppoAngleVectNor5[0],baseY+radius5*oppoAngleVectNor5[1]+height5,baseZ+radius5*oppoAngleVectNor5[2],
            baseX+radius5*oppoAngleVectNor6[0],baseY+radius5*oppoAngleVectNor6[1]+height5,baseZ+radius5*oppoAngleVectNor6[2],

            baseX+radius4*oppoAngleVectNor1[0],baseY+radius4*oppoAngleVectNor1[1]+height4,baseZ+radius4*oppoAngleVectNor1[2],
            baseX+radius4*oppoAngleVectNor2[0],baseY+radius4*oppoAngleVectNor2[1]+height4,baseZ+radius4*oppoAngleVectNor2[2],
            baseX+radius4*oppoAngleVectNor3[0],baseY+radius4*oppoAngleVectNor3[1]+height4,baseZ+radius4*oppoAngleVectNor3[2],
            baseX+radius4*oppoAngleVectNor4[0],baseY+radius4*oppoAngleVectNor4[1]+height4,baseZ+radius4*oppoAngleVectNor4[2],
            baseX+radius4*oppoAngleVectNor5[0],baseY+radius4*oppoAngleVectNor5[1]+height4,baseZ+radius4*oppoAngleVectNor5[2],
            baseX+radius4*oppoAngleVectNor6[0],baseY+radius4*oppoAngleVectNor6[1]+height4,baseZ+radius4*oppoAngleVectNor6[2],

            baseX+radius3*oppoAngleVectNor1[0],baseY+radius3*oppoAngleVectNor1[1]+height3,baseZ+radius3*oppoAngleVectNor1[2],
            baseX+radius3*oppoAngleVectNor2[0],baseY+radius3*oppoAngleVectNor2[1]+height3,baseZ+radius3*oppoAngleVectNor2[2],
            baseX+radius3*oppoAngleVectNor3[0],baseY+radius3*oppoAngleVectNor3[1]+height3,baseZ+radius3*oppoAngleVectNor3[2],
            baseX+radius3*oppoAngleVectNor4[0],baseY+radius3*oppoAngleVectNor4[1]+height3,baseZ+radius3*oppoAngleVectNor4[2],
            baseX+radius3*oppoAngleVectNor5[0],baseY+radius3*oppoAngleVectNor5[1]+height3,baseZ+radius3*oppoAngleVectNor5[2],
            baseX+radius3*oppoAngleVectNor6[0],baseY+radius3*oppoAngleVectNor6[1]+height3,baseZ+radius3*oppoAngleVectNor6[2],

            baseX+radius2*oppoAngleVectNor1[0],baseY+radius2*oppoAngleVectNor1[1]+height2,baseZ+radius2*oppoAngleVectNor1[2],
            baseX+radius2*oppoAngleVectNor2[0],baseY+radius2*oppoAngleVectNor2[1]+height2,baseZ+radius2*oppoAngleVectNor2[2],
            baseX+radius2*oppoAngleVectNor3[0],baseY+radius2*oppoAngleVectNor3[1]+height2,baseZ+radius2*oppoAngleVectNor3[2],
            baseX+radius2*oppoAngleVectNor4[0],baseY+radius2*oppoAngleVectNor4[1]+height2,baseZ+radius2*oppoAngleVectNor4[2],
            baseX+radius2*oppoAngleVectNor5[0],baseY+radius2*oppoAngleVectNor5[1]+height2,baseZ+radius2*oppoAngleVectNor5[2],
            baseX+radius2*oppoAngleVectNor6[0],baseY+radius2*oppoAngleVectNor6[1]+height2,baseZ+radius2*oppoAngleVectNor6[2],

            baseX,baseY+height2,baseZ,
            baseX,baseY+height2,baseZ,
            baseX,baseY+height2,baseZ,
            baseX,baseY+height2,baseZ,
            baseX,baseY+height2,baseZ,
            baseX,baseY+height2,baseZ,
    };

    GameWorld::makeUpBezierLine(bezierPointCoral0th,bezierControlPoints,8,6,25);
    GameWorld::makeUpBspline(10,25,3,blinesPoints_coralGroup0th,blinesPointsNormal_coral0th,bezierPointCoral0th,texcoord_coral0th);

    flowerPosition1[0]=bezierPointCoral0th[(2*25+12)*3];
    flowerPosition1[1]=bezierPointCoral0th[(2*25+12)*3+1];
    flowerPosition1[2]=bezierPointCoral0th[(2*25+12)*3+2];
    flowerPosition0[0]=bezierPointCoral0th[(3*25+22)*3];
    flowerPosition0[1]=bezierPointCoral0th[(3*25+22)*3+1];
    flowerPosition0[2]=bezierPointCoral0th[(3*25+22)*3+2];
    flowerPosition4[0]=flowerPosition1[0];
    flowerPosition4[1]=flowerPosition1[1];
    flowerPosition4[2]=flowerPosition1[2];
    ///////////////////////////////////////////////////////////////
    //////////////中间部位的珊瑚/////////////////////////
    float oppoVectCoral0Nor1[]={1.0,0.0,0.0};
    float oppoVectCoral0Nor2[]={1.0,0.0,-1.0};
    WizardGeomSupple::normalize(oppoVectCoral0Nor2);
    float oppoVectCoral0Nor3[]={0.0,0.0,-1.0};
    float oppoVectCoral0Nor4[]={-1.0,0.0,-1.0};
    WizardGeomSupple::normalize(oppoAngleVectNor4);
    float oppoVectCoral0Nor5[]={-1.0,0.0,0.0};
    float oppoVectCoral0Nor6[]={0.0,0.0,1.0};

    float floor12thX=bezPointGather_floor[13*3]+2.5;
    float floor12thY=bezPointGather_floor[13*3+1];
    float floor12thZ=bezPointGather_floor[13*3+2];
    float floorRadius0=4.0;
    float floorRadius1=3.0;
    float floorRadius2=5.0;
    float floorRadius3=7.0;
    float floorRadius4=7.0;
    float floorRadius5=7.0;
    float floorRadius6=6.0;


    float floorHeight2=12.0;
    float floorHeight3=10.0;
    float floorHeight4=8.0;
    float floorHeight5=6.0;
    float floorHeight6=4.0;
    float floorHeight7=2.0;
    float floorHeight8=0.0;

    float coralControlPoints[]={

            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor1[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor2[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor3[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor4[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor5[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor6[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius0,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor1[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor2[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor3[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor4[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor5[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor6[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius1,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor1[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor2[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor3[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor4[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor5[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor6[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius2,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor1[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor2[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor3[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor4[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor5[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor6[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius3,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor1[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor2[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor3[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor4[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor5[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor6[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius4,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoAngleVectNor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor3[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor4[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5[0]*(floorRadius5+3.0f),floor12thY+floorHeight7+oppoVectCoral0Nor5[1]*(floorRadius5+3.0f),floor12thZ+oppoVectCoral0Nor5[2]*(floorRadius5+3.0f),
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor1[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor2[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor3[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor4[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor5[0]*(floorRadius6+1.0f),floor12thY+floorHeight8+oppoVectCoral0Nor5[1]*(floorRadius6+1.0f)-1.0f,floor12thZ+oppoVectCoral0Nor5[2]*(floorRadius6+1.0f),
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor6[1]*floorRadius6-1.0f,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius6,


    };

    GameWorld::makeUpBezierLine(bezierPointCoral1th,coralControlPoints,8,6,25);
    flowerPosition5[0]=bezierPointCoral1th[(2*25+10)*3]-2.5;
    flowerPosition5[1]=bezierPointCoral1th[(2*25+10)*3+1];
    flowerPosition5[2]=bezierPointCoral1th[(2*25+10)*3+2]-0.5;
    GameWorld::makeUpBspline(10,25,3,blinesPoints_coralGroup1th,blinesPointsNormal_coral1th,bezierPointCoral1th,texcoord_coral1th);
    ///////////////////////////////////////////////////////////////////////////////////
    /////////////////左边的珊瑚/////////////////////////////////////////////
    floor12thX=bezPointGather_floor[13*3]+10.0;
    floor12thY=bezPointGather_floor[13*3+1]+1.0;
    floor12thZ=bezPointGather_floor[13*3+2];
    floorRadius0=4.0;
    floorRadius1=6.0;
    floorRadius2=8.0;
    floorRadius3=6.0;
    floorRadius4=3.0;
    floorRadius5=0.0;

    floorHeight2=8.0;
    floorHeight3=6.0;
    floorHeight4=4.0;
    floorHeight5=3.0;
    floorHeight6=2.0;
    floorHeight7=2.0;
    floorHeight8=2.5;

    float coralControl1Points[]={

            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor1[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor2[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor3[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor4[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor5[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor6[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius0,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor1[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor2[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor3[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor4[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor5[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor6[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius1,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor1[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor2[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor3[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor4[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor5[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor6[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius2,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor1[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor2[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor3[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor4[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor5[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor6[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius3,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor1[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor2[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor3[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor4[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor5[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor6[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius4,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoAngleVectNor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor3[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor4[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor5[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor3[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor4[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor5[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,


    };
    GameWorld::makeUpBezierLine(bezierPointCoral2th,coralControl1Points,8,6,25);
//    for(int i=0;i<25*6*3;i++){
//        bezierControlPointsMap[i]=bezierPointCoral2th[i];
//    }
    flowerPosition2[0]=bezierPointCoral2th[(3*25+3)*3];
    flowerPosition2[1]=bezierPointCoral2th[(3*25+3)*3+1];
    flowerPosition2[2]=bezierPointCoral2th[(3*25+3)*3+2];
    GameWorld::makeUpBspline(10,25,3,blinesPoints_coralGroup2th,blinesPointsNormal_coral2th,bezierPointCoral2th,texcoord_coral2th);
    //////////////////////////////////////////////////////////
    //////////////右上的珊瑚//////////////////////////////
    floor12thX=bezPointGather_floor[13*3]-4.0;
    floor12thY=bezPointGather_floor[13*3+1]+6.0;
    floor12thZ=bezPointGather_floor[13*3+2];
    floorRadius0=4.0;
    floorRadius1=6.0;
    floorRadius2=8.0;
    floorRadius3=6.0;
    floorRadius4=3.0;
    floorRadius5=1.0;
    floorRadius6=0.0;

    floorHeight2=5.0;
    floorHeight3=4.5;
    floorHeight4=4.0;
    floorHeight5=3.0;
    floorHeight6=2.5;
    floorHeight7=2.0;
    floorHeight8=2.1;
    float upVect[]={1.0,1.0,0.0};
    WizardGeomSupple::normalize(upVect);
    float coralControl3Points[]={

            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor1[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor2[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor3[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor4[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor5[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor6[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius0,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor1[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor2[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor3[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor4[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor5[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor6[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius1,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor1[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor2[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor3[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor4[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor5[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor6[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius2,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor1[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor2[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor3[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor4[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor5[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor6[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius3,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor1[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor2[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor3[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor4[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor5[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor6[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius4,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoAngleVectNor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor3[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor4[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor5[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor1[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor2[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor3[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor4[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor5[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor6[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius6,


    };

    GameWorld::makeUpBezierLine(bezierPointCoral3th,coralControl3Points,8,6,18);
//    for(int i=0;i<25*6*3;i++){
//        bezierControlPointsMap[i]=bezierPointCoral3th[i];
//    }
    flowerPosition3[0]=bezierPointCoral3th[(3*18+7)*3]+1.5;
    flowerPosition3[1]=bezierPointCoral3th[(3*18+7)*3+1];
    flowerPosition3[2]=bezierPointCoral3th[(3*18+7)*3+2];

    GameWorld::makeUpBspline(10,18,3,blinesPoints_coralGroup3th,blinesPointsNormal_coral3th,bezierPointCoral3th,texcoord_coral3th);
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////最左侧的珊瑚/////////////////////
    floor12thX=bezPointGather_floor[13*3]+25.0;
    floor12thY=bezPointGather_floor[13*3+1]-3.0;
    floor12thZ=bezPointGather_floor[13*3+2]-3.0;
    floorRadius0=2.0;
    floorRadius1=3.0;
    floorRadius2=4.0;
    floorRadius3=4.0;
    floorRadius4=2.0;
    floorRadius5=2.0;
    floorRadius6=2.0;

    floorHeight2=10.0;
    floorHeight3=8.0;
    floorHeight4=6.0;
    floorHeight5=4.0;
    floorHeight6=2.0;
    floorHeight7=1.0;
    floorHeight8=1.0;

    float coralControl4Points[]={

            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor1[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor2[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor3[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor4[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor5[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor6[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius0,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor1[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor2[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor3[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor4[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor5[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor6[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius1,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor1[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor2[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor3[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor4[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor5[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor6[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius2,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor1[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor2[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor3[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius3,
            floor12thX,floor12thY+floorHeight5,floor12thZ,
            floor12thX,floor12thY+floorHeight5,floor12thZ,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor6[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius3,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor1[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor2[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor3[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius4,
            floor12thX,floor12thY+floorHeight6,floor12thZ,
            floor12thX,floor12thY+floorHeight6,floor12thZ,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor6[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius4,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoAngleVectNor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*(floorRadius5),floor12thY+floorHeight7+oppoVectCoral0Nor3[1]*(floorRadius5),floor12thZ+oppoVectCoral0Nor3[2]*(floorRadius5),
            floor12thX,floor12thY+floorHeight7,floor12thZ,
            floor12thX,floor12thY+floorHeight7,floor12thZ,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor1[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor2[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor3[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor4[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor5[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor6[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius6,


    };

    GameWorld::makeUpBezierLine(bezierPointCoral4th,coralControl4Points,8,6,25);
    GameWorld::makeUpBspline(10,25,3,blinesPoints_coralGroup4th,blinesPointsNormal_coral4th,bezierPointCoral4th,texcoord_coral4th);
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////顶部的珊瑚/////////////////////////////////////
    floor12thX=bezPointGather_floor[13*3]+1.0;
    floor12thY=bezPointGather_floor[13*3+1]+8.0;
    floor12thZ=bezPointGather_floor[13*3+2];
    floorRadius0=3.0;
    floorRadius1=13.0;
    floorRadius2=3.0;
    floorRadius3=2.0;
    floorRadius4=1.0;
    floorRadius5=1.0;

    floorHeight2=8.0;
    floorHeight3=8.0;
    floorHeight4=7.5;
    floorHeight5=7.5;
    floorHeight6=7.0;
    floorHeight7=6.0;
    floorHeight8=2.0;

    float coralControl5Points[]={

            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor1[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor2[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor3[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor4[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor5[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor6[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius0,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor1[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor2[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor3[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor4[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor5[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor6[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius1,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor1[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor2[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor3[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor4[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor5[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor6[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius2,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor1[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor2[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor3[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor4[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor5[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor6[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius3,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor1[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor2[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor3[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor4[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor5[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor6[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius4,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoAngleVectNor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor3[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor4[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor5[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,

            floor12thX+oppoVectCoral0Nor1[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor1[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor2[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor2[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor3[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor4[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor5[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor5[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor6[0]*floorRadius5,floor12thY+floorHeight8+oppoVectCoral0Nor6[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6[2]*floorRadius5,


    };

    GameWorld::makeUpBezierLine(bezierPointCoral5th,coralControl5Points,8,6,25);
    GameWorld::makeUpBspline(10,25,3,blinesPoints_coralGroup5th,blinesPointsNormal_coral5th,bezierPointCoral5th,texcoord_coral5th);
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////
    float aloneYMoveLeng_=tanf(PI_GAMEWORLD*2.0f);
    float oppoVectCoral0Nor1_[]={1.0,0.0,0.0};
    oppoVectCoral0Nor1_[1]+=aloneYMoveLeng_;
    WizardGeomSupple::normalize(oppoVectCoral0Nor1_);
    float oppoVectCoral0Nor2_[]={1.0,0.0,-1.0};
    WizardGeomSupple::normalize(oppoVectCoral0Nor2_);
    float oppoVectCoral0Nor3_[]={0.0,0.0,-1.0};
    oppoVectCoral0Nor3_[1]-=aloneYMoveLeng_;
    WizardGeomSupple::normalize(oppoVectCoral0Nor3_);
    float oppoVectCoral0Nor4_[]={-1.0,0.0,-1.0};
    WizardGeomSupple::normalize(oppoVectCoral0Nor4_);
    oppoVectCoral0Nor4_[1]-=aloneYMoveLeng_;
    WizardGeomSupple::normalize(oppoVectCoral0Nor4_);
    float oppoVectCoral0Nor5_[]={-1.0,0.0,0.0};
    WizardGeomSupple::normalize(oppoVectCoral0Nor5_);
    float oppoVectCoral0Nor6_[]={0.0,0.0,1.0};
    oppoVectCoral0Nor6_[1]+=aloneYMoveLeng_;
    WizardGeomSupple::normalize(oppoVectCoral0Nor6_);
    floor12thX=bezPointGather_floor[10*3]+12.0;
    floor12thY=bezPointGather_floor[10*3+1]+2.0;
    floor12thZ=bezPointGather_floor[10*3+2]-3.0;
    floorRadius0=3.0;
    floorRadius1=7.0;
    floorRadius2=3.0;
    floorRadius3=2.0;
    floorRadius4=1.0;
    floorRadius5=0.3;
    floorRadius6=0.3;

    floorHeight2=11.0;
    floorHeight3=11.0;
    floorHeight4=10.5;
    floorHeight5=10.0;
    floorHeight6=9.0;
    floorHeight7=8.0;
    floorHeight8=5.0;


    float coralControl6Points[]={

            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,
            floor12thX,floor12thY+floorHeight2,floor12thZ,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor1_[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor2_[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor3_[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor4_[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor5_[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius0,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius0,floor12thY+floorHeight2+oppoVectCoral0Nor6_[1]*floorRadius0,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius0,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor1_[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor2_[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor3_[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor4_[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor5_[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius1,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius1,floor12thY+floorHeight3+oppoVectCoral0Nor6_[1]*floorRadius1,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius1,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor1_[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor2_[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor3_[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor4_[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor5_[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius2,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius2,floor12thY+floorHeight4+oppoVectCoral0Nor6_[1]*floorRadius2,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius2,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor1_[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor2_[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor3_[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor4_[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor5_[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius3,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius3,floor12thY+floorHeight5+oppoVectCoral0Nor6_[1]*floorRadius3,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius3,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor1_[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor2_[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor3_[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor4_[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor5_[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius4,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius4,floor12thY+floorHeight6+oppoVectCoral0Nor6_[1]*floorRadius4,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius4,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor1_[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor2_[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor3_[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor4_[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor5_[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius5,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius5,floor12thY+floorHeight7+oppoVectCoral0Nor6_[1]*floorRadius5,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius5,

            floor12thX+oppoVectCoral0Nor1_[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor1_[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor1_[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor2_[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor2_[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor2_[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor3_[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor3_[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor3_[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor4_[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor4_[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor4_[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor5_[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor5_[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor5_[2]*floorRadius6,
            floor12thX+oppoVectCoral0Nor6_[0]*floorRadius6,floor12thY+floorHeight8+oppoVectCoral0Nor6_[1]*floorRadius6,floor12thZ+oppoVectCoral0Nor6_[2]*floorRadius6,


    };

    GameWorld::makeUpBezierLine(bezierPointCoral6th,coralControl6Points,8,6,18);
    GameWorld::makeUpBspline(10,18,3,blinesPoints_coralGroup6th,blinesPointsNormal_coral6th,bezierPointCoral6th,texcoord_coral6th);

}


void GameWorld::drawCoral(GLuint textureCoralReefLocation,GLuint texcoordCoralReefLocation){

    //LOGD("########## i = %d", 100);
    GLuint* coralTextureList=getCoralTextureList();
    GLuint drawCoralProgram = shaderUtilGameWorld.getDrawCoralProgram();
    glUseProgram(drawCoralProgram);

    GLuint modelMatrixLocation = glGetUniformLocation(drawCoralProgram,"ModelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(drawCoralProgram,"ViewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(drawCoralProgram,"ProjectionMatrix");
    flyElephantGameWorld.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);

    GLuint lightPositionLocation = glGetUniformLocation(drawCoralProgram,"lightPosition");
    glUniform3f(lightPositionLocation,
                bezPointGather_floor[10*3]-50.0f,
                bezPointGather_floor[10*3+1]+30.0f,
                bezPointGather_floor[10*3+2]+50.0f);
    GLuint cameraPositionLocation = glGetUniformLocation(drawCoralProgram,"cameraPosition");
    glUniform3f(cameraPositionLocation,
                FlyElephant::cameraPosition[0],
                FlyElephant::cameraPosition[1],
                FlyElephant::cameraPosition[2]);

    GLuint positionNormalLocation = glGetAttribLocation(drawCoralProgram,"positionNormal");
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral0th);
    glEnableVertexAttribArray(positionNormalLocation);
    GLuint positionLocation = glGetAttribLocation(drawCoralProgram,"position");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup0th);
    glEnableVertexAttribArray(positionLocation);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[0]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral0th);
    glEnableVertexAttribArray(texcoordCoralReefLocation);
    glDrawArrays(GL_TRIANGLES, 0, 10000);
    //////////////////////////////////////
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral1th);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup1th);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[1]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral1th);
    glDrawArrays(GL_TRIANGLES, 0, 10000);
    ///////////////////////////////////////////////
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral2th);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup2th);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[2]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral2th);
    glDrawArrays(GL_TRIANGLES, 0, 10000);
    /////////////////////////////////////////////
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral3th);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup3th);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[3]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral3th);
    glDrawArrays(GL_TRIANGLES, 0, 10000);
    /////////////////////////////////////////
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral4th);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup4th);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[4]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral4th);
    glDrawArrays(GL_TRIANGLES, 0, 10000);
    ///////////////////////////////////////////////
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral5th);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup5th);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[5]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral5th);
    glDrawArrays(GL_TRIANGLES, 0, 10000);
    ///////////////////////////////////////////////
    glVertexAttribPointer(positionNormalLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPointsNormal_coral6th);
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, blinesPoints_coralGroup6th);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, coralTextureList[5]);
    glUniform1i(textureCoralReefLocation, 0);
    glVertexAttribPointer(texcoordCoralReefLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_coral6th);
    glDrawArrays(GL_TRIANGLES, 0, 10000);

    glUseProgram(0);

    //drawPointLine(bezierControlPointsMap,18);

}

int drawScenePointer=0;
bool drawScenePointerAdd=true;
void GameWorld::textureMapping(GLuint texture,GLuint textureLocation,GLuint light_wavesTexture,
        GLuint textureFloorLightWavesLocation,GLuint texcoordLocation,GLuint longLatitudeFloorLocation){

    if(drawScenePointerAdd){
        drawScenePointer++;
        if(drawScenePointer>rand()%200){
            drawScenePointerAdd=false;
        }
    }else{
        drawScenePointer--;
        if(drawScenePointer<-200){
            drawScenePointerAdd=true;
        }
    }

    GLuint textureProgramScene=shaderUtilGameWorld.getTextureProgram();
    glUseProgram(textureProgramScene);
    GLuint modelMatrixLocation = glGetUniformLocation(textureProgramScene,"ModelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(textureProgramScene,"ViewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(textureProgramScene,"ProjectionMatrix");
    flyElephantGameWorld.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint positionLocation = glGetAttribLocation(textureProgramScene,"position");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, bezPointGather_floorGroup);
    glEnableVertexAttribArray(positionLocation);
    GLuint drawSecenePointerLocation=glGetUniformLocation(textureProgramScene,"drawScenePointer");
    glUniform1i(drawSecenePointerLocation,drawScenePointer);
    GLuint randNumberLocation=glGetUniformLocation(textureProgramScene,"randNumber");
    glUniform1f(randNumberLocation,rand()%10*0.1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureLocation, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, light_wavesTexture);
    glUniform1i(textureFloorLightWavesLocation, 1);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoord_floor);
    glEnableVertexAttribArray(texcoordLocation);
    glVertexAttribPointer(longLatitudeFloorLocation, 2, GL_FLOAT, GL_FALSE, 2*4, longLatitudecGather);
    glEnableVertexAttribArray(longLatitudeFloorLocation);
    glDrawArrays(GL_TRIANGLES,0,1200);
    glUseProgram(0);

}

float* GameWorld::getBezPointGather_floor(){
    return bezPointGather_floor;
}

float* GameWorld::getBezierControlPointsMap(){
    return bezierControlPointsMap;
}