#include "StarShip.h"
#include "TextureManager.h"

StarShip::StarShip()
{
	TextureManager::Instance().Load("../Assets/textures/ncl.png", "starship");

	const auto size = TextureManager::Instance().GetTextureSize("starship");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::AGENT);

	// Starting Motion Properties
	m_maxSpeed = 50.0f; // a maximim number of pixels moved per frame
	m_turnRate = 5.0f; // a maximim number of degree to turn each time-step
	m_accelerationRate = 4.0f; // a maximum number of pixels to add to the velocity each frame

	SetCurrentDirection(glm::vec2(1.0f, 0.0f)); // Facing right

}

StarShip::~StarShip()
= default;

void StarShip::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("starship", 
		GetTransform()->position, static_cast<double>(GetCurrentHeading()), 255, true);
}
void StarShip::Update()
{
	
}
void StarShip::Clean()
{
	
}

float StarShip::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float StarShip::GetTurnRate() const
{
	return m_turnRate;
}

float StarShip::GetAccelerationRate() const
{
	return m_accelerationRate;
}

glm::vec2 StarShip::GetDesiredVelocity() const
{
	return m_desiredVelocity;
}

void StarShip::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

void StarShip::SetTurnRate(float angle)
{
	m_turnRate = angle;
}

void StarShip::SetAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void StarShip::SetDesiredVelocity(glm::vec2 target_position)
{

}

void StarShip::Seek()
{
}

void StarShip::LookWhereYoureGoing(glm::vec2 target_direction)
{
}

void StarShip::m_move()
{
}

