#include "MoveToLOSAction.h"

#include <iostream>

MoveToLOSAction::MoveToLOSAction()
{
	m_name = "Move To LOS Action";
}

MoveToLOSAction::~MoveToLOSAction()
= default;

void MoveToLOSAction::Action()
{
	if (GetAgent()->GetActionState() != ActionState::MOVE_TO_LOS)
	{
		std::cout << "Performing " << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::MOVE_TO_LOS);
	}
}
