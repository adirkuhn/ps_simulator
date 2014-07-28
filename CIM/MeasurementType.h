#ifndef MEASUREMENTTYPE_H
#define MEASUREMENTTYPE_H

#include <QObject>
#include <QMetaEnum>

#include <String.h>

#include <cassert>

class MeasurementType : public QObject
{
    Q_OBJECT
    Q_ENUMS( enum_type )

public:
/**
 * Tipo de medição para auxiliar na busca.
 */
typedef enum
{
    /**
     * Potencia ativa primário ou principal.
     */
    Pp,
    /**
     * Potencia ativa secundário ou secundária/alternativa.
     */
    Ps,
    /**
     * Potencia reativa primário ou principal.
     */
    Qp,
    /**
     * Potencia reativa secundário ou secundária/alternativa.
     */
    Qs,
    /**
     * Tensão.
     */
    V,
    /**
     * Status ponto digital / binário.
     */
    status,
    /**
     * Status para informar se Trafo esta IN ou OUT
     * 0 - out
     * 1 - in
     */
    InOut
} enum_type;

private:
    enum_type val;

public:
    explicit MeasurementType( QObject *parent = 0 )
        : QObject( parent )
    {

    }

    MeasurementType( enum_type val = Pp )
        : val( val )
    {
        assert( val <= Qs );
    }

    operator enum_type() const
    {
        return val;
    }

    static QStringList strList()
    {
        QStringList lst;

        QMetaEnum mEnum = metaEnum();

        for ( int e = 0; e < mEnum.keyCount(); ++e )
        {
            // dá para usar tr( metaEnum.key( e ) )
            lst.append( mEnum.key( e ) );
        }

        return lst;
    }

    static QString toString( enum_type val )
    {
        return QString( metaEnum().valueToKey( val ) );
    }

    static enum_type toEnum( const QString str )
    {
        QByteArray byteArray = str.toUtf8();

        int value = metaEnum().keyToValue( byteArray.data() );

        enum_type e = static_cast<enum_type>( value );

        return e;
    }

    static QMetaEnum metaEnum()
    {
        const QMetaObject &mo = MeasurementType::staticMetaObject;

        int index = mo.indexOfEnumerator( "enum_type" );

        return mo.enumerator( index );
    }

    static bool isDiscrete( const QString str )
    {
        if ( str == "status" || str == "InOut")
            return true;
        else
            return false;
    }
};
#endif // MEASUREMENTTYPE_H
