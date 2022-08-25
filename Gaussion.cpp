#include "Gaussion.h"
#include<iostream>
#include<algorithm>
Image Gaussion::FunctionFilter(const Image& m)
{
    int h = m.GetHeight();
    int w = m.GetWidth();
    int size = this->GetFilterNumber();

    DATA** rect = dataExpand(m);

    double* kernel = new double[size * size]{ 1.0/16,2.0/16,1.0/16,
                                              2.0/16,4.0/16,2.0/16,
                                              1.0/16,2.0/16,1.0/16 };

    for (int i{ 0 }; i < h; i++)
    {
        for (int j{ 0 }; j < w; j++)
        {
            double sumR{ 0 }, sumG{ 0 }, sumB{ 0 };
            int cnt{ 0 };
            for (int s{ i }; s < i + size; s++)
            {
                for (int r{ j }; r < j + size; r++)
                {
                    sumR += kernel[cnt] * rect[s][r].R;
                    sumG += kernel[cnt] * rect[s][r].G;
                    sumB += kernel[cnt] * rect[s][r].B;
                    cnt++;
                }
            }
            m.GetData()[i][j].R = sumR;
            m.GetData()[i][j].G = sumG;
            m.GetData()[i][j].B = sumB;

        }
    }
    delete[]kernel;
    return m;
}
