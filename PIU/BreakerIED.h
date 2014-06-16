#ifndef BREAKERIED_H
#define BREAKERIED_H

#include "LD.h"
#include "XCBR.h"
#include <QString>
#include <P_VISIBLE_STRING32.h>
#include <BreakerStatus.h>
#include <DPStatusKind.h>

#include <QDebug>

class BreakerIED: public LD
{
private:
    XCBR *XCBR1;
    XCBR *XCBR2;
    XCBR *XCBR3;

public:
    BreakerIED();

    void setLDName(QString name);
    QString getLDName();
    void setPos(int pos);
    int getPos();
    void exec();

};

#endif // BREAKERIED_H
