#include "StarShip.h"
#include "TextureManager.h"

StarShip::StarShip()
{
	TextureManager::Instance().Load("../Assets/textures/ncl.png", "starship");

	const auto size = TextureManager::Instance().GetTextureSize("starship");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = glm::vec2(100.0f, 100.0f);
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;

	SetType(GameObjectType::STARSHIP);
}
StarShip::~StarShip()
= default;

void StarShip::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("starship", 
		GetTransform()->position, 0, 255, true);
}
void StarShip::Update()
{
	
}
void StarShip::Clean()
{
	
}

