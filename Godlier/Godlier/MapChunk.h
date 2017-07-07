#pragma once

#include "Entity.h"
#include "Tile.h"
#include "Constants.h"

#include <SFML/Graphics/VertexArray.hpp>

class MapChunk : public Entity
{
public:

#define ChunkNrTilesX Constants::World::Chunk::NrTilesX
#define ChunkNrTilesY Constants::World::Chunk::NrTilesY
#define TileWidth Constants::World::Tile::Width
#define TileHeight Constants::World::Tile::Height
#define CliffHeight Constants::World::Tile::CliffHeight
#define _MaxCliffHeight Constants::World::Tile::MaxCliffHeight
#define _MinCliffHeight Constants::World::Tile::MinCliffHeight
#define Tilepath Constants::Filepaths::Graphics::TileMapsFolder
#define VertArrSize ChunkNrTilesX * ChunkNrTilesY * 4

	MapChunk();
	virtual ~MapChunk();

	void setup(float frequency, int seed);

private:
	sf::Vector2i findTextureCoords(int tileNr);

public:

	virtual void tick(const sf::Time& deltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void updateTileHeight(int firstVertexIndex, int chunkIndex, int height);

private:
	Tile m_tiles[ChunkNrTilesX * ChunkNrTilesY];
	sf::Texture* m_backgroundTilesetTexture;
	sf::Texture* m_objectTilesetTexture;
	sf::VertexArray m_tileVertexArray;
	sf::VertexArray m_cliffVertexArray;

};