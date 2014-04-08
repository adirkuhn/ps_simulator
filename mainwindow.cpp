#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent )//, ui( new Ui::MainWindow )
{
    //ui->setupUi(this);

    //this->table = ui->dataTableView;

    simDataWidget = new SimulatorDataWidget( this );

    simDataWidget->setupUi( this );

    addStatusBar();

    this->table = simDataWidget->dataTableView;

    this->simData = new SimulatorData( this );

    setTable();

    this->simulator = new Simulator();

    // thread Timer
    this->simulator->moveToThread( &thread );
    thread.start();

    // conecta botões Iniciar / Parar
    connect( simDataWidget->btnStartSimul, SIGNAL( clicked() ),
             this->simulator, SLOT( startPeriodicExec() ) );

    connect( simDataWidget->btnStopSimul, SIGNAL( clicked() ),
             this->simulator, SLOT( stopPeriodicExec() ) );

    // conecta ciclo simulação
    connect( this->simulator, SIGNAL( updatedData() ),
             this, SLOT( updateData() ) );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete simulator;
}

void MainWindow::addStatusBar()
{
    statusBar = new QStatusBar( this );

    statusBar->setObjectName( QStringLiteral( "statusBar" ) );

    this->setStatusBar( statusBar );
}

void MainWindow::setTable()
{
    table->setShowGrid( true );

    table->horizontalHeader()->show();
    table->verticalHeader()->show();

    table->horizontalHeader()->setMinimumSectionSize( 1 );
    table->verticalHeader()->setMinimumSectionSize( 1 );

    table->setModel( simData->getTableModel() );
}

void MainWindow::updateData()
{
    qDebug() << "    atualizando dados GUI ...";

}
