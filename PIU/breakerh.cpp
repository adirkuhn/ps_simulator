#include "breakerh.h"
#include <QDebug>

BreakerH::BreakerH()
{
    ld = new LD();
    xcbr = new XCBR();
}

void BreakerH::setPos(BreakerStatus pos)
{
    qDebug() << "Breaker Harmonization";
    qDebug() << this->xcbr->Pos.stVal.getAttr().getVal();


    switch(pos)
    {
        case BreakerStatus::open:
            qDebug() << "Open";
            xcbr->Pos.stVal.getAttr().setVal(offOrFalse);
            break;

        case BreakerStatus::half_open:
            qDebug() << "HALF-OPEN";
            xcbr->Pos.stVal.getAttr().setVal(intermediateState);
            break;

        case BreakerStatus::closed:
            qDebug() << "Closed";
            xcbr->Pos.stVal.getAttr().setVal(onOrTrue);
            break;
    }

    qDebug() << pos;
}
