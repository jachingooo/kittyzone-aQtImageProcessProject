#pragma once
#include"Image.h"
#include<vector>

using std::vector;

class Filter
{
public:
    Filter() : FilterNumber {0}{};
    Filter(int FilterNumber) { this->FilterNumber = FilterNumber; };

    void FilterNumberToFather(int FilterNumber_) { FilterNumber = FilterNumber_; };

    int GetFilterNumber() { return FilterNumber; };

    virtual Image FunctionFilter(const Image& m) = 0;

    DATA** dataExpand(const Image& m){

            int h = m.GetHeight();
            int w = m.GetWidth();
            DATA** dataExpand = new DATA*[h+FilterNumber-1];
            for (int i{ 0 }; i < h+FilterNumber-1; i++)
            {
                dataExpand[i] = new DATA[w+FilterNumber-1];
            }
            for (int i{ 0 }; i < h + FilterNumber - 1; i++)
            {
                for (int j{ 0 }; j < w + FilterNumber - 1; j++)
                {
                    dataExpand[i][j].R = 0;
                    dataExpand[i][j].G = 0;
                    dataExpand[i][j].B = 0;
                }
            }
            for (int i{ 0 }; i < h; i++)
            {
                for (int j{ 0 }; j < w; j++)
                {
                    dataExpand[i + FilterNumber / 2][j + FilterNumber / 2].R = m.GetData()[i][j].R;
                    dataExpand[i + FilterNumber / 2][j + FilterNumber / 2].G = m.GetData()[i][j].G;
                    dataExpand[i + FilterNumber / 2][j + FilterNumber / 2].B = m.GetData()[i][j].B;
                }
            }

            return dataExpand;


    };

private:
    int FilterNumber;
};
