//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// Definitions for the Uniform class.  This class loads textures, attributes, and uniforms.
//
//=================================================================================================================================
// $Id: //depot/3darg/Tools/Handheld/esTestApps/common/Uniform.h#1 $ 
// 
// Last check-in:  $DateTime: 2008/01/23 11:45:40 $ 
// Last edited by: $Author: dginsbur $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

#ifndef _UNIFORM_H_
#define _UNIFORM_H_

#ifdef USE_STANDARD_GL
#include <glew.h>
#else
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>
#include <Misc.h>
#include <iostream>
#endif //USE_STANDARD_GL

#include "UniformData.h"
#include "ArgDefines.h"
#include <vector>
#include <string>
#include <stdlib.h>


#define GEN_TEX_UNIT 0
#define GEN_TEX_ID 100

#define SAMPLE_FLOAT        0x1
#define SAMPLE_FLOAT_VEC2   0x2
#define SAMPLE_FLOAT_VEC3   0x3
#define SAMPLE_FLOAT_VEC4   0x4
#define SAMPLE_INT          0x5
#define SAMPLE_FLOAT_MAT4   0xd
#define SAMPLE_PROGRAM      0xe
using namespace std;
//=================================================================================================================================
/// Uniform class - Derived from UniformData class.  This class loads and sets the uniforms, attributes, and textures.
//=================================================================================================================================

class MatrixTransformData
{
public:
	MatrixTransformData::MatrixTransformData(){ };
	MatrixTransformData::MatrixTransformData(float scaleValue, float angleChange) :scaleValue(scaleValue), angleChange(angleChange){};

public:
	float windowWidth;
	float windowHeight;
	float angleChange;
	float scaleValue;
	float lightPosX;
	float lightPosY;
	float lightPosZ;
};

class Uniform : public UniformData
{

	

public:
	Uniform::Uniform()
	{
		//std::cout << "" << std::endl;
	}
   /// \brief Gets es texture id.
   int32 getUnitID() const { return m_unitID; }

   /// \brief Loads uniforms/textures/attributes from text file into structure.
   bool parseUniforms(const char8* fileName);

   /// \brief Updates the value of a uniform
   bool updateOneUniform( const char8* name, float32* vals );

   /// \brief Gets the program handle
   GLuint Uniform::getProgramHandle( const char8* name );

   /// \brief Binds a texture into GL
   bool bindTexture( const char8* name, int32 width, int32 height );

   /// \brief Binds an FBO into GL
   bool bindFbo( const char8* name, int32 width, int32 height );

   /// \brief Deletes all the GL resources that we have loaded
   void freeAllData();

   /// \brief Updates all the uniform data after a link
   void updateAllUniforms( GLuint curProg );

   float* getPointArrayTest();
   float* getPointArrayTest2();
   float* getPointArrayTest3();
   float* getPointArrayTest4();
   float* getPointArrayTest5();
   float* getPointArrayTest6();
   float* getPointArrayTest7();
   float* getBezierGather();
   float* getVertexArray();
   uint32* getIndices();
   uint32* getShaderIndices();

   float* getVertexTexcoord();
   std::vector<UniformData*> getUniformDataList();
   int getBezierSteps();
   void saveUniformData(UniformData* uniformDataPoint);
   int getBezierSplitNum();
   int getBeizierTransverSpan();
   int getBlinePointNum();
   
   float* getBezierShaderPoints1Uniform();
   float* getBezierShaderPoints2Uniform();
   float* getBezierShaderPoints3Uniform();
   float* getBezierShaderPoints4Uniform();

   float* getBlineFactors1Uniform();
   float* getBlineFactors2Uniform();

   float* getVertexOrhterArr3();
   float* getVertexOrhterArr4();
   float* getVertexOrhterArr5();

   void operateBezierPoint();

   float Uniform::jiecheng2(int i);
   void Uniform::makeBezierData();
   float* Uniform::getPointArrayUniform();
   float middlePoint[3000];
   float newPoints[3000];
   //void Uniform::controlPointMove(int i, float prod);
   void controlPointMove(int splitNumber, float* splitSqurePoints);
   void getMiddVectVertPoint(int planeNum, int cutPointNum, float* verticalPoints);
   void repeatingMotion();//重复运动
   //斜向运动
   void Uniform::obliqueDirecMotion(float* verticalPoints, int splitNumber, float radius, float PX, float PY, float PZ, int j, bool plusOrMinus);
   //贝塞尔控制点向下运动
   void jellyFishMoveDown();
   void jellyFishMoveUp();
   bool isDown = true;
   


   float firstVerticalPoints[3];
   float secondVerticalPoints[3];
   float thirdVerticalPoints[3];
   float fourthVerticalPoints[3];
   float fifthVerticalPoints[3];
   float sixthVerticalPoints[3];

   void getNewPointByVertVect(float* verticalPoints, float PX, float PY, float PZ, float* splitSqurePoints, int splitNumber, int pNum,float radius,int j);
   
//private:
   bool Uniform::loadShaderObject( const char8* filename, GLuint shaderHandle );

   typedef std::vector<UniformData*>	   UniformDataList;
   typedef UniformDataList::iterator	UniformDataIterator;

   /// Vector of all the data for the different uniforms/textures/attributes.
   UniformDataList m_uniforms;
   // The most recent program handle (used to know which program attribs and uniforms are bound to)
   GLuint m_recentProgramHandle;

   /// Iter to walk through all the uniform/texture/attribute data
   int32 m_unitID;
};

#endif // _UNIFORM_H_