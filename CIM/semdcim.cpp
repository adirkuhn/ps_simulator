#include "semdcim.h"
#include "semddata.h"
#include "BreakerStatus.h"
#include <math.h>
#include <Analog.h>
#include <Discrete.h>
#include "PIU/busied.h"

#include <QDebug>

SEMDCIM::SEMDCIM( QObject *parent ) :
    QObject( parent )
{
    qDebug() << "Starting CIM Model";

    dataUpdateSystem = new DataUpdateSystem();

    modelAuthority.name.str = SEMDData::AUTH_ID;
    modelAuthoritySet.modelingAuthority = & modelAuthority;

    setBases();

    setRegion();
    setSubstation();

    addBuses();
    addBays();

    addGenerators();
    addLoads();
    addTrafos();
    addBreakers();

    addMeasurements();

    qDebug() << "CIM Model completed";
}

QVariant SEMDCIM::getValue( const Measurement *m )
{
    if ( MeasurementType::isDiscrete( m->measurementType.str ) )
    {
        const Discrete* mD = dynamic_cast<const Discrete*>( m );

        assert( mD != NULL );

        return QVariant( mD->discreteValues.at( 0 )->value.val );
    } else
    {
        const Analog* mAn = dynamic_cast<const Analog*>( m );

        assert( mAn != NULL );

        return QVariant( mAn->analogValues.at( 0 )->value.val );
    }

    return QVariant();
}

QVariant SEMDCIM::getEqData( QString eq, QString mType )
{
    QList<Measurement*> ms = measurements.values( eq );

    foreach ( const Measurement* m, ms )
    {
        if ( m->measurementType.str == mType )
            return getValue( m );
    }

    return QVariant();
}

QList<QVariant> SEMDCIM::getEqData( QString eq )
{
    QList<QVariant> values;

    QList<Measurement*> ms = measurements.values( eq );

    foreach ( const Measurement* m, ms )
    {
        QVariant value = getValue( m );

        if ( value.isValid() )
            values.append( value );
    }

    return values;
}

bool SEMDCIM::setEqData( QString eq, QString mType, const QVariant &value )
{
    bool flag = false;

    QList<Measurement*> ms = measurements.values( eq );

    foreach ( Measurement* m, ms )
    {
        if ( m->measurementType.str == mType )
        {
            if ( MeasurementType::isDiscrete( m->measurementType.str ) )
            {
                Discrete* mD = dynamic_cast<Discrete*>( m );

                assert( mD != NULL );

                mD->discreteValues.at( 0 )->value.val = value.toInt();
            } else
            {
                const Analog* mAn = dynamic_cast<const Analog*>( m );

                assert( mAn != NULL );

                mAn->analogValues.at( 0 )->value.val = value.toFloat();
            }

            //return true;
            flag = true;
        }
    }

    //Verifica o tipo de equipamento e chama funcao para troca de dados
    if(isBreaker(eq) > -1) {
        this->dataUpdateSystem->updateBreaker(this->breakers[isBreaker(eq)], this->breakerIEDs[isBreaker(eq)]);

        //muda valores do trado ligado /desligado (in/out)
        changeInOutStatus(isBreaker(eq));
    }
    if (isTrafo(eq) > -1) {
        this->dataUpdateSystem->updateTrafo(this->trafos[isTrafo(eq)], this->trafoIEDs[isTrafo(eq)]);
    }
    if(isBus(eq) > -1) {
        this->dataUpdateSystem->updateBus(this->buses[isBus(eq)], this->busIEDs[isBus(eq)]);
    }


    return flag;
}

int SEMDCIM::isBreaker( QString eq )
{
    for ( int b = 0; b < SEMDData::BREAKERS; b++ )
    {
        if ( eq == SEMDData::breakersID[b] )
            return b;
    }

    return -1;
}

int SEMDCIM::isBus( QString eq )
{
    for ( int b = 0; b < SEMDData::BUSES; b++ )
    {
        if ( eq == SEMDData::busID[b] )
            return b;
    }

    return -1;
}

int SEMDCIM::isTrafo(QString eq) {
    for (int t=0; t < SEMDData::TRAFOS; t++) {
        if ( eq == SEMDData::trafosID[t]) {
            return t;
        }
    }

    return -1;
}


void SEMDCIM::setRegion()
{
    geoRegion.name.str    = SEMDData::REGION_ID;
    subGeoRegion.name.str = SEMDData::SUBREGION_ID;

    geoRegion.regions.append( subGeoRegion );
}

void SEMDCIM::setBases()
{
    Voltage v500kV, v220kV;

    v500kV.value = SEMDData::V_BASE_500kV;
    v500kV.multiplier = UnitMultiplier::k;

    v220kV.value = SEMDData::V_BASE_220kV;
    v220kV.multiplier = UnitMultiplier::k;

    vBase500kV.isDC.val = false;
    vBase500kV.nominalVoltage = v500kV;

    vBase220kV.isDC.val = false;
    vBase220kV.nominalVoltage = v220kV;

    vBase500kV.aliasName.str = "500 kV";
    vBase220kV.aliasName.str = "220 kV";

    // Potencia Aparente Base
    ApparentPower ap;

    ap.value = SEMDData::S_BASE;
    ap.multiplier = UnitMultiplier::M;

    basePower.basePower = ap;
    basePower.aliasName.str = "100 MVA";

    // Zb = Vb² / Sb
    Zbase500kV = pow( vBase500kV.nominalVoltage.value.val, 2 ) / \
                 basePower.basePower.value.val;
    Zbase220kV = pow( vBase220kV.nominalVoltage.value.val, 2 ) / \
                 basePower.basePower.value.val;
}

/******************************************************************************
 ***         Configuração da Subestação: Tensões, Barras e Bays             ***
 *****************************************************************************/
void SEMDCIM::setSubstation()
{
    semd.modelingAuthoritySet = & modelAuthoritySet;

    semd.name.str = SEMDData::SUBS_ID;
    semd.mRID.str = SEMDData::SUBS_ID;

    semd.voltageLevels.append( & vl220kV );
    semd.voltageLevels.append( & vl500kV );

    vl500kV.baseVoltage = & vBase500kV;
    vl220kV.baseVoltage = & vBase220kV;

    Voltage vHigh500kV, vLow500kV, vHigh220kV, vLow220kV;

    // 1.05 pu
    vHigh500kV.value = SEMDData::V_HIGH_500kV;
    vHigh500kV.multiplier = UnitMultiplier::k;

    // 0.95 pu
    vLow500kV.value = SEMDData::V_LOW_500kV;
    vLow500kV.multiplier = UnitMultiplier::k;

    vHigh220kV.value = SEMDData::V_HIGH_220kV;
    vHigh220kV.multiplier = UnitMultiplier::k;

    vLow220kV.value = SEMDData::V_LOW_220kV;
    vLow220kV.multiplier = UnitMultiplier::k;

    vl500kV.highVoltageLimit = vHigh500kV;
    vl500kV.lowVoltageLimit  = vLow500kV;

    vl220kV.highVoltageLimit = vHigh220kV;
    vl220kV.lowVoltageLimit  = vLow220kV;
}

void SEMDCIM::addBuses()
{
    vControlZone500kV.name.str = SEMDData::VCZ_500kV;
    vControlZone220kV.name.str = SEMDData::VCZ_220kV;

    BusbarSection * bus;
    BusIED * busIED;

    for ( int b = 0; b < SEMDData::BUSES; b++ )
    {
        bus = new BusbarSection();
        busIED = new BusIED();


        bus->name.str = SEMDData::busID[b];
        busIED->setLDName(SEMDData::busID[b]);

        if ( bus->name.str.endsWith( "500kV" ) ){
            bus->voltageControlZone = & vControlZone500kV;

        }

        else
        if ( bus->name.str.endsWith( "220kV" ) ) {
            bus->voltageControlZone = & vControlZone220kV;

        }

        bus->normallyInService.val = true;

        buses.append( bus );
        busIEDs.append ( busIED );
    }
}

void SEMDCIM::addBays()
{
    Bay *bay;

    for ( int trafo = 0; trafo < SEMDData::TRAFOS; ++trafo )
    {
        bay = new Bay();

        bay->name.str= "Bay " + SEMDData::trafosID[trafo];

        bay->breakerConfiguration  = BreakerConfiguration::breakerAndAHalf;
        bay->busBarConfiguration   = BusbarConfiguration::doubleBus;
        bay->bayPowerMeasFlag.val  = true;
        bay->bayEnergyMeasFlag.val = false;

        // atualiza listas Substation & VoltageLevels
        semd.bays.append( bay );

        vl500kV.bays.append( bay );
        vl220kV.bays.append( bay );

        bays.append( bay );
    }
}

/******************************************************************************
 ***              Equipamentos: Geradores, Cargas e Trafos                  ***
 *****************************************************************************/
void SEMDCIM::addGenerators()
{
    SynchronousMachine *gen;

    for ( int g = 0; g < SEMDData::GENUNITS; ++g )
    {
        gen = new SynchronousMachine();

        gen->name.str = SEMDData::genID[g];

        gen->coolantType = CoolantType::water;

        gen->aggregate.val = true;

        Voltage minU, maxU;

        minU.value = SEMDData::GEN_MIN_V;
        minU.multiplier = UnitMultiplier::k;

        maxU.value = SEMDData::GEN_MAX_V;
        maxU.multiplier = UnitMultiplier::k;

        gen->minU = minU;
        gen->maxU = maxU;

        ReactivePower minQ, maxQ;

        minQ.value = SEMDData::GEN_MIN_Q;
        minU.multiplier = UnitMultiplier::M;

        maxQ.value = SEMDData::GEN_MAX_Q;
        maxQ.multiplier = UnitMultiplier::M;

        gen->minQ = minQ;
        gen->maxQ = maxQ;

        gen->type = SynchronousMachineType::generator;
        gen->synchronousGeneratorType = SynchronousGeneratorType::salientPole;

        genUnits.append( gen );
    }
}

void SEMDCIM::addLoads()
{
    EnergyConsumer *load;

    for ( int l = 0; l < SEMDData::LOADS; ++l )
    {
        load = new EnergyConsumer();

        lrcConstPower.pConstantPower = SEMDData::LOAD_P_CONSTPOWER;
        lrcConstPower.qConstantPower = SEMDData::LOAD_Q_CONSTPOWER;

        load->name.str = SEMDData::loadsID[l];
        load->loadResponse = & lrcConstPower;

        loads.append( load );
    }
}

void SEMDCIM::addTrafos()
{
    PowerTransformer *pwTrafo;
    TrafoIED *trafoIED;
    PowerTransformerEnd *pwTrafo500kVEnd, *pwTrafo220kVEnd;
    RatioTapChanger *tapChanger;
    RatioTapChangerTabular *tapChgTabular;

    for ( int t = 0; t < SEMDData::TRAFOS; ++t )
    {
        pwTrafo = new PowerTransformer();
        trafoIED = new TrafoIED();

        pwTrafo500kVEnd = new PowerTransformerEnd();
        pwTrafo220kVEnd = new PowerTransformerEnd();

        tapChanger    = new RatioTapChanger();
        tapChgTabular = new RatioTapChangerTabular();

        pwTrafo->name.str = SEMDData::trafosID[t];
        trafoIED->setLDName(SEMDData::trafosID[t]);

        pwTrafo500kVEnd->baseVoltage    = & vBase500kV;
        pwTrafo500kVEnd->connectionKind = WindingConnection::Yn;

        pwTrafo500kVEnd->r.value      = SEMDData::trafoResPU[0] * Zbase500kV;
        pwTrafo500kVEnd->r.multiplier = UnitMultiplier::none;

        pwTrafo500kVEnd->x.value      = SEMDData::trafoReactPU[t] * Zbase500kV;
        pwTrafo500kVEnd->x.multiplier = UnitMultiplier::none;

        pwTrafo220kVEnd->baseVoltage    = & vBase220kV;
        pwTrafo220kVEnd->connectionKind = WindingConnection::Yn;

        tapChanger->initialDelay.value    = SEMDData::TAP_INI_DELAY;
        tapChanger->subsequentDelay.value = SEMDData::TAP_SUB_DELAY;

        tapChanger->tculControlMode = TransformerControlMode::volt;

        tapChanger->name.str = "Curva Real LTC " + pwTrafo->name.str;

        //TODO: Tap tem 19 posições (0-18) ?
        for ( int tapPos = 0; tapPos < SEMDData::TRAFOS_TAPS; ++tapPos )
        {
            RatioTapChangerTabularPoint tabularPoint;

            tabularPoint.step.val = tapPos + 1;
            tabularPoint.ratio    = SEMDData::trafoLTCRatios[t][tapPos];

            // Xtap% = XtrfN / Xtap * 100
            tabularPoint.x.value =
                SEMDData::trafoLTCReactPU[t][tapPos] /
                SEMDData::trafoReactPU[t] * 100;

            tapChgTabular->tabularPoints.append( tabularPoint );

            tapChanger->ratioTapChangerTabular = tapChgTabular;
        }

        // LTC do lado de 220 kV
        pwTrafo220kVEnd->ratioTapChanger = tapChanger;

        pwTrafo->powerTransformerEnds.append( pwTrafo500kVEnd );
        pwTrafo->powerTransformerEnds.append( pwTrafo220kVEnd );

        // atualiza Bay
        bays.at( t )->equipments.append( pwTrafo );

        // lista local
        trafos.append( pwTrafo );
        trafoIEDs.append(trafoIED);
    }
}

void SEMDCIM::addBreakers()
{
    Breaker *breaker;
    BreakerIED *breakerIED;

    for ( int b = 0; b < SEMDData::BREAKERS; b++ )
    {
        breaker = new Breaker();
        breakerIED = new BreakerIED();

        //nomeando equipamento
        breaker->name.str = SEMDData::breakersID[b];
        breakerIED->setLDName(SEMDData::breakersID[b]);

        // lista local
        breakers.append( breaker );
        breakerIEDs.append(breakerIED);

    }
}

/******************************************************************************
 ***                        Medidas / Leituras                              ***
 *****************************************************************************/
void SEMDCIM::addMeasurements()
{
    Measurement *m;

    // breakers
    for ( int b = 0; b < SEMDData::BREAKERS; b++ )
    {
        m = addDiMeasurement( MeasurementType::status, SEMDData::breakersID[b],
                              UnitSymbol::none, UnitMultiplier::none,
                              Integer( BreakerStatus::closed ) );

        // atualiza equipamento
        breakers.at( b )->measurements.append( m );

        //posicao do breaker (61850)
        breakerIEDs.at(b)->setPos(BreakerStatus::closed);
        qDebug() << "TODO: Setar posiçao do breaker dentro do modelo da norma iec61850!!!";
    }

    // Barras
    for ( int b = 0; b < SEMDData::BUSES; b++ )
    {
        // Tensão
        m = addAnMeasurement( MeasurementType::V, SEMDData::busID[b],
                              UnitSymbol::V, UnitMultiplier::k,
                              SEMDData::buskV[b] );

        // atualiza equipamento
        buses.at( b )->measurements.append( m );

        //atualiza IED
        this->busIEDs.at(b)->setVol(SEMDData::buskV[b]);
    }

    // Pot Gerados
    for ( int g = 0; g < SEMDData::GENUNITS; ++g )
    {
        // Pot Ativa
        m = addAnMeasurement( MeasurementType::Pp, SEMDData::genID[g],
                              UnitSymbol::W, UnitMultiplier::M,
                              SEMDData::genMW[g] );

        genUnits.at( g )->measurements.append( m );

        // Pot Reativa
        m = addAnMeasurement( MeasurementType::Qp, SEMDData::genID[g],
                              UnitSymbol::VAr, UnitMultiplier::M,
                              SEMDData::genMVar[g] );

        genUnits.at( g )->measurements.append( m );
    }

    // Pot Cargas
    for ( int l = 0; l < SEMDData::LOADS; ++l )
    {
        // Pot Ativa
        m = addAnMeasurement( MeasurementType::Pp, SEMDData::loadsID[l],
                              UnitSymbol::W, UnitMultiplier::M,
                              SEMDData::loadsMW[l] );

        loads.at( l )->measurements.append( m );

        // Pot Reativa
        m = addAnMeasurement( MeasurementType::Qp, SEMDData::loadsID[l],
                              UnitSymbol::VAr, UnitMultiplier::M,
                              SEMDData::loadsMVar[l] );

        loads.at( l )->measurements.append( m );
    }

    // Pot Trafos
    for ( int t = 0; t < SEMDData::TRAFOS; ++t )
    {
        // Pot Ativa Primário - 500 kV
        m = addAnMeasurement( MeasurementType::Pp, SEMDData::trafosID[t],
                              UnitSymbol::W, UnitMultiplier::M,
                              SEMDData::trafoMWP[t] );

        trafos.at( t )->measurements.append( m );

        // Pot Reativa Primário - 500 kV
        m = addAnMeasurement( MeasurementType::Qp, SEMDData::trafosID[t],
                              UnitSymbol::VAr, UnitMultiplier::M,
                              SEMDData::trafoMVarP[t] );

        trafos.at( t )->measurements.append( m );

        // Pot Ativa Secundário - 220 kV
        m = addAnMeasurement( MeasurementType::Ps, SEMDData::trafosID[t],
                              UnitSymbol::W, UnitMultiplier::M,
                              SEMDData::trafoMWS[t] );

        trafos.at( t )->measurements.append( m );

        // Pot Reativa Secundário - 220 kV
        m = addAnMeasurement( MeasurementType::Qs, SEMDData::trafosID[t],
                              UnitSymbol::VAr, UnitMultiplier::M,
                              SEMDData::trafoMVarS[t] );

        trafos.at( t )->measurements.append( m );

        // Tap Pos
        m = addDiMeasurement( MeasurementType::status, SEMDData::trafosID[t],
                              UnitSymbol::none, UnitMultiplier::none,
                              10 );
        trafos.at( t )->measurements.append( m );

        this->trafoIEDs.at(t)->setPos(10);

        //In Out
        m = addDiMeasurement(MeasurementType::InOut, SEMDData::trafosID[t],
                             UnitSymbol::none, UnitMultiplier::none,
                             1);
        trafos.at(t)->measurements.append(m);

    }
}

QMultiMap<QString, Measurement *> SEMDCIM::getMeasurements() const
{
    return measurements;
}

Measurement* SEMDCIM::addDiMeasurement(
        MeasurementType::enum_type mType, QString eq,
        UnitSymbol sym, UnitMultiplier mul, Integer val )
{
    Discrete      *status = new Discrete();
    DiscreteValue *sValue = new DiscreteValue();

    setMeasNameType( status, eq, mType );

    setMeasUnits( status, sym, mul );

    // TESTE
    sValue->sensorAccuracy.value = 1.0;
    sValue->timeStamp.val =
        QDateTime( QDate( 2014, 02, 14 ),
                   QTime( 10, 59, 59, 999 ),
                   Qt::LocalTime );

    sValue->value = val;

    status->discreteValues.append( sValue );

    // lista local
    measurements.insert( eq, status );

    return status;
}

Measurement* SEMDCIM::addAnMeasurement(
        MeasurementType::enum_type mType, QString eq,
        UnitSymbol sym, UnitMultiplier mul, Float val )
{
    Analog      *analog = new Analog();
    AnalogValue *aValue = new AnalogValue();

    setMeasNameType( analog, eq, mType );

    setMeasUnits( analog, sym, mul );

    aValue->value = val;

    analog->analogValues.append( aValue );

    // lista local
    measurements.insert( eq, analog );

    return analog;
}

void SEMDCIM::setMeasNameType( Measurement* m, QString name,
                               MeasurementType::enum_type mType )
{
    m->name.str            = name;
    m->measurementType.str = MeasurementType::toString( mType );
}

void SEMDCIM::setMeasUnits( Measurement* m, UnitSymbol sym, UnitMultiplier mul )
{
    m->unitSymbol     = sym;
    m->unitMultiplier = mul;
}

/******************************************************************************
 ***               Nós de Conexão e Terminais de Conexão                    ***
 *****************************************************************************/
void SEMDCIM::addConnNodes()
{

}


void SEMDCIM::addTerminals()
{

}

/******************************************************************************
 ***               Retorna as colecoes de tipos                             ***
 *****************************************************************************/
QList<BreakerIED*> SEMDCIM::getBreakersIED() {
    return this->breakerIEDs;
}

QList<BusIED*> SEMDCIM::getBusesIED() {
    return this->busIEDs;
}

QList<TrafoIED*> SEMDCIM::getTrafosIED() {
    return this->trafoIEDs;
}


//in out
void SEMDCIM::changeInOutStatus(int breakerID) {

    /**
     * Mapeamento
     *
     * b[1] 04T01 - t[0] T01-R01 - b[7] 03T01
     * b[2] 84T02 - t[1] T02-R02 - b[8] 03T02
     * b[3] 04T03 - t[2] T03-R03 - b[9] 03T03
     * b[4] 84T04 - t[3] T04-R04 - b[10] 03T04
     * b[5] 84T05 - t[4] T05-R05 - b[11] 83T05
     * b[6] 04T0X - t[5] T0X-R0X - b[12] 03T0X
     */

    int b1, b2, trafoID, statusB1, statusB2;
    Discrete *b1Meas, *b2Meas, *trafoMeas;

    //status breaker1
    b1 = breakerID;
    b1Meas = dynamic_cast<Discrete*>(breakers.at(b1)->measurements[0]);
    statusB1 = b1Meas->discreteValues.at(0)->value.val;

    switch (breakerID) {
    case 1: b2 = 7;
    case 7: b2 = 1;
        trafoID = 0;
        break;
    case 2: b2 = 8;
    case 8: b2 = 2;
        trafoID = 1;
        break;
    case 3: b2 = 9;
    case 9: b2 = 3;
        trafoID = 2;
        break;
    case 4:  b2 = 10;
    case 10: b2 = 4;
        trafoID = 3;
        break;
    case 5:  b2 = 11;
    case 11: b2 = 5;
        trafoID = 4;
        break;
    case 6:  b2 = 12;
    case 12: b2 = 6;
        trafoID = 6;
        break;
    }

    //statusB2
    b2Meas = dynamic_cast<Discrete*>(breakers.at(b2)->measurements[0]);
    statusB2 = b2Meas->discreteValues.at(0)->value.val;

    trafoMeas = dynamic_cast<Discrete*>(trafos.at(trafoID)->measurements[5]);

    if (statusB1 == 2 && statusB2 == 2)
        trafoMeas->discreteValues.at(0)->value.val = 1; //IN
    else
        trafoMeas->discreteValues.at(0)->value.val = 0; //OUT
}
