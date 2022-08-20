#pragma once
class Image
{
#pragma pack(push,1)
	struct BMPFILEHEADER
	{
		unsigned short bfType;
		unsigned int   bfSize;
		unsigned short bfReserved1;
		unsigned short bfReserved2;
		unsigned int   bfOffBits;
	};
#pragma pack(pop)

	struct BITMAPINFOHEADER
	{
		unsigned long    biSize;           
		long             biWidth;           
		long             biHeight;          
		unsigned short   biPlanes;         
		unsigned short   biBitCount;       
											
		unsigned long    biCompression;     
											
		unsigned long    biSizeImage;      
		long             biXPelsPerMeter;  
		long             biYPelsPerMeter;   
		unsigned long    biClrUsed;       
		unsigned long    biClrImportant;   
	};
public:
	Image();
	Image(const char* ImageName);
	Image(const Image& im);
	~Image();
	void ReadBMP(const char* filename); 					
	void WriteBMP(const char* filename); 				
	void Flip(int code); 							
	void Resize(int code); 						
	void Crop(int x1, int y1, int x2, int y2);		
	void Rotate(int degree);							
	friend void Swap(Image& a, Image& b);				


	void Myfree(unsigned char** data,int height );
	
private:
	unsigned char** data;
	int height;
	int width;
	BMPFILEHEADER fh;
	BITMAPINFOHEADER ih;
};

