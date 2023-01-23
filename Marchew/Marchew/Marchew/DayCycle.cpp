#include "DayCycle.h"
#include <iostream>

DayCycle::DayCycle()
{
	this->dayLength = 86400.0f;
	this->daySecond = 0.0f;
	this->timeScale = 60.0f;
	this->sunrise = 5.0f * 3600.0f;
	this->sunset = dayLength - 4.0f * 3600.0f;
}

void DayCycle::setTimeScale(float scale)
{
	this->timeScale = scale;
}

void DayCycle::setDayLength(float length)
{
	this->dayLength = length;
}

void DayCycle::setSunrise(float sunrise)
{
	this->sunrise = sunrise * 3600.0f;
}
void DayCycle::setSunset(float sunset)
{
	this->sunset = sunset * 3600.0f;
}
void DayCycle::update(float elapsed)
{
	daySecond += elapsed * timeScale;
	if (daySecond > dayLength) daySecond = 0.0f;
}
glm::vec3 DayCycle::getSunDirection()
{
	glm::vec3 ret = glm::vec3(cos((daySecond - (dayLength / 4.0f)) / (dayLength) * 2 * M_PI), sin((daySecond - (dayLength / 4.0f)) / (dayLength) * 2 * M_PI), 0.0f);
	if (this->isDay()) return ret;
	else return -ret;
}
bool DayCycle::isDay() 
{
	return (daySecond > sunrise && daySecond < sunset);
}
glm::vec3 DayCycle::getLightColor()
{
	glm::vec3 ret;
	float intensity = 0.3f;
	if (this->isDay())
	{
		intensity += 0.7f * (float)(((sin((daySecond - sunrise) / (sunset - sunrise) * M_PI)) + 1.0f) / 2.0f);
		ret = glm::vec3(1.0f, 1.0f, 1.0f) * intensity;
	}
	else 
	{
		intensity += 0.145f;
		ret = glm::vec3(0.95f, 0.95f, 1.0f) * intensity;
	}
	return ret;
}
