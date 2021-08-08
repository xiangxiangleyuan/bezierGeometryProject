#include "BezierAnimationByAngle.h"

WizardGeom wizardGeomBezierAnimationByAngle;
BezierAnimationByAngle::BezierAnimationByAngle() {}
BezierAnimationByAngle::~BezierAnimationByAngle() {}
//�ڷ��ִⷭ�е�֡��
int frameTotal=26;
//�ִⷭ�еĸܸ˲���
float outTurnLeverParam=0.75;//0.4
//�ⷭʱ���ֻ���ִ�еĸܸ˲���
float blendLeverParam=0.8; //0.7   0.3
float bendAngle0th = 0.8;
int innerOuterTurnBezierIndex=2;//4
int animationFrame=0;
int substractAnimFrame0th=0;
int substractAnimFrame00th=0;
int substractAnimFrame1th=0;
int substractAnimFrame2th=0;
bool isAnimStop0th=false;
bool isAnimStop1th=false;
//true���ڷ� false���ⷭ
bool isInnerTurn=false;
float BezierAnimationByAngle::vertBaseLineVects[300];
float BezierAnimationByAngle::vertCrossBezierLineVects[300];
float BezierAnimationByAngle::middleLineVectNor[3];
/////////////////////////////////
bool isStop=false;
float PI_ANIM=(3.1415926/180.0);
float frontMoveBendAngle=0.0;
bool isCacheAngle=false;
int subFrame=0;
int addFrame=0;
bool isAddFrame=false;
bool isAddEnd=false;
int umbrellaCount=0;
bool isInitEnd=true;
void BezierAnimationByAngle::bezierAnimation2(int wgIndex) {

    if(wgIndex == 0){
        subFrame++;
        if(isAddFrame){
            addFrame++;
        }else{
            addFrame=0;
        }
        //����λ��
        if(FlyElephantExercise::moveLeng>0.0){
            frontMoveBendAngle+=0.4;
            if(frontMoveBendAngle>30.0){
                frontMoveBendAngle=30.0;
            }

        }
        else{
            frontMoveBendAngle-=0.4;
            if(frontMoveBendAngle<0.0){
                frontMoveBendAngle=0.0;
            }
        }
        if(FlyElephantExercise::moveLeng>0.001){
            //�ڷ�ʱ�ķ��ȴ�С
            frameTotal=20;
        }else{
            if(umbrellaCount<200&&isInitEnd){
                umbrellaCount++;
                frameTotal=1;
            }else{
                frameTotal=7;
                isInitEnd=false;
                umbrellaCount=0;
            }
        }

        //��ʼ�ڷ�
        if(isInnerTurn) {
            animationFrame++;
            if(animationFrame>frameTotal){
                //��ʼ�ⷭ
                isInnerTurn=false;
                animationFrame=frameTotal;
            }
        }
        if(!isAnimStop0th&&!isAnimStop1th){
            substractAnimFrame0th++;
        }
        if(isAnimStop0th&&!isAnimStop1th){
            substractAnimFrame00th++;
        }
        if(isAnimStop0th&&isAnimStop1th){
            substractAnimFrame1th++;
        }
        if(!isAnimStop0th&&isAnimStop1th){
            substractAnimFrame2th++;
        }


        WizardGeom* fishBodyGeom = wizardGeomBezierAnimationByAngle.getCurrWizardGeom(0);
        WizardGeom* fishHeaderGeom = wizardGeomBezierAnimationByAngle.getCurrWizardGeom(1);

        float middLineVectX = fishHeaderGeom->baseData[0] - fishHeaderGeom->baseData[3];
        float middLineVectY = fishHeaderGeom->baseData[1] - fishHeaderGeom->baseData[4];
        float middLineVectZ = fishHeaderGeom->baseData[2] - fishHeaderGeom->baseData[5];
        middleLineVectNor[0]=middLineVectX;middleLineVectNor[1]=middLineVectY;middleLineVectNor[2]=middLineVectZ;
        WizardGeomSupple::normalize(middleLineVectNor);
        //40=5*8��
        for(int bezierLineIndex=0;bezierLineIndex < 40;bezierLineIndex++){
            float vertBaseLineVectX = WizardGeomSupple::baseLinePercentPoints[(fishHeaderGeom->baseDataPercentNum-1)*3]
                                      - fishHeaderGeom->splitPoints[((fishHeaderGeom->baseDataPercentNum - 1)*fishHeaderGeom->degreeSplitNum + bezierLineIndex)*3];
            float vertBaseLineVectY = WizardGeomSupple::baseLinePercentPoints[(fishHeaderGeom->baseDataPercentNum-1)*3 + 1]
                                      - fishHeaderGeom->splitPoints[((fishHeaderGeom->baseDataPercentNum - 1)*fishHeaderGeom->degreeSplitNum + bezierLineIndex)*3 + 1];
            float vertBaseLineVectZ = WizardGeomSupple::baseLinePercentPoints[(fishHeaderGeom->baseDataPercentNum-1)*3 + 2]
                                      - fishHeaderGeom->splitPoints[((fishHeaderGeom->baseDataPercentNum - 1)*fishHeaderGeom->degreeSplitNum + bezierLineIndex)*3 + 2];

            vertBaseLineVects[bezierLineIndex*3]=vertBaseLineVectX;vertBaseLineVects[bezierLineIndex*3+1]=vertBaseLineVectY;vertBaseLineVects[bezierLineIndex*3+2]=vertBaseLineVectZ;

            float vertCrossBezierLineVector[3];
            WizardGeomSupple::getVerticalVect(middLineVectX,middLineVectY,middLineVectZ,vertBaseLineVectX,vertBaseLineVectY,vertBaseLineVectZ,vertCrossBezierLineVector);
            WizardGeomSupple::normalize(vertCrossBezierLineVector);
            vertCrossBezierLineVects[bezierLineIndex*3]=vertCrossBezierLineVector[0];vertCrossBezierLineVects[bezierLineIndex*3+1]=vertCrossBezierLineVector[1];
            vertCrossBezierLineVects[bezierLineIndex*3+2]=vertCrossBezierLineVector[2];

            for(int bezierIndex = 2;bezierIndex < fishBodyGeom->bezierStep;bezierIndex++) {
                if(bezierIndex==2){
                    BezierAnimationByAngle::bezierAnimFirst(fishBodyGeom,bezierLineIndex,bezierIndex,vertCrossBezierLineVector,
                            vertBaseLineVectX,vertBaseLineVectY,vertBaseLineVectZ);
                }else {
                    BezierAnimationByAngle::bezierAnimOrthers(fishBodyGeom,bezierLineIndex,bezierIndex,vertCrossBezierLineVector);
                }

            }

        }

        if(FlyElephantExercise::moveLeng==0.0){
            //Ϊ������һ�ֻ���Ƕ���׼��
            isCacheAngle=false;
        }else{
            //��������ɲ���������
            isCacheAngle= true;
        }
    }

}

float BezierAnimationByAngle::setPrev2currLengthValueByBezierIndex(int bezierLineIndex,int bezierIndex,float prev2currLengthS){
    float resultLength = 0.0;
    if(bezierLineIndex == 2 || bezierLineIndex == 7 || bezierLineIndex == 12 || bezierLineIndex == 17 || bezierLineIndex == 22
       || bezierLineIndex == 27 || bezierLineIndex == 32 || bezierLineIndex == 37){
        resultLength = prev2currLengthS*1.7;//����ĳ���
    }
    else if(bezierLineIndex == 1||bezierLineIndex == 3||bezierLineIndex == 6||bezierLineIndex == 8||bezierLineIndex == 11||bezierLineIndex == 13
       ||bezierLineIndex == 16||bezierLineIndex == 18||bezierLineIndex == 21||bezierLineIndex == 32||bezierLineIndex == 26||bezierLineIndex == 28
       ||bezierLineIndex == 31||bezierLineIndex == 33||bezierLineIndex == 36||bezierLineIndex == 38){
        resultLength = prev2currLengthS;//��������ĳ���
    }
    else{
        resultLength = prev2currLengthS*0.7;//�������������ĳ���
    }
    return resultLength;
}



float angleCacheList[30];
void BezierAnimationByAngle::bezierAnimOrthers(WizardGeom* fishBodyGeom,int bezierLineIndex,int bezierIndex,float* vertCrossBezierLineVector){

    float prev2currLengthS = 0.0176470932;
    float prev2thBezierX = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 2)) * 3];
    float prev2thBezierY = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 2)) * 3 + 1];
    float prev2thBezierZ = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 2)) * 3 + 2];

    float prevBezierX = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 1)) * 3];
    float prevBezierY = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 1)) * 3 + 1];
    float prevBezierZ = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 1)) * 3 + 2];
    float prev2th2prevBezierVectX = prev2thBezierX - prevBezierX;
    float prev2th2prevBezierVectY = prev2thBezierY - prevBezierY;
    float prev2th2prevBezierVectZ = prev2thBezierZ - prevBezierZ;
    //�ϸ�������ϸ���֮�������
    float prev2th2prevBezierVectNor[]={prev2th2prevBezierVectX,prev2th2prevBezierVectY,prev2th2prevBezierVectZ};
    WizardGeomSupple::normalize(prev2th2prevBezierVectNor);
    //�ϸ�������ϸ���֮��ļ��
    float prev2currLength = BezierAnimationByAngle::setPrev2currLengthValueByBezierIndex(bezierLineIndex,bezierIndex,prev2currLengthS);
    //�ڷ����ⷭ��þ��еĽǶ�
    float trueBendAngle1th = BezierAnimationByAngle::setBendAngle1thValueByBezierIndex(bezierLineIndex,bezierIndex);

    float moveLeng = prev2currLength*tanf((3.1415926/180.0)*trueBendAngle1th);
    //��һ�������ϸ�������ϸ���֮�������������ĵ�
    float alonePrev2th2prevX = prevBezierX - prev2currLength*prev2th2prevBezierVectNor[0];
    float alonePrev2th2prevY = prevBezierY - prev2currLength*prev2th2prevBezierVectNor[1];
    float alonePrev2th2prevZ = prevBezierZ - prev2currLength*prev2th2prevBezierVectNor[2];
    //λ�Ƶķ�������
    float moveVerticalVectNor[3];
    //�ϸ�������ϸ���֮��������ͺᴩ��ֱ�ڱ������߶������Ĵ�ֱ����
    WizardGeomSupple::getVerticalVect(prev2th2prevBezierVectNor[0], prev2th2prevBezierVectNor[1],prev2th2prevBezierVectNor[2],
                                      vertCrossBezierLineVector[0],vertCrossBezierLineVector[1],vertCrossBezierLineVector[2], moveVerticalVectNor);
    WizardGeomSupple::normalize(moveVerticalVectNor);

    float prevPoint[3]={prevBezierX,prevBezierY,prevBezierZ};
    //��������λ�ƺ�Ŀ���洢�ļ���
    float movedPoint[3];

    {
        float movedX = alonePrev2th2prevX - moveLeng*moveVerticalVectNor[0];
        float movedY = alonePrev2th2prevY - moveLeng*moveVerticalVectNor[1];
        float movedZ = alonePrev2th2prevZ - moveLeng*moveVerticalVectNor[2];
        //��һ����Ͱ�λ�Ʒ�������λ�ƺ���µ�֮�������
        float prev2movedVectNor[]={prevPoint[0]-movedX,prevPoint[1]-movedY,prevPoint[2]-movedZ};
        WizardGeomSupple::normalize(prev2movedVectNor);
        movedPoint[0] = prevPoint[0] - prev2currLength*prev2movedVectNor[0];
        movedPoint[1] = prevPoint[1] - prev2currLength*prev2movedVectNor[1];
        movedPoint[2] = prevPoint[2] - prev2currLength*prev2movedVectNor[2];

    }

    fishBodyGeom->bezPointGather[(bezierLineIndex*fishBodyGeom->bezierStep + bezierIndex) * 3] = movedPoint[0];
    fishBodyGeom->bezPointGather[(bezierLineIndex*fishBodyGeom->bezierStep + bezierIndex) * 3 + 1] = movedPoint[1];
    fishBodyGeom->bezPointGather[(bezierLineIndex*fishBodyGeom->bezierStep + bezierIndex) * 3 + 2] = movedPoint[2];

}

void BezierAnimationByAngle::bezierAnimFirst(WizardGeom* fishBodyGeom,int bezierLineIndex,int bezierIndex,float* vertCrossBezierLineVector,
        float vertBaseLineVectX,float vertBaseLineVectY,float vertBaseLineVectZ) {

    float prev2currLength = 0.017647055;
    float prevBezierX = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 1)) * 3];
    float prevBezierY = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 1)) * 3 + 1];
    float prevBezierZ = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + (bezierIndex - 1)) * 3 + 2];

    float currBezierX = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + bezierIndex) * 3];
    float currBezierY = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + bezierIndex) * 3 + 1];
    float currBezierZ = fishBodyGeom->bezPointGather[(bezierLineIndex * fishBodyGeom->bezierStep + bezierIndex) * 3 + 2];

    float prev2currBezierVectX = prevBezierX - currBezierX;
    float prev2currBezierVectY = prevBezierY - currBezierY;
    float prev2currBezierVectZ = prevBezierZ - currBezierZ;
    float prev2currBezierVectNor[]={prev2currBezierVectX,prev2currBezierVectY,prev2currBezierVectZ};
    WizardGeomSupple::normalize(prev2currBezierVectNor);

    //isEndΪfalse
    if(animationFrame==frameTotal){//�ⷭʱ����ת�۳�
        bendAngle0th=0.9;//0.5 0.9
    }else{
        //�ڷ�ʱ����ת�۳�
        bendAngle0th=1.4;//1.5
    }
    //isEndΪfalse
//    if(animationFrame==frameTotal){//�ⷭʱ����ת�۳�
//        bendAngle0th=0.7;//0.5 0.9
//    }else{
//        //�ڷ�ʱ����ת�۳�
//        bendAngle0th=1.1;//1.5
//    }
    float moveLeng = prev2currLength*tanf((3.1415926/180.0)*bendAngle0th);

    float moveVerticalVectNor[3];
    WizardGeomSupple::getVerticalVect(prev2currBezierVectX, prev2currBezierVectY,prev2currBezierVectZ,
                                      vertCrossBezierLineVector[0],vertCrossBezierLineVector[1],vertCrossBezierLineVector[2], moveVerticalVectNor);
    WizardGeomSupple::normalize(moveVerticalVectNor);
    if(animationFrame==frameTotal){
        //�ⷭ�ķ��������ʹ�ֱ���м��ߵ������ĵ��(����ֵ������)
        float dotPruduct=moveVerticalVectNor[0]*vertBaseLineVectX+moveVerticalVectNor[1]*vertBaseLineVectY+moveVerticalVectNor[2]*vertBaseLineVectZ;
        if(dotPruduct>0.0){
            return;//�ж���������Խ��ƽ�д�ֱ��
        }
    }
    //�������㴥������Ҫ���������
//    if(meetReturnCondition(bezierIndex,bezierLineIndex)){
//        return;
//    }

    int currIndex=(bezierLineIndex*fishBodyGeom->bezierStep+bezierIndex)*3;
    if(animationFrame==frameTotal){  //�ⷭ
        float movedX = currBezierX + moveLeng*moveVerticalVectNor[0];
        float movedY = currBezierY + moveLeng*moveVerticalVectNor[1];
        float movedZ = currBezierZ + moveLeng*moveVerticalVectNor[2];

        fishBodyGeom->bezPointGather[currIndex] = movedX;
        fishBodyGeom->bezPointGather[currIndex+1] = movedY;
        fishBodyGeom->bezPointGather[currIndex+2] = movedZ;

    }else if(animationFrame<frameTotal){  //�ڷ�

        //BezierAnimationByAngle::meetStopCondition(bezierIndex,bezierLineIndex);

        float movedX = currBezierX - moveLeng*moveVerticalVectNor[0];
        float movedY = currBezierY - moveLeng*moveVerticalVectNor[1];
        float movedZ = currBezierZ - moveLeng*moveVerticalVectNor[2];

        fishBodyGeom->bezPointGather[currIndex] = movedX;
        fishBodyGeom->bezPointGather[currIndex+1] = movedY;
        fishBodyGeom->bezPointGather[currIndex+2] = movedZ;

    }

}

float BezierAnimationByAngle::setBendAngle1thValueByBezierIndex(int bezierLineIndex,int bezierIndex){

    float resultAngle=0.0;
    if(isInnerTurn){//��ʼ�ڷ�
        if(bezierIndex==innerOuterTurnBezierIndex+2||bezierIndex==innerOuterTurnBezierIndex+3
           ||bezierIndex==innerOuterTurnBezierIndex+4||bezierIndex==innerOuterTurnBezierIndex+5
           ||bezierIndex==innerOuterTurnBezierIndex+6||bezierIndex==innerOuterTurnBezierIndex+7
           ||bezierIndex==innerOuterTurnBezierIndex+8){
            resultAngle=animationFrame*outTurnLeverParam;
        }
        return resultAngle;
    }else{//�����ⷭ
        resultAngle=BezierAnimationByAngle::getBezierMoveAngle(bezierLineIndex,bezierIndex);
        return resultAngle;
    }

}

//�ⷭʱ���õĽǶ�
float BezierAnimationByAngle::getBezierMoveAngle(int bezierLineIndex,int bezierIndex){

    float resultAngle=0.0;
    if (!isAnimStop0th&&!isAnimStop1th) {
        if (bezierIndex==innerOuterTurnBezierIndex+2
            ||bezierIndex==innerOuterTurnBezierIndex+3
            ||bezierIndex == innerOuterTurnBezierIndex+4) {
            //�������ⷭ
            resultAngle = (animationFrame)*outTurnLeverParam-(substractAnimFrame0th*substractAnimFrame0th*0.001)*7.0;
            if(resultAngle<0.0){
                resultAngle=0.0;
                //����Ϊtrue��������һ���ж����
                isAnimStop0th = true;
            }
        }
        if (bezierIndex == innerOuterTurnBezierIndex+5||
            bezierIndex == innerOuterTurnBezierIndex+6
            ||bezierIndex == innerOuterTurnBezierIndex+7
            ||bezierIndex == innerOuterTurnBezierIndex+8) {
            //�ڷ���Ϊ�˱��ִ�����������
            resultAngle = (animationFrame)*(outTurnLeverParam);

        }
        /////�����///////
        else if(bezierIndex == innerOuterTurnBezierIndex+9
                  ||bezierIndex == innerOuterTurnBezierIndex+10
                  ||bezierIndex == innerOuterTurnBezierIndex+11){
            resultAngle = (animationFrame)*(outTurnLeverParam);

        }
        ////////////////
    } else if (isAnimStop0th&&!isAnimStop1th) {
        if (bezierIndex == innerOuterTurnBezierIndex+5||
            bezierIndex == innerOuterTurnBezierIndex+6
            ||bezierIndex == innerOuterTurnBezierIndex+7
            ||bezierIndex==innerOuterTurnBezierIndex+8) {
            //�������ⷭ
            resultAngle=animationFrame*(outTurnLeverParam)-(substractAnimFrame00th*blendLeverParam)*9.0;
            if(resultAngle<0.0){
                resultAngle=0.0;
                isAnimStop1th = true;
            }
        }
        if (bezierIndex==innerOuterTurnBezierIndex+9
            ||bezierIndex==innerOuterTurnBezierIndex+10
            ||bezierIndex==innerOuterTurnBezierIndex+11) {
            //�ڷ���Ϊ�˱��ִ�����������
            resultAngle=(animationFrame)*(outTurnLeverParam)+substractAnimFrame00th*(blendLeverParam+3.0);//0.5
        }
    }else if(isAnimStop0th&&isAnimStop1th){

        if (bezierIndex==innerOuterTurnBezierIndex+9
            ||bezierIndex==innerOuterTurnBezierIndex+10
            ||bezierIndex==innerOuterTurnBezierIndex+11) {
            //�������ⷭ
            resultAngle=(animationFrame)*(outTurnLeverParam)+substractAnimFrame00th*(blendLeverParam+3.0)-substractAnimFrame1th*(blendLeverParam+1.0)*7.0;
            if(resultAngle<0.0){
                isAnimStop0th= false;
                resultAngle=0.0;
            }
        }
        //�ڷ���Ϊ�˱��ִ�����������
        if (bezierIndex==innerOuterTurnBezierIndex+12||bezierIndex>innerOuterTurnBezierIndex+12) {
            resultAngle=substractAnimFrame1th*(blendLeverParam+8.0);//0.0
        }

    }else if(!isAnimStop0th&&isAnimStop1th){
        if (bezierIndex==innerOuterTurnBezierIndex+12||bezierIndex>innerOuterTurnBezierIndex+12) {
            resultAngle=substractAnimFrame1th*(blendLeverParam+8.0)-float(substractAnimFrame2th*substractAnimFrame2th*(blendLeverParam+2.0))*3.0;
            if(resultAngle<0.0){
                resultAngle=0.0;

                //if(animLoopTime<20)
                {
                    //�����ſ���ͣ��״̬
                    isInnerTurn=true;
                    animationFrame=0;
                    substractAnimFrame0th=0;
                    substractAnimFrame00th=0;
                    substractAnimFrame1th=0;
                    substractAnimFrame2th=0;
                    isAnimStop0th=false;
                    isAnimStop1th=false;
                }

            }

        }

    }

    return resultAngle;
}


//���ڷ�����������������������ֹͣ�����������߸�ֵ �ʹ��ھ�ֹͣ��״̬
void BezierAnimationByAngle::meetStopCondition(int bezierIndex,int bezierLineIndex){
    if((bezierLineIndex>25&&bezierLineIndex<39)&&(FlyElephantExercise::moveLeng>0.0)){
        isStop=true;
    }

}

//������������Ͳ��ٸ����������߸�ֵ���ھ�ֹͣ��״̬
bool BezierAnimationByAngle::meetReturnCondition(int bezierIndex,int bezierLineIndex){
    if((isStop&&(bezierLineIndex>25&&bezierLineIndex<39))&&(FlyElephantExercise::moveLeng>0.0)){
        return true;
    }else{
        return false;
    }

}
