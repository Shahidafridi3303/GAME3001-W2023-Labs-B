#include "PatrolAction.h"

#include <iostream>

PatrolAction::PatrolAction()
{
	m_name = "Patrol Action";
}

PatrolAction::~PatrolAction()
= default;

void PatrolAction::Action()
{
	if (GetAgent()->GetActionState() != ActionState::PATROL)
	{
		std::cout << "Performing " << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::PATROL);
	}
}
