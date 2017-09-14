#include <fstream>

#include "GameManager.h"

int main()
{
	GameManager gm;
	gm.run();


	/*char* memblock;
	std::streampos size = 4;
	char toWrite[4] = { 0b00000001, 0b00010000,  0b01111111, 0b01000000 };
	memblock = toWrite;
	std::string file = "Resources/Maps/";
	file += toWrite;

	std::ofstream oss(file, std::ios::binary);
	if (oss.is_open())
	{
		oss.write(memblock, size);
		oss.close();
	}
	std::ofstream os;
	os.open("Resources/Maps/Savename.txt", std::ios::binary);
	os.write(memblock, size);
	os.close();

	std::ifstream is;
	std::streampos begin, end;
	is.open("Resources/Maps/Savename.txt", std::ios::binary);
	begin = is.tellg();
	is.seekg(0, std::ios::end);
	end = is.tellg();
	is.close();
	std::printf("size of file: %i bytes", end - begin);*/

	return 0;
}