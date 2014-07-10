/****************************************************************************
** Meta object code from reading C++ file 'localwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "localwidget.h"
#include <QDebug>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'localwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_localWidget_t {
    QByteArrayData data[4];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_localWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_localWidget_t qt_meta_stringdata_localWidget = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 11),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 5)
    },
    "localWidget\0refreshYLTC\0\0index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_localWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void localWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        localWidget *_t = static_cast<localWidget *>(_o);
        switch (_id) {
        case 0: _t->refreshYLTC((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject localWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_localWidget.data,
      qt_meta_data_localWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *localWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *localWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_localWidget.stringdata))
        return static_cast<void*>(const_cast< localWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int localWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE


localWidget::localWidget()
{
}

void localWidget::setupUi(SimulatorData *simData){

    //trás os dados do simData
    this->simData = simData;


    //layout principal
    QGridLayout *mainLayout = new QGridLayout;



    //layout local, tabs
    QTabWidget *localTabs = new QTabWidget;

    //adiciona equips
    localTP(localTabs);
    localBreakers (localTabs);
    LocalYLTC(localTabs);

    //adiciona as tabs
    mainLayout->addWidget(localTabs, 0,0);

    //seta layout principal na janela
    this->setLayout(mainLayout);


}

void localWidget::localTP(QTabWidget *mainTab){

    //tp layout
    QGridLayout *tpMainLayout = new QGridLayout;
    QGroupBox *tpBox = new QGroupBox;

    //tp1
    QLabel *tp1Label = new QLabel(this->simData->getCIMModel()->getBusesIED()[0]->getLDName());
    QLineEdit *tp1LineEdit = new QLineEdit(QString("%1").arg(this->simData->getCIMModel()->getBusesIED()[0]->getVol()));



    tpMainLayout->addWidget(tp1Label, 0, 0);
    tpMainLayout->addWidget(tp1LineEdit, 0, 1, 1, 2);


    //tp2
    QLabel *tp2Label = new QLabel(this->simData->getCIMModel()->getBusesIED()[1]->getLDName());
    QLineEdit *tp2LineEdit = new QLineEdit(QString("%1").arg(this->simData->getCIMModel()->getBusesIED()[1]->getVol()));

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
    QTableWidget *breakerTable = new QTableWidget;

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

void localWidget::LocalYLTC(QTabWidget *mainTab){

    //Layout
    QGridLayout *yltcLayout = new QGridLayout;

    QGroupBox *yltcBox = new QGroupBox;

    //comboBox
    QComboBox *combo = new QComboBox;

    for (int i=0; i<this->simData->getCIMModel()->getTrafosIED().size(); i++) {

        combo->insertItem(i, QString("%1").arg(this->simData->getCIMModel()->getTrafosIED().at(i)->getLDName()));
    }

    //SIGNAL para chamar a função que atualiza os dados da tela de acordo com o index selecionado no combo box
    connect (combo, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshYLTC(int)));


    //campos

    QLabel *modo = new QLabel("Modo");
    QLabel *pos = new QLabel("Pos");
    QLabel *posL = new QLabel("Pos L");
    QLabel *posR = new QLabel("Pos R");

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
