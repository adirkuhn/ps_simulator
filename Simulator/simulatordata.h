#ifndef SIMULATORDATA_H
#define SIMULATORDATA_H

#include <QObject>

#include <QString>
#include <QMultiHash>
#include <qstringlist.h>

#include <QAbstractTableModel>

#include <Measurement.h>

#include <semdcim.h>

class TableModel;

class SimulatorData : public QObject
{
    Q_OBJECT

private:
    SEMDCIM    *cimModel;

    TableModel *table;

    QStringList equipments;
    QStringList measTypes;

public:
    explicit SimulatorData( QObject *parent = 0 );

    QStringList getEqList()    { return this->equipments; }
    QStringList getMeasTypes() { return this->measTypes; }

    TableModel* getTableModel() { return this->table; }

    SEMDCIM* getCIMModel() { return this->cimModel; }

    void updateMeasurements();

private:
    void init();
};

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    int rows, cols;

    SimulatorData *simData;

private:
    int getColOffset( QString eq ) const;

public:
    explicit TableModel( QObject *parent = 0 );

    void setSize( int rows, int cols );

    // QAbstractItemModel interface
    int rowCount   ( const QModelIndex &parent ) const;
    int columnCount( const QModelIndex &parent ) const;

    QVariant data      ( const QModelIndex &index, int role ) const;
    bool     setData   ( const QModelIndex &index,
                         const QVariant &value, int role );
    QVariant headerData( int section,
                         Qt::Orientation orientation, int role ) const;

    Qt::ItemFlags flags( const QModelIndex &index ) const;
};

#endif // SIMULATORDATA_H
