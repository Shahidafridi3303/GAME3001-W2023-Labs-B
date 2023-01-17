#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default; 

void PlayScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{
	// update player
	m_pPlayer->Update();

	// check distance between player and right end of screen
	float distance = Util::Distance(m_pPlayer->GetTransform()->position, glm::vec2(800, m_pPlayer->GetTransform()->position.y));
	if (distance < m_closeDistance)
	{
		// change to end scene
		Game::Instance().ChangeSceneState(SceneState::END);
	}

	UpdateDisplayList();
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}

void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_LEFT);
			m_pPlayer->GetTransform()->position -= glm::vec2(5.0f, 0.0f);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_RIGHT);
			m_pPlayer->GetTransform()->position += glm::vec2(5.0f, 0.0f);
			m_playerFacingRight = true;
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_UP);
			m_pPlayer->GetTransform()->position -= glm::vec2(0.0f, 5.0f);
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S)) 
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_DOWN);
			m_pPlayer->GetTransform()->position += glm::vec2(0.0f, 5.0f);
		}
		else
		{
			if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_W))
    {
        m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_IDLE_UP);
    }
    else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S))
    {
        m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_IDLE_DOWN);
    }
			else if (m_playerFacingRight)
			{
				m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_IDLE_LEFT);
			}
		}
	}
	

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void PlayScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Player Sprite
	m_pPlayer = new Player();
	m_pPlayer->GetTransform()->position = glm::vec2(50.0f, 50.0f);
	AddChild(m_pPlayer);
	m_playerFacingRight = true;

	ImGuiWindowFrame::Instance().SetGuiFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 -W2023 - Lab1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar );

	float float2[2] = { m_pPlayer->GetTransform()->position.x, m_pPlayer->GetTransform()->position.y };
	if(ImGui::SliderFloat2("Player Position", float2, 0.0f, 800.0f))
	{
		if(float2[0] > m_pPlayer->GetTransform()->position.x)
		{
			//moving right
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_RIGHT);
		}

		if (float2[0] > m_pPlayer->GetTransform()->position.x)
		{
			m_pPlayer->SetAnimationState(PlayerAnimationState::PLAYER_RUN_LEFT);
		}
		m_pPlayer->GetTransform()->position = glm::vec2(float2[0], float2[1]);
	
	}
	
	ImGui::End();
}
