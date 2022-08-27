#ifndef MEANFILTER_H
#define MEANFILTER_H

#include "Filter.h"
class MeanFilter : public Filter
{
public:
    MeanFilter(int size);
    virtual ~MeanFilter();
    virtual Matrix Filtering(const Matrix& input); 
};

#endif
