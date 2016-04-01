#include "common.h"
#include "Pixel.h"
#include "Image.h"
#include "Operation.h"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc < 2)
	{

		cout << "Usage: main /path/to/pgm/image <x1,y1 x2,y2>";

		return 0;

	}

	char *arg = argv[1];
	string filename = string(arg);
	Pixel *p[2];

	if(argc >= 3)
	{

		char *coordArg = argv[2];
		string coordStr = string(coordArg);
		uint64_t x = atol(coordStr.substr(0, coordStr.find(",")).c_str());
		uint64_t y = atol(coordStr.substr(coordStr.find(",") + 1).c_str());

		p[0] = new Pixel(x, y);

		coordArg = argv[3];
		coordStr = string(coordArg);
		x = atol(coordStr.substr(0, coordStr.find(",")).c_str());
		y = atol(coordStr.substr(coordStr.find(",") + 1).c_str());

		p[1] = new Pixel(x, y);

	}

	Image *image = NULL;

	Operation *openImage = new Operation(OPERATION_NONE, filename);
	image = openImage->execute();

	map<uint8_t, uint64_t> frequencies = image->getIntensityFrequencies();
	cout << "Frequência das Intensidades:" << endl;
	for(auto it = frequencies.begin(); it != frequencies.end(); it++)
		cout << "    " << (uint32_t) it->first << ": " << it->second << endl;

	cout << endl;

	cout << "Média das Intensidades: " << (uint32_t) image->getIntensityMean() << endl;
	cout << "Desvio Padrão: " << (uint32_t) image->getIntensityStandardDeviation() << endl;

	if(argc >= 3)
	{
		
		cout << "Dados os pixels (" << p[0]->getX() << ", " << p[0]->getY() << ") e (" << p[1]->getX() << ", " << p[1]->getY() << "):" << endl;
		cout << "    Distância Euclidiana: " << Pixel::euclidianDistance(p[1], p[0]) << endl;
		cout << "    Distância Mannhatan: " << Pixel::mannhatanDistance(p[1], p[0]) << endl;

	}

	return 0;

}