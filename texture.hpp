#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>

class Texture
{
public:
    Texture(GLfloat r, GLfloat g, GLfloat b);
    Texture();
    ~Texture();
    bool load(const char path[], bool gamma_correction = true);
    bool load(SDL_Surface *surface, bool gamma_correction = true);
    void colour(GLfloat r, GLfloat g, GLfloat b);
    void bind(GLenum texture = GL_TEXTURE0) const;
    int getW();
    int getH();
private:
    GLuint texture;
    int w;
    int h;
};

#endif // TEXTURE_HPP