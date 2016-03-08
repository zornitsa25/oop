#pragma once
#ifndef __P3__H
#define __P3__H

#include"Image.h"
#include"Color.h"
#include"LoadImage.h"

#include<iostream>
#include<fstream>
using namespace std;

class P3:public LoadImage
{
public:
	P3();
	virtual ~P3();

	virtual void Read(const char*);
	virtual void Grayscale(const char*);
	virtual void Monochrome(const char*);
private:
	int r, g, b;
};

#endif
