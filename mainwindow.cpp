#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/localwidget.h"

#include <QDebug>

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ), ui( new Ui::MainWindow )
{
    this->sender = new Sender();
    this->receiver = new Receiver();

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

    //setGoose
    //this->goose = new Goose();

    // thread Timer
    this->simulator->moveToThread( &thread );
    thread.start();

    //desabilita botoes
    simDataWidget->btnStopSimul->setEnabled(false);

    //leitura de pacotes
    connect(receiver->udpSocket, SIGNAL(readyRead()),
            receiver, SLOT(processPendingDatagrams()));

    connect(receiver, SIGNAL(multicastReceivedData(QJsonObject)),
            this, SLOT(processGooseCommand(QJsonObject)));

    // conecta botões Iniciar / Parar
    connect( simDataWidget->btnStartSimul, SIGNAL( clicked() ),
             this->simulator, SLOT( startPeriodicExec() ) );

    connect( simDataWidget->btnStopSimul, SIGNAL( clicked() ),
             this->simulator, SLOT( stopPeriodicExec() ) );

    // conecta ciclo simulação
    connect( this->simulator, SIGNAL( updatedData() ),
             this, SLOT( updateData() ) );
    // conecta botão abrir localissimo
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
    delete receiver;
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

    //enviar msg goose
    this->sendGoose();
}

void MainWindow::processGooseCommand(QJsonObject command) {
    qDebug() << "COMANDOS EM ACAO";
    qDebug() << command;

    //TODO: subindo provisoriamente o valor da barra, tem que mudar para alterar as posiçoes do tap de verdade com goose
    //Analog *analogMeas = dynamic_cast<Analog*>(this->simData->getCIMModel()->buses.at(0)->measurements.at(0));
    float novoTap = this->simData->getCIMModel()->getEqData("A2-220kV", "V").toFloat();
    //float novoTap = analogMeas->analogValues.at(0)->value.val;
    //float novoTap = 1;
    if (command["mudarTap"] == "up") {
        qDebug() << "ELA FEZ O TAP SUBIR";
        novoTap += 1;
    }
    else if (command["mudarTap"] == "down") {
        qDebug() << "TAP DOWN";
        novoTap -= 1;
    }
    qDebug() << "NOVO TAP";
    qDebug() << novoTap;
    this->simData->getCIMModel()->setEqData("A2-220kV", "V", novoTap);
    //this->table = this->simDataWidget->dataTableView;
    //this->table->setModel(this->simData->getTableModel());

}

void MainWindow::openLocal(){

   localWidget *win = new localWidget();
   win->setupUi(this->simData);
   win->show();
}

void MainWindow::sendGoose() {
    //breakers
    QList<BreakerIED*> bIed;
    bIed =  this->simData->getCIMModel()->getBreakersIED();

    for (int i=0; i < bIed.count(); i++) {
        bIed.at(i)->setMacAddress(i);
        bIed.at(i)->sendGoose();
    }
}
