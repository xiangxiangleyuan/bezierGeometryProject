#include "scene.h"

static AAssetManager* sAssetManager = NULL;
ControlPanel controlPanelNative;
SeaGrass seaGrassNative;

unsigned char * LoadFileContent(const char*path,int & filesize){
    unsigned char*fileContent=nullptr;
    filesize=0;
    AAsset*asset=AAssetManager_open(sAssetManager,path,AASSET_MODE_UNKNOWN);
    if(asset==nullptr){
        return nullptr;
    }
    filesize=AAsset_getLength(asset);
    fileContent=new unsigned char[filesize+1];
    AAsset_read(asset,fileContent,filesize);
    fileContent[filesize]='\0';
    AAsset_close(asset);
    return fileContent;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_InitAssetManager(
        JNIEnv *env,
        jobject /* this */,
        jobject am) {

    sAssetManager = AAssetManager_fromJava(env,am);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_InitOpenGL(
        JNIEnv *env,
        jobject /* this */) {
    Init();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_OnViewportChanged(
        JNIEnv *env,
        jobject /* this */,
        float width, float height) {
    SetViewportSize(width,height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_Render(
        JNIEnv *env,
        jobject /* this */) {

    Draw();
}

/////////////绘制手势轨迹//////////////////////////////////
////////////////////////////////////////////////////////////////////////////
extern "C" JNIEXPORT void JNICALL
        Java_com_example_myapplication_MainActivity_incomingMoveCoords
        (JNIEnv *env,
         jobject,
         float moveX,float moveY,int movePointer){
    controlPanelNative.saveMoveCoord(moveX,moveY,movePointer);

}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_controlPanelDraw(JNIEnv *env,
                                                             jobject){
    controlPanelNative.drawMoveTrajectory();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_clearControlPanelCollect(JNIEnv *env,
                                                             jobject){
    controlPanelNative.clearControlPanelCollect();
}

extern "C" JNIEXPORT void JNICALL
        Java_com_example_myapplication_MainActivity_setIsMoveEvent(JNIEnv *env,
                                                                   jobject,
                                                                   bool isMoveEvent){
    controlPanelNative.setIsMoveEvent(isMoveEvent);
}


extern "C" JNIEXPORT bool JNICALL
Java_com_example_myapplication_MainActivity_getIsDrawEnd(JNIEnv *env,
                                                           jobject,
                                                           bool isMoveEvent){
    return controlPanelNative.getIsDrawEnd();
}
//////////////////////飞象位移/////////////////////////////////////
extern "C" JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_setFrontMoveCountZero(JNIEnv *env,
                                                         jobject){
    controlPanelNative.setFrontMoveCountZero();
}

