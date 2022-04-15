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
#include "../rendering/vec2.h"

namespace game::tileIds
{
	inline uint8_t nextId = 0;
	inline uint8_t nextTexPos = 0;
	inline uint8_t nextCutoutTexPos = 0;

	struct TileId
	{
		uint8_t id;
		bool isAir;
		bool isCutout;

		float uvMinX, uvMinY;
		float uvMaxX, uvMaxY;

		TileId(uint8_t _id,uint8_t texPos, bool _isAir, bool _isCutout)
		{
			id = _id;
			isAir = _isAir;
			isCutout = _isCutout;
			if (isCutout)
			{
				float x = float(texPos % game::atlasCutoutSizeX) / (float)game::atlasCutoutSizeX;
				float y = float(texPos / game::atlasCutoutSizeX) / (float)game::atlasCutoutSizeX;

				uvMinX = x;
				uvMinY = y;
				uvMaxX = x + (1.0f / (float)game::atlasCutoutSizeX);
				uvMaxY = y + (1.0f / (float)game::atlasCutoutSizeX);
			}
			else
			{
				float x = float(texPos % game::atlasSizeX) / (float)game::atlasSizeX;
				float y = float(texPos / game::atlasSizeX) / (float)game::atlasSizeX;

				uvMinX = x;
				uvMinY = y;
				uvMaxX = x + (1.0f / (float)game::atlasSizeX);
				uvMaxY = y + (1.0f / (float)game::atlasSizeX);
			}
		}
	};

	inline TileId genTile(bool isAir, bool isCutout)
	{
		if (isAir)
		{
			return TileId(nextId++, 0, true, false);
		}
		if (isCutout)
		{
			return TileId(nextId++, nextCutoutTexPos++, false, true);
		}
		return TileId(nextId++,nextTexPos++,false,false);
	}

	const TileId air = genTile(true, false);
	//
	const TileId dirt = genTile(false, false);
	const TileId stone = genTile(false, false);
	const TileId clay = genTile(false, false);
	const TileId rocks = genTile(false, false);
	const TileId grass = genTile(false, false);
	//robot :)
	const TileId aIPX = genTile(false, true);
	const TileId aINX = genTile(false, true);
	const TileId aIPZ = genTile(false, true);
	const TileId aINZ = genTile(false, true);
	//

	const TileId ids[] = { air, dirt, stone, clay, rocks, grass,aIPX,aINX,aIPZ,aINZ };

}
