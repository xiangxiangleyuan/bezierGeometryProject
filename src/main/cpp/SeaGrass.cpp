#include "SeaGrass.h"

SeaGrass::SeaGrass() {};
SeaGrass::~SeaGrass() {};

GameWorld gameWorldSeaGrass;
FlyElephantEar flyElephantEarSeaGrass;
ShaderUtil shaderUtilSeaGrass;
FlyElephant flyElephantSeaGrass;

float seaGrassGather0th[150];
float seaGrassGather2th[150];
float seaGrassGather4th[150];
float seaGrassGather5th[150];
float seaGrassGather6th[150];
float seaGrassGather7th[150];
float seaGrassGather8th[150];

void SeaGrass::drawSeaGrass(){

//    std::thread t();
//    t.join();
    seaGrassSway();
    //海草里的TAG的用途1.用来识别图片底板的颜色来设置透明度2.用来区别加载那个图片纹理
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather0th,4,6,4,5);
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather2th,4,6,4,4);
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather4th,4,6,4,8);
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather5th,4,6,4,9);
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather6th,4,6,4,10);
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather7th,4,6,4,11);
    flyElephantEarSeaGrass.MakeEarPoints(seaGrassGather8th,4,6,4,12);

    SeaGrass::drawSeaGrassMap(10,GameWorld::flowerPosition3);
    int currPointIndex=6*3;
    float floorPosition0[]={gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]-3.0f,
                            gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1],
                            gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2]-3.5f};
    SeaGrass::drawSeaGrassMap(11,floorPosition0);
    float seaSnailPosition1[]={GameWorld::flowerPosition4[0]-3.0f,GameWorld::flowerPosition4[1],GameWorld::flowerPosition4[2]-1.0f};
    SeaGrass::drawSeaGrassMap(12,seaSnailPosition1);
    SeaGrass::drawSeaGrassMap(13,GameWorld::flowerPosition5);
    currPointIndex=22*3;
    float floorPosition1[]={gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]+1.0f,
                            gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1]-1.0f,
                            gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2]-4.0f};
    SeaGrass::drawSeaGrassMap(14,floorPosition1);
    currPointIndex=21*3;
    float floorPosition2[]={gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]-2.0f,
                            gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1],
                            gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2]-5.0f};
    SeaGrass::drawSeaGrassMap(15,floorPosition2);
    float seaSnailPosition0[]={GameWorld::flowerPosition2[0]+1.5f,GameWorld::flowerPosition2[1]-1.0f,GameWorld::flowerPosition2[2]-1.0f};
    SeaGrass::drawSeaGrassMap(16,seaSnailPosition0);
    float seaSnailPosition2[]={GameWorld::flowerPosition3[0]+6.0f,GameWorld::flowerPosition3[1]+0.3f,GameWorld::flowerPosition3[2]};
    SeaGrass::drawSeaGrassMap(17,seaSnailPosition2);
    float seaSnailPosition3[]={GameWorld::flowerPosition3[0]+3.0f,GameWorld::flowerPosition3[1]+0.15f,GameWorld::flowerPosition3[2]+1.0f};
    SeaGrass::drawSeaGrassMap(18,seaSnailPosition3);
    float seaSnailPosition4[]={GameWorld::flowerPosition2[0]+5.5f,GameWorld::flowerPosition2[1]-1.0f,GameWorld::flowerPosition2[2]-1.0f};
    SeaGrass::drawSeaGrassMap(19,seaSnailPosition4);
    float seaSnailPosition5[]={floorPosition1[0]+23.0f,floorPosition1[1]+2.0f,floorPosition1[2]};
    SeaGrass::drawSeaGrassMap(20,seaSnailPosition5);
//    if(!ControlPanel::isCanStart){
//        float position[]={0.5,-0.3,0.0};
//        SeaGrass::drawSeaGrassMap(100,position);
//    }

}

/////////////////////////////////////////
//摆动范围  摆动点的组合 摆动的方向 摆动的速率 只有特定的点摆动 不同点之间摆动不一样的数据
int maxminRange=0;
//是否生成随机数
bool isGeneRandValue=true;
int drawSeaGrassPointer=0;
//水草的指针是否在增加
bool isSeaGrassPointerAdd=true;
int maxminRange2th=0;
//是否生成随机数
bool isGeneRandValue2th=true;
int drawSeaGrassPointer2th=0;
//水草的指针是否在增加
bool isSeaGrassPointerAdd2th=true;
int maxminRange4th=0;
//是否生成随机数
bool isGeneRandValue4th=true;
int drawSeaGrassPointer4th=0;
//水草的指针是否在增加
bool isSeaGrassPointerAdd4th=true;
bool isSeaGrassPointerAdd5th=true;
int maxminRange5th=0;
//是否生成随机数
bool isGeneRandValue5th=true;
int drawSeaGrassPointer5th=0;
//水草的指针是否在增加
bool isSeaGrassPointerAdd6th=true;
int maxminRange6th=0;
//是否生成随机数
bool isGeneRandValue6th=true;
int drawSeaGrassPointer6th=0;
//////////////////////////////////
//水草的指针是否在增加
bool isSeaGrassPointerAdd7th=true;
int maxminRange7th=0;
//是否生成随机数
bool isGeneRandValue7th=true;
int drawSeaGrassPointer7th=0;
////////////////////////////////////////
//水草的指针是否在增加
bool isSeaGrassPointerAdd8th=true;
int maxminRange8th=0;
//是否生成随机数
bool isGeneRandValue8th=true;
int drawSeaGrassPointer8th=0;

//临时的运动方向向量
float tempMoveVectNor0th[3]={0.0,0.0,0.0};
float tempMoveVectNor1th[3]={0.0,0.0,0.0};
float tempMoveVectNor2th[3]={0.0,0.0,0.0};
float tempMoveVectNor6th[3]={0.0,0.0,0.0};
float tempMoveVectNor7th[3]={0.0,0.0,0.0};
float tempMoveVectNor8th[3]={0.0,0.0,0.0};
float tempMoveVectNor12th[3]={0.0,0.0,0.0};
float tempMoveVectNor13th[3]={0.0,0.0,0.0};
float tempMoveVectNor14th[3]={0.0,0.0,0.0};
float tempMoveVectNor15th[3]={0.0,0.0,0.0};
float tempMoveVectNor16th[3]={0.0,0.0,0.0};
float tempMoveVectNor17th[3]={0.0,0.0,0.0};
float tempMoveVectNor18th[3]={0.0,0.0,0.0};
float tempMoveVectNor19th[3]={0.0,0.0,0.0};
float tempMoveVectNor20th[3]={0.0,0.0,0.0};
float tempMoveVectNor21th[3]={0.0,0.0,0.0};
float tempMoveVectNor22th[3]={0.0,0.0,0.0};
float tempMoveVectNor23th[3]={0.0,0.0,0.0};


//用来测试摆动点的集合
float waverPoints[300];
void SeaGrass::seaGrassSway(){

    {
        if (isSeaGrassPointerAdd) {
            drawSeaGrassPointer++;
            //一个循环里生成一个随机数
            if (isGeneRandValue) {
                maxminRange = 30;
                isGeneRandValue = false;
            }

        } else {
            drawSeaGrassPointer--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue) {
                maxminRange = 50;
                isGeneRandValue = true;
            }
        }

        if (drawSeaGrassPointer > maxminRange) {
            isSeaGrassPointerAdd = false;
        } else if (drawSeaGrassPointer < -maxminRange) {
            isSeaGrassPointerAdd = true;
        }
    }

    {
        if (isSeaGrassPointerAdd2th) {
            drawSeaGrassPointer2th++;
            //一个循环里生成一个随机数
            if (isGeneRandValue2th) {
                maxminRange2th = 45;
                isGeneRandValue2th = false;
            }

        } else {
            drawSeaGrassPointer2th--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue2th) {
                maxminRange2th = 80;
                isGeneRandValue2th = true;
            }
        }

        if (drawSeaGrassPointer2th > maxminRange2th) {
            isSeaGrassPointerAdd2th = false;
        } else if (drawSeaGrassPointer2th < -maxminRange2th) {
            isSeaGrassPointerAdd2th = true;
        }
    }

    {
        if (isSeaGrassPointerAdd4th) {
            drawSeaGrassPointer4th++;
            //一个循环里生成一个随机数
            if (isGeneRandValue4th) {
                maxminRange4th = 30;
                isGeneRandValue4th = false;
            }

        } else {
            drawSeaGrassPointer4th--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue4th) {
                maxminRange4th = 60;
                isGeneRandValue4th = true;
            }
        }

        if (drawSeaGrassPointer4th > maxminRange4th) {
            isSeaGrassPointerAdd4th = false;
        } else if (drawSeaGrassPointer4th < -maxminRange4th) {
            isSeaGrassPointerAdd4th = true;
        }
    }

    {
        if (isSeaGrassPointerAdd5th) {
            drawSeaGrassPointer5th++;
            //一个循环里生成一个随机数
            if (isGeneRandValue5th) {
                maxminRange5th = 50;
                isGeneRandValue6th = false;
            }

        } else {
            drawSeaGrassPointer5th--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue5th) {
                maxminRange5th = 90;
                isGeneRandValue5th = true;
            }
        }

        if (drawSeaGrassPointer5th > maxminRange5th) {
            isSeaGrassPointerAdd5th = false;
        } else if (drawSeaGrassPointer5th < -maxminRange5th) {
            isSeaGrassPointerAdd5th = true;
        }
    }

    {
        if (isSeaGrassPointerAdd6th) {
            drawSeaGrassPointer6th++;
            //一个循环里生成一个随机数
            if (isGeneRandValue6th) {
                maxminRange6th = 100;
                isGeneRandValue6th = false;
            }

        } else {
            drawSeaGrassPointer6th--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue6th) {
                maxminRange6th = 70;
                isGeneRandValue6th = true;
            }
        }

        if (drawSeaGrassPointer6th > maxminRange6th) {
            isSeaGrassPointerAdd6th = false;
        } else if (drawSeaGrassPointer6th < -maxminRange6th) {
            isSeaGrassPointerAdd6th = true;
        }
    }

    {
        if (isSeaGrassPointerAdd7th) {
            drawSeaGrassPointer7th++;
            //一个循环里生成一个随机数
            if (isGeneRandValue7th) {
                maxminRange7th = 60;
                isGeneRandValue7th = false;
            }

        } else {
            drawSeaGrassPointer7th--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue7th) {
                maxminRange7th = 40;
                isGeneRandValue7th = true;
            }
        }

        if (drawSeaGrassPointer7th > maxminRange7th) {
            isSeaGrassPointerAdd7th = false;
        } else if (drawSeaGrassPointer7th < -maxminRange7th) {
            isSeaGrassPointerAdd7th = true;
        }
    }

    {
        if (isSeaGrassPointerAdd8th) {
            drawSeaGrassPointer8th++;
            //一个循环里生成一个随机数
            if (isGeneRandValue8th) {
                maxminRange8th = 90;
                isGeneRandValue8th = false;
            }

        } else {
            drawSeaGrassPointer8th--;
            //一个循环里生成一个随机数
            if (!isGeneRandValue8th) {
                maxminRange8th = 50;
                isGeneRandValue8th = true;
            }
        }

        if (drawSeaGrassPointer8th > maxminRange8th) {
            isSeaGrassPointerAdd8th = false;
        } else if (drawSeaGrassPointer8th < -maxminRange8th) {
            isSeaGrassPointerAdd8th = true;
        }
    }

    //生成一个临时运动方向向量
    int tag=rand()%2;
    if(drawSeaGrassPointer==0){
        tempMoveVectNor0th[0]=1.0;
        int randNum=rand();
        if(tag==0){
            tempMoveVectNor0th[1]=randNum%5*0.1;
            tempMoveVectNor0th[2]=randNum%6*0.1;
        }else{
            tempMoveVectNor0th[1]=-randNum%3*0.1;
            tempMoveVectNor0th[2]=-randNum%6*0.1;
        }

        tempMoveVectNor1th[0]=-1.0;
        if(tag==1){
            tempMoveVectNor1th[1]=randNum%5*0.1;
            tempMoveVectNor1th[2]=randNum%9*0.1;
        }else{
            tempMoveVectNor1th[1]=-randNum%5*0.1;
            tempMoveVectNor1th[2]=-randNum%6*0.1;
        }

        tempMoveVectNor2th[0]=1.0;
        if(tag==0){
            tempMoveVectNor2th[1]=randNum%3*0.1;
            tempMoveVectNor2th[2]=randNum%8*0.11;
        }else{
            tempMoveVectNor2th[1]=-randNum%3*0.1;
            tempMoveVectNor2th[2]=-randNum%4*0.15;
        }

    }

    if(drawSeaGrassPointer2th==0){
        tempMoveVectNor6th[0]=1.0;
        int randNum=rand();
        if(tag==0){
            tempMoveVectNor6th[1]=randNum%4*0.25;
            tempMoveVectNor6th[2]=randNum%6*0.15;
        }else{
            tempMoveVectNor6th[1]=-randNum%3*0.3333;
            tempMoveVectNor6th[2]=-randNum%4*0.25;
        }

        tempMoveVectNor7th[0]=1.0;
        if(tag==1){
            tempMoveVectNor7th[1]=randNum%4*0.25;
            tempMoveVectNor7th[2]=randNum%6*0.15;
        }else{
            tempMoveVectNor7th[1]=-randNum%3*0.3333;
            tempMoveVectNor7th[2]=-randNum%6*0.15;
        }

        tempMoveVectNor8th[0]=1.0;
        if(tag==0){
            tempMoveVectNor8th[1]=randNum%3*0.3333;
            tempMoveVectNor8th[2]=randNum%6*0.15;
        }else{
            tempMoveVectNor8th[1]=-randNum%3*0.33;
            tempMoveVectNor8th[2]=-randNum%5*0.2;
        }

    }
    if(drawSeaGrassPointer4th==0){
        tempMoveVectNor12th[0]=1.0;
        int randNum=rand();
        if(tag==1){
            tempMoveVectNor12th[1]=randNum%6*0.15;
            tempMoveVectNor12th[2]=randNum%3*0.33;
        }else{
            tempMoveVectNor12th[1]=-randNum%6*0.155;
            tempMoveVectNor12th[2]=-randNum%5*0.2;
        }

        tempMoveVectNor13th[0]=1.0;
        if(tag==0){
            tempMoveVectNor13th[1]=randNum%4*0.25;
            tempMoveVectNor13th[2]=randNum%3*0.33;
        }else{
            tempMoveVectNor13th[1]=-randNum%5*0.2;
            tempMoveVectNor13th[2]=-randNum%6*0.155;
        }

        tempMoveVectNor14th[0]=1.0;
        if(tag==1){
            tempMoveVectNor14th[1]=randNum%6*0.15;
            tempMoveVectNor14th[2]=randNum%5*0.2;
        }else{
            tempMoveVectNor14th[1]=-rand()%6*0.15;
            tempMoveVectNor14th[2]=-rand()%4*0.25;
        }

    }

    if(drawSeaGrassPointer5th==0){
        tempMoveVectNor15th[0]=1.0;
        int randNum=rand();
        if(tag==1){
            tempMoveVectNor15th[1]=randNum%3*0.33;
            tempMoveVectNor15th[2]=randNum%6*0.155;
        }else{
            tempMoveVectNor15th[1]=-randNum%8*0.125;
            tempMoveVectNor15th[2]=-randNum%9*0.1111;
        }

        tempMoveVectNor16th[0]=1.0;
        if(tag==0){
            tempMoveVectNor16th[1]=randNum%7*0.14;
            tempMoveVectNor16th[2]=randNum%6*0.155;
        }else{
            tempMoveVectNor16th[1]=-randNum%(3)*0.3333;
            tempMoveVectNor16th[2]=-randNum%(6)*0.15;
        }

        tempMoveVectNor17th[0]=1.0;
        if(tag==1){
            tempMoveVectNor17th[1]=randNum%4*0.25;
            tempMoveVectNor17th[2]=randNum%8*0.125;
        }else{
            tempMoveVectNor17th[1]=-randNum%9*0.1111;
            tempMoveVectNor17th[2]=-randNum%5*0.2;
        }

    }

    int randNum=rand();
    if(drawSeaGrassPointer6th==0){
        tempMoveVectNor18th[0]=1.0;
        if(tag==1){
            tempMoveVectNor18th[1]=randNum%2*0.5;
            tempMoveVectNor18th[2]=randNum%6*0.15;
        }else{
            tempMoveVectNor18th[1]=-randNum%3*0.3333;
            tempMoveVectNor18th[2]=-randNum%6*0.16;
        }

        tempMoveVectNor19th[0]=1.0;
        if(tag==0){
            tempMoveVectNor19th[1]=randNum%(3)*0.3333;
            tempMoveVectNor19th[2]=randNum%(6)*0.166;
        }else{
            tempMoveVectNor19th[1]=-randNum%(3)*0.1;
            tempMoveVectNor19th[2]=-randNum%(7)*0.142;
        }

        tempMoveVectNor20th[0]=1.0;
        if(tag==1){
            tempMoveVectNor20th[1]=randNum%3*0.3333;
            tempMoveVectNor20th[2]=randNum%6*0.161;
        }else{
            tempMoveVectNor20th[1]=-randNum%4*0.25;
            tempMoveVectNor20th[2]=-randNum%6*0.16;
        }

    }

    if(drawSeaGrassPointer7th==0){
        tempMoveVectNor21th[0]=1.0;
        if(tag==1){
            tempMoveVectNor21th[1]=randNum%3*0.3333;
            tempMoveVectNor21th[2]=randNum%2*0.5;
        }else{
            tempMoveVectNor21th[1]=-randNum%9*0.11111;
            tempMoveVectNor21th[2]=-rand()%8*0.125;
        }

        tempMoveVectNor22th[0]=1.0;
        if(tag==0){
            tempMoveVectNor22th[1]=randNum%3*0.3333;
            tempMoveVectNor22th[2]=randNum%6*0.155;
        }else{
            tempMoveVectNor22th[1]=-randNum%5*0.2;
            tempMoveVectNor22th[2]=-randNum%6*0.151;
        }

        tempMoveVectNor23th[0]=1.0;
        if(tag==1){
            tempMoveVectNor23th[1]=randNum%3*0.3333;
            tempMoveVectNor23th[2]=randNum%6*0.15;
        }else{
            tempMoveVectNor23th[1]=-randNum%4*0.25;
            tempMoveVectNor23th[2]=-randNum%5*0.2;
        }

    }



    WizardGeomSupple::normalize(tempMoveVectNor0th);
    WizardGeomSupple::normalize(tempMoveVectNor1th);
    WizardGeomSupple::normalize(tempMoveVectNor2th);
    WizardGeomSupple::normalize(tempMoveVectNor6th);
    WizardGeomSupple::normalize(tempMoveVectNor7th);
    WizardGeomSupple::normalize(tempMoveVectNor8th);
    WizardGeomSupple::normalize(tempMoveVectNor12th);
    WizardGeomSupple::normalize(tempMoveVectNor13th);
    WizardGeomSupple::normalize(tempMoveVectNor14th);
    WizardGeomSupple::normalize(tempMoveVectNor15th);
    WizardGeomSupple::normalize(tempMoveVectNor16th);
    WizardGeomSupple::normalize(tempMoveVectNor17th);
    WizardGeomSupple::normalize(tempMoveVectNor18th);
    WizardGeomSupple::normalize(tempMoveVectNor19th);
    WizardGeomSupple::normalize(tempMoveVectNor20th);
    WizardGeomSupple::normalize(tempMoveVectNor21th);
    WizardGeomSupple::normalize(tempMoveVectNor22th);
    WizardGeomSupple::normalize(tempMoveVectNor23th);


    float* bezierGatherFloor=gameWorldSeaGrass.getBezPointGather_floor();
    float baseX=GameWorld::flowerPosition1[0];
    float baseY=GameWorld::flowerPosition1[1]-1.5;
    float baseZ=GameWorld::flowerPosition1[2];
    seaGrassGather0th[0]=baseX;
    seaGrassGather0th[1]=baseY;
    seaGrassGather0th[2]=baseZ;
    seaGrassGather0th[3]=baseX;
    seaGrassGather0th[4]=baseY+1.5;
    seaGrassGather0th[5]=baseZ;
    seaGrassGather0th[6]=baseX;
    seaGrassGather0th[7]=baseY+3.0;
    seaGrassGather0th[8]=baseZ;
    seaGrassGather0th[9]=baseX;
    seaGrassGather0th[10]=baseY+4.5;
    seaGrassGather0th[11]=baseZ;
    seaGrassGather0th[12]=baseX;
    seaGrassGather0th[13]=baseY+6.0;
    seaGrassGather0th[14]=baseZ;
    seaGrassGather0th[15]=baseX;
    seaGrassGather0th[16]=baseY+7.5;
    seaGrassGather0th[17]=baseZ;

    seaGrassGather0th[18]=baseX-1.0;
    seaGrassGather0th[19]=baseY;
    seaGrassGather0th[20]=baseZ;
    seaGrassGather0th[21]=baseX-1.0;
    seaGrassGather0th[22]=baseY+1.5;
    seaGrassGather0th[23]=baseZ;
    seaGrassGather0th[24]=baseX-1.0;
    seaGrassGather0th[25]=baseY+3.0;
    seaGrassGather0th[26]=baseZ;
    seaGrassGather0th[27]=baseX-1.0;
    seaGrassGather0th[28]=baseY+4.5;
    seaGrassGather0th[29]=baseZ;
    seaGrassGather0th[30]=baseX-1.0;
    seaGrassGather0th[31]=baseY+6.0;
    seaGrassGather0th[32]=baseZ;
    seaGrassGather0th[33]=baseX-1.0;
    seaGrassGather0th[34]=baseY+7.5;
    seaGrassGather0th[35]=baseZ;

    seaGrassGather0th[36]=baseX-2.0;
    seaGrassGather0th[37]=baseY;
    seaGrassGather0th[38]=baseZ;
    seaGrassGather0th[39]=baseX-2.0;
    seaGrassGather0th[40]=baseY+1.5;
    seaGrassGather0th[41]=baseZ;
    seaGrassGather0th[42]=baseX-2.0;
    seaGrassGather0th[43]=baseY+3.0;
    seaGrassGather0th[44]=baseZ;
    seaGrassGather0th[45]=baseX-2.0;
    seaGrassGather0th[46]=baseY+4.5;
    seaGrassGather0th[47]=baseZ;
    seaGrassGather0th[48]=baseX-2.0;
    seaGrassGather0th[49]=baseY+6.0;
    seaGrassGather0th[50]=baseZ;
    seaGrassGather0th[51]=baseX-2.0;
    seaGrassGather0th[52]=baseY+7.5;
    seaGrassGather0th[53]=baseZ;

    seaGrassGather0th[54]=baseX-3.0;
    seaGrassGather0th[55]=baseY;
    seaGrassGather0th[56]=baseZ;
    seaGrassGather0th[57]=baseX-3.0;
    seaGrassGather0th[58]=baseY+1.5;
    seaGrassGather0th[59]=baseZ;
    seaGrassGather0th[60]=baseX-3.0;
    seaGrassGather0th[61]=baseY+3.0;
    seaGrassGather0th[62]=baseZ;
    seaGrassGather0th[63]=baseX-3.0;
    seaGrassGather0th[64]=baseY+4.5;
    seaGrassGather0th[65]=baseZ;
    seaGrassGather0th[66]=baseX-3.0;
    seaGrassGather0th[67]=baseY+6.0;
    seaGrassGather0th[68]=baseZ;
    seaGrassGather0th[69]=baseX-3.0;
    seaGrassGather0th[70]=baseY+7.5;
    seaGrassGather0th[71]=baseZ;


    float increment=0.02*drawSeaGrassPointer;
    seaGrassGather0th[15]+=(increment*tempMoveVectNor0th[0]);
    seaGrassGather0th[16]+=(increment*tempMoveVectNor0th[1]);
    seaGrassGather0th[17]+=(increment*tempMoveVectNor0th[2]);
    seaGrassGather0th[33]+=(increment*tempMoveVectNor0th[0]);
    seaGrassGather0th[34]+=(increment*tempMoveVectNor0th[1]);
    seaGrassGather0th[35]+=(increment*tempMoveVectNor0th[2]);
    seaGrassGather0th[51]+=(increment*tempMoveVectNor0th[0]);
    seaGrassGather0th[52]+=(increment*tempMoveVectNor0th[1]);
    seaGrassGather0th[53]+=(increment*tempMoveVectNor0th[2]);
    seaGrassGather0th[69]+=(increment*tempMoveVectNor0th[0]);
    seaGrassGather0th[70]+=(increment*tempMoveVectNor0th[1]);
    seaGrassGather0th[71]+=(increment*tempMoveVectNor0th[2]);
    increment=0.015*drawSeaGrassPointer;
    seaGrassGather0th[12]+=(increment*tempMoveVectNor1th[0]);
    seaGrassGather0th[13]+=(increment*tempMoveVectNor1th[1]);
    seaGrassGather0th[14]+=(increment*tempMoveVectNor1th[2]);
    seaGrassGather0th[30]+=(increment*tempMoveVectNor1th[0]);
    seaGrassGather0th[31]+=(increment*tempMoveVectNor1th[1]);
    seaGrassGather0th[32]+=(increment*tempMoveVectNor1th[2]);
    seaGrassGather0th[48]+=(increment*tempMoveVectNor1th[0]);
    seaGrassGather0th[49]+=(increment*tempMoveVectNor1th[1]);
    seaGrassGather0th[50]+=(increment*tempMoveVectNor1th[2]);
    seaGrassGather0th[66]+=(increment*tempMoveVectNor1th[0]);
    seaGrassGather0th[67]+=(increment*tempMoveVectNor1th[1]);
    seaGrassGather0th[68]+=(increment*tempMoveVectNor1th[2]);
    increment=0.01*drawSeaGrassPointer;
    seaGrassGather0th[9]+=(increment*tempMoveVectNor2th[0]);
    seaGrassGather0th[10]+=(increment*tempMoveVectNor2th[1]);
    seaGrassGather0th[11]+=(increment*tempMoveVectNor2th[2]);
    seaGrassGather0th[27]+=(increment*tempMoveVectNor2th[0]);
    seaGrassGather0th[28]+=(increment*tempMoveVectNor2th[1]);
    seaGrassGather0th[29]+=(increment*tempMoveVectNor2th[2]);
    seaGrassGather0th[45]+=(increment*tempMoveVectNor2th[0]);
    seaGrassGather0th[46]+=(increment*tempMoveVectNor2th[1]);
    seaGrassGather0th[47]+=(increment*tempMoveVectNor2th[2]);
    seaGrassGather0th[63]+=(increment*tempMoveVectNor2th[0]);
    seaGrassGather0th[64]+=(increment*tempMoveVectNor2th[1]);
    seaGrassGather0th[65]+=(increment*tempMoveVectNor2th[2]);
    /////////////////////////////////
    baseX=GameWorld::flowerPosition0[0];
    baseY=GameWorld::flowerPosition0[1]-2.0;
    baseZ=GameWorld::flowerPosition0[2];
    seaGrassGather2th[0]=baseX;
    seaGrassGather2th[1]=baseY;
    seaGrassGather2th[2]=baseZ;
    seaGrassGather2th[3]=baseX;
    seaGrassGather2th[4]=baseY+2.0;
    seaGrassGather2th[5]=baseZ;
    seaGrassGather2th[6]=baseX;
    seaGrassGather2th[7]=baseY+4.0;
    seaGrassGather2th[8]=baseZ;
    seaGrassGather2th[9]=baseX;
    seaGrassGather2th[10]=baseY+6.0;
    seaGrassGather2th[11]=baseZ;
    seaGrassGather2th[12]=baseX;
    seaGrassGather2th[13]=baseY+8.0;
    seaGrassGather2th[14]=baseZ;
    seaGrassGather2th[15]=baseX;
    seaGrassGather2th[16]=baseY+10.0;
    seaGrassGather2th[17]=baseZ;

    seaGrassGather2th[18]=baseX-1.0;
    seaGrassGather2th[19]=baseY;
    seaGrassGather2th[20]=baseZ;
    seaGrassGather2th[21]=baseX-1.0;
    seaGrassGather2th[22]=baseY+2.0;
    seaGrassGather2th[23]=baseZ;
    seaGrassGather2th[24]=baseX-1.0;
    seaGrassGather2th[25]=baseY+4.0;
    seaGrassGather2th[26]=baseZ;
    seaGrassGather2th[27]=baseX-1.0;
    seaGrassGather2th[28]=baseY+6.0;
    seaGrassGather2th[29]=baseZ;
    seaGrassGather2th[30]=baseX-1.0;
    seaGrassGather2th[31]=baseY+8.0;
    seaGrassGather2th[32]=baseZ;
    seaGrassGather2th[33]=baseX-1.0;
    seaGrassGather2th[34]=baseY+10.0;
    seaGrassGather2th[35]=baseZ;

    seaGrassGather2th[36]=baseX-2.0;
    seaGrassGather2th[37]=baseY;
    seaGrassGather2th[38]=baseZ;
    seaGrassGather2th[39]=baseX-2.0;
    seaGrassGather2th[40]=baseY+2.0;
    seaGrassGather2th[41]=baseZ;
    seaGrassGather2th[42]=baseX-2.0;
    seaGrassGather2th[43]=baseY+4.0;
    seaGrassGather2th[44]=baseZ;
    seaGrassGather2th[45]=baseX-2.0;
    seaGrassGather2th[46]=baseY+6.0;
    seaGrassGather2th[47]=baseZ;
    seaGrassGather2th[48]=baseX-2.0;
    seaGrassGather2th[49]=baseY+8.0;
    seaGrassGather2th[50]=baseZ;
    seaGrassGather2th[51]=baseX-2.0;
    seaGrassGather2th[52]=baseY+10.0;
    seaGrassGather2th[53]=baseZ;

    seaGrassGather2th[54]=baseX-3.0;
    seaGrassGather2th[55]=baseY;
    seaGrassGather2th[56]=baseZ;
    seaGrassGather2th[57]=baseX-3.0;
    seaGrassGather2th[58]=baseY+2.0;
    seaGrassGather2th[59]=baseZ;
    seaGrassGather2th[60]=baseX-3.0;
    seaGrassGather2th[61]=baseY+4.0;
    seaGrassGather2th[62]=baseZ;
    seaGrassGather2th[63]=baseX-3.0;
    seaGrassGather2th[64]=baseY+6.0;
    seaGrassGather2th[65]=baseZ;
    seaGrassGather2th[66]=baseX-3.0;
    seaGrassGather2th[67]=baseY+8.0;
    seaGrassGather2th[68]=baseZ;
    seaGrassGather2th[69]=baseX-3.0;
    seaGrassGather2th[70]=baseY+10.0;
    seaGrassGather2th[71]=baseZ;


    float increment2=0.02*drawSeaGrassPointer2th;
    seaGrassGather2th[15]+=(increment2*tempMoveVectNor6th[0]);
    seaGrassGather2th[16]+=(increment2*tempMoveVectNor6th[1]);
    seaGrassGather2th[17]+=(increment2*tempMoveVectNor6th[2]);
    seaGrassGather2th[33]+=(increment2*tempMoveVectNor6th[0]);
    seaGrassGather2th[34]+=(increment2*tempMoveVectNor6th[1]);
    seaGrassGather2th[35]+=(increment2*tempMoveVectNor6th[2]);
    seaGrassGather2th[51]+=(increment2*tempMoveVectNor6th[0]);
    seaGrassGather2th[52]+=(increment2*tempMoveVectNor6th[1]);
    seaGrassGather2th[53]+=(increment2*tempMoveVectNor6th[2]);
    seaGrassGather2th[69]+=(increment2*tempMoveVectNor6th[0]);
    seaGrassGather2th[70]+=(increment2*tempMoveVectNor6th[1]);
    seaGrassGather2th[71]+=(increment2*tempMoveVectNor6th[2]);
    increment2=0.015*drawSeaGrassPointer2th;
    seaGrassGather2th[12]+=(increment2*tempMoveVectNor7th[0]);
    seaGrassGather2th[13]+=(increment2*tempMoveVectNor7th[1]);
    seaGrassGather2th[14]+=(increment2*tempMoveVectNor7th[2]);
    seaGrassGather2th[30]+=(increment2*tempMoveVectNor7th[0]);
    seaGrassGather2th[31]+=(increment2*tempMoveVectNor7th[1]);
    seaGrassGather2th[32]+=(increment2*tempMoveVectNor7th[2]);
    seaGrassGather2th[48]+=(increment2*tempMoveVectNor7th[0]);
    seaGrassGather2th[49]+=(increment2*tempMoveVectNor7th[1]);
    seaGrassGather2th[50]+=(increment2*tempMoveVectNor7th[2]);
    seaGrassGather2th[66]+=(increment2*tempMoveVectNor7th[0]);
    seaGrassGather2th[67]+=(increment2*tempMoveVectNor7th[1]);
    seaGrassGather2th[68]+=(increment2*tempMoveVectNor7th[2]);
    increment2=0.01*drawSeaGrassPointer2th;
    seaGrassGather2th[9]+=(increment2*tempMoveVectNor8th[0]);
    seaGrassGather2th[10]+=(increment2*tempMoveVectNor8th[1]);
    seaGrassGather2th[11]+=(increment2*tempMoveVectNor8th[2]);
    seaGrassGather2th[27]+=(increment2*tempMoveVectNor8th[0]);
    seaGrassGather2th[28]+=(increment2*tempMoveVectNor8th[1]);
    seaGrassGather2th[29]+=(increment2*tempMoveVectNor8th[2]);
    seaGrassGather2th[45]+=(increment2*tempMoveVectNor8th[0]);
    seaGrassGather2th[46]+=(increment2*tempMoveVectNor8th[1]);
    seaGrassGather2th[47]+=(increment2*tempMoveVectNor8th[2]);
    seaGrassGather2th[63]+=(increment2*tempMoveVectNor8th[0]);
    seaGrassGather2th[64]+=(increment2*tempMoveVectNor8th[1]);
    seaGrassGather2th[65]+=(increment2*tempMoveVectNor8th[2]);
    /////////////////////////////////////
    baseX=GameWorld::flowerPosition2[0];
    baseY=GameWorld::flowerPosition2[1]-1.3;
    baseZ=GameWorld::flowerPosition2[2];
    seaGrassGather4th[0]=baseX;
    seaGrassGather4th[1]=baseY;
    seaGrassGather4th[2]=baseZ;
    seaGrassGather4th[3]=baseX;
    seaGrassGather4th[4]=baseY+1.5;
    seaGrassGather4th[5]=baseZ;
    seaGrassGather4th[6]=baseX;
    seaGrassGather4th[7]=baseY+3.0;
    seaGrassGather4th[8]=baseZ;
    seaGrassGather4th[9]=baseX;
    seaGrassGather4th[10]=baseY+4.5;
    seaGrassGather4th[11]=baseZ;
    seaGrassGather4th[12]=baseX;
    seaGrassGather4th[13]=baseY+6.0;
    seaGrassGather4th[14]=baseZ;
    seaGrassGather4th[15]=baseX;
    seaGrassGather4th[16]=baseY+7.5;
    seaGrassGather4th[17]=baseZ;

    seaGrassGather4th[18]=baseX+1.5;
    seaGrassGather4th[19]=baseY;
    seaGrassGather4th[20]=baseZ;
    seaGrassGather4th[21]=baseX+1.5;
    seaGrassGather4th[22]=baseY+1.5;
    seaGrassGather4th[23]=baseZ;
    seaGrassGather4th[24]=baseX+1.5;
    seaGrassGather4th[25]=baseY+3.0;
    seaGrassGather4th[26]=baseZ;
    seaGrassGather4th[27]=baseX+1.5;
    seaGrassGather4th[28]=baseY+4.5;
    seaGrassGather4th[29]=baseZ;
    seaGrassGather4th[30]=baseX+1.5;
    seaGrassGather4th[31]=baseY+6.0;
    seaGrassGather4th[32]=baseZ;
    seaGrassGather4th[33]=baseX+1.5;
    seaGrassGather4th[34]=baseY+7.5;
    seaGrassGather4th[35]=baseZ;

    seaGrassGather4th[36]=baseX+3.0;
    seaGrassGather4th[37]=baseY;
    seaGrassGather4th[38]=baseZ;
    seaGrassGather4th[39]=baseX+3.0;
    seaGrassGather4th[40]=baseY+1.5;
    seaGrassGather4th[41]=baseZ;
    seaGrassGather4th[42]=baseX+3.0;
    seaGrassGather4th[43]=baseY+3.0;
    seaGrassGather4th[44]=baseZ;
    seaGrassGather4th[45]=baseX+3.0;
    seaGrassGather4th[46]=baseY+4.5;
    seaGrassGather4th[47]=baseZ;
    seaGrassGather4th[48]=baseX+3.0;
    seaGrassGather4th[49]=baseY+6.0;
    seaGrassGather4th[50]=baseZ;
    seaGrassGather4th[51]=baseX+3.0;
    seaGrassGather4th[52]=baseY+7.5;
    seaGrassGather4th[53]=baseZ;

    seaGrassGather4th[54]=baseX+4.5;
    seaGrassGather4th[55]=baseY;
    seaGrassGather4th[56]=baseZ;
    seaGrassGather4th[57]=baseX+4.5;
    seaGrassGather4th[58]=baseY+1.5;
    seaGrassGather4th[59]=baseZ;
    seaGrassGather4th[60]=baseX+4.5;
    seaGrassGather4th[61]=baseY+3.0;
    seaGrassGather4th[62]=baseZ;
    seaGrassGather4th[63]=baseX+4.5;
    seaGrassGather4th[64]=baseY+4.5;
    seaGrassGather4th[65]=baseZ;
    seaGrassGather4th[66]=baseX+4.5;
    seaGrassGather4th[67]=baseY+6.0;
    seaGrassGather4th[68]=baseZ;
    seaGrassGather4th[69]=baseX+4.5;
    seaGrassGather4th[70]=baseY+7.5;
    seaGrassGather4th[71]=baseZ;


    float increment4=0.02*drawSeaGrassPointer4th;
    seaGrassGather4th[15]+=(increment4*tempMoveVectNor12th[0]);
    seaGrassGather4th[16]+=(increment4*tempMoveVectNor12th[1]);
    seaGrassGather4th[17]+=(increment4*tempMoveVectNor12th[2]);
    seaGrassGather4th[33]+=(increment4*tempMoveVectNor12th[0]);
    seaGrassGather4th[34]+=(increment4*tempMoveVectNor12th[1]);
    seaGrassGather4th[35]+=(increment4*tempMoveVectNor12th[2]);
    seaGrassGather4th[51]+=(increment4*tempMoveVectNor12th[0]);
    seaGrassGather4th[52]+=(increment4*tempMoveVectNor12th[1]);
    seaGrassGather4th[53]+=(increment4*tempMoveVectNor12th[2]);
    seaGrassGather4th[69]+=(increment4*tempMoveVectNor12th[0]);
    seaGrassGather4th[70]+=(increment4*tempMoveVectNor12th[1]);
    seaGrassGather4th[71]+=(increment4*tempMoveVectNor12th[2]);
    increment4=0.015*drawSeaGrassPointer4th;
    seaGrassGather4th[12]+=(increment4*tempMoveVectNor13th[0]);
    seaGrassGather4th[13]+=(increment4*tempMoveVectNor13th[1]);
    seaGrassGather4th[14]+=(increment4*tempMoveVectNor13th[2]);
    seaGrassGather4th[30]+=(increment4*tempMoveVectNor13th[0]);
    seaGrassGather4th[31]+=(increment4*tempMoveVectNor13th[1]);
    seaGrassGather4th[32]+=(increment4*tempMoveVectNor13th[2]);
    seaGrassGather4th[48]+=(increment4*tempMoveVectNor13th[0]);
    seaGrassGather4th[49]+=(increment4*tempMoveVectNor13th[1]);
    seaGrassGather4th[50]+=(increment4*tempMoveVectNor13th[2]);
    seaGrassGather4th[66]+=(increment4*tempMoveVectNor13th[0]);
    seaGrassGather4th[67]+=(increment4*tempMoveVectNor13th[1]);
    seaGrassGather4th[68]+=(increment4*tempMoveVectNor13th[2]);
    increment4=0.01*drawSeaGrassPointer4th;
    seaGrassGather4th[9]+=(increment4*tempMoveVectNor14th[0]);
    seaGrassGather4th[10]+=(increment4*tempMoveVectNor14th[1]);
    seaGrassGather4th[11]+=(increment4*tempMoveVectNor14th[2]);
    seaGrassGather4th[27]+=(increment4*tempMoveVectNor14th[0]);
    seaGrassGather4th[28]+=(increment4*tempMoveVectNor14th[1]);
    seaGrassGather4th[29]+=(increment4*tempMoveVectNor14th[2]);
    seaGrassGather4th[45]+=(increment4*tempMoveVectNor14th[0]);
    seaGrassGather4th[46]+=(increment4*tempMoveVectNor14th[1]);
    seaGrassGather4th[47]+=(increment4*tempMoveVectNor14th[2]);
    seaGrassGather4th[63]+=(increment4*tempMoveVectNor14th[0]);
    seaGrassGather4th[64]+=(increment4*tempMoveVectNor14th[1]);
    seaGrassGather4th[65]+=(increment4*tempMoveVectNor14th[2]);
    ////////////////////////////////////////////////////////////////////
    int currPointIndex=(30+10)*3;
    baseX=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]-3.4;
    baseY=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1]-0.7;
    baseZ=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2];
    seaGrassGather5th[0]=baseX;
    seaGrassGather5th[1]=baseY;
    seaGrassGather5th[2]=baseZ;
    seaGrassGather5th[3]=baseX;
    seaGrassGather5th[4]=baseY+1.5;
    seaGrassGather5th[5]=baseZ;
    seaGrassGather5th[6]=baseX;
    seaGrassGather5th[7]=baseY+3.0;
    seaGrassGather5th[8]=baseZ;
    seaGrassGather5th[9]=baseX;
    seaGrassGather5th[10]=baseY+4.5;
    seaGrassGather5th[11]=baseZ;
    seaGrassGather5th[12]=baseX;
    seaGrassGather5th[13]=baseY+6.0;
    seaGrassGather5th[14]=baseZ;
    seaGrassGather5th[15]=baseX;
    seaGrassGather5th[16]=baseY+7.5;
    seaGrassGather5th[17]=baseZ;

    seaGrassGather5th[18]=baseX+1.5;
    seaGrassGather5th[19]=baseY;
    seaGrassGather5th[20]=baseZ;
    seaGrassGather5th[21]=baseX+1.5;
    seaGrassGather5th[22]=baseY+1.5;
    seaGrassGather5th[23]=baseZ;
    seaGrassGather5th[24]=baseX+1.5;
    seaGrassGather5th[25]=baseY+3.0;
    seaGrassGather5th[26]=baseZ;
    seaGrassGather5th[27]=baseX+1.5;
    seaGrassGather5th[28]=baseY+4.5;
    seaGrassGather5th[29]=baseZ;
    seaGrassGather5th[30]=baseX+1.5;
    seaGrassGather5th[31]=baseY+6.0;
    seaGrassGather5th[32]=baseZ;
    seaGrassGather5th[33]=baseX+1.5;
    seaGrassGather5th[34]=baseY+7.5;
    seaGrassGather5th[35]=baseZ;

    seaGrassGather5th[36]=baseX+3.0;
    seaGrassGather5th[37]=baseY;
    seaGrassGather5th[38]=baseZ;
    seaGrassGather5th[39]=baseX+3.0;
    seaGrassGather5th[40]=baseY+1.5;
    seaGrassGather5th[41]=baseZ;
    seaGrassGather5th[42]=baseX+3.0;
    seaGrassGather5th[43]=baseY+3.0;
    seaGrassGather5th[44]=baseZ;
    seaGrassGather5th[45]=baseX+3.0;
    seaGrassGather5th[46]=baseY+4.5;
    seaGrassGather5th[47]=baseZ;
    seaGrassGather5th[48]=baseX+3.0;
    seaGrassGather5th[49]=baseY+6.0;
    seaGrassGather5th[50]=baseZ;
    seaGrassGather5th[51]=baseX+3.0;
    seaGrassGather5th[52]=baseY+7.5;
    seaGrassGather5th[53]=baseZ;

    seaGrassGather5th[54]=baseX+4.5;
    seaGrassGather5th[55]=baseY;
    seaGrassGather5th[56]=baseZ;
    seaGrassGather5th[57]=baseX+4.5;
    seaGrassGather5th[58]=baseY+1.5;
    seaGrassGather5th[59]=baseZ;
    seaGrassGather5th[60]=baseX+4.5;
    seaGrassGather5th[61]=baseY+3.0;
    seaGrassGather5th[62]=baseZ;
    seaGrassGather5th[63]=baseX+4.5;
    seaGrassGather5th[64]=baseY+4.5;
    seaGrassGather5th[65]=baseZ;
    seaGrassGather5th[66]=baseX+4.5;
    seaGrassGather5th[67]=baseY+6.0;
    seaGrassGather5th[68]=baseZ;
    seaGrassGather5th[69]=baseX+4.5;
    seaGrassGather5th[70]=baseY+7.5;
    seaGrassGather5th[71]=baseZ;


    float increment5=0.02*drawSeaGrassPointer5th;
    seaGrassGather5th[15]+=(increment5*tempMoveVectNor15th[0]);
    seaGrassGather5th[16]+=(increment5*tempMoveVectNor15th[1]);
    seaGrassGather5th[17]+=(increment5*tempMoveVectNor15th[2]);
    seaGrassGather5th[33]+=(increment5*tempMoveVectNor15th[0]);
    seaGrassGather5th[34]+=(increment5*tempMoveVectNor15th[1]);
    seaGrassGather5th[35]+=(increment5*tempMoveVectNor15th[2]);
    seaGrassGather5th[51]+=(increment5*tempMoveVectNor15th[0]);
    seaGrassGather5th[52]+=(increment5*tempMoveVectNor15th[1]);
    seaGrassGather5th[53]+=(increment5*tempMoveVectNor15th[2]);
    seaGrassGather5th[69]+=(increment5*tempMoveVectNor15th[0]);
    seaGrassGather5th[70]+=(increment5*tempMoveVectNor15th[1]);
    seaGrassGather5th[71]+=(increment5*tempMoveVectNor15th[2]);
    increment5=0.015*drawSeaGrassPointer5th;
    seaGrassGather5th[12]+=(increment5*tempMoveVectNor16th[0]);
    seaGrassGather5th[13]+=(increment5*tempMoveVectNor16th[1]);
    seaGrassGather5th[14]+=(increment5*tempMoveVectNor16th[2]);
    seaGrassGather5th[30]+=(increment5*tempMoveVectNor16th[0]);
    seaGrassGather5th[31]+=(increment5*tempMoveVectNor16th[1]);
    seaGrassGather5th[32]+=(increment5*tempMoveVectNor16th[2]);
    seaGrassGather5th[48]+=(increment5*tempMoveVectNor16th[0]);
    seaGrassGather5th[49]+=(increment5*tempMoveVectNor16th[1]);
    seaGrassGather5th[50]+=(increment5*tempMoveVectNor16th[2]);
    seaGrassGather5th[66]+=(increment5*tempMoveVectNor16th[0]);
    seaGrassGather5th[67]+=(increment5*tempMoveVectNor16th[1]);
    seaGrassGather5th[68]+=(increment5*tempMoveVectNor16th[2]);
    increment5=0.01*drawSeaGrassPointer5th;
    seaGrassGather5th[9]+=(increment5*tempMoveVectNor17th[0]);
    seaGrassGather5th[10]+=(increment5*tempMoveVectNor17th[1]);
    seaGrassGather5th[11]+=(increment5*tempMoveVectNor17th[2]);
    seaGrassGather5th[27]+=(increment5*tempMoveVectNor17th[0]);
    seaGrassGather5th[28]+=(increment5*tempMoveVectNor17th[1]);
    seaGrassGather5th[29]+=(increment5*tempMoveVectNor17th[2]);
    seaGrassGather5th[45]+=(increment5*tempMoveVectNor17th[0]);
    seaGrassGather5th[46]+=(increment5*tempMoveVectNor17th[1]);
    seaGrassGather5th[47]+=(increment5*tempMoveVectNor17th[2]);
    seaGrassGather5th[63]+=(increment5*tempMoveVectNor17th[0]);
    seaGrassGather5th[64]+=(increment5*tempMoveVectNor17th[1]);
    seaGrassGather5th[65]+=(increment5*tempMoveVectNor17th[2]);
    /////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////
    currPointIndex=(30+20)*3;
    baseX=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]-7.0;
    baseY=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1]-0.7;
    baseZ=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2];
    seaGrassGather6th[0]=baseX;
    seaGrassGather6th[1]=baseY;
    seaGrassGather6th[2]=baseZ;
    seaGrassGather6th[3]=baseX;
    seaGrassGather6th[4]=baseY+1.5;
    seaGrassGather6th[5]=baseZ;
    seaGrassGather6th[6]=baseX;
    seaGrassGather6th[7]=baseY+3.0;
    seaGrassGather6th[8]=baseZ;
    seaGrassGather6th[9]=baseX;
    seaGrassGather6th[10]=baseY+4.5;
    seaGrassGather6th[11]=baseZ;
    seaGrassGather6th[12]=baseX;
    seaGrassGather6th[13]=baseY+6.0;
    seaGrassGather6th[14]=baseZ;
    seaGrassGather6th[15]=baseX;
    seaGrassGather6th[16]=baseY+7.5;
    seaGrassGather6th[17]=baseZ;

    seaGrassGather6th[18]=baseX+1.5;
    seaGrassGather6th[19]=baseY;
    seaGrassGather6th[20]=baseZ;
    seaGrassGather6th[21]=baseX+1.5;
    seaGrassGather6th[22]=baseY+1.5;
    seaGrassGather6th[23]=baseZ;
    seaGrassGather6th[24]=baseX+1.5;
    seaGrassGather6th[25]=baseY+3.0;
    seaGrassGather6th[26]=baseZ;
    seaGrassGather6th[27]=baseX+1.5;
    seaGrassGather6th[28]=baseY+4.5;
    seaGrassGather6th[29]=baseZ;
    seaGrassGather6th[30]=baseX+1.5;
    seaGrassGather6th[31]=baseY+6.0;
    seaGrassGather6th[32]=baseZ;
    seaGrassGather6th[33]=baseX+1.5;
    seaGrassGather6th[34]=baseY+7.5;
    seaGrassGather6th[35]=baseZ;

    seaGrassGather6th[36]=baseX+3.0;
    seaGrassGather6th[37]=baseY;
    seaGrassGather6th[38]=baseZ;
    seaGrassGather6th[39]=baseX+3.0;
    seaGrassGather6th[40]=baseY+1.5;
    seaGrassGather6th[41]=baseZ;
    seaGrassGather6th[42]=baseX+3.0;
    seaGrassGather6th[43]=baseY+3.0;
    seaGrassGather6th[44]=baseZ;
    seaGrassGather6th[45]=baseX+3.0;
    seaGrassGather6th[46]=baseY+4.5;
    seaGrassGather6th[47]=baseZ;
    seaGrassGather6th[48]=baseX+3.0;
    seaGrassGather6th[49]=baseY+6.0;
    seaGrassGather6th[50]=baseZ;
    seaGrassGather6th[51]=baseX+3.0;
    seaGrassGather6th[52]=baseY+7.5;
    seaGrassGather6th[53]=baseZ;

    seaGrassGather6th[54]=baseX+4.5;
    seaGrassGather6th[55]=baseY;
    seaGrassGather6th[56]=baseZ;
    seaGrassGather6th[57]=baseX+4.5;
    seaGrassGather6th[58]=baseY+1.5;
    seaGrassGather6th[59]=baseZ;
    seaGrassGather6th[60]=baseX+4.5;
    seaGrassGather6th[61]=baseY+3.0;
    seaGrassGather6th[62]=baseZ;
    seaGrassGather6th[63]=baseX+4.5;
    seaGrassGather6th[64]=baseY+4.5;
    seaGrassGather6th[65]=baseZ;
    seaGrassGather6th[66]=baseX+4.5;
    seaGrassGather6th[67]=baseY+6.0;
    seaGrassGather6th[68]=baseZ;
    seaGrassGather6th[69]=baseX+4.5;
    seaGrassGather6th[70]=baseY+7.5;
    seaGrassGather6th[71]=baseZ;


    float increment6=0.02*drawSeaGrassPointer6th;
    seaGrassGather6th[15]+=(increment6*tempMoveVectNor18th[0]);
    seaGrassGather6th[16]+=(increment6*tempMoveVectNor18th[1]);
    seaGrassGather6th[17]+=(increment6*tempMoveVectNor18th[2]);
    seaGrassGather6th[33]+=(increment6*tempMoveVectNor18th[0]);
    seaGrassGather6th[34]+=(increment6*tempMoveVectNor18th[1]);
    seaGrassGather6th[35]+=(increment6*tempMoveVectNor18th[2]);
    seaGrassGather6th[51]+=(increment6*tempMoveVectNor18th[0]);
    seaGrassGather6th[52]+=(increment6*tempMoveVectNor18th[1]);
    seaGrassGather6th[53]+=(increment6*tempMoveVectNor18th[2]);
    seaGrassGather6th[69]+=(increment6*tempMoveVectNor18th[0]);
    seaGrassGather6th[70]+=(increment6*tempMoveVectNor18th[1]);
    seaGrassGather6th[71]+=(increment6*tempMoveVectNor18th[2]);
    increment6=0.015*drawSeaGrassPointer6th;
    seaGrassGather6th[12]+=(increment6*tempMoveVectNor19th[0]);
    seaGrassGather6th[13]+=(increment6*tempMoveVectNor19th[1]);
    seaGrassGather6th[14]+=(increment6*tempMoveVectNor19th[2]);
    seaGrassGather6th[30]+=(increment6*tempMoveVectNor19th[0]);
    seaGrassGather6th[31]+=(increment6*tempMoveVectNor19th[1]);
    seaGrassGather6th[32]+=(increment6*tempMoveVectNor19th[2]);
    seaGrassGather6th[48]+=(increment6*tempMoveVectNor19th[0]);
    seaGrassGather6th[49]+=(increment6*tempMoveVectNor19th[1]);
    seaGrassGather6th[50]+=(increment6*tempMoveVectNor19th[2]);
    seaGrassGather6th[66]+=(increment6*tempMoveVectNor19th[0]);
    seaGrassGather6th[67]+=(increment6*tempMoveVectNor19th[1]);
    seaGrassGather6th[68]+=(increment6*tempMoveVectNor19th[2]);
    increment6=0.01*drawSeaGrassPointer6th;
    seaGrassGather6th[9]+=(increment6*tempMoveVectNor20th[0]);
    seaGrassGather6th[10]+=(increment6*tempMoveVectNor20th[1]);
    seaGrassGather6th[11]+=(increment6*tempMoveVectNor20th[2]);
    seaGrassGather6th[27]+=(increment6*tempMoveVectNor20th[0]);
    seaGrassGather6th[28]+=(increment6*tempMoveVectNor20th[1]);
    seaGrassGather6th[29]+=(increment6*tempMoveVectNor20th[2]);
    seaGrassGather6th[45]+=(increment6*tempMoveVectNor20th[0]);
    seaGrassGather6th[46]+=(increment6*tempMoveVectNor20th[1]);
    seaGrassGather6th[47]+=(increment6*tempMoveVectNor20th[2]);
    seaGrassGather6th[63]+=(increment6*tempMoveVectNor20th[0]);
    seaGrassGather6th[64]+=(increment6*tempMoveVectNor20th[1]);
    seaGrassGather6th[65]+=(increment6*tempMoveVectNor20th[2]);
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    currPointIndex=(30+17)*3;
    baseX=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]+3.0;
    baseY=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1]-2.4;
    baseZ=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2]+1.0;
    seaGrassGather7th[0]=baseX;
    seaGrassGather7th[1]=baseY;
    seaGrassGather7th[2]=baseZ;
    seaGrassGather7th[3]=baseX;
    seaGrassGather7th[4]=baseY+3.0;
    seaGrassGather7th[5]=baseZ;
    seaGrassGather7th[6]=baseX;
    seaGrassGather7th[7]=baseY+6.0;
    seaGrassGather7th[8]=baseZ;
    seaGrassGather7th[9]=baseX;
    seaGrassGather7th[10]=baseY+9.0;
    seaGrassGather7th[11]=baseZ;
    seaGrassGather7th[12]=baseX;
    seaGrassGather7th[13]=baseY+12.0;
    seaGrassGather7th[14]=baseZ;
    seaGrassGather7th[15]=baseX;
    seaGrassGather7th[16]=baseY+15.0;
    seaGrassGather7th[17]=baseZ;

    seaGrassGather7th[18]=baseX+1.5;
    seaGrassGather7th[19]=baseY;
    seaGrassGather7th[20]=baseZ;
    seaGrassGather7th[21]=baseX+3.0;
    seaGrassGather7th[22]=baseY+3.0;
    seaGrassGather7th[23]=baseZ;
    seaGrassGather7th[24]=baseX+1.5;
    seaGrassGather7th[25]=baseY+6.0;
    seaGrassGather7th[26]=baseZ;
    seaGrassGather7th[27]=baseX+1.5;
    seaGrassGather7th[28]=baseY+9.0;
    seaGrassGather7th[29]=baseZ;
    seaGrassGather7th[30]=baseX+1.5;
    seaGrassGather7th[31]=baseY+12.0;
    seaGrassGather7th[32]=baseZ;
    seaGrassGather7th[33]=baseX+1.5;
    seaGrassGather7th[34]=baseY+15.0;
    seaGrassGather7th[35]=baseZ;

    seaGrassGather7th[36]=baseX+3.0;
    seaGrassGather7th[37]=baseY;
    seaGrassGather7th[38]=baseZ;
    seaGrassGather7th[39]=baseX+3.0;
    seaGrassGather7th[40]=baseY+3.0;
    seaGrassGather7th[41]=baseZ;
    seaGrassGather7th[42]=baseX+3.0;
    seaGrassGather7th[43]=baseY+6.0;
    seaGrassGather7th[44]=baseZ;
    seaGrassGather7th[45]=baseX+3.0;
    seaGrassGather7th[46]=baseY+9.0;
    seaGrassGather7th[47]=baseZ;
    seaGrassGather7th[48]=baseX+3.0;
    seaGrassGather7th[49]=baseY+12.0;
    seaGrassGather7th[50]=baseZ;
    seaGrassGather7th[51]=baseX+3.0;
    seaGrassGather7th[52]=baseY+15.0;
    seaGrassGather7th[53]=baseZ;

    seaGrassGather7th[54]=baseX+4.5;
    seaGrassGather7th[55]=baseY;
    seaGrassGather7th[56]=baseZ;
    seaGrassGather7th[57]=baseX+4.5;
    seaGrassGather7th[58]=baseY+3.0;
    seaGrassGather7th[59]=baseZ;
    seaGrassGather7th[60]=baseX+4.5;
    seaGrassGather7th[61]=baseY+6.0;
    seaGrassGather7th[62]=baseZ;
    seaGrassGather7th[63]=baseX+4.5;
    seaGrassGather7th[64]=baseY+9.0;
    seaGrassGather7th[65]=baseZ;
    seaGrassGather7th[66]=baseX+4.5;
    seaGrassGather7th[67]=baseY+12.0;
    seaGrassGather7th[68]=baseZ;
    seaGrassGather7th[69]=baseX+4.5;
    seaGrassGather7th[70]=baseY+15.0;
    seaGrassGather7th[71]=baseZ;


    float increment7=0.02*drawSeaGrassPointer7th;
    seaGrassGather7th[15]+=(increment7*tempMoveVectNor21th[0]);
    seaGrassGather7th[16]+=(increment7*tempMoveVectNor21th[1]);
    seaGrassGather7th[17]+=(increment7*tempMoveVectNor21th[2]);
    seaGrassGather7th[33]+=(increment7*tempMoveVectNor21th[0]);
    seaGrassGather7th[34]+=(increment7*tempMoveVectNor21th[1]);
    seaGrassGather7th[35]+=(increment7*tempMoveVectNor21th[2]);
    seaGrassGather7th[51]+=(increment7*tempMoveVectNor21th[0]);
    seaGrassGather7th[52]+=(increment7*tempMoveVectNor21th[1]);
    seaGrassGather7th[53]+=(increment7*tempMoveVectNor21th[2]);
    seaGrassGather7th[69]+=(increment7*tempMoveVectNor21th[0]);
    seaGrassGather7th[70]+=(increment7*tempMoveVectNor21th[1]);
    seaGrassGather7th[71]+=(increment7*tempMoveVectNor21th[2]);
    increment7=0.015*drawSeaGrassPointer7th;
    seaGrassGather7th[12]+=(increment7*tempMoveVectNor22th[0]);
    seaGrassGather7th[13]+=(increment7*tempMoveVectNor22th[1]);
    seaGrassGather7th[14]+=(increment7*tempMoveVectNor22th[2]);
    seaGrassGather7th[30]+=(increment7*tempMoveVectNor22th[0]);
    seaGrassGather7th[31]+=(increment7*tempMoveVectNor22th[1]);
    seaGrassGather7th[32]+=(increment7*tempMoveVectNor22th[2]);
    seaGrassGather7th[48]+=(increment7*tempMoveVectNor22th[0]);
    seaGrassGather7th[49]+=(increment7*tempMoveVectNor22th[1]);
    seaGrassGather7th[50]+=(increment7*tempMoveVectNor22th[2]);
    seaGrassGather7th[66]+=(increment7*tempMoveVectNor22th[0]);
    seaGrassGather7th[67]+=(increment7*tempMoveVectNor22th[1]);
    seaGrassGather7th[68]+=(increment7*tempMoveVectNor22th[2]);
    //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////
    currPointIndex=(30+18)*3;
    baseX=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex]+9.2;
    baseY=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+1]-0.4;
    baseZ=gameWorldSeaGrass.getBezPointGather_floor()[currPointIndex+2];
    seaGrassGather8th[0]=baseX;
    seaGrassGather8th[1]=baseY;
    seaGrassGather8th[2]=baseZ;
    seaGrassGather8th[3]=baseX;
    seaGrassGather8th[4]=baseY+1.5;
    seaGrassGather8th[5]=baseZ;
    seaGrassGather8th[6]=baseX;
    seaGrassGather8th[7]=baseY+3.0;
    seaGrassGather8th[8]=baseZ;
    seaGrassGather8th[9]=baseX;
    seaGrassGather8th[10]=baseY+4.5;
    seaGrassGather8th[11]=baseZ;
    seaGrassGather8th[12]=baseX;
    seaGrassGather8th[13]=baseY+6.0;
    seaGrassGather8th[14]=baseZ;
    seaGrassGather8th[15]=baseX;
    seaGrassGather8th[16]=baseY+7.5;
    seaGrassGather8th[17]=baseZ;

    seaGrassGather8th[18]=baseX+1.5;
    seaGrassGather8th[19]=baseY;
    seaGrassGather8th[20]=baseZ;
    seaGrassGather8th[21]=baseX+1.5;
    seaGrassGather8th[22]=baseY+1.5;
    seaGrassGather8th[23]=baseZ;
    seaGrassGather8th[24]=baseX+1.5;
    seaGrassGather8th[25]=baseY+3.0;
    seaGrassGather8th[26]=baseZ;
    seaGrassGather8th[27]=baseX+1.5;
    seaGrassGather8th[28]=baseY+4.5;
    seaGrassGather8th[29]=baseZ;
    seaGrassGather8th[30]=baseX+1.5;
    seaGrassGather8th[31]=baseY+6.0;
    seaGrassGather8th[32]=baseZ;
    seaGrassGather8th[33]=baseX+1.5;
    seaGrassGather8th[34]=baseY+7.5;
    seaGrassGather8th[35]=baseZ;

    seaGrassGather8th[36]=baseX+3.0;
    seaGrassGather8th[37]=baseY;
    seaGrassGather8th[38]=baseZ;
    seaGrassGather8th[39]=baseX+3.0;
    seaGrassGather8th[40]=baseY+1.5;
    seaGrassGather8th[41]=baseZ;
    seaGrassGather8th[42]=baseX+3.0;
    seaGrassGather8th[43]=baseY+3.0;
    seaGrassGather8th[44]=baseZ;
    seaGrassGather8th[45]=baseX+3.0;
    seaGrassGather8th[46]=baseY+4.5;
    seaGrassGather8th[47]=baseZ;
    seaGrassGather8th[48]=baseX+3.0;
    seaGrassGather8th[49]=baseY+6.0;
    seaGrassGather8th[50]=baseZ;
    seaGrassGather8th[51]=baseX+3.0;
    seaGrassGather8th[52]=baseY+7.5;
    seaGrassGather8th[53]=baseZ;

    seaGrassGather8th[54]=baseX+4.5;
    seaGrassGather8th[55]=baseY;
    seaGrassGather8th[56]=baseZ;
    seaGrassGather8th[57]=baseX+4.5;
    seaGrassGather8th[58]=baseY+1.5;
    seaGrassGather8th[59]=baseZ;
    seaGrassGather8th[60]=baseX+4.5;
    seaGrassGather8th[61]=baseY+3.0;
    seaGrassGather8th[62]=baseZ;
    seaGrassGather8th[63]=baseX+4.5;
    seaGrassGather8th[64]=baseY+4.5;
    seaGrassGather8th[65]=baseZ;
    seaGrassGather8th[66]=baseX+4.5;
    seaGrassGather8th[67]=baseY+6.0;
    seaGrassGather8th[68]=baseZ;
    seaGrassGather8th[69]=baseX+4.5;
    seaGrassGather8th[70]=baseY+7.5;
    seaGrassGather8th[71]=baseZ;


    float increment8=0.02*drawSeaGrassPointer8th;
    seaGrassGather8th[15]+=(increment8*tempMoveVectNor18th[0]);
    seaGrassGather8th[16]+=(increment8*tempMoveVectNor18th[1]);
    seaGrassGather8th[17]+=(increment8*tempMoveVectNor18th[2]);
    seaGrassGather8th[33]+=(increment8*tempMoveVectNor18th[0]);
    seaGrassGather8th[34]+=(increment8*tempMoveVectNor18th[1]);
    seaGrassGather8th[35]+=(increment8*tempMoveVectNor18th[2]);
    seaGrassGather8th[51]+=(increment8*tempMoveVectNor18th[0]);
    seaGrassGather8th[52]+=(increment8*tempMoveVectNor18th[1]);
    seaGrassGather8th[53]+=(increment8*tempMoveVectNor18th[2]);
    seaGrassGather8th[69]+=(increment8*tempMoveVectNor18th[0]);
    seaGrassGather8th[70]+=(increment8*tempMoveVectNor18th[1]);
    seaGrassGather8th[71]+=(increment8*tempMoveVectNor18th[2]);
    increment8=0.015*drawSeaGrassPointer8th;
    seaGrassGather8th[12]+=(increment8*tempMoveVectNor19th[0]);
    seaGrassGather8th[13]+=(increment8*tempMoveVectNor19th[1]);
    seaGrassGather8th[14]+=(increment8*tempMoveVectNor19th[2]);
    seaGrassGather8th[30]+=(increment8*tempMoveVectNor19th[0]);
    seaGrassGather8th[31]+=(increment8*tempMoveVectNor19th[1]);
    seaGrassGather8th[32]+=(increment8*tempMoveVectNor19th[2]);
    seaGrassGather8th[48]+=(increment8*tempMoveVectNor19th[0]);
    seaGrassGather8th[49]+=(increment8*tempMoveVectNor19th[1]);
    seaGrassGather8th[50]+=(increment8*tempMoveVectNor19th[2]);
    seaGrassGather8th[66]+=(increment8*tempMoveVectNor19th[0]);
    seaGrassGather8th[67]+=(increment8*tempMoveVectNor19th[1]);
    seaGrassGather8th[68]+=(increment8*tempMoveVectNor19th[2]);
    increment8=0.01*drawSeaGrassPointer8th;
    seaGrassGather8th[9]+=(increment8*tempMoveVectNor20th[0]);
    seaGrassGather8th[10]+=(increment8*tempMoveVectNor20th[1]);
    seaGrassGather8th[11]+=(increment8*tempMoveVectNor20th[2]);
    seaGrassGather8th[27]+=(increment8*tempMoveVectNor20th[0]);
    seaGrassGather8th[28]+=(increment8*tempMoveVectNor20th[1]);
    seaGrassGather8th[29]+=(increment8*tempMoveVectNor20th[2]);
    seaGrassGather8th[45]+=(increment8*tempMoveVectNor20th[0]);
    seaGrassGather8th[46]+=(increment8*tempMoveVectNor20th[1]);
    seaGrassGather8th[47]+=(increment8*tempMoveVectNor20th[2]);
    seaGrassGather8th[63]+=(increment8*tempMoveVectNor20th[0]);
    seaGrassGather8th[64]+=(increment8*tempMoveVectNor20th[1]);
    seaGrassGather8th[65]+=(increment8*tempMoveVectNor20th[2]);

}


void SeaGrass::drawSeaGrassMap(int tag,float* flowerPosition){
    GLuint seaGrassMapProgram=shaderUtilSeaGrass.getSeaGrassMapProgram();
    glUseProgram(seaGrassMapProgram);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);                                                             //开混合模式贴图
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式
    GLuint projectionMatrixLocation = glGetUniformLocation(seaGrassMapProgram,"ProjectionMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(seaGrassMapProgram,"ViewMatrix");
    GLuint modelMatrixLocation = glGetUniformLocation(seaGrassMapProgram,"ModelMatrix");
    flyElephantSeaGrass.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint eyeEarMouthTagLocation = glGetUniformLocation(seaGrassMapProgram,"seaGrassTag");
    glUniform1i(eyeEarMouthTagLocation,tag);

    GLint positionLocation=glGetAttribLocation(seaGrassMapProgram,"positionV");

    GLuint* seaGrassTextures=getSeaGrassTextureList();
    GLuint* rockTextures=getRockList();
    GLuint* seaSnailTextures=getSeaSnailList();
    glActiveTexture(GL_TEXTURE0);
    float subX=5.0;
    float subY=5.0;
    if(tag==10){
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[12]);
    }else if(tag==11){
        subY=6.0;
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[14]);
    }else if(tag==12){
        subX=4.0;
        subY=3.0;
        glBindTexture(GL_TEXTURE_2D, seaSnailTextures[6]);
    }else if(tag==13){
        subX=3.0;
        subY=5.0;
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[15]);
    }else if(tag==14){
        subX=13.0;
        subY=9.0;
        glBindTexture(GL_TEXTURE_2D, rockTextures[2]);
    }else if(tag==15){
        subY=11.0;
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[11]);
    }else if(tag==16){
        subX=4.0;
        subY=2.0;
        glBindTexture(GL_TEXTURE_2D, seaSnailTextures[2]);
    }else if(tag==17){
        subX=2.5;
        subY=2.0;
        glBindTexture(GL_TEXTURE_2D, seaSnailTextures[8]);
    }else if(tag==18){
        subX=3.0;
        subY=3.0;
        glBindTexture(GL_TEXTURE_2D, seaSnailTextures[3]);
    }else if(tag==19){
        subX=3.0;
        subY=3.0;
        glBindTexture(GL_TEXTURE_2D, seaSnailTextures[7]);
    }else if(tag==20){
        subX=17.0;
        subY=2.0;
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[20]);
    }else if(tag==100){
        subX=0.8;
        subY=0.6;
        glBindTexture(GL_TEXTURE_2D, seaGrassTextures[21]);
    }
    float position[]={flowerPosition[0],flowerPosition[1]+subY,flowerPosition[2],      flowerPosition[0],flowerPosition[1],flowerPosition[2],
                      flowerPosition[0]-subX,flowerPosition[1],flowerPosition[2],
                      flowerPosition[0],flowerPosition[1]+subY,flowerPosition[2],      flowerPosition[0]-subX,flowerPosition[1],flowerPosition[2],
                      flowerPosition[0]-subX,flowerPosition[1]+subY,flowerPosition[2]};
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3*4, position);
    glEnableVertexAttribArray(positionLocation);

    GLuint seaGrassTextureLocation = glGetUniformLocation(seaGrassMapProgram, "U_Texture");
    glUniform1i(seaGrassTextureLocation, 0);
    GLuint seaGrassTexcoordLocation = glGetAttribLocation(seaGrassMapProgram, "texcoord");
    float texcoordGather[]={0.0,1.0,0.0,0.0,1.0,0.0,0.0,1.0,1.0,0.0,1.0,1.0};
    glVertexAttribPointer(seaGrassTexcoordLocation, 2, GL_FLOAT, GL_FALSE, 2*4, texcoordGather);
    glEnableVertexAttribArray(seaGrassTexcoordLocation);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisable(GL_BLEND);
    glUseProgram(0);

}
