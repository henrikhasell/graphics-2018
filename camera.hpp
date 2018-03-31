#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <SDL2/SDL.h>

struct Camera
{
	Camera();

	void handle(const SDL_MouseMotionEvent &motion);
	void handle(const Uint8 *keyboard);
	void look(float x, float y, float z);

    glm::mat4 matrix() const;
	glm::vec3 forward() const;

	glm::vec3 position;
	float pitch;
	float yaw;
};

#endif