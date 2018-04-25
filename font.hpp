#ifndef FONT_HPP
#define FONT_HPP

#include <SDL2/SDL_ttf.h>
#include "texture.hpp"

class Font
{
    friend class Sprite;
public:
    Font();
    ~Font();
    bool load(const char path[], int size);
    bool render(Texture &texture, const char string[]);
private:
    TTF_Font *font;
};


#endif