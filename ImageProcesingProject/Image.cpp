#include"Image.h"

#include<iostream>
#include<fstream>
using namespace std;

Image::Image()
{
	pixels = NULL;
	magic[3] = {};
	width =0;
	height=0;
	max_num=0;
}

Image::Image(const Image& other)
{
	*this = other;
}

Image& Image::operator=(const Image& other)
{
	if (&other != this)
	{
		setMagic(other.getMagic());
		setWidth(other.getWidth());
		setHeight(other.getHeight());
		setMaxNum(other.getMaxNum());

		setPixels(other.pixels,other.height,other.width);
	}
	return *this;
}

Image::~Image()
{
}

// copy array into pixels array
void Image::setPixels(Color** rgb,int h,int w)
{
	pixels = new (std::nothrow) Color*[h];
	if (pixels)
	{
		for (int i = 0; i < h; i++)
		{
			pixels[i] = new (std::nothrow) Color[w];

			if (!pixels[i])
			{
				cerr << "Cannot allocate memory \n";
				clearPixels();
				return;
			}
		}
	}
	if (rgb != NULL)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				pixels[i][j] = rgb[i][j];
			}
		}
	}
}

// ------ SET HEADER FUNCTIONS -------

void Image::setMagic(const char* magic)
{
	strcpy(this->magic, magic);
}

void Image::setWidth(int width)
{
	this->width = width;
}
void Image::setHeight(int height)
{
	this->height = height;
}
void Image::setMaxNum(int max)
{
	this->max_num = max;
}

// ------ GET HEADER FUNCTIONS -------

const char* Image::getMagic() const
{
	return this->magic;
}
int Image::getWidth() const
{
	return this->width;
}
int Image::getHeight() const
{
	return this->height;
}
int Image::getMaxNum() const
{
	return this->max_num;
}

// returns pixels array from the base class
Color** Image::getPixels() const
{
	return pixels;
}

// ------ CREATE PIXELS ARRAY -------
Color** Image::createPixelsArray(int height,int width)
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

// ------ DELETE PIXELS ARRAY -------
void Image::clearPixels()
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

// returns size of the file
int Image::getLengthFile(ifstream& file) const
{
	file.seekg(0, ios::end);
	int bytes = file.tellg();
	int length = bytes / sizeof(Color);

	file.seekg(0, ios::beg);
	return length;
}

// checks if the image is already grayscale or monochrome
bool Image::isGrayMonochrome()
{
	for (int i = 0; i < getHeight(); i++)
	{
		for (int j = 0; j < getWidth(); j++)
		{

			if (getPixels()[i][j].red!=getPixels()[i][j].green ||
				getPixels()[i][j].green!=getPixels()[i][j].blue ||
				getPixels()[i][j].red!=getPixels()[i][j].blue)
			{
				return false;
			}
		}
	}
	return true;
}

// must delete char* buff after using the function
char* Image::ChangeFileName(const char* filename, const char* func)
{
	char* buff = new char[50];
	int i = 0;
	while (filename[i] != '.')
	{
		buff[i] = filename[i];
		i++;
	}
	int lengthFile = strlen(func) + 1;
	for (int j = 0; j < lengthFile; j++)
	{
		buff[i] = func[j];
		i++;
	}
	buff[i] = '\0';
	return buff;
}

void Image::SkipComment(ifstream& file)
{
	char linebuf[1024];
	char comment;

	//returns the next character in the input sequence, without extracting it
	//http://www.cplusplus.com/reference/istream/istream/peek/?kw=peek
	while (comment = file.peek(), comment == '\n' || comment == '\r')
	{
		// extracts a single character from the stream
		//http://www.cplusplus.com/reference/tuple/get/?kw=get
		file.get();
	}
	if (comment == '#')
	{
		file.getline(linebuf, 1023);
	}
}