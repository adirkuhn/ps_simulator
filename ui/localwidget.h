#ifndef LOCALWIDGET_H
#define LOCALWIDGET_H


#include<QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QTabWidget>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include "simulatordata.h"

class localWidget: public QWidget
{
    Q_OBJECT
private:
    SimulatorData *simData;

    //dados yltc
    QLineEdit *modoline;
    QLineEdit *linepos;
    QLineEdit *lineL;
    QLineEdit *lineR;

    QCheckBox *localbox;
    QCheckBox *remotobox;


public:
    localWidget();

    void setupUi (SimulatorData *simData);

    void localTP (QTabWidget *mainTab);
    void localBreakers (QTabWidget *mainTab);
    void LocalYLTC (QTabWidget *mainTab);

public slots:
    void refreshYLTC(int index);
};


#endif // LOCALWIDGET_H
