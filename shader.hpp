#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <GL/glew.h>

class Shader
{
	friend class Program;
public:
    Shader(GLenum type);
    ~Shader();
    bool load(const char path[]) const;
    bool compile(std::string source) const;
    bool compileStatus() const;
    std::string infoLog() const;
private:
    GLuint shader;
};

#endif