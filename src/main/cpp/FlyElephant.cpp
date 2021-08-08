#include "FlyElephant.h"

FlyElephant::FlyElephant() {};
FlyElephant::~FlyElephant() {};

ShaderUtil shaderUtilFlyElephant;
WizardGeom wizardGeomFlyElephant;
BezierBspline bezierBsplineFlyElephant;
float FlyElephant::lightPosition[3];
float FlyElephant::cameraPosition[3];
glm::mat4 modelMatrix, viewMatrix,projectMatrix;
//-0.2, 0.45, 0.8,
void FlyElephant::initFlyElephantLocation() {
    lightPosition[0]=-0.2;lightPosition[1]=0.45;lightPosition[2]=0.6;
//    cameraPosition[0]=0.0;cameraPosition[1]=1.0;cameraPosition[2]=2.0;
 //   cameraPosition[0]=0.0;cameraPosition[1]=0.3;cameraPosition[2]=-0.5;
    cameraPosition[0]=0.0;cameraPosition[1]=0.0;cameraPosition[2]=-0.5;

    for(int i=0;i<2;i++){
        WizardGeom* wizardGeomPoint = wizardGeomFlyElephant.getCurrWizardGeom(i);
        GLuint flyElephantProgram = shaderUtilFlyElephant.getGeomProgram();
        wizardGeomPoint->projectionMatrixLocation = glGetUniformLocation(flyElephantProgram,"ProjectionMatrix");
        wizardGeomPoint->viewMatrixLocation = glGetUniformLocation(flyElephantProgram,"ViewMatrix");
        wizardGeomPoint->modelMatrixLocation = glGetUniformLocation(flyElephantProgram,"ModelMatrix");
        wizardGeomPoint->blinePoints1Location = glGetAttribLocation(flyElephantProgram, "blinePoints1");
        wizardGeomPoint->blinePoints2Location = glGetAttribLocation(flyElephantProgram, "blinePoints2");
        wizardGeomPoint->blinePoints3Location = glGetAttribLocation(flyElephantProgram, "blinePoints3");
        wizardGeomPoint->blinePoints4Location = glGetAttribLocation(flyElephantProgram, "blinePoints4");
        wizardGeomPoint->blindex1Location = glGetAttribLocation(flyElephantProgram, "blindex1");
        wizardGeomPoint->blindex2Location = glGetAttribLocation(flyElephantProgram, "blindex2");
        wizardGeomPoint->blinePercentLocation = glGetAttribLocation(flyElephantProgram, "blinePercent");
        wizardGeomPoint->lightPositionLocation = glGetUniformLocation(flyElephantProgram, "lightPosition");
        wizardGeomPoint->modelInverseTransposeMatrixLocation=glGetUniformLocation(flyElephantProgram,"normalMatrix");
        wizardGeomPoint->cameraPositionLocation=glGetUniformLocation(flyElephantProgram,"cameraPosition");
        wizardGeomPoint->wizardGeomIndexLocation=glGetUniformLocation(flyElephantProgram,"wizardGeomIndex");
    }

}

int colorTag=0;
void FlyElephant::drawFlyElephant(){
    if(BalloonFish::isPrick) {
        colorTag++;
    }
    GLuint flyElephantProgram = shaderUtilFlyElephant.getGeomProgram();
    glUseProgram(flyElephantProgram);

    for(int i=0;i<2;i++)
    {
        bezierBsplineFlyElephant.boneAnimation(i);
        WizardGeom* wizardGeomPoint = wizardGeomFlyElephant.getCurrWizardGeom(i);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE_BUFFER_BIT7_QCOM);
        //传递碰撞后的飞象章鱼的颜色
        GLuint flyElephantProgram=shaderUtilFlyElephant.getGeomProgram();
        GLuint colorArrayLocation=glGetUniformLocation(flyElephantProgram,"colorArray");
//        glUniform3f(colorArrayLocation,0.8745,0.62353,0.07843);
        if(BalloonFish::isPrick){
            if(colorTag%2==0){
                glUniform3f(colorArrayLocation,1.0,0.62353,0.01);
            }else{
                glUniform3f(colorArrayLocation,1.0,0.4,0.0);
            }
        }else{
            glUniform3f(colorArrayLocation,1.0,0.62353,0.01);
            colorTag=0;
        }


        glUniform3f(wizardGeomPoint->lightPositionLocation,lightPosition[0],lightPosition[1],lightPosition[2]);
        glUniform3f(wizardGeomPoint->cameraPositionLocation,cameraPosition[0],cameraPosition[1],cameraPosition[2]);
        glUniform1i(wizardGeomPoint->wizardGeomIndexLocation,i);
        FlyElephant::SetMatrixByLocation(wizardGeomPoint->modelMatrixLocation,wizardGeomPoint->viewMatrixLocation,wizardGeomPoint->projectionMatrixLocation);
        //转置逆矩阵
        glVertexAttribPointer(wizardGeomPoint->blinePoints1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->trueBezierShaderPoints1);
        glEnableVertexAttribArray(wizardGeomPoint->blinePoints1Location);
        glVertexAttribPointer(wizardGeomPoint->blinePoints2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->trueBezierShaderPoints2);
        glEnableVertexAttribArray(wizardGeomPoint->blinePoints2Location);
        glVertexAttribPointer(wizardGeomPoint->blinePoints3Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->trueBezierShaderPoints3);
        glEnableVertexAttribArray(wizardGeomPoint->blinePoints3Location);
        glVertexAttribPointer(wizardGeomPoint->blinePoints4Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->trueBezierShaderPoints4);
        glEnableVertexAttribArray(wizardGeomPoint->blinePoints4Location);
        glVertexAttribPointer(wizardGeomPoint->blindex1Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->trueBlineFactors1);
        glEnableVertexAttribArray(wizardGeomPoint->blindex1Location);
        glVertexAttribPointer(wizardGeomPoint->blindex2Location, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->trueBlineFactors2);
        glEnableVertexAttribArray(wizardGeomPoint->blindex2Location);
        glVertexAttribPointer(wizardGeomPoint->blinePercentLocation, 3, GL_FLOAT, GL_FALSE, 3 * 4, wizardGeomPoint->bsplinePercent);
        glEnableVertexAttribArray(wizardGeomPoint->blinePercentLocation);
//        int num=wizardGeomPoint->blineSplitNum*wizardGeomPoint->degreeSplitNum*(wizardGeomPoint->bezierStep - 1) * 6;

        if(i==0){
            glDrawArrays(GL_TRIANGLES, 0, 19200);
        }else{
            glDrawArrays(GL_TRIANGLES, 0, 12000);
        }
        //glDrawArrays(GL_POINTS, 0, wizardGeomPoint->blineSplitNum*wizardGeomPoint->degreeSplitNum*(wizardGeomPoint->bezierStep - 1) * 6);
        //LOGD("==*==*** %i",num);
    }

    glUseProgram(0);

}

void FlyElephant::SetMatrixByLocation(GLuint modelMatrixLocation,GLuint viewMatrixLocation,GLuint projectionMatrixLocation){

    viewMatrix=glm::lookAt(glm::vec3(cameraPosition[0],cameraPosition[1],cameraPosition[2]),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    //位置、旋转变换矩阵引用
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    //摄像机位置朝向9参数矩阵
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    //4x4矩阵 投影用
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4(getProjectionMatrix())));


}

glm::mat4 FlyElephant::getViewMatrix(){
    return viewMatrix;
}