#include "scene.h"
#include "ggl.h"


ShaderUtil shaderUtilScene;
WizardGeom wizardGeomScene;
FlyElephant flyElephantScene;
FlyElephantEar flyElephantEarScene;
FlyElephantEye flyElephantEyeScene;
GameWorld gameWorldScene;
ControlPanel controlPanelScene;
SeaGrass seaGrassScene;
BalloonFish balloonFishScene;
BalloonFlyFishCollisionDetection balloonFlyFishCollisionDetection;
glm::mat4 projectionMatrix;
//////////珊瑚的纹理柄集合///////////////////
GLuint textureCoralReefLocation;
GLuint texcoordCoralReefLocation;
GLuint coralTextureList[10];
//////////地面的纹理柄集合////////////////
GLuint floorTexture;
//地面的纹理图片柄
GLuint textureFloorLocation;
//地面的纹理坐标柄
GLuint texcoordFloorLocation;
GLuint textureFloorLightWavesLocation;
GLuint light_wavesTexture;
GLuint longLatitudeFloorLocation;
/////////海草////////
GLuint seaGrassTextureList[30];
GLuint seaGrassTextureLocation;
GLuint seaGrassTexcoordLocation;
////////石头////////////////////
GLuint rockList[10];
///////海螺集合/////
GLuint seaSnailList[10];

float widthVP;
float heightVP;
void Init(){
    wizardGeomScene.compWizardGeom();
    //绘制飞象章鱼的shader
    shaderUtilScene.compGeomShader();
    //检测点和线的shader
    shaderUtilScene.compDrawCoralShader();
    //绘制飞象鱼耳朵的shader
    shaderUtilScene.compFlyElephantEarShader();
    shaderUtilScene.compDrawPointLineShader();
    //初始化海草的shader
    shaderUtilScene.compSeaGrassShader();
    shaderUtilScene.compSeaGrassMapShader();
    shaderUtilScene.compBalloonFishShader();
    shaderUtilScene.compBalloonFishSTABShader();
    flyElephantScene.initFlyElephantLocation();
    ///////////刺豚////////////////////
    balloonFishScene.initBalloonFish();
    ///////////地板纹理贴图////////////
    gameWorldScene.initGameWorld();
    GLuint textureFloorProgramScene=shaderUtilScene.compTextureShader();
    textureFloorLocation = glGetUniformLocation(textureFloorProgramScene, "U_Texture");
    textureFloorLightWavesLocation = glGetUniformLocation(textureFloorProgramScene, "lightWave_Texture");
    texcoordFloorLocation = glGetAttribLocation(textureFloorProgramScene, "texcoord");
    longLatitudeFloorLocation=glGetAttribLocation(textureFloorProgramScene, "longLatitude");
    floorTexture = CreateTexture2DFromBMP("Res/floorTexture0.bmp");
    light_wavesTexture = CreateTexture2DFromBMP("Res/light_waves.bmp");
    ////////////珊瑚贴图////////////
    gameWorldScene.initCoralReef();
    GLuint coralTexture = CreateTexture2DFromBMP("Res/coralTexture0.bmp");
    GLuint coralTexture1th = CreateTexture2DFromBMP("Res/coralTexture1.bmp");
    GLuint coralTexture2th = CreateTexture2DFromBMP("Res/coralTexture2.bmp");
    GLuint coralTexture3th = CreateTexture2DFromBMP("Res/coralTexture7.bmp");
    GLuint coralTexture4th = CreateTexture2DFromBMP("Res/coralTexture8.bmp");
    GLuint coralTexture5th = CreateTexture2DFromBMP("Res/coralTexture6.bmp");
    GLuint coralTexture6th = CreateTexture2DFromBMP("Res/balloonFishBodyTexture.bmp");
    GLuint balloonFishTailTexture = CreateTexture2DFromBMP("Res/balloonFishTailTexture.bmp");

    GLuint drawCoralProgram=shaderUtilScene.getDrawCoralProgram();
    textureCoralReefLocation = glGetUniformLocation(drawCoralProgram, "U_Texture");
    texcoordCoralReefLocation = glGetAttribLocation(drawCoralProgram, "texcoord");
    coralTextureList[0]=coralTexture;coralTextureList[1]=coralTexture1th;coralTextureList[2]=coralTexture2th;
    coralTextureList[3]=coralTexture3th;coralTextureList[4]=coralTexture4th;coralTextureList[5]=coralTexture5th;
    coralTextureList[6]=coralTexture6th;coralTextureList[7]=balloonFishTailTexture;
    //////////海草贴图//////////////
    GLuint seaGrass0Texture = CreateTexture2DFromBMP("Res/seaGrass0.bmp");
    GLuint seaGrass1Texture = CreateTexture2DFromBMP("Res/seaGrass1.bmp");
    GLuint seaGrass2Texture = CreateTexture2DFromBMP("Res/seaGrass2.bmp");
    GLuint seaGrass7Texture = CreateTexture2DFromBMP("Res/seaGrass7.bmp");
    GLuint seaGrass9Texture = CreateTexture2DFromBMP("Res/seaGrass9.bmp");
    GLuint seaGrass10Texture = CreateTexture2DFromBMP("Res/seaGrass10.bmp");
    GLuint seaGrass11Texture = CreateTexture2DFromBMP("Res/seaGrass11.bmp");
    GLuint seaGrass12Texture = CreateTexture2DFromBMP("Res/seaGrass12.bmp");
    GLuint seaGrass13Texture = CreateTexture2DFromBMP("Res/seaGrass13.bmp");
    GLuint seaGrass14Texture = CreateTexture2DFromBMP("Res/seaGrass14.bmp");
    GLuint seaGrass15Texture = CreateTexture2DFromBMP("Res/seaGrass15.bmp");
    GLuint seaGrass17Texture = CreateTexture2DFromBMP("Res/seaGrass17.bmp");
    GLuint seaGrass20Texture = CreateTexture2DFromBMP("Res/seaGrass20.bmp");
    GLuint gameStartTexture = CreateTexture2DFromBMP("Res/gameStart.bmp");

    seaGrassTextureList[0]=seaGrass0Texture;
    seaGrassTextureList[1]=seaGrass1Texture;
    seaGrassTextureList[2]=seaGrass2Texture;
    seaGrassTextureList[7]=seaGrass7Texture;
    seaGrassTextureList[9]=seaGrass9Texture;
    seaGrassTextureList[10]=seaGrass10Texture;
    seaGrassTextureList[11]=seaGrass11Texture;
    seaGrassTextureList[12]=seaGrass12Texture;
    seaGrassTextureList[13]=seaGrass13Texture;
    seaGrassTextureList[14]=seaGrass14Texture;
    seaGrassTextureList[15]=seaGrass15Texture;
    seaGrassTextureList[17]=seaGrass17Texture;
    seaGrassTextureList[20]=seaGrass20Texture;
    seaGrassTextureList[21]=gameStartTexture;


    GLuint seaGrassProgram=shaderUtilScene.getSeaGrassProgram();
    seaGrassTextureLocation = glGetUniformLocation(seaGrassProgram, "U_Texture");
    seaGrassTexcoordLocation = glGetAttribLocation(seaGrassProgram, "texcoord");
    ///////////////石头图///////////////////////
    GLuint rock3Texture = CreateTexture2DFromBMP("Res/rock3.bmp");
    rockList[2]=rock3Texture;
    /////////////海螺图/////////
    GLuint seaSnail2Texture = CreateTexture2DFromBMP("Res/seaSnail2.bmp");
    GLuint seaSnail3Texture = CreateTexture2DFromBMP("Res/seaSnail3.bmp");
    GLuint seaSnail5Texture = CreateTexture2DFromBMP("Res/seaSnail5.bmp");
    GLuint seaSnail6Texture = CreateTexture2DFromBMP("Res/seaSnail6.bmp");
    GLuint seaSnail7Texture = CreateTexture2DFromBMP("Res/seaSnail7.bmp");
    GLuint seaSnail8Texture = CreateTexture2DFromBMP("Res/seaSnail8.bmp");
    GLuint seaSnail9Texture = CreateTexture2DFromBMP("Res/seaSnail9.bmp");

    seaSnailList[2]=seaSnail2Texture;
    seaSnailList[3]=seaSnail3Texture;
    seaSnailList[5]=seaSnail5Texture;
    seaSnailList[6]=seaSnail6Texture;
    seaSnailList[7]=seaSnail7Texture;
    seaSnailList[8]=seaSnail8Texture;
    seaSnailList[9]=seaSnail9Texture;


}

void SetViewportSize(float width, float height){
    widthVP=width;
    heightVP=height;
    projectionMatrix = glm::perspective(60.0f, (width) / (height), 0.1f, 100.0f);

}

void Draw(){

    glClearColor(0.1f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //画手势轨迹
    controlPanelScene.drawGesturePath();
    //画飞象章鱼
    flyElephantScene.drawFlyElephant();
    flyElephantEarScene.MakeFishEar(0);//耳朵
    flyElephantEarScene.MakeFishEar(1);//耳朵
    flyElephantEyeScene.drawFlyElephantEye(10,12,14); //嘴
    flyElephantEyeScene.drawFlyElephantEye(15,17,19);//眼睛  19列
    flyElephantEyeScene.drawFlyElephantEye(5,7,9);  //眼睛   0列
    //////////////////////////////////////////////////
    //画珊瑚
    gameWorldScene.drawCoral(textureCoralReefLocation,texcoordCoralReefLocation);
    //画地板
    gameWorldScene.textureMapping(floorTexture,textureFloorLocation,light_wavesTexture,textureFloorLightWavesLocation,texcoordFloorLocation,longLatitudeFloorLocation);
    //画海草
    seaGrassScene.drawSeaGrass();
    //画刺豚
    balloonFishScene.drawBalloonFish();
    //飞象和刺豚的碰撞检测
    balloonFlyFishCollisionDetection.checkCollisionDetection();


}

void drawPointLine(float* pointsDraw,int number,bool isPointOrLine,float colorR,float colorG,float colorB,float pointSize){

    GLuint drawPointLineProgram = shaderUtilScene.getDrawPointLineProgram();
    glUseProgram(drawPointLineProgram);
    glEnable(GL_DEPTH_TEST);



    GLuint modelMatrixLocation = glGetUniformLocation(drawPointLineProgram,"ModelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(drawPointLineProgram,"ViewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(drawPointLineProgram,"ProjectionMatrix");
    flyElephantScene.SetMatrixByLocation(modelMatrixLocation,viewMatrixLocation,projectionMatrixLocation);

    GLint colorRLocation=glGetUniformLocation(drawPointLineProgram,"colorR");
    GLint colorGLocation=glGetUniformLocation(drawPointLineProgram,"colorG");
    GLint colorBLocation=glGetUniformLocation(drawPointLineProgram,"colorB");
    glUniform1f(colorRLocation,colorR);
    glUniform1f(colorGLocation,colorG);
    glUniform1f(colorBLocation,colorB);
    GLint pointSizeLocation=glGetUniformLocation(drawPointLineProgram,"pointSize");
    glUniform1f(pointSizeLocation,pointSize);

    GLuint positionLocation = glGetAttribLocation(drawPointLineProgram,"position");
    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, pointsDraw);
    glEnableVertexAttribArray(positionLocation);
    if(isPointOrLine){
        glDrawArrays(GL_POINTS, 0, number);
    }else{
        glDrawArrays(GL_LINES, 0, number);
    }

    glUseProgram(0);


}


glm::mat4 getProjectionMatrix(){
    return projectionMatrix;
}

float getWidth(){
    return  widthVP;
}
float getHeight(){
    return heightVP;
}

GLuint getSeaGrassTextureLocation(){
    return seaGrassTextureLocation;
}

GLuint getSeaGrassTexcoordLocation(){
    return seaGrassTexcoordLocation;
}

GLuint* getCoralTextureList(){
    return coralTextureList;
}

GLuint* getSeaGrassTextureList(){
    return seaGrassTextureList;
}

GLuint* getRockList(){
    return rockList;
}

GLuint* getSeaSnailList(){
    return seaSnailList;
}