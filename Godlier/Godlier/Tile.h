#pragma once
#include <array>
#include <SFML/Graphics/Transformable.hpp>

class Tile : public sf::Transformable
{
public:
	Tile();
	~Tile();

	void initalize(int chunkIndex, class MapChunk* mapChunk);

	void setVertexArrayFirstIndex(int firstVertexIndex);
	int getVertexArrayIndices() const;

	void setHeight(int newHeight);
	int getHeight() const;

	void setTextureID(int ID);
	int getTextureID() const;

	int getChunkIndex() const;

private:
	int m_vertexArrayFirstIndex;
	int m_height;
	int m_textureID;
	int m_chunkIndex;
	class MapChunk* m_mapChunk;
};