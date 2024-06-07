#pragma once
#include "GameObject.h"

class BaseState
{
public:
	BaseState();
	virtual ~BaseState() = default;
	//virtual void HandleInput()


	virtual void Update(float) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

};

