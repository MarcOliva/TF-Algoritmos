#include "columna.h"
#include "lista.h"
#include <vector>
using namespace std;

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
    /*
    void ActualizarDatos(Columna* dato, int index)
    {
        this->ActualizarDatos(this->columnas, dato, index);
    }
    */
    void InsertarDato(Columna* nuevoDato, int nroColumnas)
    {
        if ((int)this->columnas->size() < nroColumnas)
        {
            //this->columnas->agregar_final(nuevoDato);
            this->columnas->agregar_final(nuevoDato);
        }
        //si no: se retorna un mensaje de error, para controlar el programa. Posible mensaje: "se llego al limite de columnas".
    }

    bool compararMayor(Fila* otro, int indexcomparar)
    {
        Columna* current = this->getColumnaporIndice(indexcomparar);
        Columna* other = otro->getColumnaporIndice(indexcomparar);

        std::cout << "Dato del current: "; this->imprimirColumna(current); std::cout << '\n';
        std::cout << "Dato del other: "; this->imprimirColumna(other); std::cout << '\n';

        bool dec = false;
        if (current->getTipo() == other->getTipo())
        {
            switch (current->getTipo())
            {
            case Tipo::boolean:
                if (((ColumnaBool*)current)->getDato() > ((ColumnaBool*)other)->getDato()) dec = true;
                else dec = false;

                break;
            case Tipo::integer:
                if (((ColumnaInt*)current)->getDato() > ((ColumnaInt*)other)->getDato()) dec = true;
                else dec = false;

                break;
            case Tipo::decimal:
                if (((ColumnaDecimal*)current)->getDato() > ((ColumnaDecimal*)other)->getDato()) dec = true;
                else dec = false;

                break;
            case Tipo::caracter:
                if (((ColumnaCaracter*)current)->getDato() > ((ColumnaCaracter*)other)->getDato()) dec = true;
                else dec = false;

                break;
            case Tipo::cadena:
                if (((ColumnaString*)current)->getDato() > ((ColumnaString*)other)->getDato()) dec = true;
                else dec = false;

                break;
            default:
                break;
            }
        }

        return dec;
    }

    //mayor, menor e igual
    bool compararEnFiltro(Lista<int, -1>* indexSelectColumnas, Columna* dato, int opcion)
    {
        bool dec = true;
        switch (opcion)
        {
        //mayor
        case 1:
            for (int index : *indexSelectColumnas)
            {
                Columna* tmp = this->getColumnaporIndice(index);
                switch (tmp->getTipo())
                {
                case Tipo::integer:
                    if (((ColumnaInt*)tmp)->getDato() > ((ColumnaInt*)dato)->getDato()) dec = true;
                    else dec = false;

                    break;
                case Tipo::decimal:
                    if (((ColumnaDecimal*)tmp)->getDato() > ((ColumnaDecimal*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                case Tipo::caracter:
                    if (((ColumnaCaracter*)tmp)->getDato() > ((ColumnaCaracter*)tmp)->getDato()) dec = true;
                    else dec = false;

                    break;
                case Tipo::cadena:
                    if (((ColumnaString*)tmp)->getDato() > ((ColumnaString*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                default:
                    dec = false;
                    break;
                }
                if (!dec) break;
            }
            break;
         
        //menor
        case 2:
            for (int index : *indexSelectColumnas)
            {
                Columna* tmp = this->getColumnaporIndice(index);
                switch (tmp->getTipo())
                {
                case Tipo::integer:
                    if (((ColumnaInt*)tmp)->getDato() < ((ColumnaInt*)dato)->getDato()) dec = true;
                    else dec = false;

                    break;
                case Tipo::decimal:
                    if (((ColumnaDecimal*)tmp)->getDato() < ((ColumnaDecimal*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                case Tipo::caracter:
                    if (((ColumnaCaracter*)tmp)->getDato() < ((ColumnaCaracter*)tmp)->getDato()) dec = true;
                    else dec = false;

                    break;
                case Tipo::cadena:
                    if (((ColumnaString*)tmp)->getDato() < ((ColumnaString*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                default:
                    dec = false;
                    break;
                }
                if (!dec) break;
            }
            break;
        //igual
        case 3:
            for (int index : *indexSelectColumnas)
            {
                Columna* tmp = this->getColumnaporIndice(index);
                switch (tmp->getTipo())
                {
                case Tipo::boolean:
                    if (((ColumnaBool*)tmp)->getDato() == ((ColumnaBool*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                case Tipo::integer:
                    if (((ColumnaInt*)tmp)->getDato() == ((ColumnaInt*)dato)->getDato()) dec = true;
                    else dec = false;

                    break;
                case Tipo::decimal:
                    if (((ColumnaDecimal*)tmp)->getDato() == ((ColumnaDecimal*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                case Tipo::caracter:
                    if (((ColumnaCaracter*)tmp)->getDato() == ((ColumnaCaracter*)tmp)->getDato()) dec = true;
                    else dec = false;

                    break;
                case Tipo::cadena:
                    if (((ColumnaString*)tmp)->getDato() == ((ColumnaString*)dato)->getDato()) dec = true;
                    else dec = false;
                    break;
                default:
                    dec = false;
                    break;
                }
                if (!dec) break;
            }
            break;
        default:
            dec = false;
            break;
        }

        return dec;
    }

    /*
    bool operator < ( Fila otro )
    {
        //Columna* current = this->columnas->get_pos(indexcompara);
        Columna* current = this->columnas->get_pos(this->indexcompara);
        Columna* other = otro.getColumnaporIndice(indexcompara);

        std::cout << "Dato del current: "; this->imprimirColumna(current); std::cout << '\n';
        std::cout << "Dato del other: "; this->imprimirColumna(other); std::cout << '\n';

        bool dec = false;
        if ( current->getTipo() == other->getTipo() )
        {
            switch ( current->getTipo() )
            {
            case Tipo::boolean:
                if ( ((ColumnaBool*)current)->getDato() < ((ColumnaBool*)other)->getDato() ) dec = true;
                else dec = false;

                break;
            case Tipo::integer:
                if ( ((ColumnaInt*)current)->getDato() < ((ColumnaInt*)other)->getDato() ) dec = true;
                else dec = false;

                break;
            case Tipo::decimal:
                if ( ((ColumnaDecimal*)current)->getDato() < ((ColumnaDecimal*)other)->getDato() ) dec = true;
                else dec = false;

                break;
            case Tipo::caracter:
                if ( ((ColumnaCaracter*)current)->getDato() < ((ColumnaCaracter*)other)->getDato() ) dec = true;
                else dec = false;

                break;
            case Tipo::cadena:
                if ( ((ColumnaString*)current)->getDato() < ((ColumnaString*)other)->getDato() ) dec = true;
                else dec = false;

                break;
            default:
                break;
            }
        }

        return dec;
    }
    */
    //bool validarCondicion(Lista<int, -1>* aux, int opcion) {
    //    bool dec;
    //    switch (opcion)
    //    {
    //    case 1:
    //        for (int x : *aux) {
    //            
    //        }
    //    default:
    //        break;
    //    }
   
    //}

    Columna* getColumnaporIndice(int indice)
    {
        //return this->columnas->get_pos(indice);
        return this->columnas->get_pos(indice);
    }

    void imprimirFila()
    {
        for (Columna* x : *columnas)
        {
            this->imprimirColumna(x);
            std::cout << ' ';
        }
    }

    void imprimirFilaporSeleccionColumnas(Lista<int, -1>* indexs)
    {
        for (int i : *indexs)
        {
            if (i >= 0)
            {
                this->imprimirColumna(this->columnas->get_pos(i));
                std::cout << ' ';
            }
        }
    }

    void imprimirColumna(Columna* x)
    {
        if (x == nullptr) return;
        switch (x->getTipo())
        {
        case Tipo::boolean:
            std::cout << (((ColumnaBool*)x)->getDato());

            break;
        case Tipo::integer:
            std::cout << (((ColumnaInt*)x)->getDato());

            break;
        case Tipo::decimal:
            std::cout << (((ColumnaDecimal*)x)->getDato());

            break;
        case Tipo::caracter:
            std::cout << (((ColumnaCaracter*)x)->getDato());

            break;
        case Tipo::cadena:
            std::cout << (((ColumnaString*)x)->getDato());

            break;
        default:
            break;
        }
    }

    string exportarFila()
    {
        string tmp;
        int n = 0;
        for (auto x : *columnas)
        {
            tmp += this->exportarColumna(x);
            ++n;
            if (n < this->columnas->size())  tmp += ';';
        }
        return tmp;
    }
private:
    /*
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
    */

    string exportarColumna(Columna* x)
    {
        string dato;
        if (x == nullptr) return "";
        switch (x->getTipo())
        {
        case Tipo::boolean:
            dato += to_string((((ColumnaBool*)x)->getDato()));

            break;
        case Tipo::integer:
            dato += to_string((((ColumnaInt*)x)->getDato()));

            break;
        case Tipo::decimal:
            dato += to_string((((ColumnaDecimal*)x)->getDato()));

            break;
        case Tipo::caracter:
            dato += (((ColumnaCaracter*)x)->getDato());

            break;
        case Tipo::cadena:
            dato += (((ColumnaString*)x)->getDato());

            break;
        default:
            break;
        }
        return dato;
    }
};