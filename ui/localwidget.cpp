/****************************************************************************
** Meta object code from reading C++ file 'localwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "localwidget.h"
#include <QDebug>


localWidget::localWidget()
{
}

void localWidget::setupUi(SimulatorData *simData){

    //trás os dados do simData
    this->simData = simData;


    //layout principal
    QGridLayout *mainLayout = new QGridLayout;



    //layout local, tabs e botao save
    QTabWidget *localTabs = new QTabWidget;
    QPushButton *savebtn = new QPushButton("Salvar");

    //SIGNAL para chamar a função que salva os dados da tela no modelo
    connect (savebtn, SIGNAL(clicked()),this, SLOT(saveYLTC()));

    //adiciona equips
    localTP(localTabs);
    localBreakers (localTabs);
    LocalYLTC(localTabs);
    localSwitches(localTabs);

    //adiciona as tabs
    mainLayout->addWidget(localTabs, 0,0);
    mainLayout->addWidget(savebtn, 1, 0);

    //seta layout principal na janela
    this->setLayout(mainLayout);


}

void localWidget::localTP(QTabWidget *mainTab){

    //tp layout
    QGridLayout *tpMainLayout = new QGridLayout;
    QGroupBox *tpBox = new QGroupBox;

    //tp1
    this->tp1Label = new QLabel(this->simData->getCIMModel()->getBusesIED()[0]->getLDName());
    this->tp1LineEdit = new QLineEdit(QString("%1").arg(this->simData->getCIMModel()->getBusesIED()[0]->getVol()));



    tpMainLayout->addWidget(tp1Label, 0, 0);
    tpMainLayout->addWidget(tp1LineEdit, 0, 1, 1, 2);


    //tp2
    this->tp2Label = new QLabel(this->simData->getCIMModel()->getBusesIED()[1]->getLDName());
    this->tp2LineEdit = new QLineEdit(QString("%1").arg(this->simData->getCIMModel()->getBusesIED()[1]->getVol()));

    tpMainLayout->addWidget(tp2Label, 1, 0);
    tpMainLayout->addWidget(tp2LineEdit, 1, 1, 1, 2);

    //add tab
    tpBox->setLayout(tpMainLayout);
    mainTab->addTab(tpBox, "TP");
}

void localWidget::localBreakers(QTabWidget *mainTab) {

    //Breaker Layout
    QGroupBox *breakerBox = new QGroupBox;
    QHBoxLayout *breakerLayout = new QHBoxLayout;
    this->breakerTable = new QTableWidget;

    //populate table
    breakerTable->insertColumn(0);
    breakerTable->insertColumn(1);

    breakerTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Breaker"));
    breakerTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Status"));


    for(int i=0; i<this->simData->getCIMModel()->getBreakersIED().size(); i++) {
        breakerTable->insertRow(i);

        breakerTable->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(this->simData->getCIMModel()->getBreakersIED().at(i)->getLDName())));
        breakerTable->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(this->simData->getCIMModel()->getBreakersIED().at(i)->getPos())));
    }

    breakerLayout->addWidget(breakerTable);

    //add tab
    breakerBox->setLayout(breakerLayout);
    mainTab->addTab(breakerBox, "Breakers");
}

void localWidget::localSwitches(QTabWidget *mainTab) {

    //Breaker Layout
    QGroupBox *switchBox = new QGroupBox;
    QHBoxLayout *switchLayout = new QHBoxLayout;
    this->switchTable = new QTableWidget;

    //populate table
    switchTable->insertColumn(0);
    switchTable->insertColumn(1);

    switchTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Breaker"));
    switchTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Status"));


    for(int i=0; i<this->simData->getCIMModel()->getSwitchesIED().size(); i++) {
        switchTable->insertRow(i);

        switchTable->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(this->simData->getCIMModel()->getSwitchesIED().at(i)->getLDName())));
        switchTable->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(this->simData->getCIMModel()->getSwitchesIED().at(i)->getPos())));
    }

    switchLayout->addWidget(switchTable);

    //add tab
    switchBox->setLayout(switchLayout);
    mainTab->addTab(switchBox, "Switches");
}

void localWidget::LocalYLTC(QTabWidget *mainTab){

    //Layout
    QGridLayout *yltcLayout = new QGridLayout;

    QGroupBox *yltcBox = new QGroupBox;

    //comboBox
    this->combo = new QComboBox;

    for (int i=0; i<this->simData->getCIMModel()->getTrafosIED().size(); i++) {

        combo->insertItem(i, QString("%1").arg(this->simData->getCIMModel()->getTrafosIED().at(i)->getLDName()));
    }

    //SIGNAL para chamar a função que atualiza os dados da tela de acordo com o index selecionado no combo box
    connect (combo, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshYLTC(int)));



    //campos

    this->modo = new QLabel("Modo");
    this->pos = new QLabel("Pos");
    this->posL = new QLabel("Pos L");
    this->posR = new QLabel("Pos R");

    this->modoline = new QLineEdit;
    this->linepos = new QLineEdit;
    this->lineL = new QLineEdit;
    this->lineR = new QLineEdit;
    this->refreshYLTC(0);

    this->localbox = new QCheckBox ("Local");
    this->remotobox = new QCheckBox ("Remoto");

    //adiciona os capmos na tela
    yltcLayout->addWidget(combo, 0,0);
    yltcLayout->addWidget(modo, 1, 0);
    yltcLayout->addWidget(pos, 2, 0);
    yltcLayout->addWidget(posL,3, 0);
    yltcLayout->addWidget(posR,4, 0);
    yltcLayout->addWidget(modoline, 1, 1, 1, 2);
    yltcLayout->addWidget(linepos, 2, 1, 1, 2);
    yltcLayout->addWidget(lineL, 3, 1, 1, 2);
    yltcLayout->addWidget(lineR, 4, 1, 1, 2);
    yltcLayout->addWidget(localbox, 5,0);
    yltcLayout->addWidget(remotobox, 5,1);





     //add tab
    yltcBox->setLayout(yltcLayout);
    mainTab->addTab(yltcBox, "YLTC");
}

//lê os campos de cada YLTC de acordo com o index do combo box
void localWidget::refreshYLTC (int index) {
    qDebug () << "refresh";
    qDebug () << index;
    this->modoline->setText("slave/master");
    this->linepos->setText(QString("%1").arg(this->simData->getCIMModel()->getTrafosIED().at(index)->getPos()));
    this->lineL->setText(QString("%1").arg(this->simData->getCIMModel()->getTrafosIED().at(index)->getEndPosL()));
    this->lineR->setText(QString("%1").arg(this->simData->getCIMModel()->getTrafosIED().at(index)->getEndPosR()));
}

void localWidget::saveYLTC(){
    qDebug() << this->tp1Label->text();

    //tp
    this->simData->getCIMModel()->setEqData(this->tp1Label->text(), "V", this->tp1LineEdit->text());
    this->simData->getCIMModel()->setEqData(this->tp2Label->text(), "V", this->tp2LineEdit->text());

    //breaker
    for(int i=0; i<this->breakerTable->rowCount(); i++) {

        this->simData->getCIMModel()->setEqData(this->breakerTable->item(i,0)->text(), "status", this->breakerTable->item(i, 1)->text());

    }

    //YLTC - TODO MODO - CHECKBOX - ainda não tem no modelo de dados
    this->simData->getCIMModel()->setEqData(this->combo->currentText(), "status", this->linepos->text());


}
