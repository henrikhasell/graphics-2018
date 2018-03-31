#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <GL/glew.h>
#include "shader.hpp"

class Program
{
public:
    Program();
    ~Program();
    bool link(const Shader &a, const Shader &b) const;
    bool linkStatus() const;
    std::string infoLog() const;
    GLuint getUniformLocation(const char name[]) const;
    void bindAttributeLocation(GLuint index, const char name[]) const;
    void use() const;
private:
    GLuint program;
};

#endif