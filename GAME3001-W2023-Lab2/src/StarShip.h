#pragma once
#ifndef __STARSHIP__
#define __STARSHIP__

#include "DisplayObject.h"
class StarShip : public DisplayObject
{
public:
	// Constructor Function
	StarShip();

	//Destructor Function
	~StarShip();

	// LifeCycle Functions
	void Draw() override;
	void Update() override;
	void Clean() override;

private:

};

#endif /* defined ( STARSHIP )*/
