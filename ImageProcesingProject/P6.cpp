#include"P6.h"
#include"P3.h"

P6::P6()
{
	int r = 0;
	int g = 0;
	int b = 0;
}

P6::~P6()
{
	clearPixels();
}

// ------ P6 READ -------

void P6::Read(const char* filename)
{
	ifstream inBinaryFile(filename, ios::binary | ios::in);
	if (!inBinaryFile)
	{
		cerr << "Cannot read P6 file! \n";
		return;
	}
	inBinaryFile.seekg(0, ios::beg);
	inBinaryFile.getline(magic, 3);
	SkipComment(inBinaryFile);
	char ch;

	inBinaryFile >> width >> height >> max_num;
	inBinaryFile.get(ch);

	this->setMagic(magic);
	this->setWidth(width);
	this->setHeight(height);
	this->setMaxNum(max_num);

	pixels = createPixelsArray(height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			inBinaryFile.read((char*)&r, sizeof(char));
			inBinaryFile.read((char*)&g, sizeof(char));
			inBinaryFile.read((char*)&b, sizeof(char));

			pixels[i][j].setRed(r);
			pixels[i][j].setGreen(g);
			pixels[i][j].setBlue(b);
		}
	}
	inBinaryFile.close();
}

// ------ P6 GRAYSCALE -------

void P6::Grayscale(const char* filename)
{
	if (isGrayMonochrome() == true)
	{
		cout << "The image is already grayscale \n";
		return;
	}
	else
	{
		char* newName = ChangeFileName(filename, "_grayscale.ppm");
		ofstream outFile(newName, ios::out | ios::binary);
		if (!outFile)
		{
			cerr << "Cannot write P6 file \n";
			return;
		}
		char magic_pgm[3] = "P6";
		outFile << magic_pgm << endl << width << " " << height << endl << max_num << endl;

		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				r = getPixels()[i][j].getRed();
				g = getPixels()[i][j].getGreen();
				b = getPixels()[i][j].getBlue();

				int gray = grayscale(r, g, b);
				outFile.write((const char*)&gray, sizeof(Color) / 3);
				outFile.write((const char*)&gray, sizeof(Color) / 3);
				outFile.write((const char*)&gray, sizeof(Color) / 3);
			}
		}
		outFile.flush();
		outFile.close();
		delete[] newName;
	}	
}

// ------ P6 MONOCHROME -------

void P6::Monochrome(const char* filename)
{
	if (isGrayMonochrome() == true)
	{
		cout << "The image is already monochrome \n";
		return;
	}
	else
	{
		char* newName = ChangeFileName(filename, "_monochrome.ppm");
		ofstream outFile(newName, ios::out);
		if (!outFile)
		{
			cerr << "Cannot write P6 file \n";
			return;
		}
		char magic_pbm[3] = "P6";
		outFile << magic_pbm << endl << getWidth() << " " << getHeight() << endl << getMaxNum() << endl;

		int r = 0, g = 0, b = 0;
		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				r = getPixels()[i][j].getRed();
				g = getPixels()[i][j].getGreen();
				b = getPixels()[i][j].getBlue();

				int gray = grayscale(r, g, b);
				int m = monochrome(gray);

				outFile.write((const char*)&m, sizeof(char));
				outFile.write((const char*)&m, sizeof(char));
				outFile.write((const char*)&m, sizeof(char));
			}
		}

		outFile.flush();
		outFile.close();
		delete[] newName;
	}
}