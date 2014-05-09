#include "breakerh.h"

BreakerH::BreakerH()
{
    ld = new LD();
    xcbr = new XCBR();
}

void BreakerH::setPos(BreakerStatus pos)
{
    switch(pos)
    {
        case BreakerStatus::open:
            xcbr->Pos.stVal.getAttr().setVal(offOrFalse);
            break;

        case BreakerStatus::half_open:
            xcbr->Pos.stVal.getAttr().setVal(intermediateState);
            break;

        case BreakerStatus::closed:
            xcbr->Pos.stVal.getAttr().setVal(onOrTrue);
            break;
    }
}

DPStatusKind BreakerH::getPos() {
    return this->xcbr->Pos.stVal.getAttr().getVal();
}

void BreakerH::setName(QString name)
{
    //Breaker name
    this->name.str = name;
}

QString BreakerH::getName()
{
    return this->name.str;
}
