#pragma once
#ifndef __RGB__H
#define __RGB__H

class Color
{
public:
	Color();
	Color(int r, int g, int b);
	~Color();

	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);

	unsigned char getRed() const;
	unsigned char getGreen() const;
	unsigned char getBlue() const;

	unsigned char red;
	unsigned char green;
	unsigned char blue;
};

#endif