#pragma once
#ifndef __STARSHIP__
#define __STARSHIP__
#include "DisplayObject.h"
class StarShip : public DisplayObject
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

#endif
