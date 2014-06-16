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
    void setPos(int pos);
    int getPos();
//    void setEndPosL(int endPosL);
//    int getEndPosL();
//    void setEndPosR(int);
//    int getEndPosR();

};

#endif // TRAFOIED_H
