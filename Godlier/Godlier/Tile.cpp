#include "Tile.h"
#include "MapChunk.h"

Tile::Tile()
	:m_height(0)
{

}

Tile::~Tile()
{

}

void Tile::initalize(int chunkIndex, class MapChunk* mapChunk)
{
	m_chunkIndex = chunkIndex;
	m_mapChunk = mapChunk;
}

void Tile::setVertexArrayFirstIndex(int firstVertexIndex)
{
	// Verify that the index is divisible by 4
	if (firstVertexIndex % 4 != 0)
	{
		std::printf("");

		return;
	}
	m_vertexArrayFirstIndex = firstVertexIndex;
}

int Tile::getVertexArrayIndices() const
{
	return m_vertexArrayFirstIndex;
}

void Tile::setHeight(int newHeight)
{
	int oldHeight = m_height;
	m_height = newHeight;
	m_height = std::max(m_height, Constants::World::Tile::MinCliffHeight);
	m_height = std::min(m_height, Constants::World::Tile::MaxCliffHeight);

	//if (m_height == oldHeight) return;

	m_mapChunk->updateTileHeight(m_vertexArrayFirstIndex, m_chunkIndex, newHeight);
}

int Tile::getHeight() const
{
	return m_height;
}

void Tile::setTextureID(int ID)
{
	m_textureID = ID;
}

int Tile::getTextureID() const
{
	return m_textureID;
}

int Tile::getChunkIndex() const
{
	return m_chunkIndex;
}
