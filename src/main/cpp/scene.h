#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "ggl.h"
#include "ShaderUtil.h"
#include "utils.h"
#include "WizardGeom.h"
#include "FlyElephant.h"
#include "BezierBspline.h"
#include "WizardGeomSupple.h"
#include "FlyElephantEar.h"
#include "FlyElephantEye.h"
#include "BezierBspline.h"
#include "BezierAnimationByAngle.h"
#include "FlyElephantExercise.h"
#include "GameWorld.h"
#include "ControlPanel.h"
#include "SeaGrass.h"
#include "BalloonFish.h"
#include "BalloonFlyFishCollisionDetection.h"
#include <math.h>
#include<android/log.h>

#define TAG    "mzc-jni-log" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)

void Init();
void SetViewportSize(float width, float height);
void Draw();
glm::mat4 getProjectionMatrix();
float getWidth();
float getHeight();
void drawPointLine(float* pointsDraw,int number,bool isPointOrLine,float colorR,float colorG,float colorB,float pointSize);

GLuint getSeaGrassTextureLocation();
GLuint getSeaGrassTexcoordLocation();
GLuint* getCoralTextureList();
GLuint* getSeaGrassTextureList();
GLuint* getRockList();
GLuint* getSeaSnailList();