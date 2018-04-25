#include "font.hpp"
#include <iostream>

Font::Font() : font(nullptr)
{

}

Font::~Font()
{
    if(font)
    {
        TTF_CloseFont(font);
    }
}

bool Font::load(const char path[], int size)
{
    if(font)
    {
        TTF_CloseFont(font);
    }

    font = TTF_OpenFont(path, size);

    if(font == nullptr)
    {
        std::cerr << "Failed to load " << path << ": " << TTF_GetError() << std::endl;
    }

    return font != nullptr;
}

bool Font::render(Texture &texture, const char string[])
{
    SDL_Colour colour;

    colour.r = 0xff;
    colour.g = 0xff;
    colour.b = 0xff;
    colour.a = 0xff;

    SDL_Surface *surface = TTF_RenderText_Blended(font, string, colour);

    if(surface)
    {
        texture.load(surface);
    }

    return surface != nullptr;
}
