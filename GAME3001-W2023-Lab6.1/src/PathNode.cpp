#include "PathNode.h"
#include "Util.h"

PathNode::PathNode()
{
	SetWidth(10);
	SetHeight(10);
	GetTransform()->position = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PATH_NODE);

	SetCurrentHeading(0.0f);
	SetLOSDistance(1000.0f);
	SetLOSColour(glm::vec4(0.0f, 0.5f, 1.0f, 1.0f)); // light blue color
}

PathNode::~PathNode()
{
}

void PathNode::Draw()
{
	Util::DrawRect(GetTransform()->position - glm::vec2(5.0f, 5.0f), GetWidth(), GetHeight(), GetLOSColour());
}

void PathNode::Update()
{
}

void PathNode::Clean()
{
}