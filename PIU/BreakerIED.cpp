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
    //DPStatus dpStatus;
    BOOLEAN ctVal;
    P_BOOLEAN val;

    switch(breakerStatus)
    {
        case BreakerStatus::open:
            //dpStatus.setVal(offOrFalse);
            val.setVal(false);
            break;

        case BreakerStatus::half_open:
            //dpStatus.setVal(intermediateState);
            qDebug() << "TODO: Precisa implementar!!!";
            qDebug() << "TODO: Sentando provisoriamente como false!!!";
            val.setVal(false);
            break;

        case BreakerStatus::closed:
            //dpStatus.setVal(onOrTrue);
            val.setVal(true);
            break;
    }

    ctVal.setVal(val);
    this->XCBR1->Pos.ctlVal.setAttr(ctVal);
    qDebug() << "Atribuido valor do Pos ao ctlVal. Agora precisa mudar posiçao do breaker e jogar o resultado em stVal";
    //this->XCBR1->Pos.stVal.setAttr(dpStatus);
    this->exec();
}

//TODO: Mudar a posiçao do breaker e setar valor no stVal
void BreakerIED::exec() {
    DPStatus dpStatus;

    dpStatus.setVal(offOrFalse);

    if (this->XCBR1->Pos.ctlVal.getAttr().getVal().getVal()) {
        dpStatus.setVal(onOrTrue);
    }

    //stVal
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
