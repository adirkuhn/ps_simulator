#ifndef SEMDDATA_H
#define SEMDDATA_H

#include <QString>

class SEMDData
{
public:
    /**************************************************************************
     ***                            Dados Gerais                            ***
     *************************************************************************/
    static const QString AUTH_ID;
    static const QString REGION_ID;
    static const QString SUBREGION_ID;
    static const QString SUBS_ID;

    static const QString VCZ_500kV;
    static const QString VCZ_220kV;

    // Base
    static const float V_BASE_500kV  = 525.00; // kV
    static const float V_BASE_220kV  = 220.00; // kV

    static const float S_BASE        = 100.00; // MVA

    // 0.95 e 1.05 pu
    static const float V_LOW_500kV  = 475.00;
    static const float V_HIGH_500kV = 525.00;
    static const float V_LOW_220kV  = 209.00;
    static const float V_HIGH_220kV = 231.00;

    /**************************************************************************
     ***                            Dados Barras                            ***
     *************************************************************************/
    static const int BUSES = 2;

    static const QString busID[BUSES];

    static const float buskV[BUSES];

    /**************************************************************************
     ***                           Dados Geradores                          ***
     *************************************************************************/
    static const int GENUNITS = 1;

    static const float GEN_MIN_V = 475.00;
    static const float GEN_MAX_V = 525.00;

    static const float GEN_MIN_Q = -9999.00;
    static const float GEN_MAX_Q =  9999.00;

    static const QString genID[GENUNITS];

    static const float genMW[GENUNITS];
    static const float genMVar[GENUNITS];

    /**************************************************************************
     ***                             Dados Cargas                           ***
     *************************************************************************/
    static const int LOADS = 4;

    static const float LOAD_P_CONSTPOWER = 1250.00;
    static const float LOAD_Q_CONSTPOWER =  250.00;

    // ids cargas
    static const QString loadsID[LOADS];

    static const float loadsMW[LOADS];
    static const float loadsMVar[LOADS];

    /**************************************************************************
     ***                             Dados Trafos                           ***
     *************************************************************************/
    static const int TRAFOS          = 6;
    static const int TRAFOS_TAPS     = 19;

    static const float TAP_INI_DELAY = 4.0;
    static const float TAP_SUB_DELAY = 5.0;

    // ids trafos
    static const QString trafosID[TRAFOS];

    // T01 a T0X e T05 - Base 100 MVA e 525 kV
    static const float trafoResPU[TRAFOS];

    // T01 a T05 e T0X - Base 100 MVA e 525 kV
    static const float trafoReactPU[TRAFOS];

    static const float trafoLTCRatios [TRAFOS][TRAFOS_TAPS];
    static const float trafoLTCReactPU[TRAFOS][TRAFOS_TAPS];

    static const float trafoMWP[TRAFOS];
    static const float trafoMWS[TRAFOS];
    static const float trafoMVarP[TRAFOS];
    static const float trafoMVarS[TRAFOS];

    /**************************************************************************
     ***                            Dados Breakers                          ***
     *************************************************************************/
    static const int BREAKERS = GENUNITS + TRAFOS * 2 + LOADS * 1;

    // ids trafos
    static const QString breakersID[BREAKERS];

public:
    SEMDData();
};

#endif // SEMDDATA_H
