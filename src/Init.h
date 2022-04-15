/*
    program name: ai-replication-game, a game where you can train ais to do stuff in a 3d world, and make them create copies
    Copyright (C) 2022  a-cpu-a

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    you can contact me electronicly by making a issue at https://github.com/a-cpu-a/ai-replication-game/issues/new
*/
#pragma once

#include <cstdint>

#include "Game.h"
#include "TileIds.h"

namespace game
{

	inline void initWorld(uint64_t seed)
	{
		for (size_t X = 0; X < worldSizeX; X++)
		{

			for (size_t Y = 0; Y < worldSizeY; Y++)
			{

				for (size_t Z = 0; Z < worldSizeZ; Z++)
				{
					if (Y == 0)
					{
						tiles[X][Y][Z] = tileIds::grass.id;
					}
					else if (Y == 2 && X==3 && Z==2)
					{
						tiles[X][Y][Z] = tileIds::aIPX.id;
					}
					else
					{
						tiles[X][Y][Z] = tileIds::air.id;
					}
				}
			}
		}
	}
}
