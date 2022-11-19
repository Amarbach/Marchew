#pragma once
#include "GameState.h"
#include "GameStateSim.h"
#include "View.h"
#include <stack>

class Game
{
private:
	std::stack<GameState*> stateMachine;
	View view;
	bool isRunning;

public:
	Game();
	~Game();
	void Run();

};

