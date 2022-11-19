#pragma once
#include "GameState.h"

class GameStateSim : public GameState
{
private:
public:
	GameStateSim(View*);
	~GameStateSim();
	void execute();
};

