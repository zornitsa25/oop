#include"LoadImage.h"

LoadImage::LoadImage()
{
}
LoadImage::~LoadImage()
{
}

// grayscale algorithm
int LoadImage::grayscale(int r, int g, int b)
{
	int sum = (r + g + b) / 3;
	return sum;
}

// monochrome algorithm
int LoadImage::monochrome(int grayscale)
{
	int white = 255;
	int black = 0;
	if (grayscale < 128)
	{
		return black;
	}
	else
	{
		return white;
	}
}

// Luminance (0.299*R + 0.587*G + 0.114*B)