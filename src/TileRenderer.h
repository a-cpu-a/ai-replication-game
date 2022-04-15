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

#include "Game.h"
#include "TileIds.h"
#include "../rendering/render.h"

namespace game::render
{
	inline void renderTiles(rendering::VertexBuffer* vertexBuffer)
	{
		std::vector<float> vertexData;
		std::vector<float> vertexDataCutout;

		for (size_t X = 0; X < worldSizeX; X++)
		{

			for (size_t Z = 0; Z < worldSizeZ; Z++)
			{
				for (size_t Y = 0; Y < worldSizeY; Y++)
				{
					uint8_t tileId = tiles[X][Y][Z];
					tileIds::TileId tileType = tileIds::ids[tileId];
					if (tileType.isAir)
					{
						continue;
					}

					float x = X * tileSizeMulX - cameraMulX;
					float y = Z * tileSizeMulY - cameraMulZ;

					float xMax = X * tileSizeMulX - cameraMulX + tileSizeMulX;
					float yMax = Z * tileSizeMulY - cameraMulZ + tileSizeMulY;

					/*const std::vector<float> vertices = {
						x,      y, tileType.uvMinX,tileType.uvMinY,
						x,yMax,    tileType.uvMinX,tileType.uvMaxY,
						xMax,yMax, tileType.uvMaxX,tileType.uvMaxY,

						xMax,yMax, tileType.uvMaxX,tileType.uvMaxY,
						xMax,   y, tileType.uvMaxX,tileType.uvMinY,
						x,      y, tileType.uvMinX,tileType.uvMinY
					};*/

					if (tileType.isCutout)
					{
						//vertexDataCutout.insert(vertexDataCutout.end(),vertices.begin(), vertices.end());
						//rendering::renderQuadRGB(rendering::vec2(x, y), rendering::vec2(x, y + tileSize), rendering::vec2(x + tileSize, y + tileSize), rendering::vec2(x + tileSize, y), rendering::color3(1.0));
						rendering::renderQuadTexCutout(rendering::vec2(x, y), rendering::vec2(xMax, yMax), rendering::vec2(tileType.uvMinX, tileType.uvMinY), rendering::vec2(tileType.uvMaxX, tileType.uvMaxY));
					}
					else
					{
						//vertexData.insert(vertexData.end(), vertices.begin(), vertices.end());
						//rendering::renderQuadRGB(rendering::vec2(x, y), rendering::vec2(x, y + tileSize), rendering::vec2(x + tileSize, y + tileSize), rendering::vec2(x + tileSize, y), rendering::color3(1.0));
						rendering::renderQuadTex(rendering::vec2(x, y), rendering::vec2(xMax, yMax), rendering::vec2(tileType.uvMinX, tileType.uvMinY), rendering::vec2(tileType.uvMaxX, tileType.uvMaxY));
					}
				}
			}
		}
		//if(vertexData.size() > 0)
		//	rendering::renderTex(vertexData, vertexBuffer);
		
		//if (vertexDataCutout.size() > 0)
		//	rendering::renderTexCutout(vertexDataCutout, vertexBuffer);

	}
}
