#pragma once
#include "include/glm/glm.hpp"

# define M_PI 3.14159265358979323846

class DayCycle
{
private:
	float dayLength;
	float timeScale;
	float daySecond;
	float sunrise, sunset;

public:
	DayCycle();
	void setTimeScale(float);
	void setDayLength(float);
	void setSunrise(float);
	void setSunset(float);
	void update(float);
	glm::vec3 getSunDirection();
	bool isDay();
	glm::vec3 getLightColor();
};

