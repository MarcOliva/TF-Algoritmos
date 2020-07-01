#include <iostream>
#include <fstream>
#include "fila.h"
#include "ABB.h"

class Tabla
{
private:
    std::string nombre;
    Lista<ColumnaNombre*, nullptr>* nombresColumnas;
    ABB<Fila*, Fila, nullptr>* datosArbol;
    Lista<int, -1>* selectColumnas;
    int nroColumnas;
    int indexColumna;
public:
    Tabla(std::string name, int nrocols, Lista<ColumnaNombre*, nullptr>* nombresCols = nullptr, int indexCol = 0, 
        function<Fila(Fila*)> _key = [](Fila* a) { return (*a); })
        : nombre(name), nroColumnas(nrocols), indexColumna(indexCol)
    {
        this->nombresColumnas = new Lista<ColumnaNombre*, nullptr>();

        this->datosArbol = new ABB<Fila*, Fila, nullptr>(_key);
        
        for ( auto x : *nombresCols )
        {
            nombresColumnas->agregar_final(x);
        }

        this->selectColumnas = new Lista<int, -1>();
    }

    ~Tabla()
    {
        delete nombresColumnas;
        delete selectColumnas;
        delete datosArbol;
    }

    void imprimirTabla()
    {
        if (this->selectColumnas != nullptr && this->selectColumnas->size() > 0)
        {
            for (auto x : *selectColumnas)
                if( x >= 0 ) std::cout << this->nombresColumnas->get_pos(x)->getNombre() << '\t';
            std::cout << '\n';
            
            Lista<int, -1>* aux = this->selectColumnas;
            auto func = [aux](Fila* current)
            {
                current->imprimirFilaporSeleccionColumnas(aux);
                std::cout << '\n';
            };
            this->datosArbol->inOrder(func);
            
        }
        else
        {
            for (auto x : *nombresColumnas)
                std::cout << x->getNombre() << '\t';
            std::cout << '\n';
            
            auto func = [](Fila* current)
            {
                current->imprimirFila();
                std::cout << '\n';
            };
            this->datosArbol->inOrder(func);
        }
        
    }

    bool InsertarFila( Lista<string*, nullptr> * fila )
    {
        Fila* nuevafila = new Fila(this->indexColumna);
        //cout << "LLego hasta aqui 2\n";
        int index = 0; bool dec = true;
        for( string* s : *fila )
        {
            //cout << "LLego hasta aqui 3\n";
            //cout << s->size() << '\n';
            Columna* nuevo = this->validacion(s, this->nombresColumnas->get_pos(index++)->getTipo());
            //cout << "LLego hasta aqui\n";
            if( nuevo != nullptr ) nuevafila->InsertarDato(nuevo, this->nroColumnas);
            else
            {
                dec = false; break;
            }
            //cout << "LLego hasta aqui\n";
        }

        if (dec) this->datosArbol->addElemento(nuevafila);
        return dec;
    }

    void agregarColumnaSeleccion(int index)
    {
        this->selectColumnas->agregar_final(index);
    }

    void limpiarSeleccionColumnas()
    {
        delete selectColumnas;
        this->selectColumnas = new Lista<int, -1>();
    }

    void SeleccionarColumna(int index);

    void FiltrarDatosporColumna(function<Columna(Fila)> func);

    Tabla* OrdenarDatosporColumna(int index);

    void ExportacionTabla(string nombre="default")
    {
        if (nombre == "default") nombre = this->getNombre();
        std::ofstream archivo;
        archivo.open(nombre + ".txt");
        if (archivo.is_open())
        {
            int n = 0;
            for (auto nombColumna : *nombresColumnas)
            {
                archivo << nombColumna->getNombre();
                ++n;
                if (n < nombresColumnas->size()) archivo << ';';
            }
            archivo << '\n';

            auto func = [&archivo](Fila* current)
            {
                archivo << current->exportarFila();
                archivo << '\n';
            };
            this->datosArbol->inOrder(func);
        }
        else cout << "Hubo un error al abrir el archivo " + nombre + ".txt\n";
        
        archivo.close();
    }

    string getNombre() { return this->nombre; }

    int getNroFila() { return this->datosArbol->size(); }

    int getNroColumnas() { return this->nroColumnas; }
private:

    Columna* validacion(string * s, Tipo tp)
    {
        Columna* nuevo = nullptr;
        //cout << "LLego hasta aqui 4\n";
        //cout << (*s) << '\n';
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
            //cout << "LLego hasta aqui, entro al integer\n";
            if ( ( (int)(*s)[0] >= 48 && (int)(*s)[0] <= 57 ) || (int)(*s)[0] == 43 || (int)(*s)[0] == 45 )
            {
                //cout << "LLego a entrar al if de integer\n";
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
                    //cout << "LLego hasta aqui, para crear la columna\n";
                    int dato = stoi(*s);
                    nuevo = new ColumnaInt(dato);
                    //cout << "LLego hasta aqui,se termino de crear la columna\n";
                }
            }        
            //else cout << "no entro al if del integer\n";
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
        //cout << "LLego hasta aqui 5\n";
        return nuevo;
    }

};