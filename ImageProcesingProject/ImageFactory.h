#pragma once
#ifndef __IMAGE_FACTORY__H
#define __IMAGE_FACTORY__H

#include "LoadImage.h"
#include"Histogram.h"
#include"P3.h"
#include"P6.h"

#include<fstream>

class ImageFactory
{
private:
	ImageFactory();
	ImageFactory(const ImageFactory&);
	ImageFactory& operator=(const ImageFactory&);
	~ImageFactory();
public:
	static bool CanCreateCommands(int argc, char* argv[]);
	static bool CanReadFile(const char* filename);
	static LoadImage* RecognizeImage(const char* filename);

public:
	static void findExecuteCommands(LoadImage* load, const char* filename, int argc, char* argv[]);
	static LoadImage* CreateImageObject(int argc, char* argv[]);
	
	static char* getImageName(int argc, char* argv[], int i);
	static char* ChangeFileName(const char* filename, const char* func);
};

#endif