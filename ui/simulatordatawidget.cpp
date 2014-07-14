#include "simulatordatawidget.h"

#include "simulatordatawidget_p.h"

#include <QGroupBox>

SimulatorDataWidget::SimulatorDataWidget( QWidget *parent ) :
    QWidget( parent )
{
}

void SimulatorDataWidget::setupUi( QMainWindow *MainWindow )
{
    if ( MainWindow->objectName().isEmpty() )
        MainWindow->setObjectName( QStringLiteral( "MainWindow" ) );

    MainWindow->resize( 731, 490 );

    QSizePolicy sizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    sizePolicy.setHorizontalStretch( 0 );
    sizePolicy.setVerticalStretch( 0 );
    sizePolicy.setHeightForWidth( MainWindow->sizePolicy().hasHeightForWidth() );

    MainWindow->setSizePolicy( sizePolicy );
    MainWindow->setMinimumSize( QSize( 500, 400 ) );

    QSizePolicy thisSPolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    thisSPolicy.setHorizontalStretch( 0 );
    thisSPolicy.setVerticalStretch( 0 );
    thisSPolicy.setHeightForWidth( this->sizePolicy().hasHeightForWidth() );

    this->setSizePolicy( thisSPolicy );
    this->setMinimumSize( QSize( 500, 400 ) );

    mainLayout = new QVBoxLayout( this );
    Q_CHECK_PTR( mainLayout );

    mainLayout->setObjectName( "SimulatorDataWidgetBLayout" );

    mainLayout->setMargin( V_BOX_LAYOUT_MARGIN );
    mainLayout->setSpacing( V_BOX_LAYOUT_SPACING );
    mainLayout->setSizeConstraint( QLayout::SetMinAndMaxSize );

    // Adiciona layout vertical
    QGroupBox *gb = new QGroupBox( this );
    Q_CHECK_PTR( gb );

    gb->setObjectName( "SimulatorDataWidgetGBox" );

    QSizePolicy gbSPolicy( QSizePolicy::Expanding, QSizePolicy::Fixed );
    gbSPolicy.setHorizontalStretch( 0 );
    gbSPolicy.setVerticalStretch( 0 );
    gbSPolicy.setHeightForWidth( gb->sizePolicy().hasHeightForWidth() );

    gb->setSizePolicy( gbSPolicy );

    gb->setTitle( tr( "Dados da Simulação", "Titulo do GroupBox" ) );

    gridLayout = new QGridLayout();

    Q_CHECK_PTR( gridLayout );

    gridLayout->setObjectName( "SimulatorDataWidgetGridLayout" );

    gridLayout->setSpacing( G_BOX_LAYOUT_SPACING );
    gridLayout->setMargin( G_BOX_LAYOUT_MARGIN );
    gridLayout->setSizeConstraint( QLayout::SetDefaultConstraint );

    gb->setLayout( gridLayout );

    // bloco dados básicos
    dirLabel = new QLabel( tr( "Diretório Base", "Label" ), gb );
    Q_CHECK_PTR( dirLabel );

    dirLabel->setObjectName( "SimulatorDataWidgetDirLabel" );
    dirLabel->setMinimumSize( QSize( 0, 30 ) );
    dirLabel->setMaximumSize( QSize( 120, 30 ) );

    dirLEdit = new QTextEdit( gb );
    Q_CHECK_PTR( dirLEdit );

    dirLEdit->setObjectName( "SimulatorDataWidgetDirLEdit" );
    dirLabel->setMinimumSize( QSize( 0, 30 ) );
    dirLEdit->setMaximumSize( QSize( 1600, 30 ) );

    btnDir = new QToolButton( gb );
    Q_CHECK_PTR( btnDir );

    btnDir->setObjectName( "SimulatorDataWidgetDirToolBtn" );
    btnDir->setMinimumSize( QSize( 0, 30 ) );
    btnDir->setMaximumSize( QSize( 40, 30 ) );

    gridLayout->addWidget( dirLabel, 0, 0 );
    gridLayout->addWidget( dirLEdit, 0, 1 );
    gridLayout->addWidget( btnDir, 0, 2 );

    timerLabel = new QLabel( tr( "Tempo Simulação", "Label" ), gb );
    Q_CHECK_PTR( timerLabel );

    timerLabel->setObjectName( "SimulatorDataWidgetTimerLabel" );
    timerLabel->setMinimumSize( QSize( 0, 30 ) );
    timerLabel->setMaximumSize( QSize( 120, 30 ) );

    timerLEdit = new QTextEdit( gb );
    Q_CHECK_PTR( timerLEdit );

    timerLEdit->setObjectName( "SimulatorDataWidgetTimerLEdit" );
    timerLEdit->setMinimumSize( QSize( 0, 30 ) );
    timerLEdit->setMaximumSize( QSize( 1600, 30 ) );

    gridLayout->addWidget( timerLabel, 1, 0, Qt::AlignAbsolute );
    gridLayout->addWidget( timerLEdit, 1, 1 );

    // Adiciona o grid ao layout base
    mainLayout->addWidget( gb );

    // adiciona Tab e Tabela
    tab = new QTabWidget( this );
    Q_CHECK_PTR( tab );

    tab->setObjectName( "SimulatorDataWidgetTabW" );

    QSizePolicy tabSPolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    tabSPolicy.setHorizontalStretch( 0 );
    tabSPolicy.setVerticalStretch( 0 );
    tabSPolicy.setHeightForWidth( tab->sizePolicy().hasHeightForWidth() );

    tab->setSizePolicy( tabSPolicy );

    QWidget* dataTab = new QWidget();
    Q_CHECK_PTR( dataTab );

    dataTab->setObjectName( "SimulatorDataWidgetDataTab" );

    tab->addTab( dataTab, tr( "Dados", "Titulo do DataTab" ) );

    QHBoxLayout* dataTabHBox = new QHBoxLayout( dataTab );

    dataTableView = new QTableView();

    dataTabHBox->addWidget( dataTableView );

    mainLayout->addWidget( tab );

    // bloco final botôes
    btnLayout = new QHBoxLayout();
    Q_CHECK_PTR( btnLayout );

    btnLayout->setObjectName( "SimulatorDataWidgetBtnLayout" );

    btnLayout->setSpacing( BTN_BOX_LAYOUT_SPACING );
    btnLayout->setMargin( BTN_BOX_LAYOUT_MARGIN );

    // Adiciona os botoes de Confirmar e Cancelar ao Dialogo
    btnStartSimul = new QPushButton( gb );
    Q_CHECK_PTR( btnStartSimul );

    btnStartSimul->setObjectName( "SimulatorDataWidgetBtnStartSimul" );

    btnStartSimul->setText( tr( "Iniciar", "PButton" ) );

    btnStopSimul = new QPushButton( gb );
    Q_CHECK_PTR( btnStopSimul );

    btnStopSimul->setObjectName( "SimulatorDataWidgetBtnStopSimul" );

    QSizePolicy btnSPolicy( QSizePolicy::Minimum, QSizePolicy::Fixed );
    btnSPolicy.setHorizontalStretch( 0 );
    btnSPolicy.setVerticalStretch( 0 );
    btnSPolicy.setHeightForWidth(
        btnStopSimul->sizePolicy().hasHeightForWidth() );

    btnStopSimul->setSizePolicy( btnSPolicy );

    btnStopSimul->setText( tr( "Parar", "PButton" ) );

    btnLocal = new QPushButton( gb );
    Q_CHECK_PTR ( btnLocal );

    btnLocal->setObjectName("SimulatorDataWidgetBtnOpenLocals");
    btnLocal->setText(tr("Abrir Localíssimos (PIU)", "PButton"));



    // adiciona botôes
    btnLayout->addWidget( btnStartSimul, 0, 0 );
    btnLayout->addWidget( btnStopSimul, 0, 0 );
    btnLayout->addSpacing(300);
    btnLayout->addWidget(btnLocal, 0, 0 );

    QSpacerItem *horizontalSpacer =
        new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );

    btnLayout->addItem( horizontalSpacer );

    mainLayout->addLayout( btnLayout );

    MainWindow->setCentralWidget( this );
}
