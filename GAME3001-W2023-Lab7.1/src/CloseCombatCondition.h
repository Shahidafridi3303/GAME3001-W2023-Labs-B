#pragma once
#ifndef __CLOSE_COMBAT__CONDITION__
#define __CLOSE_COMBAT__CONDITION__

#include "ConditionNode.h"

class CloseCombatCondition : public ConditionNode
{
public:
	CloseCombatCondition(bool within_combat_range = false);
	virtual ~CloseCombatCondition();

	// Setter
	void SetIsWithinCombatRange(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinCombatRange{};
};
#endif  /* defined (__CLOSE_COMBAT__CONDITION__) */