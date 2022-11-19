#pragma once
#include <thread>
#include <chrono>
#include <iostream>

class View
{
private:
	float fps;
	bool isRunning;
public:
	View();
	~View();

	void update();
	void run();
	std::thread start();
};

