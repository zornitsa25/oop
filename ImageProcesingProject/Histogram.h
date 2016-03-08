#pragma once
#ifndef __HISTOGRAM__H
#define __HISTOGRAM__H

#include"Image.h"
#include"LoadImage.h"

class Histogram:public Image
{
public:
	Histogram();
	~Histogram();

public:
	int* getRedValues(int*, LoadImage*);
	int* getGreenValues(int*, LoadImage*);
	int* getBlueValues(int*, LoadImage*);

	Color** createHistogramArray();
	void clearHistogramArray();

	void setPercentHistogram(int* buffer, Image* img);

	void setGreenHistogramPixels(int* buffer, Color** hist);
	void setRedHistogramPixels(int* buffer, Color** hist);
	void setBlueHistogramPixels(int* buffer, Color** hist);

	void writeHistogram(ostream& os, Color** hist);
public:
	void redHistogram(LoadImage* img,const char* filename);
	void greenHistogram(LoadImage* img, const char* filename);
	void blueHistogram(LoadImage* img, const char* filename);

public:
	//void histogramP1(LoadImage* img, const char* filename);

private:
	int r, g, b;
};

#endif