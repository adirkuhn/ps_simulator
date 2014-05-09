#ifndef BREAKERH_H
#define BREAKERH_H

#include <Breaker.h>
#include <LD.h>
#include <XCBR.h>
//#include <DPStatusKind.h>
#include <BreakerStatus.h>
#include <DPStatus_ST_dchg.h>

class BreakerH : public Breaker
{
public:
    LD *ld;
    XCBR *xcbr;

    BreakerH();
    void setPos(BreakerStatus pos);
    DPStatusKind getPos();
    void setName(QString name);
    QString getName();
};

#endif // BREAKERH_H
