#ifndef SWITCHIED_H
#define SWITCHIED_H

#include "LD.h"
#include "XSWI.h"
#include <QString>
#include <P_VISIBLE_STRING32.h>
#include <DPStatusKind.h>
#include <qdebug.h>

class SwitchIED: public LD
{

private:
    XSWI *XSWI1;


public:
    SwitchIED();

    void setLDName(QString name);
    QString getLDName();
    void setPos(int pos);
    int getPos();
    void exec();
};

#endif // SWITCHIED_H
