#include"P3.h"

#include<iostream>
#include<fstream>
using namespace std;

P3::P3()
{
	int r = 0;
	int g = 0;
	int b = 0;
}
P3::~P3()
{
	clearPixels();
}

// ------ P3 READ -------

void P3::Read(const char* filename)
{
	ifstream inFile(filename, ios::out);
	if (!inFile)
	{
		cerr << "Cannot read P3 file! \n";
		return;
	}
	inFile.seekg(0, ios::beg);
	inFile.getline(magic, 3);
	SkipComment(inFile);
	inFile >> width >> height >> max_num;

	this->setMagic(magic);
	this->setWidth(width);
	this->setHeight(height);
	this->setMaxNum(max_num);
	
	pixels = createPixelsArray(height, width);

	for (int i = 0; i < height;i++)
	{
		for (int j = 0; j < width; j++)
		{
			inFile >> r >> g >> b;
			pixels[i][j].setRed(r);
			pixels[i][j].setGreen(g);
			pixels[i][j].setBlue(b);
		}
	}
	inFile.close();
}

// ------ P3 GRAYSCALE -------

void P3::Grayscale(const char* filename)
{
	if (isGrayMonochrome() == true)
	{
		cout << "The image is already grayscale \n";
		return;
	}
	else
	{
		char* newName = ChangeFileName(filename, "_grayscale.ppm");
		ofstream outFile(newName, ios::out);
		if (!outFile)
		{
			cerr << "Cannot write P2 file \n";
			return;
		}
		char magic_pgm[3] = "P3";
		outFile << magic_pgm << endl << width << " " << height << endl << max_num << endl;

		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				r = getPixels()[i][j].getRed();
				g = getPixels()[i][j].getGreen();
				b = getPixels()[i][j].getBlue();
			
				int gray = grayscale(r, g, b);
				outFile << gray << " " << gray << " " << gray<<" ";
			}
		}
		outFile.close();
		delete[] newName;
	}
}

// ------ P3 MONOCHROME -------

void P3::Monochrome(const char* filename)
{
	if (isGrayMonochrome() == true)
	{
		cout << "The image is already monochrome \n";
		return;
	}
	else
	{
		char* newName = ChangeFileName(filename, "_monochrome.ppm");
		ofstream outFile(newName, ios::out | ios::binary);
		if (!outFile)
		{
			cerr << "Cannot write P3 file \n";
			return;
		}
		char magic_pbm[3] = "P3";
		outFile << magic_pbm << endl << getWidth() << " " << getHeight() <<endl<<getMaxNum()<< endl;

		for (int i = 0; i < getHeight(); i++)
		{
			for (int j = 0; j < getWidth(); j++)
			{
				r = getPixels()[i][j].getRed();
				g = getPixels()[i][j].getGreen();
				b = getPixels()[i][j].getBlue();

				int gray = grayscale(r, g, b);
				int m = monochrome(gray);

				outFile << m << " "<<m<<" "<<m<<" ";
			}
		}
		outFile.close();
		delete[] newName;
	}
}
