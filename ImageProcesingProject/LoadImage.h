#pragma once
#ifndef __LOADIMAGE__H
#define __LOADIMAGE__H

#include"Image.h"

#include<iostream>
#include<fstream>
using namespace std;

class LoadImage:public Image
{
public:
	LoadImage();
	virtual ~LoadImage();

	virtual void Read(const char*) = 0;
	virtual void Grayscale(const char*) = 0;
	virtual void Monochrome(const char*) = 0;

	int grayscale(int r, int g, int b);
	int monochrome(int grayscale);
};

#endif