#pragma once
#ifndef __DECISION_TREE__
#define __DECISION_TREE__

#include "Agent.h"
#include "CloseCombatCondition.h"
#include "LOSCondition.h"
#include "RadiusCondition.h"
#include "TreeNode.h"
#include "TreeNodeType.h"

#include <vector>

class DecisionTree
{
public:
	// constructor(s)
	DecisionTree(); // default / empty constructor
	DecisionTree(Agent* agent);

	// destructor
	~DecisionTree();

	// getters and setters
	[[nodiscard]] Agent* GetAgent() const;
	void SetAgent(Agent* agent);

	// ConditionNode Getters
	[[nodiscard]] LOSCondition* GetLOSNode() const;
	[[nodiscard]] RadiusCondition* GetRadiusNode() const;
	[[nodiscard]] CloseCombatCondition* GetCloseCombatNode() const;

	// Public Utility / Convenience functions
	TreeNode* AddNode(TreeNode* parent, TreeNode* child_node, TreeNodeType type);

	// Life Cycle Functions
	void Display() const;
	void Update() const;
	void Clean();

	// Main Public Method
	void MakeDecision() const; // in-order traversal of the tree
private:
	// Private data members
	Agent* m_agent{};
	LOSCondition* m_LOSNode{};
	RadiusCondition* m_RadiusNode{};
	CloseCombatCondition* m_CloseCombatNode{};

	// Tree Node List
	std::vector<TreeNode*> m_treeNodeList;
};

#endif /* defined (__DECISION_TREE__) */