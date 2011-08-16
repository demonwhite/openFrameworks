/*
 Copyright 2009 Johannes Vuorinen
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at 
 
 http://www.apache.org/licenses/LICENSE-2.0 
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "OpenGLES20Implementation.h"
#ifndef __ANDROID__
	#include <OpenGLES/ES2/gl.h>
	#include <OpenGLES/ES2/glext.h>
#else
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#endif
#include <stdlib.h>
#include "OpenGLESMath.h"

using namespace OpenGLES::OpenGLES2;

OpenGLES20Implementation::OpenGLES20Implementation() : OpenGLESImplementation()
{
	
}

OpenGLES20Implementation::~OpenGLES20Implementation()
{
	
}

void OpenGLES20Implementation::init() 
{	
	
	// Initialising these variables as otherwise they will be pointing 
	// randomly into memory if glGetIntegerv fails for whatever reason
	// http://stackoverflow.com/questions/6594214/glgetintegerv-returning-garbage-value
	colorReadFormat 				= -1;
	colorReadType					= -1;
	maxCombinedTextureImageUnits 	= -1;
	maxCubeMapTextureSize 			= -1;
	maxFragmentUniformVectors 		= -1;
	maxRenderBufferSize 			= -1;
	maxTextureImageUnits 			=  3; // this value is used later to initialise a matrix stack, will crash is it is < 0
	maxTextureSize 					= -1;
	maxVaryingVectors 				= -1;
	maxVertexAttribs 				= -1;
	maxVertexTextureImageUnits 		= -1;
	maxVertexUniformVectors 		= -1;
	maxViewportDims[0] 				= -1;
	maxViewportDims[1] 				= -1;	
	numCompressedTextureFormats 	= -1;
	numShaderBinaryFormats 			= -1;
	shaderCompilerSupported 		= false;
	depthBits 						= -1;
	stencilBits 					= -1;	
	
	glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &colorReadFormat);
	glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &colorReadType);
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombinedTextureImageUnits);
	maxCombinedTextureImageUnits = std::min(3, maxCombinedTextureImageUnits); // TODO: currently shaders support 3 textures
	glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &maxCubeMapTextureSize);
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &maxFragmentUniformVectors);
	
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderBufferSize);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
	maxTextureImageUnits = std::min(3, maxTextureImageUnits); // TODO: currently shaders support 3 textures
	glGetIntegerv(GL_MAX_VARYING_VECTORS, &maxVaryingVectors);
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureImageUnits);
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertexUniformVectors);
	
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, maxViewportDims);
	glGetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS, &numCompressedTextureFormats);
	glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &numShaderBinaryFormats);
	shaderBinaryFormats = (int *)malloc(sizeof(int) * numShaderBinaryFormats);
	glGetIntegerv(GL_SHADER_BINARY_FORMATS, shaderBinaryFormats);
	
	unsigned char tmp = 0;
	glGetBooleanv(GL_SHADER_COMPILER, &tmp);
	shaderCompilerSupported = tmp == 0;
	
	glGetIntegerv(GL_DEPTH_BITS, &depthBits);
	glGetIntegerv(GL_STENCIL_BITS, &stencilBits);
	
	print();
}
