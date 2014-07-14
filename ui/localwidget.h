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
#include <QPushButton>
#include "simulatordata.h"

class localWidget: public QWidget
{
    Q_OBJECT
private:
    SimulatorData *simData;
    //dados TP
    QLabel *tp1Label;
    QLineEdit *tp1LineEdit;
    QLabel *tp2Label;
    QLineEdit *tp2LineEdit;

    //dados Breaker
    QTableWidget *breakerTable;

    //dados yltc
    QComboBox *combo;

    QLabel *modo;
    QLabel *pos;
    QLabel *posL;
    QLabel *posR;

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
    void saveYLTC ();

};


#endif // LOCALWIDGET_H
