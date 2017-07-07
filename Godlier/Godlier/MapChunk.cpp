#include "MapChunk.h"
#include "ResourceManager.h"
#include "MapGenerator.h"
#include <SFML/Graphics/RenderTarget.hpp>


static const char* BACKGROUND_TILESET_TEXTURE = "Resources/Images/Tilesets/BackgroundTileset.png";
static const char* OBJECT_TILESET_TEXTURE = "Resources/Images/Tilesets/ObjectTileset.png";



MapChunk::MapChunk()
{
	m_backgroundTilesetTexture = &ResourceManager::getInstance().getTexture(BACKGROUND_TILESET_TEXTURE);
	m_objectTilesetTexture = &ResourceManager::getInstance().getTexture(OBJECT_TILESET_TEXTURE);

	int tileType[ChunkNrTilesX * ChunkNrTilesY];
	int heightMap[ChunkNrTilesX * ChunkNrTilesY];

	sf::Vector2f pos = getPosition();
	MapGenerator::generateMap(tileType, heightMap, ChunkNrTilesX, ChunkNrTilesY, 0.1f, pos);

	setup(tileType, heightMap);
}

MapChunk::~MapChunk()
{

}

void MapChunk::setup(const int* tiles, const int* heights)
{
	m_tileVertexArray.setPrimitiveType(sf::Quads);
	m_tileVertexArray.resize(VertArrSize);


	for (unsigned int i = 0; i < ChunkNrTilesX; i++)
	{
		for (unsigned int j = 0; j < ChunkNrTilesY; j++)
		{
			int index = i + j * ChunkNrTilesX;
			int tilenr = tiles[index];

			sf::Vector2i uvcoords = findTextureCoords(tilenr);
			//std::printf("index: %u tile nr: %i, u: %u, v: %u\n", index, tilenr, uvcoords.x, uvcoords.y);


			sf::Vertex* quad = &m_tileVertexArray[index * 4];

			m_tiles[index].initalize(index, this);
			m_tiles[index].setTextureID(tilenr);
			m_tiles[index].setVertexArrayFirstIndex(index * 4);
			m_tiles[index].setPosition((float)(i * TileWidth), (float)(j * TileHeight));
			m_tiles[index].setHeight(heights[index]);

			quad[0].texCoords = sf::Vector2f((float)(uvcoords.x * TileWidth), (float)(uvcoords.y * TileHeight));
			quad[1].texCoords = sf::Vector2f((float)((uvcoords.x + 1) * TileWidth), (float)(uvcoords.y * TileHeight));
			quad[2].texCoords = sf::Vector2f((float)((uvcoords.x + 1) * TileWidth), (float)((uvcoords.y + 1) * TileHeight));
			quad[3].texCoords = sf::Vector2f((float)(uvcoords.x * TileWidth), (float)((uvcoords.y + 1) * TileHeight));
		}
	}
	//std::printf("Tile width: %u", TileWidth);
	//std::printf("Tile height: %u", TileHeight);
	size_t limit = m_tileVertexArray.getVertexCount();
	for (size_t i = 0; i < limit; i++)
	{
		int xPos = int(m_tileVertexArray[i].position.x);
		int yPos = int(m_tileVertexArray[i].position.y);
		std::printf("[x: %i, y: %i]    ", xPos, yPos);
	}
}

// Helper function for finding the uv coordinates in the texture
sf::Vector2i  MapChunk::findTextureCoords(int tileNr)
{
	sf::Vector2i vec;
	int x = tileNr % (m_backgroundTilesetTexture->getSize().x / TileWidth);
	int y = tileNr / (m_backgroundTilesetTexture->getSize().x / TileWidth);
	int size = m_backgroundTilesetTexture->getSize().x;
	vec.x = tileNr % (m_backgroundTilesetTexture->getSize().x / TileWidth);
	vec.y = tileNr / (m_backgroundTilesetTexture->getSize().x / TileWidth);
	return vec;
}

void MapChunk::tick(const sf::Time & deltaTime)
{

}

void MapChunk::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (m_backgroundTilesetTexture)
	{
		states.texture = m_backgroundTilesetTexture;
		target.draw(m_tileVertexArray, states);
	}

	if (m_objectTilesetTexture)
	{
		states.texture = m_objectTilesetTexture;
		target.draw(m_tileVertexArray, states);
	}
}

void MapChunk::updateTileHeight(int firstVertexIndex, int chunkIndex, int height)
{
	Tile* tile = &m_tiles[chunkIndex];
	sf::Vertex* quad = &m_tileVertexArray[firstVertexIndex];
	sf::Vector2f pos[4]; // Top-left, top-right, bottom-right, bottom-left
	pos[0] = tile->getPosition();
	pos[0].y -= tile->getHeight() * CliffHeight;
	pos[3] = pos[2] = pos[1] = pos[0];
	//std::printf(" TL.x: %f, y: %f\nTR.x: %f, y: %f\n", topLeft.x, topLeft.y, topRight.x, topRight.y);
	pos[1].x += TileWidth;
	pos[2].x += TileWidth;
	pos[2].y += TileHeight;
	pos[3].y += TileWidth;

	sf::Uint8 colVal = (((float)height + (float)_MaxCliffHeight) / ((float)_MaxCliffHeight * 2.0f)) * 256.0f;
	sf::Color col(colVal, colVal, colVal);
	col.r = colVal;
	col.b = colVal;
	col.g = colVal;

	for (int i = 0; i < 4; i++)
	{
		quad[i].position = pos[i];
		quad[i].color = col;
	}
}
