#ifndef SEMDCIM_H
#define SEMDCIM_H

#include "MeasurementType.h"

#include <QObject>

#include <GeographicalRegion.h>
#include <BasePower.h>
#include <ModelingAuthoritySet.h>
#include <SynchronousMachine.h>
#include <BusbarSection.h>
#include <EnergyConsumer.h>
#include <ConnectivityNode.h>
#include <PowerTransformer.h>
#include <TransformerCoreAdmittance.h>
#include <PIU/breakerh.h>
#include <PIU/RatioTapChangerH.h>

/*
 * The Common Power System Model (CPSM) profile defines the subset of classes,
 * attributes, and associations necessary to execute the EMS applications of
 * power flow and state estimation.
 *
 * CPSM profile is defined by the IEC standard 61970-452.
 *
 * The CPSM profile is widely used because of the NERC requirements for its use;
 * and for this reason, it is sometimes called the NERC profile.
 *
 */
class SEMDCIM : public QObject
{
    Q_OBJECT

private:
    // Authority
    ModelingAuthority    modelAuthority;
    ModelingAuthoritySet modelAuthoritySet;

    // Region
    GeographicalRegion    geoRegion;
    SubGeographicalRegion subGeoRegion;

    // Substation
    Substation   semd;
    VoltageLevel vl500kV, vl220kV;
    BaseVoltage  vBase500kV, vBase220kV;
    BasePower    basePower;

    float Zbase500kV, Zbase220kV;

    // Buses
    QList<BusbarSection*> buses;
    VoltageControlZone    vControlZone500kV, vControlZone220kV;

    // Bays
    QList<Bay*> bays;

    // Geradores
    QList<SynchronousMachine*> genUnits;

    // Cargas
    QList<EnergyConsumer*>     loads;
    LoadResponseCharacteristic lrcConstPower;

    // Trafos
    QList<PowerTransformer*> trafos;

    // Breakers
    QList<BreakerH*> breakers;

    // Medidas
    // Tip - QMap only small number elements & need to sort
    QMultiMap<QString, Measurement *> measurements;

    // ConnectivityNodes
    ConnectivityNode cNodeItaipuGen, cNodeParaguayLoad;

    Measurement *addDiMeasurement( MeasurementType::enum_type mType, QString eq,
                                   UnitSymbol sym, UnitMultiplier mul, Integer val );
    Measurement *addAnMeasurement( MeasurementType::enum_type mType, QString eq,
                                   UnitSymbol sym, UnitMultiplier mul, Float val );

    void setMeasNameType( Measurement* m, QString name,
                          MeasurementType::enum_type mType );

    void setMeasUnits( Measurement* m, UnitSymbol sym, UnitMultiplier mul );

    QVariant getValue( const Measurement *m );

public:
    explicit SEMDCIM( QObject *parent = 0 );

    QMultiMap<QString, Measurement *> getMeasurements() const;

    QVariant getEqData( QString eq, QString mType );
    QList<QVariant> getEqData( QString eq );

    bool setEqData(QString eq, QString mType, const QVariant &value );

    bool isBreaker( QString eq );
    bool isBus( QString eq );

private:
    void setBases();

    void setRegion();
    void setSubstation();

    void addBuses();
    void addBays();
    void addGenerators();
    void addLoads();
    void addTrafos();
    void addBreakers();

    void addMeasurements();

    void addConnNodes();
    void addTerminals();

signals:

public slots:

};

#endif // SEMDCIM_H
