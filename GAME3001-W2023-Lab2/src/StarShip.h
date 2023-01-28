#pragma once
#ifndef __STARSHIP__
#define __STARSHIP__

#include "Agent.h"
class StarShip : public Agent // Changed type
{
public:
	//constructor Functions
	StarShip();

	//destructor Function
	~StarShip();

	//lifecyckle functions
	void Draw() override;
	void Update() override;
	void Clean() override;

private:

};

#endif /* defined (__STARSHIP__)*/
