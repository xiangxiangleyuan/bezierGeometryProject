#include "ControlPanel.h"

ControlPanel::~ControlPanel() {};
ControlPanel::ControlPanel() {};

float moveTrajectoryPoints[2000];
float coordinate3D[3000];
FlyElephant flyElephantControlPanel;
ShaderUtil shaderUtilControlPanel;
FlyElephantExercise flyElephantExerciseControlPanel;
SeaGrass seaGrassControlPanel;
//是否绘制控制板上的点
bool isDrawControlPanel=false;

//是否已给第一绘制时间初始值
bool isInitTime=false;
//是否在绘制当中
bool isMoveEvent= true;
bool isDrawEnd= false;
int movePointerDraw;
bool inverse=false;
float ControlPanel::rotateBodyAngle=1.9;
bool isSetRotateValue=false;
void ControlPanel::saveMoveCoord(float moveX, float moveY, int movePointer) {
    moveTrajectoryPoints[movePointer*2]=moveX;
    moveTrajectoryPoints[movePointer*2+1]=moveY;
    movePointerDraw=movePointer;
}

void ControlPanel::drawMoveTrajectory() {
    isSetRotateValue=true;
    isDrawControlPanel= true;
    float width=getWidth();
    float height=getHeight();
    for(int i=0;i<movePointerDraw+1;i++){
        float x2d=moveTrajectoryPoints[i*2];
        float y2d=moveTrajectoryPoints[i*2+1];
        glm::vec3 vect3=glm::vec3(x2d,y2d,0.0);
        glm::vec3 point3D=glm::unProject(vect3,flyElephantControlPanel.getViewMatrix(),getProjectionMatrix(),glm::vec4(0,0,width*10.0f,height*10.0f));

        coordinate3D[i*3]=point3D[0];
        coordinate3D[i*3+1]=-point3D[1];
        coordinate3D[i*3+2]=point3D[2]+0.01;
    }

}

//bool isInitTime2=false;
//int initTime2=0;

int initTime=0;
//绘制手势轨迹
void ControlPanel::drawGesturePath(){

    float position[]={0.5,-0.3,0.0};
    seaGrassControlPanel.drawSeaGrassMap(100,position);

    time_t timer;
    time(&timer);
    struct tm* tm_t;
    tm_t = localtime(&timer);
    //获得当前的秒数
    int currSecond=tm_t->tm_sec;
    //一次绘制初始化一次记录秒数的初始值
    if(isDrawControlPanel&&!isInitTime){
        initTime=currSecond;
        isInitTime=true;
    }
    //如果绘制了1秒时间就恢复初始值
    if(abs(currSecond-initTime)>10.5&&isDrawControlPanel){
        isDrawControlPanel=false;
        initTime=0;
        isInitTime=false;
        clearControlPanelCollect();
    }
    //////////////////////////////////////////////
    /////////////////////////////////////////////
//    if(!isCanStart){
//        time_t timer;
//        time(&timer);
//        struct tm* tm_t;
//        tm_t = localtime(&timer);
//        //获得当前的秒数
//        int currSecond=tm_t->tm_sec;
//        //一次绘制初始化一次记录秒数的初始值
//        if(!isInitTime2){
//            initTime2=currSecond;
//            isInitTime2=true;
//        }
//        //如果绘制了1秒时间就恢复初始值
//        if(abs(currSecond-initTime2)>15){
//            isCanStart=true;
//        }
//
//    }


    if(isDrawControlPanel){
        drawControlPanelPoints();
    }
    //手势正在位移或者绘制超过了秒数就返回不再绘制
    if(!isDrawControlPanel||isMoveEvent){
        isDrawEnd=true;
        return;
    }else{
        isDrawEnd=false;
    }

    if(coordinate3D[0]==0.0||coordinate3D[1]==0.0||coordinate3D[2]==0.0){
        return;
    }
    //已经赋值了可以转身了就返回不再往下执行
    if(!isSetRotateValue)
    {
        return;
    }

    computeFlyElephantMoveDirect();

}

void ControlPanel::drawControlPanelPoints(){
    //    glEnable(GL_BLEND);                                                             //开混合模式贴图
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                             //设置混合方式
    if(coordinate3D[0]==0.0&&coordinate3D[1]==0.0&&coordinate3D[2]==0.0){
        return;
    }
    float pointSize=12.0;
    float colorR=1.0;
    float colorG=0.0;
    GLuint drawPointLineProgram=shaderUtilControlPanel.getDrawPointLineProgram();
    glUseProgram(drawPointLineProgram);
    GLuint modelMatrixLocation = glGetUniformLocation(drawPointLineProgram,"ModelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(drawPointLineProgram,"ViewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(drawPointLineProgram,"ProjectionMatrix");
    flyElephantControlPanel.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);
    GLuint pointSizeLocation = glGetUniformLocation(drawPointLineProgram,"pointSize");
    glUniform1f(pointSizeLocation,pointSize);
    GLuint colorRLocation = glGetUniformLocation(drawPointLineProgram,"colorR");
    glUniform1f(colorRLocation,colorR);
    GLuint colorGLocation = glGetUniformLocation(drawPointLineProgram,"colorG");
    glUniform1f(colorGLocation,colorG);
    GLuint positionLocation = glGetAttribLocation(drawPointLineProgram,"position");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, getCoordinate3D());
    glEnableVertexAttribArray(positionLocation);
    glDrawArrays(GL_POINTS, 0, movePointerDraw);
    glDisable(GL_BLEND);
    glUseProgram(0);
}

//bool isInitTime2=false;
//int initTime2=0;
bool ControlPanel::isCanStart=false;
void ControlPanel::computeFlyElephantMoveDirect(){

//    if(!isCanStart){
//        time_t timer;
//        time(&timer);
//        struct tm* tm_t;
//        tm_t = localtime(&timer);
//        //获得当前的秒数
//        int currSecond=tm_t->tm_sec;
//        //一次绘制初始化一次记录秒数的初始值
//        if(!isInitTime2){
//            initTime2=currSecond;
//            isInitTime2=true;
//        }
//        //如果绘制了1秒时间就恢复初始值
//        if(abs(currSecond-initTime2)>5){
//            isCanStart=true;
//        }
//
//    }


    float firstX=coordinate3D[0];
    float firstY=coordinate3D[1];
    float firstZ=coordinate3D[2];
    int lastIndex=movePointerDraw*3;
    float lastX=coordinate3D[lastIndex];
    float lastY=coordinate3D[lastIndex+1];
    float lastZ=coordinate3D[lastIndex+2];

    //手势轨迹向量   Y和Z交换了位置
    float gestureVectNor[]={lastX-firstX,lastZ-firstZ,lastY-firstY};
    WizardGeomSupple::normalize(gestureVectNor);

    flyElephantExerciseControlPanel.getFrontDirectVect();
    //前进方向的向量
    float frontDirect[]={FlyElephantExercise::frontDirectNor[0],0.0,FlyElephantExercise::frontDirectNor[2]};

    float gestureXLeng=gestureVectNor[0];
    if(gestureXLeng<0.0){
        gestureXLeng=-gestureXLeng;
    }
    float frontDirectXLeng=frontDirect[0];
    if(frontDirectXLeng<0.0){
        frontDirectXLeng=-frontDirectXLeng;
    }
    //前进方向向量在第四象限   手势轨迹在第2象限
    if((frontDirect[0]>0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]>0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= true;
        }else{
            inverse= false;
        }

    }
        //前进方向向量在第2象限   手势轨迹在第4象限
    else if((gestureVectNor[0]>0.0&&gestureVectNor[2]<0.0)&&(frontDirect[0]<0.0&&frontDirect[2]>0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= true;
        }else{
            inverse= false;
        }

    }
        //前进方向向量在第一象限   手势轨迹在第三象限
    else if((frontDirect[0]>0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]<0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= false;
        }else{
            inverse= true;
        }

    }
        //前进方向向量在第3象限   手势轨迹在第1象限
    else if((frontDirect[0]<0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]>0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= true;
        }else{
            inverse= false;
        }

    }
        //前进方向向量在第一象限   手势轨迹在第二象限
    else if((frontDirect[0]>0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]>0.0)){
        inverse= true;

    }
        //前进方向向量在第一象限   手势轨迹在第四象限
    else if((frontDirect[0]>0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]<0.0)){
        inverse= false;

    }
        //前进方向向量在第二象限   手势轨迹在第一象限
    else if((frontDirect[0]<0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]>0.0)){
        inverse= false;

    }
        //前进方向向量在第二象限   手势轨迹在第三象限
    else if((frontDirect[0]<0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]<0.0)){
        inverse= true;

    }
        //前进方向向量在第三象限   手势轨迹在第二象限
    else if((frontDirect[0]<0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]>0.0)){
        inverse= false;

    }
        //前进方向向量在第三象限   手势轨迹在第四象限
    else if((frontDirect[0]<0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]<0.0)){
        inverse= true;

    }
        //前进方向向量在第四象限   手势轨迹在第一象限
    else if((frontDirect[0]>0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]>0.0)){
        inverse= true;

    }
        //前进方向向量在第四象限   手势轨迹在第三象限
    else if((frontDirect[0]>0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]<0.0)){
        inverse= false;

    }

    //第一象限
    if((frontDirect[0]>0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]>0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= true;
        }else{
            inverse= false;
        }
        //第二象限
    }else if((frontDirect[0]<0.0&&frontDirect[2]>0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]>0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= false;
        }else{
            inverse= true;
        }
        //第三象限
    }else if((frontDirect[0]<0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]<0.0&&gestureVectNor[2]<0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= true;
        }else{
            inverse= false;
        }
        //第四象限
    }else if((frontDirect[0]>0.0&&frontDirect[2]<0.0)&&(gestureVectNor[0]>0.0&&gestureVectNor[2]<0.0)){
        if(frontDirectXLeng>gestureXLeng){
            inverse= false;
        }else{
            inverse= true;
        }
    }
    if(inverse){
        inverse=false;
    }else{
        inverse= true;
    }

//    flyElephantExerciseControlPanel.getFrontDirectVect();
    //向量夹角的余弦值
    float coseValue=(gestureVectNor[0]*frontDirect[0]+gestureVectNor[1]*frontDirect[1]+gestureVectNor[2]*frontDirect[2])/
                    (sqrtf(gestureVectNor[0]*gestureVectNor[0]+gestureVectNor[1]*gestureVectNor[1]+gestureVectNor[2]*gestureVectNor[2])*
                     sqrtf(frontDirect[0]*frontDirect[0]+frontDirect[1]*frontDirect[1]+frontDirect[2]*frontDirect[2]));
    //返回余弦值对应的弧度
    double angle=acos(double(coseValue));
    //最终旋转的角度值
    float vetorialAngle=float(angle)*180.0/3.14159265;
    //需要旋转的次数
    int rotateTimes=abs(vetorialAngle/rotateBodyAngle);

    if(isSetRotateValue){
        FlyElephantExercise::rotateCountTotal=rotateTimes;
        FlyElephantExercise::isInverseRotate=inverse;
        FlyElephantExercise::flyElephantCount=0;
        isSetRotateValue=false;
    }

}

void ControlPanel::setFrontMoveCountZero(){
    FlyElephantExercise::moveLeng=0.003;
}


float* ControlPanel::getCoordinate3D(){
    return coordinate3D;
}


int ControlPanel::getMovePointerDraw(){
    return movePointerDraw;
}

void ControlPanel::clearControlPanelCollect() {

    std::memset(moveTrajectoryPoints,0,2000*sizeof(float));
    std::memset(coordinate3D,0,3000*sizeof(float));
}

void ControlPanel::setIsMoveEvent(bool moveEventIs){
    isMoveEvent=moveEventIs;
}
//用来判断JAVA层是不是可以绘制了
bool ControlPanel::getIsDrawEnd(){
    return isDrawEnd;
}