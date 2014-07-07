#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/localwidget.h"

#include <QDebug>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ), ui( new Ui::MainWindow )
{
    this->sender = new Sender();

    ui->setupUi(this);

    this->table = ui->dataTableView;

    simDataWidget = new SimulatorDataWidget( this );

    simDataWidget->setupUi( this );

    addStatusBar();

    this->table = simDataWidget->dataTableView;

    this->simData = new SimulatorData( this );

    setTable();

    this->simulator = new Simulator();
    this->simulator->setSimDataWidget(this->simDataWidget);


    // thread Timer
    this->simulator->moveToThread( &thread );
    thread.start();

    //desabilita botoes
    simDataWidget->btnStopSimul->setEnabled(false);

    // conecta botões Iniciar / Parar
    connect( simDataWidget->btnStartSimul, SIGNAL( clicked() ),
             this->simulator, SLOT( startPeriodicExec() ) );

    connect( simDataWidget->btnStopSimul, SIGNAL( clicked() ),
             this->simulator, SLOT( stopPeriodicExec() ) );

    // conecta ciclo simulação
    connect( this->simulator, SIGNAL( updatedData() ),
             this, SLOT( updateData() ) );
    //conecta botão abrir localissimo
    connect( simDataWidget->btnLocal, SIGNAL ( clicked()),
             this, SLOT(openLocal() ) );

    simDataWidget->timerLEdit->setText("6");
    qDebug() << simDataWidget->timerLEdit->toPlainText();

}

MainWindow::~MainWindow()
{
    //destroy thread
    this->thread.quit();
    this->thread.wait();

    delete sender;
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
    QJsonObject dataToSend;
    qDebug() << "    atualizando dados GUI ...";

    qDebug() << "------------------------------------------------------------";
    dataToSend = this->sender->encodeData(this->simData);
    this->sender->sendDatagram(dataToSend);
    qDebug() << "------------------------------------------------------------";

}

void MainWindow::openLocal(){

   qDebug() << "abrir janela localissimo";

   localWidget *win = new localWidget();
   win->setupUi(this->simData);
   win->show();




}

