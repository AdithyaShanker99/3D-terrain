#include "buffers.h"


Buffer::Buffer(void* data, unsigned int size)
{
	this->initialize_buffer_(data, size);
}

Buffer::~Buffer()
{
	Error_check(glDeleteBuffers(1, &Object_ID_));
}


void Buffer::Bind(GLenum bufferType)
{
	Error_check(glBindBuffer(GL_ARRAY_BUFFER, Object_ID_));
}

void Buffer::unBind(GLenum bufferType)
{
	Error_check(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


Element_buffer::Element_buffer(unsigned int* data, unsigned int size)
{
	
	Error_check(glGenBuffers(1, &Object_ID_));

	Error_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Object_ID_));

	Error_check(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Element_buffer::~Element_buffer()
{
	if(Object_ID_ != 0)	Error_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Object_ID_));	Error_check(glDeleteBuffers(1, &Object_ID_));

}


void Element_buffer::Bind()
{
	Error_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Object_ID_));
}

void Element_buffer::unBind()
{
	Error_check(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
