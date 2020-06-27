#include <iostream>
#include "fila.h"
#include "ABB.h"

class Tabla
{
private:
    std::string nombre;
    Lista<ColumnaNombre*, nullptr>* nombresColumnas;
    //ABB<Fila*, int, nullptr>* datosTabla;
    int nroColumnas;
public:
    Tabla(std::string name, int nrocols, Lista<ColumnaNombre*, nullptr>* nombresCols = nullptr ) : nombre(name), nroColumnas(nrocols)
    {
        this->nombresColumnas = new Lista<ColumnaNombre*, nullptr>();
        
        //this->datosTabla = new ABB<Fila*, int, nullptr>();
        
        for ( auto x : *nombresCols )
        {
            nombresColumnas->agregar_final(x);
        }
        
    }

    ~Tabla()
    {
        delete nombresColumnas;
        //delete datosTabla;
    }

    void imprimirTabla()
    {
        std::cout << (int)nombresColumnas->size() << '\n';
        for ( auto x : *nombresColumnas )
            std::cout << x->getNombre() << ' ';
        std::cout << '\n';
    }

    bool InsertarFila( Lista<string*, nullptr> * fila )
    {
        Fila* nuevafila = new Fila();
        
        int index = 0; bool dec = true;
        for( auto s : *fila )
        {
            Columna* nuevo = this->validacion(s, this->nombresColumnas->get_pos(index)->getTipo());
            if( nuevo != nullptr ) nuevafila->InsertarDato(nuevo, this->nroColumnas);
            else
            {
                dec = false; break;
            }
        }

        //if (dec) this->datosTabla->addElemento(nuevafila);
        return dec;
    }

    void SeleccionarColumna(int index);

    void FiltrarDatosporColumna(function<Columna(Fila)> func);

    Tabla* OrdenarDatosporColumna(int index);

    void ExportacionTabla();

private:

    Columna* validacion(string * s, Tipo tp)
    {
        Columna* nuevo = nullptr;

        switch (tp)
        {
        case Tipo::none:
            break;
        case Tipo::boolean:
            if ( (int)s->size() == 1 )
            {
                int aux = (int)s->at(0);
                if ( aux >= 48 && aux <= 57 )
                {
                    nuevo = new ColumnaBool((bool)aux);
                }
            }
            break;
        case Tipo::integer:
            if ( ( (int)(*s)[0] >= 48 && (int)(*s)[0] <= 57 ) || (int)(*s)[0] == 43 || (int)(*s)[0] == 45 )
            {
                int i = 0, cntpunto = 0; bool vd = true;
                if ( (int)(*s)[0] == 43 || (int)(*s)[0] == 45 )
                {
                    if ( (int)s->size() == 1 )
                    {
                        vd = false;
                        break;
                    }
                    ++i;
                }
                
                for ( i; i < (int)s->size(); ++i )
                {
                    int aux = (int)(*s)[i];
                    if ( aux == 46 ) ++cntpunto;
                    if ( !( ( aux >= 48 && aux <= 57 ) || aux == 46 ) || 
                    ( cntpunto > 1 ) || ( aux == 46 && i == (int)s->size() - 1 ) )
                    {
                        vd = false;
                        break;
                    }
                }
                if (vd)
                {
                    int dato = stoi(*s);
                    nuevo = new ColumnaInt(dato);
                }
            }        
            
            break;
        case Tipo::decimal:
            if ( ((int)(*s)[0] >= 48 && (int)(*s)[0] <= 57) || (int)(*s)[0] == 43 || (int)(*s)[0] == 45 )
            {
                int i = 0, cntpunto = 0; bool vd = true;
                if ( (int)(*s)[0] == 43 || (int)(*s)[0] == 45 )
                {
                    if ( (int)s->size() == 1 )
                    {
                        vd = false;
                        break;
                    }
                    ++i;
                }
                
                for ( i; i < (int)s->size(); ++i )
                {
                    int aux = (int)(*s)[i];
                    if ( aux == 46 ) ++cntpunto;
                    if ( !( ( aux >= 48 && aux <= 57 ) || aux == 46 ) || 
                    ( cntpunto > 1 ) || ( aux == 46 && i == (int)s->size() - 1 ) )
                    {
                        vd = false;
                        break;
                    }
                }
                if (vd)
                {
                    float dato = stof(*s);
                    nuevo = new ColumnaDecimal(dato);
                }
            } 
            break;
        case Tipo::caracter:
            if ( (int)s->size() == 1 )
            {
                nuevo = new ColumnaCaracter((*s)[0]);
            }
            break;
        case Tipo::cadena:
            nuevo = new ColumnaString((*s));
            break;
        default:
            break;
        }

        return nuevo;
    }
};