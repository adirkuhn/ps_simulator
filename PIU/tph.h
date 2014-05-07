#ifndef TPH_H
#define TPH_H

#include <PotentialTransformer.h>
#include <LD.h>
#include "P_VISIBLE_STRING32.h";

/**
 * @brief The TPH TP Harmonization (iec61970 + iec61850)
 */
class TPH: public PotentialTransformer
{

    public:
        LD *ld;
        TPH(QString name);
};

#endif // TPH_H
