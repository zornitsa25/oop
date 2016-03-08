#pragma once
#ifndef __IMAGE__H
#define __IMAGE__H

#include"Color.h"

#include<iostream>
#include<fstream>
using namespace std;

class Image
{
public:
	Image();
	Image(const Image& oldImage);
	Image& operator=(const Image& oldImage);
	~Image();

public:	
	Color** createPixelsArray(int height, int width);
	Color** getPixels() const;
	void setPixels(Color** rgb, int height, int width);

	void setMagic(const char*);
	void setWidth(int);
	void setHeight(int);
	void setMaxNum(int);

	const char* getMagic() const;
	int getWidth() const;
	int getHeight() const;
	int getMaxNum() const;

	int getLengthFile(ifstream&) const;

	char* ChangeFileName(const char* filename, const char* func);
	void SkipComment(ifstream& file);
	bool isGrayMonochrome();

protected:
	void clearPixels();

protected:
	Color** pixels;
	char magic[3];
	int width;
	int height;
	int max_num;
};

#endif