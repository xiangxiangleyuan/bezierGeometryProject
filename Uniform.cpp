//=================================================================================================================================
//
// Author: Maurice Ribble
//         3D Application Research Group
//         ATI Research, Inc.
//
// Implementation for the Uniform class.  This class loads textures, attributes, and uniforms.
//
//=================================================================================================================================
// $Id: //depot/3darg/Tools/Handheld/esTestApps/common/Uniform.cpp#1 $ 
// 
// Last check-in:  $DateTime: 2008/01/23 11:45:40 $ 
// Last edited by: $Author: dginsbur $
//=================================================================================================================================
//   (C) ATI Research, Inc. 2006 All rights reserved. 
//=================================================================================================================================
#include "Scene.h"
#include "uniform.h"
#include "SimpleImageLoader.h"
#include "MapVertPoints.h"
#include "BezierUtil.h"
#include "ShaderUtil.h"
#include "SupplementGeom.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>
using namespace std;


//=================================================================================================================================
///
/// Loads all the shader objects.
///
/// \param fileName is the name for the file where we get objects
/// \param stateHandle is the ES handle to different types of shaders
///
/// \return bool saying whether we passed or failed
//=================================================================================================================================
bool Uniform::loadShaderObject(const char8* filename, GLuint shaderHandle)
{
	char8* source = NULL;

	{
		// Use file io to load the code of the shader.
		std::ifstream fp(filename, ios_base::binary);
		if (fp.fail())
		{
			cout << "Failed to open shader file: ";
			cout << filename << endl;
			return false;
		}

		fp.seekg(0, std::ios_base::end);
		const long len = fp.tellg();
		fp.seekg(0, std::ios_base::beg);
		// The +1 is optional, depending on how you call glShaderSourceARB
		source = new char[len + 1];
		fp.read(source, sizeof(char)*len);
		source[len] = NULL;
	}

	const char8* gls[1] = { source };

	// Pass our sources to OpenGL. Our sources are NULL terminated, so pass NULL for the lenghts.
	glShaderSource(shaderHandle, 1, gls, NULL);
	// OpenGL made a copy. Do not need the source anymore.
	delete[] source;
	source = 0;

	// Compile that one object.
	glCompileShader(shaderHandle);

	// Check for compilation success
	GLint compilationResult = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compilationResult);

	// current implementation always succeeds.
	// The error will happen at link time.
	if (compilationResult == 0)
	{
		cout << "Failed to compile shader:";
		cout << filename << endl;
		return false;
	}

	return true;
}



//=================================================================================================================================
///
/// Parses in text file with info about the textures/uniforms/attributes
///
/// \param fileName is the filename we are to parse
///
/// \return pass or fail boolean
//=================================================================================================================================
struct record
{
	float farr1[1000000];
	float farr2[1000000];
	float farr3[1000000];
};
bool Uniform::parseUniforms(const char8* fileName)
{
	////////////////////////////////////////////////
	record* p = (record*)malloc(sizeof(record));
	
	for (int i = 0; i < 10;i++)
	{
		computeByIndex2(i);
	}
	
	makeBiezerData();
	mapBezierLine(verticalPointArray);
	drawFrame();
	suppGeomByPoint(getBlinesPoints(), getTransverSpan(), getBezierBlinePointNum(), getSplitNum());

	/*for (int i = 0; i < 7; i++)
	{
		computeByIndex3(i);
	}
	makeBiezerData();
	mapBezierLine(verticalPointArray);
	drawFrame();

	for (int i = 0; i < 7; i++)
	{
		computeByIndex4(i);
	}
	makeBiezerData();
	mapBezierLine(verticalPointArray);
	drawFrame();

	for (int i = 0; i < 7; i++)
	{
		computeByIndex5(i);
	}
	makeBiezerData();
	mapBezierLine(verticalPointArray);
	drawFrame();*/

	////////////////////////////////////////////////
	int currentLine = 0;

	m_uniforms.clear();
	m_unitID = 1;

	ifstream fin(fileName, std::ios_base::binary);

	if (fin.fail())
	{
		cout << "Failed to open uniform file: ";
		cout << fileName << endl;
		return false;
	}

	while (!fin.eof())
	{
		UniformData *newUniform = new UniformData;
		string lineString;
		string sItem;
		bool addToVec = false;

		memset(newUniform, 0, sizeof(UniformData));

		getline(fin, lineString);
		stringstream line(lineString);

		++currentLine;

		line >> sItem;

		if (sItem == "uniform_float")
		{
			string sKey;
			float32 fVal;

			line >> sKey >> fVal;

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_FLOAT;
			newUniform->m_floatData[0] = fVal;
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniform1f(newUniform->m_location, newUniform->m_floatData[0]);
		}
		else if (sItem == "uniform_vec2")
		{
			string sKey;
			float32 vVal[2];
			line >> sKey >> vVal[0] >> vVal[1];

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_FLOAT_VEC2;
			newUniform->m_floatData[0] = vVal[0];
			newUniform->m_floatData[1] = vVal[1];
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniform2f(newUniform->m_location, newUniform->m_floatData[0], newUniform->m_floatData[1]);
		}
		else if (sItem == "uniform_vec3")
		{
			string sKey;
			float32 vVal[3];
			line >> sKey >> vVal[0] >> vVal[1] >> vVal[2];

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_FLOAT_VEC3;
			newUniform->m_floatData[0] = vVal[0];
			newUniform->m_floatData[1] = vVal[1];
			newUniform->m_floatData[2] = vVal[2];
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniform3f(newUniform->m_location, newUniform->m_floatData[0], newUniform->m_floatData[1], newUniform->m_floatData[2]);
		}
		else if (sItem == "uniform_vec4")
		{
			string sKey;
			float32 vVal[4];
			line >> sKey >> vVal[0] >> vVal[1] >> vVal[2] >> vVal[3];

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_FLOAT_VEC4;
			newUniform->m_floatData[0] = vVal[0];
			newUniform->m_floatData[1] = vVal[1];
			newUniform->m_floatData[2] = vVal[2];
			newUniform->m_floatData[3] = vVal[3];
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniform4f(newUniform->m_location, newUniform->m_floatData[0], newUniform->m_floatData[1],
				newUniform->m_floatData[2], newUniform->m_floatData[3]);
		}
		else if (sItem == "uniform_mat4")
		{
			string sKey;
			line >> sKey;

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			for (int i = 0; i < 4; ++i)
			{
				float32 vVal[4];
				line >> vVal[0] >> vVal[1] >> vVal[2] >> vVal[3];
				newUniform->m_matrixData[i][0] = vVal[0];
				newUniform->m_matrixData[i][1] = vVal[1];
				newUniform->m_matrixData[i][2] = vVal[2];
				newUniform->m_matrixData[i][3] = vVal[3];
			}
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_FLOAT_MAT4;
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniformMatrix4fv(newUniform->m_location, 1, GL_FALSE, &newUniform->m_matrixData[0][0]);
		}
		else if (sItem == "attribute")
		{
			string sKey;
			int32 vVal;

			line >> sKey >> vVal;
			glBindAttribLocation(m_recentProgramHandle, vVal, sKey.c_str());
			addToVec = false;
		}
		else if (sItem == "texture")
		{
			SimpleImageLoader imgLoader;

			ImageObject *pImgObj;
			uint32 texId;

			string sKey, sVal;
			int32 texUnit;
			line >> sKey >> texUnit >> sVal;

			pImgObj = imgLoader.LoadImageFile(sVal.c_str());

			if (pImgObj != NULL)
			{
				glGenTextures(1, &texId);
				glActiveTexture(GL_TEXTURE0 + texUnit);
				glBindTexture(GL_TEXTURE_2D, texId);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				if (pImgObj->GetNumChannels() == 3)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImgObj->GetWidth(), pImgObj->GetHeight(),
						0, GL_RGB, GL_UNSIGNED_BYTE, pImgObj->GetDataPtr());
				}
				else
				{
					assert(pImgObj->GetNumChannels() == 4);
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImgObj->GetWidth(), pImgObj->GetHeight(),
						0, GL_RGBA, GL_UNSIGNED_BYTE, pImgObj->GetDataPtr());
				}
				delete pImgObj;

				addToVec = true;
				newUniform->m_attachedProgram = m_recentProgramHandle;
				newUniform->m_name = new char[sKey.length() + 1];
				strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
				newUniform->m_type = SAMPLE_INT;
				newUniform->m_textureHandle = texId;
				newUniform->m_textureUnit = texUnit;
				newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
				glUniform1i(newUniform->m_location, newUniform->m_textureUnit);
			}
			else
			{
				// Failed to load texture;
				newUniform->m_location = NULL;
				assert(0);
			}
		}
		else if (sItem == "compressed_texture")
		{
			string sCompressionType, sKey, sVal;
			int32 texUnit;
			line >> sCompressionType >> sKey >> texUnit >> sVal;

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_INT;
			newUniform->m_textureUnit = texUnit;

#ifndef USE_STANDARD_GL
			newUniform->m_textureHandle = LoadCompressedTexture(sVal.c_str(), sCompressionType.c_str(), texUnit);
#endif // USE_STANDARD_GL
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniform1i(newUniform->m_location, newUniform->m_textureUnit);
		}
		else if (sItem == "genTexture")
		{
			GLuint texId;
			int32 texUnit;
			string sKey;
			line >> sKey >> texUnit;

			addToVec = true;
			newUniform->m_attachedProgram = m_recentProgramHandle;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_INT;
			newUniform->m_textureUnit = texUnit;
			glGenTextures(1, &texId);
			newUniform->m_textureHandle = texId;
			newUniform->m_location = glGetUniformLocation(m_recentProgramHandle, sKey.c_str());
			glUniform1i(newUniform->m_location, newUniform->m_textureUnit);
		}
		else if (sItem == "nullTexture")
		{
			GLuint texId;
			int32 texUnit;
			string sKey;
			line >> sKey >> texUnit;

			addToVec = true;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_INT;
			newUniform->m_textureUnit = texUnit;
			glGenTextures(1, &texId);
			newUniform->m_textureHandle = texId;

			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else if (sItem == "colorTexFbo")
		{
			GLuint texId, fboId;
			int32 texUnit;
			string sKey;
			line >> sKey >> texUnit;

			addToVec = true;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_INT;
			newUniform->m_textureUnit = texUnit;
			glGenTextures(1, &texId);
#ifdef USE_STANDARD_GL
			glGenFramebuffersEXT( 1, &fboId );
#else
			glGenFramebuffers(1, &fboId);
#endif // USE_STANDARD_GL
			newUniform->m_textureHandle = texId;
			newUniform->m_fboHandle = fboId;

			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_2D, texId);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else if (sItem == "depthTexFbo")
		{
			GLuint texId, fboId;
			int32 texUnit;
			string sKey;
			line >> sKey >> texUnit;

			addToVec = true;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_INT;
			newUniform->m_textureUnit = texUnit;
			newUniform->m_depthTex = true;
			glGenTextures(1, &texId);
#ifdef USE_STANDARD_GL
			glGenFramebuffersEXT( 1, &fboId );
#else
			glGenFramebuffers(1, &fboId);
#endif // USE_STANDARD_GL
			newUniform->m_textureHandle = texId;
			newUniform->m_fboHandle = fboId;

			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_2D, texId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else if (sItem == "program")
		{
			string sKey, vertShader, fragShader;
			line >> sKey >> vertShader >> fragShader;

			addToVec = true;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_PROGRAM;

			// Create the one program we are going to use.
			newUniform->m_progHandle = glCreateProgram();
			m_recentProgramHandle = newUniform->m_progHandle;

			// Create one shader of object of each type.
			newUniform->m_vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
			newUniform->m_fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

			loadShaderObject(vertShader.c_str(), newUniform->m_vertShaderHandle);
			loadShaderObject(fragShader.c_str(), newUniform->m_fragShaderHandle);

			GLint compileVertResult = 0;
			GLint compileFragResult = 0;
			glGetShaderiv(newUniform->m_vertShaderHandle, GL_COMPILE_STATUS, &compileVertResult);
			glGetShaderiv(newUniform->m_fragShaderHandle, GL_COMPILE_STATUS, &compileFragResult);
			if (compileVertResult == 0 || compileFragResult == 0)
			{
				char8 *log = (char8*)malloc(1000);
				GLint length2;
				if (compileVertResult == 0)
				{
					cout << "Failed to compile vert shader." << endl;
					glGetShaderInfoLog(newUniform->m_vertShaderHandle, 1000, &length2, log);
					cout << log << endl;
				}
				if (compileFragResult == 0)
				{
					cout << "Failed to compile frag shader." << endl;
					glGetShaderInfoLog(newUniform->m_fragShaderHandle, 1000, &length2, log);
					cout << log << endl;
				}
				free(log);
			}

			// Attach them to the program.
			glAttachShader(newUniform->m_progHandle, newUniform->m_vertShaderHandle);
			glAttachShader(newUniform->m_progHandle, newUniform->m_fragShaderHandle);

			ShaderUtil shaderUtil;
			shaderUtil.compShader();
			

		}
		else if (sItem == "binaryProgram")
		{
			string sKey, filename;
			line >> sKey >> filename;

			addToVec = true;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			newUniform->m_type = SAMPLE_PROGRAM;

			char8* source = NULL;
			long len;
			{
				// Use file io to load the code of the shader.
				std::ifstream fp(filename.c_str(), ios_base::binary);
				if (fp.fail())
				{
					cout << "Failed to open shader file: ";
					cout << filename << endl;
					return false;
				}

				fp.seekg(0, std::ios_base::end);
				len = fp.tellg();
				fp.seekg(0, std::ios_base::beg);

				source = new char[len];
				fp.read(source, sizeof(char)*len);
			}

			// Create the one program we are going to use.
			newUniform->m_progHandle = glCreateProgram();
			m_recentProgramHandle = newUniform->m_progHandle;

			// Create one shader of object of each type.
			newUniform->m_vertShaderHandle = glCreateShader(GL_VERTEX_SHADER);
			newUniform->m_fragShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

#ifndef USE_STANDARD_GL
			GLuint shaders[2] = { newUniform->m_vertShaderHandle, newUniform->m_fragShaderHandle };
			glShaderBinary(2, shaders, GL_Z400_BINARY_AMD, source, len);
#endif // USE_STANDARD_GL

			// Attach them to the program.
			glAttachShader(newUniform->m_progHandle, newUniform->m_vertShaderHandle);
			glAttachShader(newUniform->m_progHandle, newUniform->m_fragShaderHandle);

			delete[] source;
		}
		else if (sItem == "link")
		{
			string progName;
			line >> progName;

			addToVec = false;
			GLuint progHandle = getProgramHandle(progName.c_str());

			// Link the whole program together.
			glLinkProgram(progHandle);

			// Check for link success
			GLint linkResult = 0;
			glGetProgramiv(progHandle, GL_LINK_STATUS, &linkResult);
			glUseProgram(progHandle);
			updateAllUniforms(progHandle);
			if (linkResult == 0)
			{
				char8 log[1000];
				GLint length;
				glGetProgramInfoLog(progHandle, 1000, &length, log);
				cout << "Failed to link program object.";
				cout << log << endl;
				return false;
			}
		}
		else if (sItem == "load")
		{
			string sKey, vertShader, fragShader;
			line >> sKey >> vertShader >> fragShader;

			addToVec = true;
			newUniform->m_name = new char[sKey.length() + 1];
			strcpy_s(newUniform->m_name, sKey.length() + 1, sKey.c_str());
			
		}
		else if (sItem.empty() || sItem[0] == '/')
		{
			// Either an empty line or a comment
			addToVec = false;
		}
		
		else
		{
			addToVec = false;
			cout << "Unsupported keyword in uniform file." << endl;
			//assert(0);
		}

		if (addToVec)
		{
			m_uniforms.push_back(newUniform);
		}
		else
		{
			delete newUniform;
		}
	}
	return true;
}

//=================================================================================================================================
///
/// Updates the value of a uniform
///
/// \param name - The name we gave to the uniform
/// \param vals - An array of values we want to to replace the current uniform values with
///
/// \return true=pass ... false=fail
//=================================================================================================================================
bool Uniform::updateOneUniform(const char8* name, float32* vals)
{
	bool updated = false;
	UniformDataIterator index;

	for (index = m_uniforms.begin(); index != m_uniforms.end(); ++index)
	{
		UniformData* current = *index;

		if (strcmp(name, current->m_name) == 0)
		{
			updated = true;

			switch (current->m_type)
			{
			case SAMPLE_FLOAT:
				memcpy(current->m_floatData, vals, sizeof(float32)* 1);
				glUniform1f(current->m_location, current->m_floatData[0]);
				break;
			case SAMPLE_FLOAT_VEC2:
				memcpy(current->m_floatData, vals, sizeof(float32)* 2);
				glUniform2f(current->m_location, current->m_floatData[0], current->m_floatData[1]);
				break;
			case SAMPLE_FLOAT_VEC3:
				memcpy(current->m_floatData, vals, sizeof(float32)* 3);
				glUniform3f(current->m_location, current->m_floatData[0], current->m_floatData[1], current->m_floatData[2]);
				break;
			case SAMPLE_FLOAT_VEC4:
				memcpy(current->m_floatData, vals, sizeof(float32)* 4);
				glUniform4f(current->m_location, current->m_floatData[0], current->m_floatData[1], current->m_floatData[2], current->m_floatData[3]);
				break;
			case SAMPLE_FLOAT_MAT4:
				memcpy(current->m_matrixData, vals, sizeof(float32)* 16);
				glUniformMatrix4fv(current->m_location, 1, GL_FALSE, &current->m_matrixData[0][0]);
				break;
			default:
				assert(0);
				break;
			}
		}

		if (updated)
		{
			break;
		}
	}

	assert(updated == true); // They probably passed in un unsupported type or invalid name
	return updated;
}

//=================================================================================================================================
///
/// Gets the program handle
///
/// \param name - The name we gave to the program
///
/// \return true=pass ... false=fail
//=================================================================================================================================
GLuint Uniform::getProgramHandle(const char8* name)
{
	bool updated = false;
	GLuint ret = 0;
	UniformDataIterator index;

	for (index = m_uniforms.begin(); index != m_uniforms.end(); ++index)
	{
		UniformData* current = *index;

		if (strcmp(name, current->m_name) == 0)
		{
			updated = true;

			switch (current->m_type)
			{
			case SAMPLE_PROGRAM:
				ret = current->m_progHandle;
				break;
			default:
				assert(0);
				break;
			}
		}

		if (updated)
		{
			break;
		}
	}

	//   assert( updated == true ); // They probably passed in un unsupported type or invalid name
	return ret;
}

//=================================================================================================================================
///
/// Binds a texture in GL
///
/// \param name - The name we gave to the texture
/// \param width - The width of the texture
/// \param height - The height of the texture
///
/// \return true=pass ... false=fail
//=================================================================================================================================
bool Uniform::bindTexture(const char8* name, int32 width, int32 height)
{
	bool updated = false;
	UniformDataIterator index;

	for (index = m_uniforms.begin(); index != m_uniforms.end(); ++index)
	{
		UniformData* current = *index;

		if (strcmp(name, current->m_name) == 0)
		{
			if (current->m_type == SAMPLE_INT && current->m_textureHandle)
			{
				updated = true;
			}
			break;
		}
	}

	if (updated)
	{
		GLint curProg, uniformLocation;
		glGetIntegerv(GL_CURRENT_PROGRAM, &curProg);
		uniformLocation = glGetUniformLocation(curProg, (*index)->m_name);
		glUniform1i(uniformLocation, (*index)->m_textureUnit);
		glActiveTexture(GL_TEXTURE0 + (*index)->m_textureUnit);
		glBindTexture(GL_TEXTURE_2D, (*index)->m_textureHandle);

		if ((*index)->m_width != width || (*index)->m_height != height)
		{
			if (width != 0 && height != 0) // If these are 0 then we just want to keep the current size
			{
				(*index)->m_width = width;
				(*index)->m_height = height;
				if ((*index)->m_depthTex)
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
				}
			}
		}
	}
	else
	{
		assert(0); // They probably passed in an a non-texture type or an invalid name
	}
	return updated;
}

//=================================================================================================================================
///
/// Binds an FBO in GL
///
/// \param name - The name of the fbo
/// \param width - The width of the fbo
/// \param height - The height of the fbo
///
/// \return true=pass ... false=fail
//=================================================================================================================================
bool Uniform::bindFbo(const char8* name, int32 width, int32 height)
{
	bool updated = false;
	UniformDataIterator index;

	for (index = m_uniforms.begin(); index != m_uniforms.end(); ++index)
	{
		UniformData* current = *index;

		if (strcmp(name, current->m_name) == 0)
		{
			if (current->m_type == SAMPLE_INT && current->m_textureHandle && current->m_fboHandle)
			{
				updated = true;
			}
			break;
		}
	}

	if (updated)
	{
#ifdef USE_STANDARD_GL
		glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, (*index)->m_fboHandle );
#else
		glBindFramebuffer(GL_FRAMEBUFFER, (*index)->m_fboHandle);
#endif // USE_STANDARD_GL

		if ((*index)->m_width != width || (*index)->m_height != height)
		{
			GLint curTexture;
			glGetIntegerv(GL_TEXTURE_BINDING_2D, &curTexture);

			(*index)->m_width = width;
			(*index)->m_height = height;
			glBindTexture(GL_TEXTURE_2D, (*index)->m_textureHandle);
			if ((*index)->m_depthTex)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			}

			glBindTexture(GL_TEXTURE_2D, curTexture);

#ifdef USE_STANDARD_GL
			if ( (*index)->m_depthTex )
			{
				if (!(*index)->m_colorRbHandle)
				{
					glGenRenderbuffersEXT( 1, &(*index)->m_colorRbHandle );
				}
				glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, (*index)->m_colorRbHandle );
				glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_RGB, width, height );
				glFramebufferRenderbufferEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, (*index)->m_colorRbHandle );
				glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, (*index)->m_textureHandle, 0 );
			}
			else
			{
				glFramebufferTexture2DEXT( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, (*index)->m_textureHandle, 0 );
			}
#else
			if ((*index)->m_depthTex)
			{
				if (!(*index)->m_colorRbHandle)
				{
					glGenRenderbuffers(1, &(*index)->m_colorRbHandle);
				}
				glBindRenderbuffer(GL_RENDERBUFFER, (*index)->m_colorRbHandle);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, (*index)->m_colorRbHandle);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (*index)->m_textureHandle, 0);
			}
			else
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (*index)->m_textureHandle, 0);
			}
#endif // USE_STANDARD_GL
		}
	}
	else
	{
		assert(0); // They probably passed in an a non-texture type or an invalid name
	}
	return updated;
}


//=================================================================================================================================
///
/// Deletes all the GL resources that we have loaded
///
/// \param name - The name we gave to the program
///
/// \return true=pass ... false=fail
//=================================================================================================================================
void Uniform::freeAllData()
{
	UniformDataIterator index;

	for (index = m_uniforms.begin(); index != m_uniforms.end(); ++index)
	{
		if ((*index)->m_textureHandle)
		{
			glDeleteTextures(1, &((*index)->m_textureHandle));
		}
		if ((*index)->m_vertShaderHandle)
		{
			glDeleteShader((*index)->m_vertShaderHandle);
		}
		if ((*index)->m_fragShaderHandle)
		{
			glDeleteShader((*index)->m_fragShaderHandle);
		}
		if ((*index)->m_progHandle)
		{
			glDeleteProgram((*index)->m_progHandle);
		}

#ifdef USE_STANDARD_GL
		if ( (*index)->m_fboHandle )
		{
			glDeleteFramebuffersEXT(1, &(*index)->m_fboHandle );
		}
		if ( (*index)->m_colorRbHandle )
		{
			glDeleteRenderbuffersEXT(1, &(*index)->m_colorRbHandle );
		}
#else
		if ((*index)->m_fboHandle)
		{
			glDeleteFramebuffers(1, &(*index)->m_fboHandle);
		}
		if ((*index)->m_colorRbHandle)
		{
			glDeleteRenderbuffers(1, &(*index)->m_colorRbHandle);
		}
#endif // USE_STANDARD_GL
	}

	for (uint32 i = 0; i < m_uniforms.size(); i++)
	{
		if (m_uniforms[i] != NULL)
		{
			delete m_uniforms[i];
		}
	}
	m_uniforms.clear();
}

//=================================================================================================================================
///
/// Updates all the uniform data after a link
///
/// \param void
///
/// \return void
//=================================================================================================================================
void Uniform::updateAllUniforms(GLuint curProg)
{
	UniformDataIterator index;

	for (index = m_uniforms.begin(); index != m_uniforms.end(); ++index)
	{
		if (curProg == (*index)->m_attachedProgram)
		{
			switch ((*index)->m_type)
			{
			case SAMPLE_FLOAT:
				glUniform1f((*index)->m_location, (*index)->m_floatData[0]);
				break;
			case SAMPLE_FLOAT_VEC2:
				glUniform2f((*index)->m_location, (*index)->m_floatData[0], (*index)->m_floatData[1]);
				break;
			case SAMPLE_FLOAT_VEC3:
				glUniform3f((*index)->m_location, (*index)->m_floatData[0], (*index)->m_floatData[1], (*index)->m_floatData[2]);
				break;
			case SAMPLE_FLOAT_VEC4:
				glUniform4f((*index)->m_location, (*index)->m_floatData[0], (*index)->m_floatData[1], (*index)->m_floatData[2], (*index)->m_floatData[3]);
				break;
			case SAMPLE_FLOAT_MAT4:
				glUniformMatrix4fv((*index)->m_location, 1, GL_FALSE, &(*index)->m_matrixData[0][0]);
				break;
			case SAMPLE_INT:
				if ((*index)->m_location != 0) // Prevents error on nullTexture which has not yet been given a location (done at bind time)
				{
					glUniform1i((*index)->m_location, (*index)->m_textureUnit);
				}
				break;
			case SAMPLE_PROGRAM:
				break;
			default:
				assert(0);
				break;
			}
		}
	}
}

///////////////////////////////////
float* Uniform::getPointArrayTest()
{
	//百分比的数组
	return pointArrayTest;
}
float* Uniform::getPointArrayTest2()
{
	//垂直于直线上的点中的其中两个
	return pointArrayTest2;
}
float* Uniform::getPointArrayTest3()
{
	//垂直于直线上的点中的其中两个
	return pointArrayTest5;
}
float* Uniform::getPointArrayTest4()
{
	return getSplitSqurePoints();
	//return pointArrayTest4;
}
float* Uniform::getPointArrayTest5()
{
	//为半径的垂直点
	return getSplitSqurePoints();
	//return pointArrayTest5;
}

float* Uniform::getBezierGather()
{
	return bezierGather;
}

float* Uniform::getPointArrayUniform()
{
	return getPointArray();
}

std::vector<UniformData*> Uniform::getUniformDataList()
{
	
	return Uniform::m_uniforms;
}
//得到bezier的步长
int Uniform::getBezierSteps()
{
	return getSteps();
}
//得到定点的数组
float* Uniform::getVertexArray()
{
	return vertex_arr2;
}

uint32* Uniform::getIndices()
{
	return getClosedSplineIndices();
}

uint32* Uniform::getShaderIndices()
{
	return getClosedSplineShaderIndices();
}

float* Uniform::getVertexTexcoord()
{
	return g_vertexTexcoord;
}

int Uniform::getBezierSplitNum()
{
	return getSplitNum();
}

int Uniform::getBeizierTransverSpan()
{
	return getTransverSpan();
}

int Uniform::getBlinePointNum()
{
	return getBezierBlinePointNum();
}
//B样条的控制点
float* Uniform::getBezierShaderPoints1Uniform()
{
	return trueBezierShaderPoints1;
}
float* Uniform::getBezierShaderPoints2Uniform()
{
	return trueBezierShaderPoints2;
}
float* Uniform::getBezierShaderPoints3Uniform()
{
	return trueBezierShaderPoints3;
}
float* Uniform::getBezierShaderPoints4Uniform()
{
	return trueBezierShaderPoints4;
}

float* Uniform::getBlineFactors1Uniform()
{
	return trueBlineFactors1;
}
float* Uniform::getBlineFactors2Uniform()
{
	return trueBlineFactors2;
}

float* Uniform::getVertexOrhterArr3()
{
	return 	getVertex_arr3();
}

float* Uniform::getVertexOrhterArr4()
{
	return 	getVertex_arr4();
}

float* Uniform::getVertexOrhterArr5()
{
	return 	getVertex_arr5();
}

float Uniform::jiecheng2(int n){
	long result = 1;	//声明一个long型的变量
	if (n == 0)			//0的阶乘为1
	{
		return 1;
	}

	for (int i = 2; i <= n; i++){	//求大于等于2的数的阶乘
		result = result*i;
	}

	return result;	//返回结果
}
//帧数
int frameNumber = 0;
void Uniform::operateBezierPoint()
{
	frameNumber++;
	
	float* splitSqurePoints = getPointArrayTest4();
	int splitNumber = getSplitNumber();
	Uniform::controlPointMove(splitNumber,splitSqurePoints);
	
	//每个面的点数
	int nu = getSplitNumber() * 3;

	//第几个切面
	for (int i = 0; i < pointNum; i++)
	{
		// i 是每个切面的点数
		int currentIndex = i * everyContainAcount * 3;
		for (int j = 0; j < getSplitNumber(); j++)
		{
			int index = j * 3;
			verticalPointArray[currentIndex + index] = splitSqurePoints[i * nu + index];//第几个切面 * 每个面的数值个数 + 当前点索引值*3
			verticalPointArray[currentIndex + index + 1] = splitSqurePoints[i * nu + index + 1];
			verticalPointArray[currentIndex + index + 2] = splitSqurePoints[i * nu + index + 2];
		}

	}

	int step = getSteps();
	int steps = getSteps();
	
	for (int everyAcount = 0; everyAcount < splitNumber;everyAcount++)
	{
		int n = pointNum - 1;
		//int steps = (int)(1.0f / span);	//总得步进数
		float jiechengNA[100];//n+1
		for (int i = 0; i <= n; i++){	//求0到n的阶乘
			jiechengNA[i] = Uniform::jiecheng2(i);
		}

		for (int i = 0; i <= steps; i++)
		{
			float t = i*(1.0 / step);
			if (t > 1)		//t的值在0-1之间
			{
				t = 1;
			}
			float xf = 0.0;
			float yf = 0.0;
			float zf = 0.0;
			float tka[100];  //n+1
			float otka[100]; //n+1
			for (int j = 0; j <= n; j++)
			{
				tka[j] = (float)pow(t, j); //计算t的j次幂
				otka[j] = (float)pow(1 - t, j); //计算1-t的j次幂
			}
			//遍历切面
			for (int k = 0; k <= n; k++)
			{
				//everyAcount 当前第几排定点  　k*(3*everyContainAcount)第几个切面
				float xs = (jiechengNA[n] / (jiechengNA[k] * jiechengNA[n - k]))*tka[k] * otka[n - k];
				xf = xf + verticalPointArray[k * (3 * everyContainAcount) + everyAcount * 3] * xs;
				yf = yf + verticalPointArray[k * (3 * everyContainAcount) + everyAcount * 3 + 1] * xs;
				zf = zf + verticalPointArray[k * (3 * everyContainAcount) + everyAcount * 3 + 2] * xs;
			}
			//steps 总的步进数　everyAcount 当前第几排数　i当前的步进数
			int bezierPointIndex = steps * everyAcount * 3;

			bezierGather[bezierPointIndex + i * 3] = xf;
			bezierGather[bezierPointIndex + i * 3 + 1] = yf;
			bezierGather[bezierPointIndex + i * 3 + 2] = zf;

		}
	}
	
	int blinePointNum = getBezierBlinePointNum();
	int splitNum = getSplitNum();
	for (int i = 0; i < splitNum; i++)
	{
		
		for (int m = 0; m < step; m++) //每条贝塞尔线段上拥有的点数  贝塞尔线段上的第m个点
		{
			int mIndex1 = m * 3; //贝塞尔线段上的第 m 个点的索引
			int loopIndex = (blinePointNum + 3) * splitNum * 3 * m;

			for (int j = 0; j < blinePointNum; j++)
			{
				int secNum = splitNum * 3 * j;//到第 j 个点时，当下的索引值
				int blindex = secNum + i * 3 + loopIndex;

				float bezierShaderPointX1 = bezierGather[j * steps * 3 + mIndex1];
				float bezierShaderPointY1 = bezierGather[j * steps * 3 + mIndex1 + 1];
				float bezierShaderPointZ1 = bezierGather[j * steps * 3 + mIndex1 + 2];

				float bezierShaderPointX2 = bezierGather[(j + 1) * steps * 3 + mIndex1];
				float bezierShaderPointY2 = bezierGather[(j + 1) * steps * 3 + mIndex1 + 1];
				float bezierShaderPointZ2 = bezierGather[(j + 1) * steps * 3 + mIndex1 + 2];

				float bezierShaderPointX3 = bezierGather[(j + 2) * steps * 3 + mIndex1];
				float bezierShaderPointY3 = bezierGather[(j + 2) * steps * 3 + mIndex1 + 1];
				float bezierShaderPointZ3 = bezierGather[(j + 2) * steps * 3 + mIndex1 + 2];

				float bezierShaderPointX4 = bezierGather[(j + 3) * steps * 3 + mIndex1];
				float bezierShaderPointY4 = bezierGather[(j + 3) * steps * 3 + mIndex1 + 1];
				float bezierShaderPointZ4 = bezierGather[(j + 3) * steps * 3 + mIndex1 + 2];

				bezierShaderPoints1[blindex] = bezierShaderPointX1;
				bezierShaderPoints1[blindex + 1] = bezierShaderPointY1;
				bezierShaderPoints1[blindex + 2] = bezierShaderPointZ1;
				bezierShaderPoints2[blindex] = bezierShaderPointX2;
				bezierShaderPoints2[blindex + 1] = bezierShaderPointY2;
				bezierShaderPoints2[blindex + 2] = bezierShaderPointZ2;
				bezierShaderPoints3[blindex] = bezierShaderPointX3;
				bezierShaderPoints3[blindex + 1] = bezierShaderPointY3;
				bezierShaderPoints3[blindex + 2] = bezierShaderPointZ3;
				bezierShaderPoints4[blindex] = bezierShaderPointX4;
				bezierShaderPoints4[blindex + 1] = bezierShaderPointY4;
				bezierShaderPoints4[blindex + 2] = bezierShaderPointZ4;


			}


			int index1 = blinePointNum * steps * 3;
			float lastThirdX1 = bezierGather[index1 + mIndex1];
			float lastThirdY1 = bezierGather[index1 + mIndex1 + 1];
			float lastThirdZ1 = bezierGather[index1 + mIndex1 + 2];
			int index2 = (blinePointNum + 1) * steps * 3;
			float lastThirdX2 = bezierGather[index2 + mIndex1];
			float lastThirdY2 = bezierGather[index2 + mIndex1 + 1];
			float lastThirdZ2 = bezierGather[index2 + mIndex1 + 2];
			int index3 = (blinePointNum + 2) * steps * 3;
			float lastThirdX3 = bezierGather[index3 + mIndex1];
			float lastThirdY3 = bezierGather[index3 + mIndex1 + 1];
			float lastThirdZ3 = bezierGather[index3 + mIndex1 + 2];
			float lastThirdX4 = bezierGather[mIndex1];
			float lastThirdY4 = bezierGather[mIndex1 + 1];
			float lastThirdZ4 = bezierGather[mIndex1 + 2];

			int lastThirdIndex = i * 3 + splitNum * 3 * blinePointNum + loopIndex;
			bezierShaderPoints1[lastThirdIndex] = lastThirdX1;
			bezierShaderPoints1[lastThirdIndex + 1] = lastThirdY1;
			bezierShaderPoints1[lastThirdIndex + 2] = lastThirdZ1;
			bezierShaderPoints2[lastThirdIndex] = lastThirdX2;
			bezierShaderPoints2[lastThirdIndex + 1] = lastThirdY2;
			bezierShaderPoints2[lastThirdIndex + 2] = lastThirdZ2;
			bezierShaderPoints3[lastThirdIndex] = lastThirdX3;
			bezierShaderPoints3[lastThirdIndex + 1] = lastThirdY3;
			bezierShaderPoints3[lastThirdIndex + 2] = lastThirdZ3;
			bezierShaderPoints4[lastThirdIndex] = lastThirdX4;
			bezierShaderPoints4[lastThirdIndex + 1] = lastThirdY4;
			bezierShaderPoints4[lastThirdIndex + 2] = lastThirdZ4;



			int index11 = (blinePointNum + 1) * steps * 3;
			float lastThirdX11 = bezierGather[index11 + mIndex1];
			float lastThirdY11 = bezierGather[index11 + mIndex1 + 1];
			float lastThirdZ11 = bezierGather[index11 + mIndex1 + 2];
			int index22 = (blinePointNum + 2) * steps * 3;
			float lastThirdX22 = bezierGather[index22 + mIndex1];
			float lastThirdY22 = bezierGather[index22 + mIndex1 + 1];
			float lastThirdZ22 = bezierGather[index22 + mIndex1 + 2];
			float lastThirdX33 = bezierGather[mIndex1];
			float lastThirdY33 = bezierGather[mIndex1 + 1];
			float lastThirdZ33 = bezierGather[mIndex1 + 2];

			float lastThirdX44 = bezierGather[steps * 3 + mIndex1];
			float lastThirdY44 = bezierGather[steps * 3 + mIndex1 + 1];
			float lastThirdZ44 = bezierGather[steps * 3 + mIndex1 + 2];

			int lastSecondIndex = i * 3 + splitNum * 3 * (blinePointNum + 1) + loopIndex;
			bezierShaderPoints1[lastSecondIndex] = lastThirdX11;
			bezierShaderPoints1[lastSecondIndex + 1] = lastThirdY11;
			bezierShaderPoints1[lastSecondIndex + 2] = lastThirdZ11;
			bezierShaderPoints2[lastSecondIndex] = lastThirdX22;
			bezierShaderPoints2[lastSecondIndex + 1] = lastThirdY22;
			bezierShaderPoints2[lastSecondIndex + 2] = lastThirdZ22;
			bezierShaderPoints3[lastSecondIndex] = lastThirdX33;
			bezierShaderPoints3[lastSecondIndex + 1] = lastThirdY33;
			bezierShaderPoints3[lastSecondIndex + 2] = lastThirdZ33;
			bezierShaderPoints4[lastSecondIndex] = lastThirdX44;
			bezierShaderPoints4[lastSecondIndex + 1] = lastThirdY44;
			bezierShaderPoints4[lastSecondIndex + 2] = lastThirdZ44;


			int lastOneIndex = i * 3 + splitNum * 3 * (blinePointNum + 2) + loopIndex;

			int index111 = (blinePointNum + 2) * steps * 3;
			float lastThirdX111 = bezierGather[index111 + mIndex1];
			float lastThirdY111 = bezierGather[index111 + mIndex1 + 1];
			float lastThirdZ111 = bezierGather[index111 + mIndex1 + 2];
			float lastThirdX222 = bezierGather[mIndex1];
			float lastThirdY222 = bezierGather[mIndex1 + 1];
			float lastThirdZ222 = bezierGather[mIndex1 + 2];
			float lastThirdX333 = bezierGather[steps * 3 + mIndex1];
			float lastThirdY333 = bezierGather[steps * 3 + mIndex1 + 1];
			float lastThirdZ333 = bezierGather[steps * 3 + mIndex1 + 2];
			float lastThirdX444 = bezierGather[2 * steps * 3 + mIndex1];
			float lastThirdY444 = bezierGather[2 * steps * 3 + mIndex1 + 1];
			float lastThirdZ444 = bezierGather[2 * steps * 3 + mIndex1 + 2];

			bezierShaderPoints1[lastOneIndex] = lastThirdX111;
			bezierShaderPoints1[lastOneIndex + 1] = lastThirdY111;
			bezierShaderPoints1[lastOneIndex + 2] = lastThirdZ111;
			bezierShaderPoints2[lastOneIndex] = lastThirdX222;
			bezierShaderPoints2[lastOneIndex + 1] = lastThirdY222;
			bezierShaderPoints2[lastOneIndex + 2] = lastThirdZ222;
			bezierShaderPoints3[lastOneIndex] = lastThirdX333;
			bezierShaderPoints3[lastOneIndex + 1] = lastThirdY333;
			bezierShaderPoints3[lastOneIndex + 2] = lastThirdZ333;
			bezierShaderPoints4[lastOneIndex] = lastThirdX444;
			bezierShaderPoints4[lastOneIndex + 1] = lastThirdY444;
			bezierShaderPoints4[lastOneIndex + 2] = lastThirdZ444;

		}

	}


	int transverSpan = getTransverSpan();
	int everyNum = splitNum*(blinePointNum + 3);
	int evenum = 18;//一个四边形 6 个索引
	//横向跨度
	for (int j = 0; j < transverSpan; j++)
	{
		int tansverSpanNum1 = j * splitNum*(blinePointNum + 3) * 3;
		int tansverSpanNum2 = (j + 1) * splitNum*(blinePointNum + 3) * 3;
		
		for (int i = 0; i < everyNum - 1; i++)//在一个闭合圈内跳跃几个点
		{
		
			//每个闭合圈点的个数 * 第几个横向跨度 + 当前闭合圈点里的第几个点
			int m = everyNum * j + i;
			
			float bezierShaderPointX1_1 = bezierShaderPoints1[i * 3 + tansverSpanNum1];
			float bezierShaderPointY1_1 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ1_1 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX2_1 = bezierShaderPoints2[i * 3 + tansverSpanNum1];
			float bezierShaderPointY2_1 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ2_1 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX3_1 = bezierShaderPoints3[i * 3 + tansverSpanNum1];
			float bezierShaderPointY3_1 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ3_1 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX4_1 = bezierShaderPoints4[i * 3 + tansverSpanNum1];
			float bezierShaderPointY4_1 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ4_1 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum1];

			trueBezierShaderPoints1[m * evenum] = bezierShaderPointX1_1;
			trueBezierShaderPoints1[m * evenum + 1] = bezierShaderPointY1_1;
			trueBezierShaderPoints1[m * evenum + 2] = bezierShaderPointZ1_1;
			trueBezierShaderPoints2[m * evenum] = bezierShaderPointX2_1;
			trueBezierShaderPoints2[m * evenum + 1] = bezierShaderPointY2_1;
			trueBezierShaderPoints2[m * evenum + 2] = bezierShaderPointZ2_1;
			trueBezierShaderPoints3[m * evenum] = bezierShaderPointX3_1;
			trueBezierShaderPoints3[m * evenum + 1] = bezierShaderPointY3_1;
			trueBezierShaderPoints3[m * evenum + 2] = bezierShaderPointZ3_1;
			trueBezierShaderPoints4[m * evenum] = bezierShaderPointX4_1;
			trueBezierShaderPoints4[m * evenum + 1] = bezierShaderPointY4_1;
			trueBezierShaderPoints4[m * evenum + 2] = bezierShaderPointZ4_1;
			
			float bezierShaderPointX1_2 = bezierShaderPoints1[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY1_2 = bezierShaderPoints1[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ1_2 = bezierShaderPoints1[(i + 1) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX2_2 = bezierShaderPoints2[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY2_2 = bezierShaderPoints2[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ2_2 = bezierShaderPoints2[(i + 1) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX3_2 = bezierShaderPoints3[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY3_2 = bezierShaderPoints3[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ3_2 = bezierShaderPoints3[(i + 1) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX4_2 = bezierShaderPoints4[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY4_2 = bezierShaderPoints4[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ4_2 = bezierShaderPoints4[(i + 1) * 3 + 2 + tansverSpanNum1];
			
			trueBezierShaderPoints1[m * evenum + 3] = bezierShaderPointX1_2;
			trueBezierShaderPoints1[m * evenum + 4] = bezierShaderPointY1_2;
			trueBezierShaderPoints1[m * evenum + 5] = bezierShaderPointZ1_2;
			trueBezierShaderPoints2[m * evenum + 3] = bezierShaderPointX2_2;
			trueBezierShaderPoints2[m * evenum + 4] = bezierShaderPointY2_2;
			trueBezierShaderPoints2[m * evenum + 5] = bezierShaderPointZ2_2;
			trueBezierShaderPoints3[m * evenum + 3] = bezierShaderPointX3_2;
			trueBezierShaderPoints3[m * evenum + 4] = bezierShaderPointY3_2;
			trueBezierShaderPoints3[m * evenum + 5] = bezierShaderPointZ3_2;
			trueBezierShaderPoints4[m * evenum + 3] = bezierShaderPointX4_2;
			trueBezierShaderPoints4[m * evenum + 4] = bezierShaderPointY4_2;
			trueBezierShaderPoints4[m * evenum + 5] = bezierShaderPointZ4_2;
			
			float bezierShaderPointX1_3 = bezierShaderPoints1[i * 3 + tansverSpanNum2];
			float bezierShaderPointY1_3 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ1_3 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX2_3 = bezierShaderPoints2[i * 3 + tansverSpanNum2];
			float bezierShaderPointY2_3 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ2_3 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX3_3 = bezierShaderPoints3[i * 3 + tansverSpanNum2];
			float bezierShaderPointY3_3 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ3_3 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX4_3 = bezierShaderPoints4[i * 3 + tansverSpanNum2];
			float bezierShaderPointY4_3 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ4_3 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum2];
			
			trueBezierShaderPoints1[m * evenum + 6] = bezierShaderPointX1_3;
			trueBezierShaderPoints1[m * evenum + 7] = bezierShaderPointY1_3;
			trueBezierShaderPoints1[m * evenum + 8] = bezierShaderPointZ1_3;
			trueBezierShaderPoints2[m * evenum + 6] = bezierShaderPointX2_3;
			trueBezierShaderPoints2[m * evenum + 7] = bezierShaderPointY2_3;
			trueBezierShaderPoints2[m * evenum + 8] = bezierShaderPointZ2_3;
			trueBezierShaderPoints3[m * evenum + 6] = bezierShaderPointX3_3;
			trueBezierShaderPoints3[m * evenum + 7] = bezierShaderPointY3_3;
			trueBezierShaderPoints3[m * evenum + 8] = bezierShaderPointZ3_3;
			trueBezierShaderPoints4[m * evenum + 6] = bezierShaderPointX4_3;
			trueBezierShaderPoints4[m * evenum + 7] = bezierShaderPointY4_3;
			trueBezierShaderPoints4[m * evenum + 8] = bezierShaderPointZ4_3;
			
			float bezierShaderPointX1_4 = bezierShaderPoints1[i * 3 + tansverSpanNum2];
			float bezierShaderPointY1_4 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ1_4 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX2_4 = bezierShaderPoints2[i * 3 + tansverSpanNum2];
			float bezierShaderPointY2_4 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ2_4 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX3_4 = bezierShaderPoints3[i * 3 + tansverSpanNum2];
			float bezierShaderPointY3_4 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ3_4 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX4_4 = bezierShaderPoints4[i * 3 + tansverSpanNum2];
			float bezierShaderPointY4_4 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ4_4 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum2];
			
			trueBezierShaderPoints1[m * evenum + 9] = bezierShaderPointX1_4;
			trueBezierShaderPoints1[m * evenum + 10] = bezierShaderPointY1_4;
			trueBezierShaderPoints1[m * evenum + 11] = bezierShaderPointZ1_4;
			trueBezierShaderPoints2[m * evenum + 9] = bezierShaderPointX2_4;
			trueBezierShaderPoints2[m * evenum + 10] = bezierShaderPointY2_4;
			trueBezierShaderPoints2[m * evenum + 11] = bezierShaderPointZ2_4;
			trueBezierShaderPoints3[m * evenum + 9] = bezierShaderPointX3_4;
			trueBezierShaderPoints3[m * evenum + 10] = bezierShaderPointY3_4;
			trueBezierShaderPoints3[m * evenum + 11] = bezierShaderPointZ3_4;
			trueBezierShaderPoints4[m * evenum + 9] = bezierShaderPointX4_4;
			trueBezierShaderPoints4[m * evenum + 10] = bezierShaderPointY4_4;
			trueBezierShaderPoints4[m * evenum + 11] = bezierShaderPointZ4_4;
			
			float bezierShaderPointX1_5 = bezierShaderPoints1[(i + 1) * 3 + tansverSpanNum2];
			float bezierShaderPointY1_5 = bezierShaderPoints1[(i + 1) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ1_5 = bezierShaderPoints1[(i + 1) * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX2_5 = bezierShaderPoints2[(i + 1) * 3 + tansverSpanNum2];
			float bezierShaderPointY2_5 = bezierShaderPoints2[(i + 1) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ2_5 = bezierShaderPoints2[(i + 1) * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX3_5 = bezierShaderPoints3[(i + 1) * 3 + tansverSpanNum2];
			float bezierShaderPointY3_5 = bezierShaderPoints3[(i + 1) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ3_5 = bezierShaderPoints3[(i + 1) * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX4_5 = bezierShaderPoints4[(i + 1) * 3 + tansverSpanNum2];
			float bezierShaderPointY4_5 = bezierShaderPoints4[(i + 1) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ4_5 = bezierShaderPoints4[(i + 1) * 3 + 2 + tansverSpanNum2];
			
			trueBezierShaderPoints1[m * evenum + 12] = bezierShaderPointX1_5;
			trueBezierShaderPoints1[m * evenum + 13] = bezierShaderPointY1_5;
			trueBezierShaderPoints1[m * evenum + 14] = bezierShaderPointZ1_5;
			trueBezierShaderPoints2[m * evenum + 12] = bezierShaderPointX2_5;
			trueBezierShaderPoints2[m * evenum + 13] = bezierShaderPointY2_5;
			trueBezierShaderPoints2[m * evenum + 14] = bezierShaderPointZ2_5;
			trueBezierShaderPoints3[m * evenum + 12] = bezierShaderPointX3_5;
			trueBezierShaderPoints3[m * evenum + 13] = bezierShaderPointY3_5;
			trueBezierShaderPoints3[m * evenum + 14] = bezierShaderPointZ3_5;
			trueBezierShaderPoints4[m * evenum + 12] = bezierShaderPointX4_5;
			trueBezierShaderPoints4[m * evenum + 13] = bezierShaderPointY4_5;
			trueBezierShaderPoints4[m * evenum + 14] = bezierShaderPointZ4_5;
			
			float bezierShaderPointX1_6 = bezierShaderPoints1[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY1_6 = bezierShaderPoints1[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ1_6 = bezierShaderPoints1[(i + 1) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX2_6 = bezierShaderPoints2[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY2_6 = bezierShaderPoints2[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ2_6 = bezierShaderPoints2[(i + 1) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX3_6 = bezierShaderPoints3[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY3_6 = bezierShaderPoints3[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ3_6 = bezierShaderPoints3[(i + 1) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX4_6 = bezierShaderPoints4[(i + 1) * 3 + tansverSpanNum1];
			float bezierShaderPointY4_6 = bezierShaderPoints4[(i + 1) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ4_6 = bezierShaderPoints4[(i + 1) * 3 + 2 + tansverSpanNum1];
			
			trueBezierShaderPoints1[m * evenum + 15] = bezierShaderPointX1_6;
			trueBezierShaderPoints1[m * evenum + 16] = bezierShaderPointY1_6;
			trueBezierShaderPoints1[m * evenum + 17] = bezierShaderPointZ1_6;
			trueBezierShaderPoints2[m * evenum + 15] = bezierShaderPointX2_6;
			trueBezierShaderPoints2[m * evenum + 16] = bezierShaderPointY2_6;
			trueBezierShaderPoints2[m * evenum + 17] = bezierShaderPointZ2_6;
			trueBezierShaderPoints3[m * evenum + 15] = bezierShaderPointX3_6;
			trueBezierShaderPoints3[m * evenum + 16] = bezierShaderPointY3_6;
			trueBezierShaderPoints3[m * evenum + 17] = bezierShaderPointZ3_6;
			trueBezierShaderPoints4[m * evenum + 15] = bezierShaderPointX4_6;
			trueBezierShaderPoints4[m * evenum + 16] = bezierShaderPointY4_6;
			trueBezierShaderPoints4[m * evenum + 17] = bezierShaderPointZ4_6;
			

		}

		for (int i = everyNum - 1; i < everyNum; i++)//在一个闭合圈内跳跃几个点
		{

			float fv1 = i*1.0 / everyNum;
			float fv2 = (i + 1)*1.0 / everyNum;
			int m = everyNum * j + i;

			float bezierShaderPointX1_1 = bezierShaderPoints1[i * 3 + tansverSpanNum1];
			float bezierShaderPointY1_1 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ1_1 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX2_1 = bezierShaderPoints2[i * 3 + tansverSpanNum1];
			float bezierShaderPointY2_1 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ2_1 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX3_1 = bezierShaderPoints3[i * 3 + tansverSpanNum1];
			float bezierShaderPointY3_1 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ3_1 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX4_1 = bezierShaderPoints4[i * 3 + tansverSpanNum1];
			float bezierShaderPointY4_1 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ4_1 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum1];
			
			trueBezierShaderPoints1[m * evenum] = bezierShaderPointX1_1;
			trueBezierShaderPoints1[m * evenum + 1] = bezierShaderPointY1_1;
			trueBezierShaderPoints1[m * evenum + 2] = bezierShaderPointZ1_1;
			trueBezierShaderPoints2[m * evenum] = bezierShaderPointX2_1;
			trueBezierShaderPoints2[m * evenum + 1] = bezierShaderPointY2_1;
			trueBezierShaderPoints2[m * evenum + 2] = bezierShaderPointZ2_1;
			trueBezierShaderPoints3[m * evenum] = bezierShaderPointX3_1;
			trueBezierShaderPoints3[m * evenum + 1] = bezierShaderPointY3_1;
			trueBezierShaderPoints3[m * evenum + 2] = bezierShaderPointZ3_1;
			trueBezierShaderPoints4[m * evenum] = bezierShaderPointX4_1;
			trueBezierShaderPoints4[m * evenum + 1] = bezierShaderPointY4_1;
			trueBezierShaderPoints4[m * evenum + 2] = bezierShaderPointZ4_1;
			
			float bezierShaderPointX1_2 = bezierShaderPoints1[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY1_2 = bezierShaderPoints1[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ1_2 = bezierShaderPoints1[(0) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX2_2 = bezierShaderPoints2[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY2_2 = bezierShaderPoints2[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ2_2 = bezierShaderPoints2[(0) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX3_2 = bezierShaderPoints3[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY3_2 = bezierShaderPoints3[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ3_2 = bezierShaderPoints3[(0) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX4_2 = bezierShaderPoints4[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY4_2 = bezierShaderPoints4[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ4_2 = bezierShaderPoints4[(0) * 3 + 2 + tansverSpanNum1];
			
			trueBezierShaderPoints1[m * evenum + 3] = bezierShaderPointX1_2;
			trueBezierShaderPoints1[m * evenum + 4] = bezierShaderPointY1_2;
			trueBezierShaderPoints1[m * evenum + 5] = bezierShaderPointZ1_2;
			trueBezierShaderPoints2[m * evenum + 3] = bezierShaderPointX2_2;
			trueBezierShaderPoints2[m * evenum + 4] = bezierShaderPointY2_2;
			trueBezierShaderPoints2[m * evenum + 5] = bezierShaderPointZ2_2;
			trueBezierShaderPoints3[m * evenum + 3] = bezierShaderPointX3_2;
			trueBezierShaderPoints3[m * evenum + 4] = bezierShaderPointY3_2;
			trueBezierShaderPoints3[m * evenum + 5] = bezierShaderPointZ3_2;
			trueBezierShaderPoints4[m * evenum + 3] = bezierShaderPointX4_2;
			trueBezierShaderPoints4[m * evenum + 4] = bezierShaderPointY4_2;
			trueBezierShaderPoints4[m * evenum + 5] = bezierShaderPointZ4_2;
			
			float bezierShaderPointX1_3 = bezierShaderPoints1[i * 3 + tansverSpanNum2];
			float bezierShaderPointY1_3 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ1_3 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX2_3 = bezierShaderPoints2[i * 3 + tansverSpanNum2];
			float bezierShaderPointY2_3 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ2_3 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX3_3 = bezierShaderPoints3[i * 3 + tansverSpanNum2];
			float bezierShaderPointY3_3 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ3_3 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX4_3 = bezierShaderPoints4[i * 3 + tansverSpanNum2];
			float bezierShaderPointY4_3 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ4_3 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum2];
			
			trueBezierShaderPoints1[m * evenum + 6] = bezierShaderPointX1_3;
			trueBezierShaderPoints1[m * evenum + 7] = bezierShaderPointY1_3;
			trueBezierShaderPoints1[m * evenum + 8] = bezierShaderPointZ1_3;
			trueBezierShaderPoints2[m * evenum + 6] = bezierShaderPointX2_3;
			trueBezierShaderPoints2[m * evenum + 7] = bezierShaderPointY2_3;
			trueBezierShaderPoints2[m * evenum + 8] = bezierShaderPointZ2_3;
			trueBezierShaderPoints3[m * evenum + 6] = bezierShaderPointX3_3;
			trueBezierShaderPoints3[m * evenum + 7] = bezierShaderPointY3_3;
			trueBezierShaderPoints3[m * evenum + 8] = bezierShaderPointZ3_3;
			trueBezierShaderPoints4[m * evenum + 6] = bezierShaderPointX4_3;
			trueBezierShaderPoints4[m * evenum + 7] = bezierShaderPointY4_3;
			trueBezierShaderPoints4[m * evenum + 8] = bezierShaderPointZ4_3;
			
			float bezierShaderPointX1_4 = bezierShaderPoints1[i * 3 + tansverSpanNum2];
			float bezierShaderPointY1_4 = bezierShaderPoints1[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ1_4 = bezierShaderPoints1[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX2_4 = bezierShaderPoints2[i * 3 + tansverSpanNum2];
			float bezierShaderPointY2_4 = bezierShaderPoints2[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ2_4 = bezierShaderPoints2[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX3_4 = bezierShaderPoints3[i * 3 + tansverSpanNum2];
			float bezierShaderPointY3_4 = bezierShaderPoints3[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ3_4 = bezierShaderPoints3[i * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX4_4 = bezierShaderPoints4[i * 3 + tansverSpanNum2];
			float bezierShaderPointY4_4 = bezierShaderPoints4[i * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ4_4 = bezierShaderPoints4[i * 3 + 2 + tansverSpanNum2];
			
			trueBezierShaderPoints1[m * evenum + 9] = bezierShaderPointX1_4;
			trueBezierShaderPoints1[m * evenum + 10] = bezierShaderPointY1_4;
			trueBezierShaderPoints1[m * evenum + 11] = bezierShaderPointZ1_4;
			trueBezierShaderPoints2[m * evenum + 9] = bezierShaderPointX2_4;
			trueBezierShaderPoints2[m * evenum + 10] = bezierShaderPointY2_4;
			trueBezierShaderPoints2[m * evenum + 11] = bezierShaderPointZ2_4;
			trueBezierShaderPoints3[m * evenum + 9] = bezierShaderPointX3_4;
			trueBezierShaderPoints3[m * evenum + 10] = bezierShaderPointY3_4;
			trueBezierShaderPoints3[m * evenum + 11] = bezierShaderPointZ3_4;
			trueBezierShaderPoints4[m * evenum + 9] = bezierShaderPointX4_4;
			trueBezierShaderPoints4[m * evenum + 10] = bezierShaderPointY4_4;
			trueBezierShaderPoints4[m * evenum + 11] = bezierShaderPointZ4_4;

			float bezierShaderPointX1_5 = bezierShaderPoints1[(0) * 3 + tansverSpanNum2];
			float bezierShaderPointY1_5 = bezierShaderPoints1[(0) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ1_5 = bezierShaderPoints1[(0) * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX2_5 = bezierShaderPoints2[(0) * 3 + tansverSpanNum2];
			float bezierShaderPointY2_5 = bezierShaderPoints2[(0) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ2_5 = bezierShaderPoints2[(0) * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX3_5 = bezierShaderPoints3[(0) * 3 + tansverSpanNum2];
			float bezierShaderPointY3_5 = bezierShaderPoints3[(0) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ3_5 = bezierShaderPoints3[(0) * 3 + 2 + tansverSpanNum2];
			float bezierShaderPointX4_5 = bezierShaderPoints4[(0) * 3 + tansverSpanNum2];
			float bezierShaderPointY4_5 = bezierShaderPoints4[(0) * 3 + 1 + tansverSpanNum2];
			float bezierShaderPointZ4_5 = bezierShaderPoints4[(0) * 3 + 2 + tansverSpanNum2];
			
			trueBezierShaderPoints1[m * evenum + 12] = bezierShaderPointX1_5;
			trueBezierShaderPoints1[m * evenum + 13] = bezierShaderPointY1_5;
			trueBezierShaderPoints1[m * evenum + 14] = bezierShaderPointZ1_5;
			trueBezierShaderPoints2[m * evenum + 12] = bezierShaderPointX2_5;
			trueBezierShaderPoints2[m * evenum + 13] = bezierShaderPointY2_5;
			trueBezierShaderPoints2[m * evenum + 14] = bezierShaderPointZ2_5;
			trueBezierShaderPoints3[m * evenum + 12] = bezierShaderPointX3_5;
			trueBezierShaderPoints3[m * evenum + 13] = bezierShaderPointY3_5;
			trueBezierShaderPoints3[m * evenum + 14] = bezierShaderPointZ3_5;
			trueBezierShaderPoints4[m * evenum + 12] = bezierShaderPointX4_5;
			trueBezierShaderPoints4[m * evenum + 13] = bezierShaderPointY4_5;
			trueBezierShaderPoints4[m * evenum + 14] = bezierShaderPointZ4_5;
			
			float bezierShaderPointX1_6 = bezierShaderPoints1[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY1_6 = bezierShaderPoints1[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ1_6 = bezierShaderPoints1[(0) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX2_6 = bezierShaderPoints2[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY2_6 = bezierShaderPoints2[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ2_6 = bezierShaderPoints2[(0) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX3_6 = bezierShaderPoints3[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY3_6 = bezierShaderPoints3[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ3_6 = bezierShaderPoints3[(0) * 3 + 2 + tansverSpanNum1];
			float bezierShaderPointX4_6 = bezierShaderPoints4[(0) * 3 + tansverSpanNum1];
			float bezierShaderPointY4_6 = bezierShaderPoints4[(0) * 3 + 1 + tansverSpanNum1];
			float bezierShaderPointZ4_6 = bezierShaderPoints4[(0) * 3 + 2 + tansverSpanNum1];
			
			trueBezierShaderPoints1[m * evenum + 15] = bezierShaderPointX1_6;
			trueBezierShaderPoints1[m * evenum + 16] = bezierShaderPointY1_6;
			trueBezierShaderPoints1[m * evenum + 17] = bezierShaderPointZ1_6;
			trueBezierShaderPoints2[m * evenum + 15] = bezierShaderPointX2_6;
			trueBezierShaderPoints2[m * evenum + 16] = bezierShaderPointY2_6;
			trueBezierShaderPoints2[m * evenum + 17] = bezierShaderPointZ2_6;
			trueBezierShaderPoints3[m * evenum + 15] = bezierShaderPointX3_6;
			trueBezierShaderPoints3[m * evenum + 16] = bezierShaderPointY3_6;
			trueBezierShaderPoints3[m * evenum + 17] = bezierShaderPointZ3_6;
			trueBezierShaderPoints4[m * evenum + 15] = bezierShaderPointX4_6;
			trueBezierShaderPoints4[m * evenum + 16] = bezierShaderPointY4_6;
			trueBezierShaderPoints4[m * evenum + 17] = bezierShaderPointZ4_6;
			
		}
	}

}

float afterOneMoveLeng = 0.00003;
float afterTwoMoveLeng = 0.00003; 
float afterThreeMoveLeng = 0.00007;
float afterFourMoveLeng = 0.00007;
float afterFiveMoveLeng = 0.00002;
float afterSixMoveLeng = 0.00002;
void Uniform::controlPointMove(int splitNumber, float* splitSqurePoints)
{
	if (isDown)
	{
		Uniform::jellyFishMoveDown();
	}
	else
	{
		Uniform::jellyFishMoveUp();
	}
		
	int pointNum = 3;
	for (int j = 0; j < splitNumber; j++)//切分的个数
	{
		//第三排控制点
		float currPointX = splitSqurePoints[pointNum * splitNumber * 3 + j * 3];
		float currPointY = splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 1];
		float currPointZ = splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 2];

		float afterOnePX = splitSqurePoints[(pointNum + 1) * splitNumber * 3 + j * 3];
		float afterOnePY = splitSqurePoints[(pointNum + 1) * splitNumber * 3 + j * 3 + 1];
		float afterOnePZ = splitSqurePoints[(pointNum + 1) * splitNumber * 3 + j * 3 + 2];
		if (firstVerticalPoints[0] == 0.0 && firstVerticalPoints[1] == 0.0 && firstVerticalPoints[2] == 0.0)
		{
			Uniform::getMiddVectVertPoint(pointNum + 1, j, firstVerticalPoints);
		}
		Uniform::getNewPointByVertVect(firstVerticalPoints, afterOnePX, afterOnePY, afterOnePZ,
			splitSqurePoints, splitNumber, pointNum + 1, afterOneMoveLeng, j);
		///////////////////////////////////////////////////////////////////////////////////////////////////
		float afterTwoPX = splitSqurePoints[(pointNum + 2) * splitNumber * 3 + j * 3];
		float afterTwoPY = splitSqurePoints[(pointNum + 2) * splitNumber * 3 + j * 3 + 1];
		float afterTwoPZ = splitSqurePoints[(pointNum + 2) * splitNumber * 3 + j * 3 + 2];
		if (secondVerticalPoints[0] == 0.0 && secondVerticalPoints[1] == 0.0 && secondVerticalPoints[2] == 0.0)
		{
			Uniform::getMiddVectVertPoint(pointNum + 2, j, secondVerticalPoints);
		}
		Uniform::getNewPointByVertVect(secondVerticalPoints,afterTwoPX,afterTwoPY,afterTwoPZ,
			splitSqurePoints,splitNumber,pointNum + 2,afterTwoMoveLeng,j);
		
		/////////////////////////////////////////////////////////////////////
		float afterThreePX = splitSqurePoints[(pointNum + 3) * splitNumber * 3 + j * 3];
		float afterThreePY = splitSqurePoints[(pointNum + 3) * splitNumber * 3 + j * 3 + 1];
		float afterThreePZ = splitSqurePoints[(pointNum + 3) * splitNumber * 3 + j * 3 + 2];
		if (thirdVerticalPoints[0] == 0.0 && thirdVerticalPoints[1] == 0.0 && thirdVerticalPoints[2] == 0.0)
		{
			Uniform::getMiddVectVertPoint(pointNum + 3, j, thirdVerticalPoints);
		}
		Uniform::getNewPointByVertVect(thirdVerticalPoints, afterThreePX, afterThreePY, afterThreePZ, 
			splitSqurePoints, splitNumber, pointNum + 3, afterThreeMoveLeng, j);
		////////////////////////////////////////////////////////////////////////
		float afterFourPX = splitSqurePoints[(pointNum + 4) * splitNumber * 3 + j * 3];
		float afterFourPY = splitSqurePoints[(pointNum + 4) * splitNumber * 3 + j * 3 + 1];
		float afterFourPZ = splitSqurePoints[(pointNum + 4) * splitNumber * 3 + j * 3 + 2];
		if (fourthVerticalPoints[0] == 0.0 && fourthVerticalPoints[1] == 0.0 && fourthVerticalPoints[2] == 0.0)
		{
			Uniform::getMiddVectVertPoint(pointNum + 4, j, fourthVerticalPoints);
		}
		Uniform::getNewPointByVertVect(fourthVerticalPoints, afterFourPX, afterFourPY, afterFourPZ, 
			splitSqurePoints, splitNumber, pointNum + 4, afterFourMoveLeng, j);
		////////////////////////////////////////////////////////////////////////
		float afterFivePX = splitSqurePoints[(pointNum + 5) * splitNumber * 3 + j * 3];
		float afterFivePY = splitSqurePoints[(pointNum + 5) * splitNumber * 3 + j * 3 + 1];
		float afterFivePZ = splitSqurePoints[(pointNum + 5) * splitNumber * 3 + j * 3 + 2];
		if (fifthVerticalPoints[0] == 0.0 && fifthVerticalPoints[1] == 0.0 && fifthVerticalPoints[2] == 0.0)
		{
			Uniform::getMiddVectVertPoint(pointNum + 5, j, fifthVerticalPoints);
		}
		Uniform::getNewPointByVertVect(fifthVerticalPoints, afterFivePX, afterFivePY, afterFivePZ, 
			splitSqurePoints, splitNumber, pointNum + 5, afterFiveMoveLeng, j);
		////////////////////////////////////////////////////////////////////////
		float afterSixPX = splitSqurePoints[(pointNum + 6) * splitNumber * 3 + j * 3];
		float afterSixPY = splitSqurePoints[(pointNum + 6) * splitNumber * 3 + j * 3 + 1];
		float afterSixPZ = splitSqurePoints[(pointNum + 6) * splitNumber * 3 + j * 3 + 2];
		if (sixthVerticalPoints[0] == 0.0 && sixthVerticalPoints[1] == 0.0 && sixthVerticalPoints[2] == 0.0)
		{
			Uniform::getMiddVectVertPoint(pointNum + 6, j, sixthVerticalPoints);
		}
		Uniform::getNewPointByVertVect(sixthVerticalPoints, afterSixPX, afterSixPY, afterSixPZ, 
			splitSqurePoints, splitNumber, pointNum + 6, afterSixMoveLeng, j);

	}

}



void Uniform::getNewPointByVertVect(float* verticalPoints, float PX, float PY, float PZ, float* splitSqurePoints,
	int splitNumber, int pointNum, float radius, int j)
{

	//if (pointNum == 90)
	//{
	//	float* parr = getPointArray();
	//	float middVectX = parr[3] - parr[0];
	//	float middVectY = parr[4] - parr[1];
	//	float middVectZ = parr[5] - parr[2];
	//	float vectLeng = sqrt(middVectX*middVectX + middVectY*middVectY + middVectZ*middVectZ);
	//	float middVectLeng = vectLeng/2.0;

	//	float middRatio = sqrt(middVectLeng*middVectLeng / (middVectX*middVectX + middVectY*middVectY + middVectZ*middVectZ));

	//	float sepx = verticalPoints[0] - middRatio*middVectX;
	//	float sepy = verticalPoints[1] - middRatio*middVectY;
	//	float sepz = verticalPoints[2] - middRatio*middVectZ;

	//	//垂直于中间线的向量
	//	float vertVectX = -PX + sepx;
	//	float vertVectY = -PY + sepy;
	//	float vertVectZ = -PZ + sepz;
	//	//按垂直向量位移后的点
	//	float ratio = sqrt(radius*radius / (vertVectX*vertVectX + vertVectY*vertVectY + vertVectZ*vertVectZ));
	//	float newPX = PX + ratio*vertVectX;
	//	float newPY = PY + ratio*vertVectY;
	//	float newPZ = PZ + ratio*vertVectZ;

	//	splitSqurePoints[pointNum * splitNumber * 3 + j * 3] = newPX;
	//	splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 1] = newPY;
	//	splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 2] = newPZ;
	//}
	//else
	{
		//垂直于中间线的向量
		float vertVectX;
		float vertVectY;
		float vertVectZ;
		if (isDown)
		{
			vertVectX = -PX + verticalPoints[0];
			vertVectY = -PY + verticalPoints[1];
			vertVectZ = -PZ + verticalPoints[2];
		}
		else
		{
			vertVectX = PX - verticalPoints[0];
			vertVectY = PY - verticalPoints[1];
			vertVectZ = PZ - verticalPoints[2];
		}
		//按垂直向量位移后的点
		float ratio = sqrt(radius*radius / (vertVectX*vertVectX + vertVectY*vertVectY + vertVectZ*vertVectZ));
		float newPX = PX + ratio*vertVectX;
		float newPY = PY + ratio*vertVectY;
		float newPZ = PZ + ratio*vertVectZ;
		
		splitSqurePoints[pointNum * splitNumber * 3 + j * 3] = newPX;
		splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 1] = newPY;
		splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 2] = newPZ;
		
	}

	//生成的新的向量
	/*float currOneVectX = newOnePX - currPointX;
	float currOneVectY = newOnePY - currPointY;
	float currOneVectZ = newOnePZ - currPointZ;
	float currOneRatio = sqrt(one2currLength*one2currLength / (currOneVectX*currOneVectX + currOneVectY*currOneVectY + currOneVectZ*currOneVectZ));
	float currOnePX = currPointX + currOneRatio*currOneVectX;
	float currOnePY = currPointY + currOneRatio*currOneVectY;
	float currOnePZ = currPointZ + currOneRatio*currOneVectZ;*/

}


void Uniform::getMiddVectVertPoint(int planeNum,int cutPointNum,float* verticalPoints)
{
	float* splitSqurePoints = getPointArrayTest4();
	int splitNumber = getSplitNumber();
	float* pointArray = getPointArray();
	//中间向量
	float middVectX = pointArray[3] - pointArray[0];
	float middVectY = pointArray[4] - pointArray[1];
	float middVectZ = pointArray[5] - pointArray[2];

	//顶点到当前点的向量
	float currVectX = splitSqurePoints[planeNum * splitNumber * 3 + cutPointNum * 3] - pointArray[0];
	float currVectY = splitSqurePoints[planeNum * splitNumber * 3 + cutPointNum * 3 + 1] - pointArray[1];
	float currVectZ = splitSqurePoints[planeNum * splitNumber * 3 + cutPointNum * 3 + 2] - pointArray[2];
	//原有点的向量和中间向量夹角的余弦值
	float cosValue = (middVectX * currVectX + middVectY * currVectY + middVectZ * currVectZ) /
		(sqrt(middVectX*middVectX + middVectY*middVectY + middVectZ * middVectZ) *
		sqrt(currVectX * currVectX + currVectY * currVectY + currVectZ * currVectZ));
	//求原有向量长度值
	float vectLength = sqrt(currVectX*currVectX + currVectY*currVectY + currVectZ*currVectZ);
	//在中间向量上的长度
	float middleVectLen = vectLength * cosValue;
	float middleVectRatio = sqrt(middleVectLen * middleVectLen / (middVectX*middVectX +
		middVectY*middVectY + middVectZ*middVectZ));
	//bezier 控制点在中间向量上的垂直点
	float middVectPointX = pointArray[0] + middleVectRatio * middVectX;
	float middVectPointY = pointArray[1] + middleVectRatio * middVectY;
	float middVectPointZ = pointArray[2] + middleVectRatio * middVectZ;
	
	//帧动画前的向量 
	float formerVectX = splitSqurePoints[planeNum * splitNumber * 3 + cutPointNum * 3] - middVectPointX;
	float formerVectY = splitSqurePoints[planeNum * splitNumber * 3 + cutPointNum * 3 + 1] - middVectPointY;
	float formerVectZ = splitSqurePoints[planeNum * splitNumber * 3 + cutPointNum * 3 + 2] - middVectPointZ;
	//bezier 控制点在中间向量上的垂直点
	verticalPoints[0] = middVectPointX;
	verticalPoints[1] = middVectPointY;
	verticalPoints[2] = middVectPointZ;
	
}



//斜向运动
void Uniform::obliqueDirecMotion(float* verticalPoints, int splitNumber,float radius, float PX, float PY, float PZ, int j, bool plusOrMinus)
{
	float* parr = getPointArray();
	float middVectX = parr[3] - parr[0];
	float middVectY = parr[4] - parr[1];
	float middVectZ = parr[5] - parr[2];
	float vectLeng = sqrt(middVectX*middVectX + middVectY*middVectY + middVectZ*middVectZ);
	float middVectLeng = vectLeng / 2.0;

	float middRatio = sqrt(middVectLeng*middVectLeng / (middVectX*middVectX + middVectY*middVectY + middVectZ*middVectZ));

	float sepx = verticalPoints[0] - middRatio*middVectX;
	float sepy = verticalPoints[1] - middRatio*middVectY;
	float sepz = verticalPoints[2] - middRatio*middVectZ;

	//垂直于中间线的向量
	float vertVectX = -PX + sepx;
	float vertVectY = -PY + sepy;
	float vertVectZ = -PZ + sepz;
	//按垂直向量位移后的点
	float ratio = sqrt(radius*radius / (vertVectX*vertVectX + vertVectY*vertVectY + vertVectZ*vertVectZ));
	float newPX = PX + ratio*vertVectX;
	float newPY = PY + ratio*vertVectY;
	float newPZ = PZ + ratio*vertVectZ;
	float* splitSqurePoints = Uniform::getPointArrayTest4();
	splitSqurePoints[pointNum * splitNumber * 3 + j * 3] = newPX;
	splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 1] = newPY;
	splitSqurePoints[pointNum * splitNumber * 3 + j * 3 + 2] = newPZ;
}

//向下帧动画
void Uniform::jellyFishMoveDown()
{
	if (frameNumber < 15)
	{
		afterOneMoveLeng = 0.00001;
		afterTwoMoveLeng = 0.00003;
		afterThreeMoveLeng = 0.00015;
		afterFourMoveLeng = 0.000095;
		afterFiveMoveLeng = 0.0001;
		afterSixMoveLeng = 0.00013;
	}
	else if (frameNumber >= 15 && frameNumber < 30)
	{
		afterOneMoveLeng = 0.00002;
		afterTwoMoveLeng = 0.00007;
		afterThreeMoveLeng = 0.00015;
		afterFourMoveLeng = 0.000095;
		afterFiveMoveLeng = 0.00015;
		afterSixMoveLeng = 0.00018;
	}
	else if (frameNumber >= 30 && frameNumber < 50)
	{
		afterOneMoveLeng = 0.00004;
		afterTwoMoveLeng = 0.00008;
		afterThreeMoveLeng = 0.00015;
		afterFourMoveLeng = 0.0001;
		afterFiveMoveLeng = 0.0003;
		afterSixMoveLeng = 0.00033;
	}
	else if (frameNumber >= 50 && frameNumber < 60)
	{
		afterOneMoveLeng = 0.00001;
		afterTwoMoveLeng = 0.00002;
		afterThreeMoveLeng = 0.0001;
		afterFourMoveLeng = 0.00015;
		afterFiveMoveLeng = 0.0003;
		afterSixMoveLeng = 0.00043;
	}
	else if (frameNumber >= 60 && frameNumber < 70)
	{
		afterOneMoveLeng = 0.00001;
		afterTwoMoveLeng = 0.00002;
		afterThreeMoveLeng = 0.00012;
		afterFourMoveLeng = 0.00015;
		afterFiveMoveLeng = 0.0004;
		afterSixMoveLeng = 0.00058;
	}

	if (frameNumber == 69)
	{
		frameNumber = 0;
		
		isDown = false;
	}
}

void Uniform::jellyFishMoveUp()
{
	if (frameNumber < 15)
	{
		afterOneMoveLeng = 0.00001;
		afterTwoMoveLeng = 0.00003;
		afterThreeMoveLeng = 0.00015;
		afterFourMoveLeng = 0.000095;
		afterFiveMoveLeng = 0.0001;
		afterSixMoveLeng = 0.00013;
	}
	else if (frameNumber >= 15 && frameNumber < 30)
	{
		afterOneMoveLeng = 0.00002;
		afterTwoMoveLeng = 0.00007;
		afterThreeMoveLeng = 0.00015;
		afterFourMoveLeng = 0.000095;
		afterFiveMoveLeng = 0.00015;
		afterSixMoveLeng = 0.00018;
	}
	else if (frameNumber >= 30 && frameNumber < 50)
	{
		afterOneMoveLeng = 0.00004;
		afterTwoMoveLeng = 0.00008;
		afterThreeMoveLeng = 0.00015;
		afterFourMoveLeng = 0.0001;
		afterFiveMoveLeng = 0.0003;
		afterSixMoveLeng = 0.00033;
	}
	else if (frameNumber >= 50 && frameNumber < 60)
	{
		afterOneMoveLeng = 0.00001;
		afterTwoMoveLeng = 0.00002;
		afterThreeMoveLeng = 0.0001;
		afterFourMoveLeng = 0.00015;
		afterFiveMoveLeng = 0.0003;
		afterSixMoveLeng = 0.00043;
	}
	else if (frameNumber >= 60 && frameNumber < 70)
	{
		afterOneMoveLeng = 0.00001;
		afterTwoMoveLeng = 0.00002;
		afterThreeMoveLeng = 0.00012;
		afterFourMoveLeng = 0.00015;
		afterFiveMoveLeng = 0.0004;
		afterSixMoveLeng = 0.00058;
	}

	if (frameNumber == 69)
	{
		frameNumber = 0;
		isDown = true;
	}


}