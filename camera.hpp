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
	/* It would be nice to have a projection class that remembers the state of the projection matrix and
	 * stores the viewport. This class would have the unProject/project methods instead of the Camera
	 * class. This would greatly improve the computational efficiency and also dryness of the project/unProject code. */
    glm::vec3 unProject(const glm::vec2 &position, const glm::vec4 &viewport) const;
    glm::vec2 project(const glm::vec3 &position, const glm::vec4 &viewport) const;

	glm::vec3 position;
	float pitch;
	float yaw;
};

#endif