#include "simulatordata.h"

#include <QDebug>

SimulatorData::SimulatorData( QObject *parent ) :
       QObject( parent )
{
    init();
}

void SimulatorData::init()
{
    cimModel = new SEMDCIM( this );

    table = new TableModel( this );

    equipments = QStringList( cimModel->getMeasurements().uniqueKeys() );
    measTypes  = MeasurementType::strList();

    table->setSize( equipments.size(), measTypes.size() );
}

/*****************************************************************************/
TableModel::TableModel( QObject *parent ) :
        QAbstractTableModel( parent )
{
    this->simData = static_cast<SimulatorData*>( parent );
}

void TableModel::setSize( int rows, int cols )
{
    this->rows = rows;
    this->cols = cols;
}

int TableModel::getColOffset( QString eq ) const
{
    if ( simData->getCIMModel()->isBreaker( eq ) )
        return 0;
    else
    if ( simData->getCIMModel()->isBus( eq ) )
        return 1;
    else
        return 2;
}

int TableModel::rowCount( const QModelIndex & /* parent */ ) const
{
    return this->rows;
}

int TableModel::columnCount( const QModelIndex & /* parent */ ) const
{
    return this->cols;
}

QVariant TableModel::data( const QModelIndex &index, int role ) const
{
    if ( !index.isValid() )
        return QVariant();

    if ( index.row() >= this->rows || index.row() < 0 )
        return QVariant();

    if ( role == Qt::DisplayRole )
    {
        QString eq = simData->getEqList().at( index.row() );

        // procura eq com medida da coluna atual
        QString mType = simData->getMeasTypes().at( index.column() );

        QVariant value = simData->getCIMModel()->getEqData( eq, mType );

        return value;
    }

    return QVariant();
}

bool TableModel::setData( const QModelIndex &index,
                          const QVariant &value, int role )
{
    qDebug() << "setData: " << value << " " << index.data();

    if ( index.isValid() && role == Qt::EditRole )
    {
        // se valor atual vazio
        if ( index.data().isNull() )
            return false;

        QString eq = simData->getEqList().at( index.row() );

        // procura eq com medida da coluna atual
        QString mType = simData->getMeasTypes().at( index.column() );

        simData->getCIMModel()->setEqData( eq, mType, value );

        emit dataChanged( index, index );

        return true;
    }

    return false;
}

QVariant TableModel::headerData( int section,
                                 Qt::Orientation orientation, int role ) const
{
    if ( role != Qt::DisplayRole )
        return QVariant();

    if ( orientation == Qt::Horizontal && section < this->cols )
        return MeasurementType::strList().at( section );

    if ( orientation == Qt::Vertical && section < this->rows )
        return simData->getEqList().at( section );

    return QVariant();
}

Qt::ItemFlags TableModel::flags( const QModelIndex &index ) const
{
    if ( !index.isValid() )
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags( index ) | Qt::ItemIsEditable;
}
