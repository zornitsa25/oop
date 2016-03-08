#pragma once
#ifndef __P6__H
#define __P6__H

#include"Image.h"
#include"Color.h"
#include"LoadImage.h"

#include<iostream>
#include<fstream>
using namespace std;

class P6 :public LoadImage
{
public:
	P6();
	virtual ~P6();

	virtual void Read(const char*);
	virtual void Grayscale(const char*);
	virtual void Monochrome(const char*);
private:
	int r, g, b;
};

#endif