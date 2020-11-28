#include "matplotlib-cpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;
int width = 0, height = 0;
unsigned char* readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f); 

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];

    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size];

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f); 
    fclose(f);

    /*for(i = 0; i < size; i += 3)
    {
            // flip the order of every 3 bytes
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
    }*/

    return data;
}

int main(int argc, char* argv[])
{
	std::cout << "BMP Start" << std::endl;
	unsigned char* data = readBMP(argv[1]);
	std::cout << "BMP Read" << std::endl;
	std::cout << width << " " << height << " " << std::endl;
	plt::figure_size(1024,768);	
	plt::xlim(0,1024);
	plt::ylim(0,768);
	plt::imshow(data,height,width,3);
	plt::save("xyz.png");
}

