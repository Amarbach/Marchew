#pragma once
#include "View.h"
#include <iostream>

class GameState
{
private:
	View *view;
protected:
	GameState(View*);
public: 
	virtual void execute() { };
	virtual ~GameState();
};

