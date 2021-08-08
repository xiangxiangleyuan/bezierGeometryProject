#pragma once

#include "scene.h"

class SeaGrass{

public:
    SeaGrass();
    ~SeaGrass();

    void drawSeaGrass();
    static void seaGrassSway();
    void drawSeaGrassMap(int tag,float* flowerPosition);



};