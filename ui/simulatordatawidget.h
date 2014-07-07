#ifndef SIMULATORDATAWIDGET_H
#define SIMULATORDATAWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>
#include <QTableView>
#include <QToolButton>
#include <QVBoxLayout>

class SimulatorDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimulatorDataWidget( QWidget *parent = 0 );

    void setupUi( QMainWindow *MainWindow );

    // Layout
    QVBoxLayout *mainLayout;

    QGridLayout *gridLayout;

    QHBoxLayout *btnLayout;

    // Widgets
    QPushButton *btnStartSimul, *btnStopSimul, *btnLocal;
    QToolButton *btnDir;

    QLabel    *dirLabel, *timerLabel;
    QTextEdit *dirLEdit, *timerLEdit;

    QTabWidget *tab;
    QTableView *dataTableView;

signals:

public slots:

};

#endif // SIMULATORDATAWIDGET_H
