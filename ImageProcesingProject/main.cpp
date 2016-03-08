// Zornitsa Chopova
#include"Image.h"
#include"Color.h"
#include"LoadImage.h"
#include"P3.h"
#include"P6.h"
#include"Histogram.h"
#include"ImageFactory.h"

//#include <cstring> strcpy
//#include <stdlib.h> exit()

#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (ImageFactory::getImageName(argc, argv, i))
		{
			char* name = ImageFactory::getImageName(argc, argv, i);
			
			LoadImage* load = ImageFactory::CreateImageObject(argc, argv);

			if (load != NULL)
			{
				ImageFactory::findExecuteCommands(load, name, argc, argv);

				delete[] load;
				load = NULL;
			}
			else
			{
				cout << "Invalid format! \n";
				return 1;
			}
		}
	}
	return 0;
}

