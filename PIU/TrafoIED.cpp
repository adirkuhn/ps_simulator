#include "TrafoIED.h"

/**
 * TODO:
 * atributos nao localizados
 * LTCMvm
 * LTCMod
 * LTCCycAlm
 * Loc
 */

TrafoIED::TrafoIED()
{
    this->YLTC1 = new YLTC();
}

void TrafoIED::setPos(int pos) {

    INT8 ctlVal;
    ctlVal.val.val = pos;

    //deve setar o valor em ctlVal
    this->YLTC1->TapPos.ctlVal.setAttr(ctlVal);
    //this->YLTC1->

    qDebug() << "TODO: Iniciar a mudança do TAP";

    //depois de mudar o valor o resultado deve ser colocado em YLTC.TapChg.valWithTrans.posVal
    //mas nao existe esse propriedade
    //this->YLTC1->
}

int TrafoIED::getPos() {

    return this->YLTC1->TapPos.valWTr.getAttr().posVal.val.val;
}

//void TrafoIED::setEndPosL(int endPosL) {
//    this->YLTC1->EndPosL
//}
