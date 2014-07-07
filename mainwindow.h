#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>
#include <QThread>

#include <simulator.h>
#include <simulatordata.h>

#include <ui/simulatordatawidget.h>
#include "ui/localwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

private:
    void setTable();

    void addStatusBar();

private:
    Ui::MainWindow *ui;

    QStatusBar *statusBar;

    SimulatorDataWidget *simDataWidget;

    QTableView *table;

    Simulator     *simulator;
    SimulatorData *simData;

    QThread thread;

public slots:
    void updateData();
    void openLocal();

};

#endif // MAINWINDOW_H
