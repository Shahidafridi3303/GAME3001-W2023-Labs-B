#include "Tile.h"
#include "Config.h"
#include "Util.h"
#include <sstream>
#include <iomanip>

#include "SceneState.h"

Tile::Tile(): m_cost(0.0f)
{
	SetWidth(Config::TILE_SIZE);
	SetHeight(Config::TILE_SIZE);
}

Tile::~Tile()
= default;

void Tile::Draw()
{
	switch(m_status)
	{
	case TileStatus::START:
		Util::DrawFilledRect(GetTransform()->position,
			GetWidth(), GetHeight(), glm::vec4(0.5f, 1.0f, 0.5f, 1.0f));
		break;
	case TileStatus::GOAL:
		Util::DrawFilledRect(GetTransform()->position,
			GetWidth(), GetHeight(), glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
		break;
	case TileStatus::IMPASSABLE:
		Util::DrawFilledRect(GetTransform()->position,
			GetWidth(), GetHeight(), glm::vec4(0.5f, 0.5f, 0.5f, 0.5f));
		break;
	default:
		Util::DrawRect(GetTransform()->position, GetWidth(), GetHeight());
		break;
	}
}

void Tile::Update()
{
}

void Tile::Clean()
{
}

Tile* Tile::GetNeighbourTile(const NeighbourTile position) const
{
	return m_neighbours[static_cast<int>(position)];
}

void Tile::SetNeighbourTile(const NeighbourTile position, Tile* tile)
{
	m_neighbours[static_cast<int>(position)] = tile;
}

float Tile::GetTileCost() const
{
	return m_cost;
}

void Tile::SetTileCost(const float cost)
{
	m_cost = cost;

	// update the Cost Label - convert from float with lots of precision to single precision
	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << m_cost;
	const std::string cost_string = stream.str();

	m_costLabel->SetText(cost_string);
}

TileStatus Tile::GetTileStatus() const
{
	return m_status;
}

void Tile::SetTileStatus(const TileStatus status)
{
	m_status = status;

	switch(m_status)
	{
	case TileStatus::UNVISITED:
		m_statusLabel->SetText("-");
		break;
	case TileStatus::OPEN:
		m_statusLabel->SetText("O");
		break;
	case TileStatus::CLOSED:
		m_statusLabel->SetText("C");
		break;
	case TileStatus::IMPASSABLE:
		m_statusLabel->SetText("I");
		break;
	case TileStatus::GOAL:
		m_statusLabel->SetText("G");
		break;
	case TileStatus::START:
		m_statusLabel->SetText("S");
		break;
	}
}

void Tile::AddLabels()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	// add cost label
	m_costLabel = new Label("99.9", "Consolas", 12);
	m_costLabel->GetTransform()->position = GetTransform()->position + offset + glm::vec2(0.0f, -6.0f);
	GetParent()->AddChild(m_costLabel);
	m_costLabel->SetEnabled(false);

	// add status label
	m_statusLabel = new Label("-", "Consolas", 12);
	m_statusLabel->GetTransform()->position = GetTransform()->position + offset + glm::vec2(0.0f, 6.0f);
	GetParent()->AddChild(m_statusLabel);
	m_statusLabel->SetEnabled(false);
}

void Tile::SetLabelsEnabled(const bool state) const
{
	m_costLabel->SetEnabled(state);
	m_statusLabel->SetEnabled(state);
}
