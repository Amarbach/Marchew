#include "View.h"

View::View()
{
	this->fps = 30.0f;
	this->isRunning = false;
}

View::~View()
{
}

void View::update() 
{
	//drawing frame goes here, ~30fps
	
}

void View::run()
{
	std::chrono::steady_clock::time_point lastFrame = std::chrono::steady_clock::now();
	while (isRunning) 
	{
		long timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFrame).count();
		if (timeElapsed > 1 / fps * 1000)
		{
			update();
			lastFrame = std::chrono::steady_clock::now();
		}
	}
}

std::thread View::start()
{
	this->isRunning = true;
	return std::thread(&View::run, this);
}
