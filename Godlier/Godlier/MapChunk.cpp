#include "MapChunk.h"
#include "ResourceManager.h"
#include "MapGenerator.h"
#include <fstream>
#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


static const char* BACKGROUND_TILESET_TEXTURE = "Resources/Images/Tilesets/BackgroundTileset.png";
static const char* OBJECT_TILESET_TEXTURE = "Resources/Images/Tilesets/ObjectTileset.png";

MapChunk::MapChunk()
{
	m_backgroundTilesetTexture = &ResourceManager::getInstance().getTexture(BACKGROUND_TILESET_TEXTURE);
	m_objectTilesetTexture = &ResourceManager::getInstance().getTexture(OBJECT_TILESET_TEXTURE);

	sf::Vector2f pos = getPosition();
}

MapChunk::~MapChunk()
{

}

void MapChunk::setupNew(float frequency, int seed)
{
	sf::Vector2f pos = getPosition();

	int tileType[ChunkNrTilesX * ChunkNrTilesY];
	int heightMap[ChunkNrTilesX * ChunkNrTilesY];
	//int objectType[ChunkNrTilesX * ChunkNrTilesY];

	MapGenerator::generateMap(seed, tileType, heightMap, ChunkNrTilesX, ChunkNrTilesY, frequency, pos);

	m_tileVertexArray.setPrimitiveType(sf::Quads);
	m_tileVertexArray.resize(VertArrSize);

	for (unsigned int i = 0; i < ChunkNrTilesX; i++)
	{
		for (unsigned int j = 0; j < ChunkNrTilesY; j++)
		{
			int index = i + j * ChunkNrTilesX;
			int tilenr = tileType[index];

			sf::Vector2i uvcoords = findTextureCoords(tilenr);

			sf::Vertex* quad = &m_tileVertexArray[index * 4];

			m_tiles[index].initalize(index, this);
			m_tiles[index].setTextureID(tilenr);
			m_tiles[index].setVertexArrayFirstIndex(index * 4);
			m_tiles[index].setPosition((float)(i * TileWidth), (float)(j * TileHeight));
			m_tiles[index].setHeight(heightMap[index]);

			quad[0].texCoords = sf::Vector2f((float)(uvcoords.x * TileWidth), (float)(uvcoords.y * TileHeight));
			quad[1].texCoords = sf::Vector2f((float)((uvcoords.x + 1) * TileWidth), (float)(uvcoords.y * TileHeight));
			quad[2].texCoords = sf::Vector2f((float)((uvcoords.x + 1) * TileWidth), (float)((uvcoords.y + 1) * TileHeight));
			quad[3].texCoords = sf::Vector2f((float)(uvcoords.x * TileWidth), (float)((uvcoords.y + 1) * TileHeight));
		}
	}
	writeToFile();
}

// Takes a char array with a size of 2 and converts it to a short
unsigned short charArrayToShort(char* arr)
{
	unsigned short val = (unsigned char)arr[0];
	unsigned short val1 = (unsigned char)arr[1];
	val1 <<= 8;
	val += val1;

	return val;
}

void retrieveData(unsigned short in, unsigned int &outHeight, unsigned int &outTile, unsigned int &outObj)
{
	// No need to mask here
	outHeight = in >> 11;
	// Mask to retrieve the relevant bits
	outTile = (in & 0b0000011110000000);
	outTile = outTile >> 7;
	outObj = (in & 0b0000000001111111);
}

void MapChunk::setupFromData(const char* file)
{
	std::streampos size = 2, begin, end;
	char* memblock = new char[size];
	std::ifstream is(file, std::ios::binary);
	if (!is.is_open()) // No such file was found. It has to be generated
	{
		return;
	}
	// TODO: Do a check to see if the size of the file match the estimate size

	sf::Vector2f pos = getPosition();

	m_tileVertexArray.setPrimitiveType(sf::Quads);
	m_tileVertexArray.resize(VertArrSize);

	for (unsigned int i = 0; i < ChunkNrTilesX; i++)
	{
		for (unsigned int j = 0; j < ChunkNrTilesY; j++)
		{
			unsigned int index = i + j * ChunkNrTilesX;
			unsigned int height, tileType, objectType;
			is.read(memblock, size);
			unsigned short _16bit = charArrayToShort(memblock);
			retrieveData(_16bit, height, tileType, objectType);

			sf::Vector2i uvcoords = findTextureCoords(tileType);
			sf::Vertex* quad = &m_tileVertexArray[index * 4];

			m_tiles[index].initalize(index, this);
			m_tiles[index].setTextureID(tileType);
			m_tiles[index].setVertexArrayFirstIndex(index * 4);
			m_tiles[index].setPosition((float)(i * TileWidth), (float)(j * TileHeight));
			m_tiles[index].setHeight(height);

			quad[0].texCoords = sf::Vector2f((float)(uvcoords.x * TileWidth), (float)(uvcoords.y * TileHeight));
			quad[1].texCoords = sf::Vector2f((float)((uvcoords.x + 1) * TileWidth), (float)(uvcoords.y * TileHeight));
			quad[2].texCoords = sf::Vector2f((float)((uvcoords.x + 1) * TileWidth), (float)((uvcoords.y + 1) * TileHeight));
			quad[3].texCoords = sf::Vector2f((float)(uvcoords.x * TileWidth), (float)((uvcoords.y + 1) * TileHeight));
		}
	}
	delete[size] memblock;

}

// arr has to be an array size 2
void intToCharArray(char* arr, unsigned int height, unsigned int tileType, unsigned int objectType)
{
	tileType <<= 7;
	height <<= 11;
	unsigned int val = objectType | height | tileType;
	arr[0] = val;
	val >>= 8;
	arr[1] = val;
}

void MapChunk::writeToFile()
{
	std::string filename = Constants::Filepaths::MapsFolder;
	sf::Vector2f pos = getPosition();
	int posX = (int)pos.x, posY = (int)pos.y;
	filename += std::to_string(posX) + "-" + std::to_string(posY) + ".txt";
	std::streampos size = 2;
	char* memblock = new char[size];
	std::ofstream os(filename, std::ios::binary);
	if (!os.is_open()) return; // Error creating and opening file.

	for (unsigned int i = 0; i < ChunkNrTilesX; i++)
	{
		for (unsigned int j = 0; j < ChunkNrTilesY; j++)
		{
			unsigned int index = i + j * ChunkNrTilesX;
			unsigned int height = m_tiles[index].getHeight();
			unsigned int tileType = m_tiles[index].getTextureID();
			unsigned int objectType = 0;

			intToCharArray(memblock, height, tileType, objectType);
			os.write(memblock, size);
		}
	}
	delete[size] memblock;
}

// Helper function for finding the uv coordinates in the texture
sf::Vector2i MapChunk::findTextureCoords(int tileNr)
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

void MapChunk::updateTileID(int ID)
{
}
