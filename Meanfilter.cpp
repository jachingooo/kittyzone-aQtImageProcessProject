#include "MeanFilter.h"
#include <iostream>
#include <cmath>
MeanFilter::MeanFilter(int size) :Filter(size)
{
    filtersize = size;
}
MeanFilter:: ~MeanFilter()
{

}

Matrix MeanFilter::Filtering(const Matrix& input) 
{
    Matrix pp(input);
    int i, j;
    double qh;
    double s = filtersize * filtersize;
    int l, m;
    int f = filtersize;
    int w = (filtersize - 1) / 2;

    int new_h = input.Height() + 2 * (filtersize - 1);
    int new_w = input.Width() + 2 * (filtersize - 1);
    Matrix p(new_h, new_w, 1.0);

    for (i = 0; i < input.Height(); i++)
    {
        for (j = 0; j < input.Width(); j++)
        {
            p.data[i + f - 1][j + f - 1] = input.data[i][j];
        }
    }
    
    for (i = 0; i < f - 1; i++)
    {
        for (j = f - 1; j <= new_w - f; j++)
        {
            p.data[i][j] = p.data[2 * (f - 1) - 1 - i][j];
        }
    }

    for (i = new_h - f; i < new_h - 1; i++)
    {
        for (j = f - 1; j <= new_w - f; j++)
        {
            p.data[i][j] = p.data[2 * new_h - 2 * (f - 1) - i - 1][j];
        }
    }

    for (i = 0; i < new_h - 1; i++)
    {
        for (j = 0; j < f - 1; j++)
        {
            p.data[i][j] = p.data[i][2 * (f - 1) - 1 - j];
        }
    }

    for (i = 0; i < new_h - 1; i++)
    {
        for (j = new_w - f + 1; j < new_w - 1; j++)
        {
            p.data[i][j] = p.data[i][2 * new_w - 2 * (f - 1) - j - 1];
        }
    }

    for (i = f - 1; i <= new_h - f; i++)
    {
        for (j = f - 1; j <= new_w - f; j++)
        {
            qh = 0;
            for (l = 0; l < filtersize; l++) 
            {
                for (m = 0; m < filtersize; m++)
                {
                    qh = qh + p.data[i - w + l][j - w + m];
                }
            }
            pp.data[i - f + 1][j - f + 1] = qh / s;
        }
    }
    Image i29(pp);
    i29.WriteBMP("¾ùÖµ.bmp");
    return pp;

}
