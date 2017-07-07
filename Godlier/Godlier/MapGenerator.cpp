#include "MapGenerator.h"
#include "simplexnoise.h"
#include <cmath>
#include <vector>
#include <SFML/System/Vector2.hpp>

float noise(float nx, float ny)
{

	return (raw_noise_2d(nx, ny) + 1.0f) / 2.0f;
}

float fBm(float x, float y, int octaves, float lacunarity, float gain)
{
	float amp = 1;
	sf::Vector2f vec(x, y);
	float sum = 0;
	for (int i = 0; i < octaves; i++)
	{
		sum += amp * raw_noise_2d(vec.x, vec.y);
		amp *= gain;
		vec *= lacunarity;
	}
	return sum;
}

float RidgedMultifractal(float x, float y, int octaves, float lacunarity, float gain, float H, float sharpness, float threshold)
{
	float result, signal, weight, exponent;
	sf::Vector2f vec(x, y);

	for (int i = 0; i < octaves; i++)
	{
		if (i == 0)
		{
			signal = raw_noise_2d(vec.x, vec.y);
			if (signal <= 0.0)
				signal = -signal;
			signal = gain - signal;
			signal = pow(signal, sharpness);
			result = signal;
			weight = 1.0f;
		}
		else
		{
			exponent = pow(lacunarity, -i*H);
			vec *= lacunarity;
			weight = signal * threshold;
			weight = std::fminf(std::fmaxf(weight, 0.0f), 1.0f);
			signal = raw_noise_2d(vec.x, vec.y);
			signal = abs(signal);
			signal *= weight;
			result += signal * exponent;
		}
	}
	return result;
}

float turbulence(float x, float y, int octaves, float lacunarity, float gain)
{
	float amp = 1;
	sf::Vector2f vec(x, y);
	float sum = 0;
	for (int i = 0; i < octaves; i++)
	{
		sum += std::abs(amp * raw_noise_2d(vec.x, vec.y));
		amp *= gain;
		vec *= lacunarity;
	}
	return sum / 2.0f;
}

void MapGenerator::generateMap(int* tileArr, int* heightArr, int width, int height, float frequency, sf::Vector2f &position)
{
	static int octaves = 8;
	static float lacunarity = 2.5f;
	static float gain = 0.8f;
	static float H = 0.8f;
	static float sharpness = 2.0f;
	static float threshold = 2.0f;

	// TODO: implement usage of a random seed for x and y
	for (int i = 0; i < width; i++)
	{

		float nx = (float)(i + position.x) * frequency;
		for (int j = 0; j < height; j++)
		{
			unsigned int index = i + j * width;
			static float multiplier = 3.0f;
			float ny = (float)j * frequency + position.y;

			float heightMap =
				RidgedMultifractal(nx, ny, octaves, lacunarity, gain, H, sharpness, threshold) * multiplier;

			heightArr[index] = (int)heightMap;

			float temp = noise(nx, ny);
			//heightMap = 3.0f;

			// If the height is larger than this, it is to be considered stone
			if (heightMap >= 5.0f)
			{
				tileArr[index] = TileType::Stone;
			}
			// If less than this it is to be considered water
			else if (heightMap < 0.5)
			{
				tileArr[index] = TileType::Water;
			}
			// Else use the value from the noise to gererate a random biome
			else
			{
				if (temp >= 0.5f)
					tileArr[index] = TileType::Grass;
				else
					tileArr[index] = TileType::Sand;
			}
		}
	}
}
