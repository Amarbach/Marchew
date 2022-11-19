#include "Game.h"
#include <stack>
#include "GameStateSim.h"

Game::Game()
{
	stateMachine = std::stack<GameState*>();
	view = View();
	isRunning = true;
	stateMachine.push(new GameStateSim(&view));
}

Game::~Game()
{
	while (!stateMachine.empty()) 
	{
		delete stateMachine.top();
		stateMachine.pop();
	}
}

void Game::Run()
{
	std::thread viewThread = view.start();
	while (isRunning) 
	{
		if (!stateMachine.empty()) stateMachine.top()->execute();
		else isRunning = false;
	}
	viewThread.join();
}
