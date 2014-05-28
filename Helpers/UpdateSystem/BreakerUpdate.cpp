#include "BreakerUpdate.h"

BreakerUpdate::BreakerUpdate(Breaker *breaker)
{
    this->breaker = breaker;
}

void BreakerUpdate::dataUpdate()
{
    qDebug() << "TODO:: Updata data equipment to IED";
}
