#include "sprite.hpp"
#include <glm/gtc/matrix_transform.hpp>

bool Sprite::text(Font &font, const char format[])
{
	bool success = font.render(texture, format);

    if(success)
    {
        shape.square(0, 0, texture.getW(), texture.getH());
    }

    return success;
}

glm::mat4 Sprite::modelMatrix() const
{
	return glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
}