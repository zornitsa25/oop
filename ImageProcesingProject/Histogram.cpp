#include"Histogram.h"

#include<iostream>
#include<fstream>
using namespace std;

Histogram::Histogram()
{
	strcpy(magic, "P3");
	width = 256;
	height = 100;
	max_num = 255;
	r = 0;
	g = 0;
	b = 0;
}
Histogram::~Histogram()
{
}

// ------ RED HISTOGRAM -------

void Histogram::redHistogram(LoadImage* img, const char* filename)
{
	char* newName = ChangeFileName(filename, "_histogram_red.ppm");
	ofstream redFile(newName, ios::out);
	if (!redFile)
	{
		cerr << "Cannot write file \n";
		return;
	}
	redFile << magic << endl << width << " " << height << endl << max_num << endl;

	Color** histogramPixels = createHistogramArray();
	int* buffer = new int[width];
	for (int i = 0; i < width; i++)
	{
		buffer[i] = 0;
	}
	buffer = getRedValues(buffer, img);

	setPercentHistogram(buffer, img);
	setRedHistogramPixels(buffer,histogramPixels);
	writeHistogram(redFile, histogramPixels);

	clearHistogramArray();
	delete[] buffer;
	delete newName;

	redFile.close();
}

// ------ GREEN HISTOGRAM -------

void Histogram::greenHistogram(LoadImage* img,const char* filename)
{
	char* newName = ChangeFileName(filename, "_histogram_green.ppm");
	ofstream greenFile(newName, ios::out | ios::binary);
	if (!greenFile)
	{
		cerr << "Cannot write file \n";
		return;
	}
	greenFile << magic << endl << width << " " << height << endl << max_num << endl;

	Color** histogramPixels = createHistogramArray();
	int* buffer = new int[width];
	for (int i = 0; i < width; i++)
	{
		buffer[i] = 0;
	}
	buffer = getGreenValues(buffer, img);

	setPercentHistogram(buffer, img);
	setGreenHistogramPixels(buffer, histogramPixels);

	writeHistogram(greenFile, histogramPixels);

	clearHistogramArray();
	delete[] buffer;
	delete newName;

	greenFile.close();
}

// ------ BLUE HISTOGRAM -------

void Histogram::blueHistogram(LoadImage* img, const char* filename)
{
	char* newName = ChangeFileName(filename, "_histogram_blue.ppm");
	ofstream blueFile(newName, ios::out);
	if (!blueFile)
	{
		cerr << "Cannot write file \n";
		return;
	}
	blueFile << magic << endl << width << " " << height << endl << max_num << endl;

	Color** histogramPixels = createHistogramArray();
	int* buffer = new int[width];
	for (int i = 0; i < width; i++)
	{
		buffer[i] = 0;
	}
	buffer = getBlueValues(buffer, img);

	setPercentHistogram(buffer, img);
	setBlueHistogramPixels(buffer, histogramPixels);
	writeHistogram(blueFile, histogramPixels);

	clearHistogramArray();
	delete[] buffer;
	delete newName;

	blueFile.close();
}

// write histogram
void Histogram::writeHistogram(ostream& os, Color** hist)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			os << (int)hist[i][j].red<< " " << (int)hist[i][j].green << " " << (int)hist[i][j].blue << " ";
		}
	}
}

// precent formula
void Histogram::setPercentHistogram(int* buffer, Image* img)
{
	for (int i = 0; i < width; i++)
	{
		buffer[i] = (buffer[i] * 1000) /(img->getHeight()*img->getWidth());
	}
}

// ------ SET RGB VALUES -------

void Histogram::setRedHistogramPixels(int* buffer, Color** hist)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (i >= (99 - buffer[j]))
			{
				hist[i][j].red = 255;
				hist[i][j].green = 0;
				hist[i][j].blue = 0;
			}
		}
	}
}

void Histogram::setGreenHistogramPixels(int* buffer, Color** hist)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (i >= (99 - buffer[j]))
			{
				hist[i][j].red = 0;
				hist[i][j].green = 255;
				hist[i][j].blue = 0;
			}
		}
	}
}

void Histogram::setBlueHistogramPixels(int* buffer, Color** hist)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (i >= (99 - buffer[j]))
			{
				hist[i][j].red = 0;
				hist[i][j].green = 0;
				hist[i][j].blue = 255;
			}
		}
	}
}

// ------ GET RGB VALUES -------

int* Histogram::getRedValues(int* buffer, LoadImage* img)
{
	for (int i = 0; i < img->getHeight(); i++)
	{
		for (int j = 0; j < img->getWidth(); j++)
		{
			r = img->getPixels()[i][j].red;
			buffer[r]++;
		}
	}
	return buffer;
}

int* Histogram::getGreenValues(int* buffer, LoadImage* img)
{
	for (int i = 0; i < img->getHeight(); i++)
	{
		for (int j = 0; j < img->getWidth(); j++)
		{
			g = img->getPixels()[i][j].green;
			buffer[g]++;
		}
	}
	return buffer;
}

int* Histogram::getBlueValues(int* buffer, LoadImage* img)
{
	for (int i = 0; i < img->getHeight(); i++)
	{
		for (int j = 0; j < img->getWidth(); j++)
		{
			b = img->getPixels()[i][j].blue;
			buffer[b]++;
		}
	}
	return buffer;
}

// ------ CREATE HISTOGRAM ARRAY -------

Color** Histogram::createHistogramArray()
{
	pixels = new Color*[height];
	if (!pixels)
	{
		cerr << "Cannot allocate memory \n";
		exit(1);
	}
	for (int i = 0; i < height; i++)
	{
		pixels[i] = new Color[width];
		if (!pixels[i])
		{
			cerr << "Cannot allocate memory \n";
			exit(1);
		}
	}
	return pixels;
}

// ------ DELETE HISTOGRAM ARRAY -------

void Histogram::clearHistogramArray()
{
	if (pixels != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] pixels[i];
		}
		delete[] pixels;
		pixels = NULL;
	}
}
