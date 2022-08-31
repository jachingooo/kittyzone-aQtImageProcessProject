#pragma once
#include<QString>
#include<QImage>
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
    unsigned long    biSize;            //本结构所占用字节数 40字节
    long             biWidth;           //位图的宽度，以像素为单位
    long             biHeight;          //位图的高度，以像素为单位
    unsigned short   biPlanes;          //目标设备的级别，必须为1
    unsigned short   biBitCount;        //每个像素所需的位数，必须是1（双色）、
                                        //4（16色）、8（256色）或24（真彩色）之一
    unsigned long    biCompression;     //位图压缩类型，必须是 0（BI_RGB不压缩）、
                                        //1（BI_RLE8压缩类型）
                                        //2（BI_RLE压缩类型）之一
    unsigned long    biSizeImage;       //位图的大小，以字节为单位
    long             biXPelsPerMeter;   //位图水平分辨率，每米像素数
    long             biYPelsPerMeter;   //位图垂直分辨率，每米像素数
    unsigned long    biClrUsed;         //位图实际使用的颜色表中的颜色数
    unsigned long    biClrImportant;    //位图显示过程中重要的颜色数
};

struct RGB
{
    double R;
    double G;
    double B;
    double serve;
};

struct DATA
{
    double R;
    double G;
    double B;
};


class Image
{
public:
    BMPFILEHEADER filehead;  // 文件头
    BITMAPINFOHEADER infohead;  // 信息头
    Image();
    Image(int h, int w);
    Image(int h, int w, DATA val);
    Image(const Image& m);

    DATA** GetData() const{ return this->data; };
    int GetHeight() const{ return this->height; };
    int GetWidth() const{ return this->width; };

    void ReadBMP(const char* filename);
    void WriteBMP(const char* filename);

    void Flip(bool mode);
    void Add(double delta);
    void Cut(int x1, int y1, int x2, int y2);
    void Rotate(int degree);
    void Cat(Image& m, int code);
    void Cold(double delta);
    void Warm(double delta);
    void Big(int code);
    int Sort(int a1[],int n);
    QImage* toQImage(Image n);
    QImage* SmoothMedianRGB(Image image);


private:
    int height;
    int width;
    DATA** data;
    BITMAPINFOHEADER ih;
};
