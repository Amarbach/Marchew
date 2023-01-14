#pragma once
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

enum ProjectionType {PERSPECTIVE, ORTHOGONAL};

class Camera
{
private:
	glm::vec3 position,	front, up;
	float fov, yaw, pitch, near, far, viewPortHeight, viewPortWidth;
	ProjectionType type;

public:
	Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, float fov, float near, float far, float viewPortHeight, float viewPortWidth, ProjectionType type);
	void orient(float deltaYaw, float deltaPitch);
	glm::mat4 getProjectionMtx();
	glm::mat4 getViewMtx();
	void translate(glm::vec3 displacement);
	void translate(float x, float y, float z);
	void moveForward(float displacement);
	void moveSide(float displacement);
	void moveUp(float displacement);
	glm::vec3 getPosition();
};

