#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QTimer>
#include <QTextEdit>
#include <ui/simulatordatawidget.h>

class Simulator : public QObject
{
    Q_OBJECT

private:
    QTimer* timer;
    int     interval;
    QString simTimeInterval;
    SimulatorDataWidget *simDataWidget;

    int getSimTimeInterval();


public:
    explicit Simulator( QObject *parent = 0 );
    void setSimDataWidget(SimulatorDataWidget *simDataWidget);

signals:
    void updatedData();

public slots:
    void execSimulation();

    void startPeriodicExec();
    void stopPeriodicExec();
};

#endif // SIMULATOR_H
