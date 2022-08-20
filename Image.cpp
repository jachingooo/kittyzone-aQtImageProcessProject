#include "Image.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

Image::Image()
{
	height = 0;
	width = 0;
	data = nullptr;
}
Image::Image(const char* ImageName)
{
	ReadBMP(ImageName);
}
Image::Image(const Image& im)
{
	height = im.height;
	width = im.width;
	ih = im.ih;
	fh = im.fh;
	data = (unsigned char**)malloc(sizeof(unsigned char*) * ih.biHeight);
	for (int i = 0; i < height; i++)
	{
		data[i] = (unsigned char*)malloc(ih.biWidth * 3);
		for (int j = 0; j < width*3; j++)
		{
			data[i][j] = im.data[i][j];
		}
	}
}
void Image::Myfree(unsigned char** data,int height)
{
	
		for (int i = 0; i < height; i++)
		{
			free(data[i]);
		}
		free(data);
	
}
Image::~Image()
{
	Myfree(data, height);
}

void Image::ReadBMP(const char* filename)
{

	FILE* fp;
	fopen_s(&fp, filename, "rb");
	fread(&fh, sizeof(fh), 1, fp);
	fread(&ih, sizeof(ih), 1, fp);
	height = ih.biHeight;
	width = ih.biWidth;

	int padding = width * 3 % 4 == 0 ? 0 : 4 - width * 3 % 4;
	data = (unsigned char**)malloc(sizeof(unsigned char*) * ih.biHeight);


	for (int i = 0; i < height; i++)
	{
		data[i] = (unsigned char*)malloc(ih.biWidth * 3);
		for (int j = 0; j < width * 3; j++)
		{

			fread(&data[i][j], 1, 1, fp);

		}

		if (padding != 0)
		{
			unsigned char dump;
			for (int p = 0; p < padding; p++)
			{
				fread(&dump, 1, 1, fp);
			}
		}

	}
	fclose(fp);
}

void Image::WriteBMP(const char* filename)
{
	FILE* fp;
	fopen_s(&fp, filename, "wb");
	int padding = width * 3 % 4 == 0 ? 0 : 4 - width * 3 % 4;
	fwrite(&fh, sizeof(fh), 1, fp);
	fwrite(&ih, sizeof(ih), 1, fp);


	for (int i = 0; i < height; i++)
	{
		fwrite(data[i], width * 3, 1, fp);
		if (padding != 0)
		{
			unsigned char dump = 0;
			for (int p = 0; p < padding; p++)
			{
				fwrite(&dump, 1, 1, fp);
			}
		}
	}
	fclose(fp);
}
void Image::Flip(int code)
{

	if (code == 0)
	{
		for (int i = 0; i < height / 2; i++)
		{
			unsigned char* temp = data[i];
			data[i] = data[height - 1 - i];
			data[height - 1 - i] = temp;


		}
		this->WriteBMP("上下翻转.bmp");
	
	}
	else
	{
		for (int i = 0; i < height ; i++)
		{
			for (int j = 0; j < width * 3 / 2; j =j+3)
			{
				unsigned char temp = data[i][j];
				data[i][j] = data[i][width * 3 - 1 - j - 2];
				data[i][width * 3 - 1 - j - 2] = temp;

				temp = data[i][j + 1];
				data[i][j + 1] = data[i][width * 3 - 1 - 1 - j];
				data[i][width * 3 - 1 - 1 - j] = temp;

				temp = data[i][j+2];
				data[i][j + 2] = data[i][width * 3 - 1 - j];
				data[i][width * 3 - 1 - j] = temp;
			}
		}
		this->WriteBMP("左右翻转.bmp");
	}
}

void Image::Resize(int code)
{
		if (code == 0)
		{
			int h = height / 2;
			int w = width / 2;
			unsigned char** d;
			d = (unsigned char**)malloc(sizeof(unsigned char*) * h);
			for (int i = 0; i < h; i++)
			{
				d[i] = (unsigned char*)malloc(w*3);
				for (int j = 0; j < w*3; j++)
				{
					d[i][j] = data[2 * i][2 * j];
				}
			}
			height = h;
			width = w;
			data = d;
			ih.biWidth = width;
			ih.biHeight = height;
			this->WriteBMP("缩小.bmp");
		}
		if(code==1)
		{
			int h = height * 4;
			int w = width * 4;
			unsigned char** d;
			d = (unsigned char**)malloc(sizeof(unsigned char*) * h);
			for (int i = 0; i < h; i++)
			{
				d[i] = (unsigned char*)malloc(w * 3);
				for (int j = 0; j < w*3; j++)
				{
					d[i][j] = data[i / 4][j / 4];
				}
			}
			height = h;
			width = w;
			data = d;
			ih.biWidth = width;
			ih.biHeight = height;
			this->WriteBMP("放大.bmp");
		}
}
