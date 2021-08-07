//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// Definitions for the Scene class.  This class wraps in drawing in GL.
//
//=================================================================================================================================
// $Id: //depot/3darg/Tools/Handheld/esTestApps/common/Scene.h#1 $ 
// 
// Last check-in:  $DateTime: 2008/01/23 11:45:40 $ 
// Last edited by: $Author: dginsbur $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "uniform.h"
#include <iostream>
#include <fstream>

#include "ArgDefines.h"
#include "esUtil.h"




//=================================================================================================================================
/// Scene class - This class loads and draws the scene.
//=================================================================================================================================
class Scene
{
public:
   /// \brief Constructor.
   Scene();

   /// \brief Destructor.
   ~Scene();

   /// \brief Draws the frame.
   void drawFrame();

   /// \brief Loads all the data from the file (textures, attributes, uniforms, shaders...)
   bool loadData(const char8* filename);

   /// \brief Puts the named program in use
   void useProgram( const char8* name );

   /// \brief Updates the value of a uniform
   bool updateUniform( const char8* name, float32* vals );

   /// \brief Deletes all the GL resources we have allocated
   void freeResources();

   /// \brief Binds a texture into GL
   bool bindTexture( const char8* name, int32 width, int32 height );

   /// \brief Binds an FBO into GL
   bool bindFbo( const char8* name, int32 width, int32 height );
  
public:

	float g_vertexTexcoord[1000000];
	uint32 g_indices[100000];
	float blinesPoints[1000000];
	//生成B样条曲线的控制点的索引值      blinePointNum必须小于splitNum
	float vertex_arr2[1000000];
	float blpoints1[100000];

   // Contains all the uniform/texture/attribute/shader data
   Uniform m_uniforms;
   
   MatrixTransformData* matrixTDPoint;
   /// Pointer to the clear color
   float32 m_clearColor[4];
};

#endif // _SCENE_H_
