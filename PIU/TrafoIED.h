#ifndef TRAFOIED_H
#define TRAFOIED_H

#include <LD.h>
#include <YLTC.h>

#include <QDebug>

class TrafoIED: public LD
{
private:
    YLTC *YLTC1;

public:
    TrafoIED();
    void setLDName(QString name);
    QString getLDName();
    void setPos(int pos);
    int getPos();
    void setEndPosL(bool endPosL);
    bool getEndPosL();
    void setEndPosR(bool endPosR);
    bool getEndPosR();

};

#endif // TRAFOIED_H
