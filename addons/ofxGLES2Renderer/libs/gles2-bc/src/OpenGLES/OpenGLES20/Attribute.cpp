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

#include "Attribute.h"
#include "ShaderProgram.h"

using namespace OpenGLES::OpenGLES2;

AttributeSimple::AttributeSimple(int id, GLint location) : id(id), location(location)
{

}

const GLint AttributeSimple::getLocation()
{
	return location;
}

const int AttributeSimple::getId()
{
	return id;
}

Attribute::Attribute() : location(-1), enabled(false), uploaded(false)
{
	bufferId = -1;	
}
Attribute::~Attribute()
{
}

const GLint Attribute::getLocation()
{
	return location;
}

void Attribute::setEnabled( bool e ) 
{
	enabled = e;
}

void Attribute::setLocation( GLint loc )
{
	location = loc;
}

void Attribute::upload(ShaderProgram *program)
{
	if (enabled) {
		glEnableVertexAttribArray(location);
		if (!uploaded) {
			
			if( bufferId > 0) { // could we have a buffer ID that is 0? This could introduce a bug, maybe change bufferID to a signed int and then convert
				//cout << "binding buffer " << bufferId << endl;		
				glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			}
			
			program->setAttributeVertexPointer(location, size, type, normalized, stride, pointer);
			uploaded = true;
		}
	} else {
		glDisableVertexAttribArray(location);
	}
}


void Attribute::setVertexAttribPointer( GLint _otherLocation ){
	
	glEnableVertexAttribArray(_otherLocation);
	glVertexAttribPointer(_otherLocation, size, type, normalized, stride, pointer);
}			


void Attribute::setValues( GLint s, GLenum t, GLsizei st, const void *p, GLuint _bufferId )
{
	size = s;
	type = t;
	stride = st;
	pointer = p;
	normalized = GL_FALSE;
	bufferId = _bufferId;
	uploaded = false;
}

void Attribute::setSize( GLint s )
{
	size = s;
}

void Attribute::setType( GLenum t )
{
	type = t;
}

void Attribute::setNormalized( GLboolean n )
{
	normalized = n;
}

void Attribute::setStride( GLsizei s )
{
	stride = s;
}

void Attribute::setPointer( const void *p )
{
	pointer = p;
}
