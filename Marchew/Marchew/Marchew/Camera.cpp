#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov, float near, float far, float viewPortHeight, float viewPortWidth, ProjectionType type)
{
	this->position = position;
	this->front = front;
	this->up = up;
	this->fov = fov;
	this->near = near;
	this->far = far;
	this->viewPortHeight = viewPortHeight;
	this->viewPortWidth = viewPortWidth;
	this->type = type;
	this->yaw = -90.0f;
	this->pitch = 0.0f;
}

void Camera::orient(float deltaYaw, float deltaPitch)
{
	this->yaw += deltaYaw;
	this->pitch += deltaPitch;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(newFront);
}

glm::mat4 Camera::getProjectionMtx()
{
	switch (type) {
	default: return glm::perspective(glm::radians(fov), viewPortWidth / viewPortHeight, near, far);
	case PERSPECTIVE: return glm::perspective(glm::radians(fov), viewPortWidth / viewPortHeight, near, far);
	case ORTHOGONAL: return glm::ortho(position.x - (viewPortWidth / 2.0f), position.x + (viewPortWidth / 2.0f), position.y - (viewPortHeight / 2.0f), position.y + (viewPortHeight / 2.0f));
	}
}

glm::mat4 Camera::getViewMtx()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::translate(glm::vec3 displacement)
{
	this->position += displacement;
}

void Camera::translate(float x, float y, float z)
{
	glm::vec3 displacement = glm::vec3(x, y, z);
	this->position += displacement;
}
