#pragma once
#include "columna.h"
#include "lista.h"

class Fila
{
    Lista<Columna*, nullptr>* columnas;

public:
    Fila(Lista<Columna*, nullptr>* cols = nullptr) : columnas(cols) {}

    void ActualizarDatos(Columna* dato, int index)
    {
        this->ActualizarDatos(this->columnas, dato, index);
    }
private:
    void ActualizarDatos(Lista<Columna*, nullptr>*& cols, Columna* dato, int index)
    {
        if (cols == nullptr) return;

        Columna* aux = cols->get_pos(index);

        if (aux == nullptr) return;

        if (aux->getTipo() == dato->getTipo())
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

            case Tipo::string:
                ((ColumnaString*)aux)->setDato(((ColumnaString*)dato)->getDato());
                break;

            default:
                break;
            }
        }
    }
};