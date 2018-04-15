#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <GL/glew.h>

class Shape
{
    friend class Orthographic;
public:
    Shape();
    ~Shape();
    void initialise(
        const GLfloat *vertexData,
        const GLfloat *textureData,
        const GLuint *indexData,
        GLsizei v_count,
        GLsizei i_count);
    void square(
        GLfloat x,
        GLfloat y,
        GLfloat width,
        GLfloat height);
private:
    GLuint vertexBuffer;
    GLuint textureBuffer;
    GLuint indexBuffer;
    GLsizei size;
};

#endif