#include "camera.hpp"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() : position(3.0f, 3.0f, 3.0f), pitch(0), yaw(0)
{
    look(0.0f, 0.0f, 0.0f);
}

void Camera::handle(const SDL_MouseMotionEvent &motion)
{
    if(SDL_GetRelativeMouseMode() == SDL_TRUE)
    {
        constexpr float sensitivity = 0.005f;

        const float xAmount = (float)motion.xrel * sensitivity;
        const float yAmount = (float)motion.yrel * sensitivity;

        constexpr auto varPitch = (float)(M_PI_2 - 0.0001);
        constexpr auto minPitch = -varPitch;
        constexpr auto maxPitch = +varPitch;

        pitch -= yAmount;

        if(pitch > maxPitch)
        {
            pitch = maxPitch;
        }
        else if(pitch < minPitch)
        {
            pitch = minPitch;
        }

        yaw -= xAmount;
    }
}

void Camera::handle(const Uint8 *keyboard)
{
    constexpr float speed = 0.1f;

    glm::vec3 direction(0.0f, 0.0f, 0.0f);

    if(keyboard[SDL_SCANCODE_W])
    {
        direction += forward();
    }
    if(keyboard[SDL_SCANCODE_S])
    {
        direction -= forward();
    }
    if(keyboard[SDL_SCANCODE_A])
    {
        direction.x += cos(yaw);
        direction.z -= sin(yaw);
    }
    if(keyboard[SDL_SCANCODE_D])
    {
        direction.x -= cos(yaw);
        direction.z += sin(yaw);
    }

    if(direction.x != 0.0f || direction.y != 0.0f || direction.z != 0.0f)
    {
        position += glm::normalize(direction) * speed;
    }
}

void Camera::look(float x, float y, float z)
{
    const float xDiff = x - position.x;
    const float zDiff = z - position.z;
    const float yDiff = y - position.y;

    const float hDiff = sqrtf(xDiff * xDiff + zDiff * zDiff);

    pitch = atan2f(yDiff, hDiff);
    yaw = atan2f(xDiff, zDiff);
}

glm::mat4 Camera::matrix() const
{
    return glm::lookAt(position, position + forward(), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::forward() const
{
    return glm::vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
}