#pragma once
#ifndef __TARGET__
#define __TARGET__

#include "Agent.h"

class Target final : public Agent
{
public:
	Target();
	~Target() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

private:
	void Move();
	void CheckBounds();
	void Reset();
};


#endif /* defined (__TARGET__) */