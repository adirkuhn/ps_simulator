#include "BreakerIED.h"


BreakerIED::BreakerIED()
{
    this->XCBR1 = new XCBR();
    this->XCBR2 = new XCBR();
    this->XCBR3 = new XCBR();

}

void BreakerIED::setLDName(QString name) {
    P_VISIBLE_STRING32 tmpName;
    tmpName.setValue(name);

    this->setName(tmpName);
}

QString BreakerIED::getLDName() {
    return this->getName().getObjectName().getValue();
}

void BreakerIED::setPos(int pos) {
    BreakerStatus breakerStatus = BreakerStatus(BreakerStatus::enum_type(pos));
    DPStatus dpStatus;

    switch(breakerStatus)
    {
        case BreakerStatus::open:
            dpStatus.setVal(offOrFalse);
            break;

        case BreakerStatus::half_open:
            dpStatus.setVal(intermediateState);
            break;

        case BreakerStatus::closed:
            dpStatus.setVal(onOrTrue);
            break;
    }

    this->XCBR1->Pos.stVal.setAttr(dpStatus);
}

int BreakerIED::getPos() {
    int val;
    DPStatusKind sk = this->XCBR1->Pos.stVal.getAttr().getVal();

    switch(sk) {
        case offOrFalse:
            val = 0;
            break;
        case intermediateState:
            val = 1;
            break;
        case onOrTrue:
            val = 2;
            break;
    }

    return val;
}
