#include "DecisionTree.h"

#include <iostream>

#include "ActionNode.h"
#include "AttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "PatrolAction.h"

DecisionTree::DecisionTree()
{
	m_buildTree();
}

DecisionTree::DecisionTree(Agent* agent)
{
	m_agent = agent;
	m_buildTree();
}

DecisionTree::~DecisionTree()
= default;

Agent* DecisionTree::GetAgent() const
{
	return m_agent;
}

void DecisionTree::SetAgent(Agent* agent)
{
	m_agent = agent;
}

LOSCondition* DecisionTree::GetLOSNode() const
{
	return m_LOSNode;
}

RadiusCondition* DecisionTree::GetRadiusNode() const
{
	return m_RadiusNode;
}

CloseCombatCondition* DecisionTree::GetCloseCombatNode() const
{
	return m_CloseCombatNode;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, const TreeNodeType type)
{
	switch (type)
	{
	case TreeNodeType::LEFT_TREE_NODE:
		parent->m_pLeft = child_node;
		break;
	case TreeNodeType::RIGHT_TREE_NODE:
		parent->m_pRight = child_node;
		break;
	}
	child_node->m_pParent = parent;
	return child_node;
}

void DecisionTree::Display() const
{
	std::cout << "Decision Tree Nodes: " << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	for (const auto node : m_treeNodeList)
	{
		std::cout << node->m_name << std::endl;
	}
	std::cout << "-----------------------------------" << std::endl;
}

void DecisionTree::Update() const
{

}

void DecisionTree::Clean()
{
	for (auto node : m_treeNodeList)
	{
		delete node;
		node = nullptr;
	}
	m_treeNodeList.clear();
	m_treeNodeList.shrink_to_fit();

	m_LOSNode = nullptr;
	m_RadiusNode = nullptr;
	m_CloseCombatNode = nullptr;
}

void DecisionTree::MakeDecision() const
{
	TreeNode* current_node = m_treeNodeList[0]; // root node

	// Traverse the tree down through each decision to the fal action
	while (!current_node->m_isLeaf)
	{
		current_node = dynamic_cast<ConditionNode*>(current_node)->Condition() ?
			(current_node->m_pRight) : (current_node->m_pLeft);
	}
	// Take Action
	dynamic_cast<ActionNode*>(current_node)->Action();
}

void DecisionTree::m_buildTree()
{
	// Conditions

	// Create and add Root Node
	m_LOSNode = new LOSCondition();
	m_treeNodeList.push_back(m_LOSNode);

	m_RadiusNode = new RadiusCondition();
	AddNode(m_LOSNode, m_RadiusNode, TreeNodeType::LEFT_TREE_NODE);
	m_treeNodeList.push_back(m_RadiusNode);

	m_CloseCombatNode = new CloseCombatCondition();
	AddNode(m_LOSNode, m_CloseCombatNode, TreeNodeType::RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_CloseCombatNode);

	// Actions

	// Left Sub-Tree
	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), TreeNodeType::LEFT_TREE_NODE);
	dynamic_cast<ActionNode*>(patrolNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(patrolNode);

	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), TreeNodeType::RIGHT_TREE_NODE);
	dynamic_cast<ActionNode*>(moveToLOSNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(moveToLOSNode);

	// Right Sub-Tree
	TreeNode* moveToPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), TreeNodeType::LEFT_TREE_NODE);
	dynamic_cast<ActionNode*>(moveToPlayerNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(moveToPlayerNode);

	TreeNode* attackNode = AddNode(m_CloseCombatNode, new AttackAction(), TreeNodeType::RIGHT_TREE_NODE);
	dynamic_cast<ActionNode*>(attackNode)->SetAgent(m_agent);
	m_treeNodeList.push_back(attackNode);
}
