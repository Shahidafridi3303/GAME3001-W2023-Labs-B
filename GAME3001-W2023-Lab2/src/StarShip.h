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

	// getters and setters (accessor and mutator)
	float GetMaxSpeed() const;
	float GetTurnRate() const;
	float GetAccelerationRate() const;
	glm::vec2 GetDesiredVelocity() const;

	void SetMaxSpeed(float speed);
	void SetTurnRate(float angle);
	void SetAccelerationRate(float rate);
	void SetDesiredVelocity(glm::vec2 target_position);

	// public functions
	void Seek();
	void LookWhereYoureGoing(glm::vec2 target_direction);

private:
	// private movement variables
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	// where we want to go
	glm::vec2 m_desiredVelocity;

	// private function
	void m_move();
};

#endif /* defined (__STARSHIP__)*/
