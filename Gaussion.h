#pragma once
#include "Filter.h"
class Gaussion :
    public Filter
{
public:
    Gaussion() { this->FilterNumberToFather(3); };
    virtual Image FunctionFilter(const Image& m);
};
