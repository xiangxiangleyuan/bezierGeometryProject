#include "ShaderUtil.h"

WizardGeom wizardGeomSU;
GLuint geomProgram;
GLuint drawCoralProgram;
GLuint flyElephantEarProgram;
GLuint textureProgram;
GLuint drawPointLineProgram;
GLuint seaGrassProgram;
GLuint seaGrassMapProgram;
GLuint balloonFishProgram;
GLuint balloonFishSTABProgram;

ShaderUtil::ShaderUtil()
{
}

ShaderUtil::~ShaderUtil()
{

}



void ShaderUtil::compGeomShader()
{
	int fileSize = 0;
    unsigned char * shaderCode = LoadFileContent("Res/test.vs", fileSize);
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)shaderCode);
    delete shaderCode;
    shaderCode = LoadFileContent("Res/test.fs", fileSize);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)shaderCode);
    delete shaderCode;
    geomProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

}

void ShaderUtil::compDrawCoralShader()
{

    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)DRAWCORAL_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)DRAWCORAL_FRAGMENT_SHADER);
    drawCoralProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
}

void ShaderUtil::compDrawPointLineShader() {
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)DRAWPOINTLINE_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)DRAWPOINTLINE_FRAGMENT_SHADER);
    drawPointLineProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

}


void ShaderUtil::compFlyElephantEarShader(){
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)FLYELEPHANTEAR_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)FLYELEPHANTEAR_FRAGMENT_SHADER);
    flyElephantEarProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
}

GLuint ShaderUtil::compTextureShader(){
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)TEXTURE_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)TEXTURE_FRAGMENT_SHADER);
    textureProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    return textureProgram;
}

GLuint ShaderUtil::compSeaGrassShader(){
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)SEAGRASS_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)SEAGRASS_FRAGMENT_SHADER);
    seaGrassProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    return seaGrassProgram;

}

GLuint ShaderUtil::compSeaGrassMapShader() {
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)SEAGRASS_VERTEX_SHADER_MAP);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)SEAGRASS_FRAGMENT_SHADER_MAP);
    seaGrassMapProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    return seaGrassMapProgram;
}

GLuint ShaderUtil::compBalloonFishShader(){

    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)BALLOONFISH_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)BALLOONFISH_FRAGMENT_SHADER);
    balloonFishProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    return balloonFishProgram;
}

GLuint ShaderUtil::compBalloonFishSTABShader(){
    GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (char*)BALLOONFISH_STAB_VERTEX_SHADER);
    GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (char*)BALLOONFISH_STAB_FRAGMENT_SHADER);
    balloonFishSTABProgram = CreateProgram(vsShader, fsShader);
    glDeleteShader(vsShader);
    glDeleteShader(fsShader);
    return balloonFishSTABProgram;
}

GLuint ShaderUtil::getGeomProgram(){
    return geomProgram;
}

GLuint ShaderUtil::getDrawPointLineProgram(){
    return drawPointLineProgram;
}


GLuint ShaderUtil::getDrawCoralProgram() {
    return drawCoralProgram;
}

GLuint ShaderUtil::getFlyElephantEarProgram(){
    return flyElephantEarProgram;
}

GLuint ShaderUtil::getTextureProgram(){
    return textureProgram;
}

GLuint ShaderUtil::getSeaGrassProgram(){
    return seaGrassProgram;
}

GLuint ShaderUtil::getSeaGrassMapProgram(){
    return seaGrassMapProgram;
}

GLuint ShaderUtil::getBalloonFishProgram() {
    return balloonFishProgram;
}

GLuint ShaderUtil::getBalloonFishSTABProgram(){
    return balloonFishSTABProgram;
}