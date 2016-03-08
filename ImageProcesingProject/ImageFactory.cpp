#include"ImageFactory.h"

void ImageFactory::findExecuteCommands(LoadImage* load, const char* filename, int argc, char* argv[])
{
	const char* functions[5] = { { "--grayscale" },
								{ "--monochrome" },
								{ "--histogram=red" },
								{ "--histogram=green" },
								{ "--histogram=blue" } };
	load->Read(filename);
		
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], functions[0]) == 0)
		{
			load->Grayscale(filename);
			break;
		}
	}
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], functions[1]) == 0)
		{
			load->Monochrome(filename);
			break;
		}
	}
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], functions[2]) == 0)
		{
			Histogram red;
			red.redHistogram(load, filename);
			break;
		}
	}
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], functions[3]) == 0)
		{
			Histogram green;
			green.greenHistogram(load, filename);
			break;
		}
	}
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], functions[4]) == 0)
		{
			Histogram blue;
			blue.blueHistogram(load, filename);
			break;
		}
	}
}

bool ImageFactory::CanCreateCommands(int argc, char* argv[])
{
	const char* functions[5] = { { "--histogram=red" },
								{ "--histogram=green" },
								{ "--histogram=blue" },
								{ "--grayscale" },
								{"--monochrome"}};
	for (int i = 1; i < argc; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (strcmp(argv[i], functions[j]) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool ImageFactory::CanReadFile(const char* filename)
{
	ifstream readFile(filename, ios::in);
	if (!readFile)
	{
		return false;
	}
	else
	{
		return true;
	}
	readFile.close();
}

LoadImage* ImageFactory::RecognizeImage(const char* filename)
{
	ifstream readHeader(filename, ios::in);
	if (!readHeader)
	{
		cerr << "Cannot read image! \n";
		exit(1);
	}

	char magic[3];
	readHeader.getline(magic, 3);

	LoadImage* load = NULL;
	if (strcmp(magic, "P3") == 0)
	{
		load = new P3();
		readHeader.close();
		return load;
	}
	else if (strcmp(magic, "P6") == 0)
	{
		load = new P6();
		return load;
	}
	else if (strcmp(magic, "P1") == 0)
	{
		return NULL;
	}
	else if (strcmp(magic, "P2") == 0)
	{
		return NULL;
	}
	else if (strcmp(magic, "P4") == 0)
	{
		return NULL;
	}
	else if (strcmp(magic, "P5") == 0)
	{
		return NULL;
	}
	readHeader.close();
	return NULL;
}

LoadImage* ImageFactory::CreateImageObject(int argc, char* argv[])
{
	if (CanCreateCommands(argc, argv))
	{
		for (int i = 0; i < argc; i++)
		{
			if (CanReadFile(argv[i]))
			{
				if (RecognizeImage != NULL)
				{
					return RecognizeImage(argv[i]);
				}
			}
		}
	}
	cout << "This function/file doesn't exist! \n";
	exit(1);
	return NULL;
}

char* ImageFactory::getImageName(int argc, char* argv[], int i)
{
	// (int i = 0; i < argc; i++)
	if (i<argc)
	{
		if (CanReadFile(argv[i]))
		{
			return argv[i];
		}
		else
		{
			return 0;
		}
	}
	cout << "Misspelled file name! \n";
	exit(1);
}

// should delete char array after using the function
char* ImageFactory::ChangeFileName(const char* filename, const char* func)
{
	char* buff = new char[50];
	int i = 0;
	while (filename[i] != '.')
	{
		buff[i] = filename[i];
		i++;
	}
	int lengthFile = strlen(func) + 1;
	for (int j = 0; j < lengthFile; j++)
	{
		buff[i] = func[j];
		i++;
	}
	buff[i] = '\0';
	return buff;
}
