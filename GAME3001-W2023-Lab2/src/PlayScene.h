#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Target.h"
#include "StarShip.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;

	// Ganme objects for sce
	Target* m_pTarget;
	StarShip* m_pStarship;

};

#endif /* defined (__PLAY_SCENE__) */