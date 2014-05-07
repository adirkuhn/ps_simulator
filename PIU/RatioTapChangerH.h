#ifndef OLTCH_H
#define OLTCH_H

#include <RatioTapChanger.h>
#include <LD.h>

class RatioTapChangerH: public RatioTapChanger
{
public:
    LD *ld;
    RatioTapChangerH();
};

#endif // OLTCH_H
