#pragma once
#ifndef _SQUARE_H_
#define _SQUARE_H_

#include "Engine.h"

class Square
{
public:
	virtual void init(int, int) = 0;
	virtual void handle_event() = 0;
	virtual void show() = 0;
	virtual ~Square(){};
};
#endif