#pragma once

#include "scene.h"

class ControlPanel{

public:
    ControlPanel();
    ~ControlPanel();

    static float rotateBodyAngle;
    static bool isCanStart;

    void saveMoveCoord(float moveX,float moveY,int movePointer);
    void drawMoveTrajectory();
    float* getCoordinate3D();
    int getMovePointerDraw();
    void clearControlPanelCollect();
    void setIsMoveEvent(bool isMoveEvent);
    void drawGesturePath();
    bool getIsDrawEnd();
    void computeFlyElephantMoveDirect();
    void setFrontMoveCountZero();
    void drawControlPanelPoints();

    };