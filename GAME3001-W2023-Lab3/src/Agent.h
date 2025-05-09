#pragma once
#ifndef __AGENT__
#define __AGENT__

#include <glm/vec4.hpp>
#include "NavigationObject.h"

class Agent : public NavigationObject
{
public:
	Agent();
	~Agent();

	// Inherited via GameObject
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	// getters
	[[nodiscard]] glm::vec2 GetTargetPosition() const;
	[[nodiscard]] glm::vec2 GetCurrentDirection() const;
	[[nodiscard]] float GetLOSDistance() const;
	[[nodiscard]] bool HasLOS() const;
	[[nodiscard]] float GetCurrentHeading() const;
	[[nodiscard]] glm::vec4 GetLOSColour() const;

	[[nodiscard]] glm::vec2 GetLeftLOSEndPoint() const;
	[[nodiscard]] glm::vec2 GetMiddleLOSEndPoint() const;
	[[nodiscard]] glm::vec2 GetRightLOSEndPoint() const;
	[[nodiscard]] glm::vec2 GetLeftleftLOSEndPoint() const;
	[[nodiscard]] glm::vec2 GetRightrightLOSEndPoint() const;
	bool* GetCollisionWhiskers(); // return the entire array
	glm::vec4 GetLineColour(int index) const;
	float GetWhiskerAngle() const;

	// setters
	void SetTargetPosition(glm::vec2 new_position);
	void SetCurrentDirection(glm::vec2 new_direction);
	void SetLOSDistance(float distance);
	void SetHasLOS(bool state);
	void SetCurrentHeading(float heading);
	void SetLOSColour(glm::vec4 colour);

	void SetLeftLOSEndPoint(glm::vec2 point);
	void SetMiddleLOSEndPoint(glm::vec2 point);
	void SetRightLOSEndPoint(glm::vec2 point);
	void SetLeftleftLOSEndPoint(glm::vec2 point);
	void SetRightrightLOSEndPoint(glm::vec2 point);
	void SetLineColour(int index, glm::vec4 colour);
	void SetWhiskerAngle(float angle);

	// Utility function
	void UpdateWhiskers(float angle);

private:
	void ChangeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

	// LOS
	float m_LOSDistance;
	bool m_hasLOS;
	glm::vec4 m_LOSColour;

	// Whiskers
	glm::vec2 m_leftLOSEndPoint;
	glm::vec2 m_middLeLOSEndPoint;
	glm::vec2 m_rightLOSEndPoint;
	glm::vec2 m_leftleftLOSEndPoint;
	glm::vec2 m_rightrightLOSEndPoint;
	glm::vec4 m_lineColour[5];
	bool m_collisionWhiskers[5];
	float m_whiskerAngle;

};



#endif /* defined ( __AGENT__) */