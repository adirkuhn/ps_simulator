#include "simulator.h"

#include <QDebug>

Simulator::Simulator( QObject *parent ) :
    QObject( parent )
{
    timer = 0;

    this->interval = 1000;
}

void Simulator::execSimulation()
{
    qDebug() << "  obtendo dados do sistema IEC 61850 ...";

    qDebug() << "  executando algoritmo simulação ...";

    qDebug() << "  obtendo dados do simulador ...";

    qDebug() << "  atualizando dados para o sistema IEC 61850 ...";

    emit( updatedData() );
}

void Simulator::startPeriodicExec()
{
    if ( !timer )
    {
        timer = new QTimer( this );

        timer->setInterval( this->interval );

        QObject::connect( timer, SIGNAL( timeout() ),
                          this, SLOT( execSimulation() ) );
    }

    timer->start();

    qDebug() << "start periodic simulation";
}

void Simulator::stopPeriodicExec()
{
    timer->stop();

    qDebug() << "stop periodic simulation";
}
