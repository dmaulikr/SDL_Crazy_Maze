#pragma once
#ifndef _STATE_H_INCLUDED_
#define _STATE_H_INCLUDED_

#include "Engine.h"
#include "ChangeState.h"

class State
{
public:
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void handle_event()= 0;
	virtual ~State(){};
};

#endif