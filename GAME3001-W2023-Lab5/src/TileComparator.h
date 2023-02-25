#pragma once
#ifndef __TILE_COMPARATOR
#define __TILE_COMPARATOR

#include "Tile.h"

class TileComparator
{
public:
	int operator() (const Tile* lhs, const Tile* rhs) const
	{
		return lhs->GetTileCost() > rhs->GetTileCost();
	}
};

#endif /* defined (TILE_COMPARATOR__) */