#include "program.hpp"
#include <vector>

Program::Program()
{
    program = glCreateProgram();
}

Program::~Program()
{
    glDeleteProgram(program);
}

bool Program::link(const Shader &a, const Shader &b) const
{
    glAttachShader(program, a.shader);
    glAttachShader(program, b.shader);
    glLinkProgram(program);
    return linkStatus();
}

bool Program::linkStatus() const
{
    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    return result == GL_TRUE;
}

std::string Program::infoLog() const
{
    GLint length;
    glGetShaderiv(program, GL_INFO_LOG_LENGTH, &length);

    std::vector<char> buffer(length + 1);
    glGetProgramInfoLog(program, length, NULL, buffer.data());
    return std::string(buffer.data());
}

GLuint Program::getUniformLocation(const char name[]) const
{
    return glGetUniformLocation(program, name);
}


void Program::bindAttributeLocation(GLuint index, const char name[]) const
{
    glBindAttribLocation(program, index, name);
}

void Program::use() const
{
    glUseProgram(program);
}