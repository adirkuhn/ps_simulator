#include "mainwindow.h"
#include <QApplication>

void test();
int qt( int argc, char *argv[] );

int main( int argc, char *argv[] )
{
    //test();

    return qt( argc, argv );
}

int qt( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}

#include <stdio.h>

#include "MeasurementType.h"

#define MACROSTR(k) #k

typedef enum {
    Zero,
    kOne,
    kTwo,
    kThree
} kConst;

static char *kConstStr[] = {
    MACROSTR(Zero),
    MACROSTR(kOne),
    MACROSTR(kTwo),
    MACROSTR(kThree)
};

void test()
{
    for ( int k = 0; k < 4; ++k )
    {
        printf( "%s \n", kConstStr[k] );
    }

    printf( "%s \n", MeasurementType::toString( MeasurementType::status ).toLatin1().data() );
}
