#include "tuxiang.h"
#include<iostream>



QImage* Image::toQImage(Image n)
{
    uchar* data = new unsigned char[n.GetHeight()*n.GetWidth()*3];
    uchar* newdata = data;
    n.Flip(1);
    for(int i{0};i<n.GetHeight();i++)
    {
        for(int j{0};j<n.GetWidth();j++)
        {
            data[(i*n.GetWidth()+j)*3] = (uchar)n.data[i][j].B;
            data[(i*n.GetWidth()+j)*3+1] = (uchar)n.data[i][j].G;
            data[(i*n.GetWidth()+j)*3+2] = (uchar)n.data[i][j].R;
        }
    }

    QImage* img = new QImage(newdata,n.GetWidth(),n.GetHeight(),QImage::Format_RGB888);

    return img;
}

Image::Image()
{
    this->height = 0;
    this->width = 0;
    this->data = nullptr;
}


Image::Image(int h, int w)
{
    this->height = h;
    this->width = w;
    this->data = new DATA* [height];
    for (int i{ 0 }; i < h; i++)
    {
        data[i] = new DATA[width];
    }
}

Image::Image(int h, int w, DATA val)
{
    this->height = h;
    this->width = w;
    for (int i{ 0 }; i < h; i++)
    {
        data[i] = new DATA[width];
        for (int j{ 0 }; j < width; j++)
        {
            data[i][j] = val;
        }
    }
}


Image::Image(const Image& m)
{
    this->height = m.height;
    this->width = m.width;
    data = new DATA* [height];
    for (int i{ 0 }; i < m.height; i++)
    {
        data[i] = new DATA[width];
        for (int j{ 0 }; j < m.width; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
    this->filehead = m.filehead;
    this->infohead = m.infohead;
}

//从硬盘读入图像文件;
void Image::ReadBMP(const char* filename)

{
    FILE* fp = nullptr;
    fopen_s(&fp, filename, "rb");
    // 读取文件头
    fread(&filehead, sizeof(BMPFILEHEADER), 1, fp);
    // 读取信息头
    fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);
    height = infohead.biHeight;
    width = infohead.biWidth;
    data = new DATA* [height];
    for (int i{ 0 }; i < height; i++)
    {
        data[i] = new DATA[width];
    }

    unsigned char R, G, B;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fread(&R, sizeof(unsigned char), 1, fp);
            fread(&G, sizeof(unsigned char), 1, fp);
            fread(&B, sizeof(unsigned char), 1, fp);
            data[i][j].R = R;
            data[i][j].G = G;
            data[i][j].B = B;
        }
    }
    fclose(fp);
}

//保存图像;
void Image::WriteBMP(const char* filename)
{
    FILE* fp2 = NULL; // 保存文件的文件指针
    fopen_s(&fp2, filename, "wb+"); // 二进制写入方式打开文件
    // 写入文件头
    fwrite(&filehead, sizeof(BMPFILEHEADER), 1, fp2);
    // 写入信息头
    fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp2);
    // 写入数据
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char m_R = (unsigned char)data[i][j].R;
            unsigned char m_G = (unsigned char)data[i][j].G;
            unsigned char m_B = (unsigned char)data[i][j].B;
            fwrite(&m_R, sizeof(unsigned char), 1, fp2);
            fwrite(&m_G, sizeof(unsigned char), 1, fp2);
            fwrite(&m_B, sizeof(unsigned char), 1, fp2);

        }
        if (width % 4 != 0)
        {
            for (int i{ 0 }; i < width % 4; i++)
                fwrite(&i, sizeof(unsigned char), 1, fp2);
        }
    }
    fclose(fp2);
}
void chg(double& a, double& b)
{
    unsigned char t = a;
    a = b;
    b = t;
}

//false 左右，true 上下;
void Image::Flip(bool mode)
{

    if (mode)
    {
        for (int i = 0; i < height / 2; i++)
        {
            for (int j = 0; j < width; j++)
            {
                chg(data[i][j].R,data[height - i - 1][j].R);
                chg(data[i][j].G,data[height - i - 1][j].G);
                chg(data[i][j].B,data[height - i - 1][j].B);
            }
        }
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width / 2; j++)
            {
                chg(data[i][j].R,data[i][width - j - 1].R);
                chg(data[i][j].G,data[i][width - j - 1].G);
                chg(data[i][j].B,data[i][width - j - 1].B);
            }
        }
    }
}

void Image::Add(double delta)
{
    for (int i{ 0 }; i < height; i++)
    {
        for (int j{ 0 }; j < width; j++)
        {
            data[i][j].R+=delta;
            if(data[i][j].R<0)  data[i][j].R=0;
            else if(data[i][j].R>255) data[i][j].R=255;

            data[i][j].G+=delta;
            if(data[i][j].G<0)  data[i][j].G=0;
            else if(data[i][j].G>255) data[i][j].G=255;

            data[i][j].B+=delta;
            if(data[i][j].B<0)  data[i][j].B=0;
            else if(data[i][j].B>255) data[i][j].B=255;
        }
    }
}

void Image::Cut(int x1, int y1, int x2, int y2)
{
    infohead.biHeight = y2 - y1;
    infohead.biWidth = x2 - x1;
    height = infohead.biHeight;
    width = infohead.biWidth;
    infohead.biSizeImage = height * width;
    for (int i{ 0 }; i < y2 - y1; i++)
    {
        for (int j{ 0 }; j < x2 - x1; j++)
        {
            data[i][j] = data[i + x1][j + y1];
        }
    }
}

//图像旋转的函数
void Image::Rotate(int degree)
{
    if (degree > 0)
    {
        for (int k{ 0 }; k < degree / 90; k++)
        {
            Flip(true);
            for (int i{ 0 }; i < height; i++)
            {
                for (int j{ i + 1 }; j < width; j++)
                {
                    DATA temp = data[i][j];
                    data[i][j] = data[j][i];
                    data[j][i] = temp;

                }
            }
        }
    }
    else
    {
        degree *= -1;
        for (int k{ 0 }; k < degree / 90; k++)
        {
            Flip(true);
            for (int i{ 0 }; i < height; i++)
            {
                for (int j{ 0 }; j < width - 1 - i; j++)
                {
                    DATA temp = data[i][j];
                    data[i][j] = data[width - 1 - i][width - 1 - i];
                    data[width - 1 - i][width - 1 - i] = temp;

                }
            }
        }
    }
}

void Image::Cat(Image& m, int code)
{
    int newHeight{height};
    int newWidth{width};
    height = infohead.biHeight;
    width = infohead.biWidth;
    if (code == 1)
    {
        newWidth += m.width;
        infohead.biWidth += m.width;
        infohead.biSizeImage = newHeight * newWidth;
    }
    else
    {
        newHeight += m.height;
        infohead.biHeight += m.height;
        infohead.biSizeImage = newHeight * newWidth;
    }
    DATA** newData=new DATA*[newHeight];
    //创建好新的空矩阵
    for (int i = 0; i < newHeight; i++)
    {
        newData[i] = new DATA[newWidth];
    }
    if (code == 1)
    {
        for (int i = 0; i < newHeight; i++)
        {
            int j;
            for (j = 0; j < width; j++)
            {
                newData[i][j] = data[i][j];
            }
            for (j = 0; j < m.width; j++)
            {
                newData[i][j + width] = m.data[i][j];
            }
        }
    }
    else
    {
        for (int i{ 0 }; i < height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                newData[i][j] = m.data[i][j];
            }
        }
        for (int i{0}; i < m.height; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                newData[i+m.height][j] = data[i][j];
            }
        }
    }
    for (int i{ 0 }; i < height; i++)
    {
        delete[]data[i];
    }
    data = newData;
    height = newHeight;
    width = newWidth;
}

void Image::Cold(double delta)
{
    for (int i{ 0 }; i < height; i++)
    {
        for (int j{ 0 }; j < width; j++)
        {
            data[i][j].R+=delta;
            if(data[i][j].R<0)  data[i][j].R=0;
            else if(data[i][j].R>255) data[i][j].R=255;

            data[i][j].G-=delta;
            if(data[i][j].G<0)  data[i][j].G=0;
            else if(data[i][j].G>255) data[i][j].G=255;

            data[i][j].B-=delta;
            if(data[i][j].B<0)  data[i][j].B=0;
            else if(data[i][j].B>255) data[i][j].B=255;
        }
    }
}
int Image:: Sort(int a1[],int n){
        int k;
        int j;
        int c;
        for (int i = 0;i<n;i++)
        {
            k = i;
            for(j = k +1;j<n;j++)
            {
            if (a1[i]>a1[j])
            {
                c = a1[j];
                a1[j] = a1[i];
                a1[i] = c;
            }
            }
        }
        return a1[n/2];
}
QImage* Image::SmoothMedianRGB(Image n)
{   uchar* data = new unsigned char[n.GetHeight()*n.GetWidth()*3];
    uchar* newdata = data;
    QImage* image = new QImage(newdata,n.GetWidth(),n.GetHeight(),QImage::Format_ARGB32);
    QImage* newImage = new QImage(image->width(),image->height(),QImage::Format_ARGB32);
    int kernel [3][3] = {
    {1,1,1},
    {1,1,1},
    {1,1,1}};
    int sizeKernel = 3;
    int sizeKernel1= sizeKernel* sizeKernel;
    int sumKernel = 1;
    QColor color;
     for(int x = sizeKernel/2;x<image->width() - sizeKernel/2;x++)
    {
       for(int y= sizeKernel/2;y<image->height() - sizeKernel/2;y++)
        {
           int * rgb1 = new int [ sizeKernel1];
           int * rgb2 = new int [sizeKernel1];
           int * rgb3 = new int [sizeKernel1];
           int rgb = 0;
            int r = 0;
            int g = 0;
            int b = 0;
            for(int i = -sizeKernel/2;i<=sizeKernel/2;i++)
            {
               for(int j = -sizeKernel/2;j<=sizeKernel/2;j++)
                {
                 color = QColor(image->pixel(x+i,y+j));

                 rgb1[rgb]=color.red()*kernel[sizeKernel/2+i][sizeKernel/2+j];
                 rgb2[rgb]=color.green()*kernel[sizeKernel/2+i][sizeKernel/2+j];
                 rgb3[rgb]=color.blue()*kernel[sizeKernel/2+i][sizeKernel/2+j];
                 rgb ++;
                 if (rgb == sizeKernel1)
                 {
                     r = Sort(rgb1,sizeKernel1);
                     g = Sort(rgb2,sizeKernel1);
                     b = Sort(rgb3,sizeKernel1);
                 }
                }
            }
            r = qBound(0,r/sumKernel,255);
            g = qBound(0,g/sumKernel,255);
            b = qBound(0,b/sumKernel,255);
            newImage->setPixel(x,y,qRgb( r,g,b));
            delete [] rgb1;
            delete [] rgb2;
            delete [] rgb3;
        }
    }

    return newImage;


}
void Image::Warm(double delta)
{
    for (int i{ 0 }; i < height; i++)
    {
        for (int j{ 0 }; j < width; j++)
        {

            data[i][j].R-=delta;
            if(data[i][j].R<0)  data[i][j].R=0;
            else if(data[i][j].R>255) data[i][j].R=255;

            data[i][j].G+=delta;
            if(data[i][j].G<0)  data[i][j].G=0;
            else if(data[i][j].G>255) data[i][j].G=255;

            data[i][j].B+=delta;
            if(data[i][j].B<0)  data[i][j].B=0;
            else if(data[i][j].B>255) data[i][j].B=255;
        }
    }
}
void Image::Big(int code){

    height = infohead.biHeight;
    width = infohead.biWidth;
    infohead.biSizeImage = height * width;
    if (code == 0)
            {
                int h = height / 2;
                int w = width / 2;
                DATA** d;
                d = (DATA**)malloc(sizeof( DATA*) * h);
                for (int i = 0; i < h; i++)
                {
                    d[i] = (DATA*)malloc(w*3);
                    for (int j = 0; j < w*3; j++)
                    {
                        d[i][j] = data[2 * i][2 * j];
                    }
                }
                height = h;
                width = w;
                infohead.biWidth = width;
                infohead.biHeight = height;
                data = d;

            }
            if(code==1)
            {
                int h = height * 4;
                int w = width * 4;
                DATA** d;
                d = (DATA**)malloc(sizeof(DATA*) * h);
                for (int i = 0; i < h; i++)
                {
                    d[i] = (DATA*)malloc(w * 3);
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
                data = d;
                height = h;
                width = w;
                this->WriteBMP("放大.bmp");
                this->ReadBMP("放大.bmp");
            }

}

