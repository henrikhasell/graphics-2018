#include "shape.hpp"

Shape::Shape()
{
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &textureBuffer);
	glGenBuffers(1, &indexBuffer);
}

Shape::~Shape()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &textureBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

void Shape::initialise(
	const GLfloat *vertexData,
	const GLfloat *textureData,
	const GLuint *indexData,
	GLsizei v_count,
	GLsizei i_count)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 2, vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, v_count * sizeof(GLfloat) * 2, textureData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, i_count * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	size = i_count;
}

void Shape::square(
        GLfloat x,
        GLfloat y,
        GLfloat width,
        GLfloat height)
{
    const GLfloat vertexData[4 * 2] = {
            x,         y,          // Top left.
            x + width, y,          // Top right.
            x,         y + height, // Bottom left.
            x + width, y + height  // Bottom right.
    };

    const GLfloat textureData[4 * 2] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
    };

    const GLuint indexData[4] = {
            0, 2, 1, 3
    };

    initialise(vertexData, textureData, indexData, 4, 4);
    drawingMode = GL_TRIANGLE_STRIP;
}

void Shape::outline(
        GLfloat x,
        GLfloat y,
        GLfloat width,
        GLfloat height)
{
    const GLfloat vertexData[4 * 2] = {
            x,         y,          // Top left.
            x + width, y,          // Top right.
            x,         y + height, // Bottom left.
            x + width, y + height  // Bottom right.
    };

    const GLfloat textureData[4 * 2] = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f
    };

    const GLuint indexData[4] = {
            0, 1, 3, 2
    };

    initialise(vertexData, textureData, indexData, 4, 6);
    drawingMode = GL_LINE_LOOP;
}