#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QTimer>

class Simulator : public QObject
{
    Q_OBJECT

private:
    QTimer* timer;
    int     interval;

public:
    explicit Simulator( QObject *parent = 0 );

signals:
    void updatedData();

public slots:
    void execSimulation();

    void startPeriodicExec();
    void stopPeriodicExec();
};

#endif // SIMULATOR_H
