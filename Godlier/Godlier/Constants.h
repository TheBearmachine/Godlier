#pragma once
#include <string>

#define const_float const float
#define const_int const int
#define const_uint const unsigned int
#define const_charptr const char*

namespace Constants
{
	namespace World
	{
		namespace Tile
		{
			const_uint Width = 32;
			const_uint HalfWidth = Width / 2;
			const_uint Height = 32;
			const_uint HalfHeight = Height / 2;
			const_uint CliffHeight = 8;
			const_uint MaxCliffHeight = 20;
			const_uint MinCliffHeight = 0;
		}
		namespace Chunk
		{
			const_uint NrTilesX = 16;
			const_uint NrTilesY = 16;
		}
	}

	namespace Player
	{

	}

	namespace Camera
	{
		const_float Speed = 100.0f;
	}

	namespace NPCs
	{

	}

	namespace Filepaths
	{
		const std::string TileMapsFolder = "Resources/Images/Tilesets/";
		const std::string MapsFolder = "Resources/Maps/";
		const std::string FontsFolder = "Resources/Fonts/";
		const std::string DefaultFont = "Resources/Fonts/sui_generis_rg.ttf";
	}
}