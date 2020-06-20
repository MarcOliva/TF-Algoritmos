#pragma once
#include <iostream>
#include "fila.h"
#include "ABB.h"

class Tabla
{
private:
    std::string nombre;
    Lista<ColumnaNombre*, nullptr>* nombresColumnas;
    ABB<Fila*, int, nullptr>* datosTabla;
    int nroColumnas;
public:
    Tabla(std::string name, int nrocols, Lista<ColumnaNombre*, nullptr>* nombresCols) : nombre(name), nroColumnas(nrocols)
    {
        this->nombresColumnas = new Lista<ColumnaNombre*, nullptr>();
        this->datosTabla = new ABB<Fila*, int, nullptr>();

        for (int i = 0; i < this->nroColumnas; ++i)
        {
            nombresColumnas->agregar_final(nombresCols->get_pos(i));
        }

    }

    ~Tabla()
    {
        delete nombresColumnas;
        delete datosTabla;
    }

    void imprimirTabla()
    {
        std::cout << (int)nombresColumnas->size() << '\n';
        for (int i = 0; i < (int)nombresColumnas->size(); ++i)
            std::cout << nombresColumnas->get_pos(i)->getNombre() << ' ';
        std::cout << '\n';
    }

    void InsertarFila(Fila* nuevafila);

    void SeleccionarColumna(int index);

    void FiltrarDatosporColumna(function<Columna(Fila)> func);

    Tabla* OrdenarDatosporColumna(int index);

    void ExportacionTabla();
};