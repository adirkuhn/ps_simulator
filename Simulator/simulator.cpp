#include "simulator.h"

#include <QDebug>


Simulator::Simulator(QObject *parent ): QObject( parent )
{
    this->timer = 0;
}

int Simulator::getSimTimeInterval()
{
    this->simTimeInterval = this->simDataWidget->timerLEdit->toPlainText();

    return this->simTimeInterval.toInt() * 1000;
}

void Simulator::setSimDataWidget(SimulatorDataWidget *simDataWidget)
{
    this->simDataWidget = simDataWidget;
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
    if ( !this->timer )
    {

        this->timer = new QTimer( this );

        this->timer->setInterval( this->getSimTimeInterval() );

        QObject::connect( this->timer, SIGNAL( timeout() ),
                          this, SLOT( execSimulation() ) );
    }
    else {
        this->timer->setInterval(this->getSimTimeInterval());
    }

    this->timer->start();

    qDebug() << "start periodic simulation";
    qDebug() << this->getSimTimeInterval();
}

void Simulator::stopPeriodicExec()
{
    if (this->timer) {
        this->timer->stop();
    }

    qDebug() << "stop periodic simulation";
}
