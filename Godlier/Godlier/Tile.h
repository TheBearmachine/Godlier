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
	unsigned int getVertexArrayIndices() const;

	void setHeight(unsigned int newHeight);
	unsigned int getHeight() const;

	void setTextureID(unsigned int ID);
	unsigned int getTextureID() const;

	int getChunkIndex() const;
	void setHasChanges();

private:
	unsigned int m_vertexArrayFirstIndex;
	unsigned int m_height;
	unsigned int m_textureID;
	unsigned int m_chunkIndex;
	bool m_hasChanges;
	class MapChunk* m_mapChunk;
};