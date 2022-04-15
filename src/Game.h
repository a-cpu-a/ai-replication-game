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

namespace game
{
	const float tileSize = 16.0f;

	const uint8_t atlasSizeX = 8;
	const uint8_t atlasCutoutSizeX = 4;

	const uint32_t worldSizeX = 8;
	const uint32_t worldSizeY = 3;
	const uint32_t worldSizeZ = 8;

	inline uint8_t tiles[worldSizeX][worldSizeY][worldSizeZ];

	inline float cameraX = ((float)worldSizeX) / 2.0f * tileSize;
	inline float cameraZ = ((float)worldSizeZ) / 2.0f * tileSize;


	inline float uIScale = 6.0f;//lower = smaller

	inline float xMul = 1.0f / (960.0f) * uIScale;//960, 
	inline float yMul = 1.0f / (720.0f) * uIScale;//720

	inline float cameraMulX = cameraX * xMul;
	inline float cameraMulZ = cameraZ * yMul;

	inline float tileSizeMulX = tileSize * xMul;
	inline float tileSizeMulY = tileSize * yMul;



}
