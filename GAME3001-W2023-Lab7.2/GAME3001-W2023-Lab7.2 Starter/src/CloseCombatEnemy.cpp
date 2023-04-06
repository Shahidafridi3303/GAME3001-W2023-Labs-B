#include "CloseCombatEnemy.h"

#include "EventManager.h"
#include "Game.h"
#include "TextureManager.h"
#include "Util.h"

CloseCombatEnemy::CloseCombatEnemy() : m_maxSpeed(20.0f),
m_turnRate(5.0f), m_accelerationRate(2.0f), m_startPosition(glm::vec2(300.0f, 500.0f))
{
	TextureManager::Instance().Load("../Assets/textures/d7_small.png", "close_combat_enemy");

	const auto size = TextureManager::Instance().GetTextureSize("close_combat_enemy");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->bounds = glm::vec2(GetWidth(), GetHeight());
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	setIsCentered(true);
	SetType(GameObjectType::AGENT);

	SetCurrentHeading(0.0f); // Current facing angle
	SetLOSDistance(400.0f);
	SetWhiskerAngle(45.0f);
	SetLOSColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Default LOS Colour = Red

	// New for Lab 7.1
	SetActionState(ActionState::NO_ACTION);
	m_buildPatrolPath();

	// New for Lab 7.2
	m_tree = new DecisionTree(this); // Create a new Tree - AI Brain
	m_buildTree();
	m_tree->Display();
}

CloseCombatEnemy::~CloseCombatEnemy()
= default;

void CloseCombatEnemy::Draw()
{
	// draw the CloseCombatEnemy
	TextureManager::Instance().Draw("close_combat_enemy", 
		GetTransform()->position, static_cast<double>(GetCurrentHeading()), 255, true);

	if(EventManager::Instance().IsIMGUIActive())
	{
		// draw the LOS Line
		Util::DrawLine(GetTransform()->position + GetCurrentDirection() * 0.5f * static_cast<float>(GetWidth()),
			GetMiddleLOSEndPoint(), GetLOSColour());
	}
}

void CloseCombatEnemy::Update()
{
	// Determine which action to perform
	m_tree->MakeDecision()
}

void CloseCombatEnemy::Clean()
{
}

float CloseCombatEnemy::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float CloseCombatEnemy::GetTurnRate() const
{
	return m_turnRate;
}

float CloseCombatEnemy::GetAccelerationRate() const
{
	return m_accelerationRate;
}

glm::vec2 CloseCombatEnemy::GetDesiredVelocity() const
{
	return m_desiredVelocity;
}

void CloseCombatEnemy::SetMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void CloseCombatEnemy::SetTurnRate(const float angle)
{
	m_turnRate = angle;
}

void CloseCombatEnemy::SetAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void CloseCombatEnemy::SetDesiredVelocity(const glm::vec2 target_position)
{
	m_desiredVelocity = Util::Normalize(target_position - GetTransform()->position);
}

void CloseCombatEnemy::Seek()
{
	// New for Lab 7.1
	// Find Next Waypoint if within 10px of the current waypoint

	if(Util::Distance(m_patrolPath[m_wayPoint], GetTransform()->position) < 10)
	{
		// check to see if you are at the last point in the path
		if(++m_wayPoint == m_patrolPath.size())
		{
			// if so..reset
			m_wayPoint = 0;
		}
		SetTargetPosition(m_patrolPath[m_wayPoint]);
	}

	SetDesiredVelocity(GetTargetPosition());

	const glm::vec2 steering_direction = GetDesiredVelocity() - GetCurrentDirection();

	LookWhereYoureGoing(steering_direction);

	GetRigidBody()->acceleration = GetCurrentDirection() * GetAccelerationRate();
}

void CloseCombatEnemy::LookWhereYoureGoing(const glm::vec2 target_direction)
{
	float target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction) -90.0f;

	const float last_rotation = target_rotation;

	constexpr float turn_sensitivity = 3.0f;

	if(target_rotation < 0)
	{
		target_rotation += 180.0f;
	}

	if(target_rotation > 176.0f && target_rotation < 184.0f)
	{
		target_rotation = last_rotation;
	}

	if(GetCollisionWhiskers()[0] || GetCollisionWhiskers()[1] || GetCollisionWhiskers()[2])
	{
		target_rotation += GetTurnRate() * turn_sensitivity;
	}
	else if(GetCollisionWhiskers()[3] || GetCollisionWhiskers()[4])
	{
		target_rotation -= GetTurnRate() * turn_sensitivity;
	}

	SetCurrentHeading(Util::LerpUnclamped(GetCurrentHeading(), 
		GetCurrentHeading() + target_rotation, GetTurnRate() * Game::Instance().GetDeltaTime()));

	UpdateWhiskers(GetWhiskerAngle());
}

void CloseCombatEnemy::Reset()
{
	GetTransform()->position = m_startPosition;
}

void CloseCombatEnemy::Patrol()
{
	if(GetActionState() != ActionState::PATROL)
	{
		// Initialize the Action
		SetActionState(ActionState::PATROL);
	}
	m_move();
}

void CloseCombatEnemy::MoveToPlayer()
{
	if (GetActionState() != ActionState::MOVE_TO_PLAYER)
	{
		// Initialize the Action
		SetActionState(ActionState::MOVE_TO_PLAYER);
	}
	//TODO: setup another action to take when moving to the player
}

DecisionTree* CloseCombatEnemy::GetTree() const
{
	return m_tree;
}

void CloseCombatEnemy::m_buildTree()
{
}

void CloseCombatEnemy::m_move()
{
	Seek();

	//                      final Position  Position Term   Velocity      Acceleration Term
	// Kinematic Equation-> Pf            = Pi +            Vi * (time) + (0.5) * Ai * (time * time)

	const float dt = Game::Instance().GetDeltaTime();

	// accessing the position Term
	const glm::vec2 initial_position = GetTransform()->position;

	// compute the velocity Term
	const glm::vec2 velocity_term = GetRigidBody()->velocity * dt;

	// compute the acceleration Term
	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f; // * dt * dt


	// compute the new position
	glm::vec2 final_position = initial_position + velocity_term + acceleration_term;

	GetTransform()->position = final_position;

	// add our acceleration to velocity
	GetRigidBody()->velocity += GetRigidBody()->acceleration;

	// clamp our velocity at max speed
	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity, GetMaxSpeed());
}

void CloseCombatEnemy::m_buildPatrolPath()
{
	m_patrolPath.emplace_back(760, 40); // Top-Right Corner of the Screen
	m_patrolPath.emplace_back(760, 560); // Bottom-Right Corner of the Screen
	m_patrolPath.emplace_back(40, 560); // Bottom-Leeft Corner of the Screen
	m_patrolPath.emplace_back(40, 40); // Top-Left Corner of the Screen
	SetTargetPosition(m_patrolPath[m_wayPoint]);
}
