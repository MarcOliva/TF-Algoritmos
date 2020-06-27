#include "columna.h"
#include "lista.h"

class Fila
{
    Lista<Columna*, nullptr>* columnas;
public:
    Fila()
    {
        this->columnas = new Lista<Columna*, nullptr>();
    }

    ~Fila()
    {
        delete this->columnas;
    }

    void ActualizarDatos(Columna* dato, int index)
    {
        this->ActualizarDatos(this->columnas, dato, index);
    }

    void InsertarDato(Columna* nuevoDato, int nroColumnas)
    {
        if( this->columnas->size() < nroColumnas )
        {
            this->columnas->agregar_final(nuevoDato);
        }
        //si no: se retorna un mensaje de error, para controlar el programa. Posible mensaje: "se llego al limite de columnas".
    }
private:
    void ActualizarDatos(Lista<Columna*, nullptr>*& cols, Columna* dato, int index)
    {
        if ( cols == nullptr ) return;

        Columna* aux = cols->get_pos(index);
        
        if( aux == nullptr ) return;

        if( aux->getTipo() == dato->getTipo() )
        {
            switch (aux->getTipo())
            {
                
            case Tipo::boolean:
                ((ColumnaBool*)aux)->setDato(((ColumnaBool*)dato)->getDato());
                break;
                
            case Tipo::integer:  
                ((ColumnaInt*)aux)->setDato(((ColumnaInt*)dato)->getDato());
                break;

            case Tipo::decimal:
                ((ColumnaDecimal*)aux)->setDato(((ColumnaDecimal*)dato)->getDato());
                break;

            case Tipo::caracter:  
            ((ColumnaCaracter*)aux)->setDato(((ColumnaCaracter*)dato)->getDato());
            break;

            case Tipo::cadena:
            ((ColumnaString*)aux)->setDato(((ColumnaString*)dato)->getDato());
            break;

            default:
                break;
            }
        }
    }

    Columna* getDatoporIndice(int indice)
    {
        return this->columnas->get_pos(indice);
    }
};