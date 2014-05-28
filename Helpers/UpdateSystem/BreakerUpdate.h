#ifndef BREAKERUPDATE_H
#define BREAKERUPDATE_H

#include "Breaker.h"
#include "XCBR.h"
#include "IEquipmentDataUpdate.h"
#include "QDebug"

class BreakerUpdate: public IEquipmentDataUpdate
{
private:
    Breaker* breaker;
    QList<XCBR*> breakerIEDSubscribers;

public:
    BreakerUpdate(Breaker *breaker);
    void dataUpdate();
};

#endif // BREAKERUPDATE_H
