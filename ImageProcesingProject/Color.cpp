#include"Color.h"

#include<iostream>

Color::Color()
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}

Color::Color(int r, int g, int b)
{
	this->red = r;
	this->green = g;
	this->blue = b;
}

Color::~Color()
{
}

// ------ SET RGB VALUES -------
void Color::setRed(int r)
{
	this->red = r;
}

void Color::setGreen(int g)
{
	this->green = g;
}

void Color::setBlue(int b)
{
	this->blue = b;
}

// ------ GET RGB VALUES -------
unsigned char Color::getRed() const
{
	return this->red;
}

unsigned char Color::getGreen() const
{
	return this->green;
}

unsigned char Color::getBlue() const
{
	return this->blue;
}
