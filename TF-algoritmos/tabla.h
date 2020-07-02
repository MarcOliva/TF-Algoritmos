#include <iostream>
#include <fstream>
#include "fila.h"
#include "ABB.h"

class Tabla
{
private:
    std::string nombre;
    Lista<ColumnaNombre*, nullptr>* nombresColumnas;
    ABB<Fila*, Fila*, nullptr>* datosArbol;
    Lista<int, -1>* selectColumnas;
    int nroColumnas;
    int indexColumna;
    function<bool(Fila*, Fila*)> comparar;
public:
    Tabla(std::string name, int nrocols, Lista<ColumnaNombre*, nullptr>* nombresCols = nullptr, int indexCol = 0)
        : nombre(name), nroColumnas(nrocols), indexColumna(indexCol)
    {
        this->nombresColumnas = new Lista<ColumnaNombre*, nullptr>();

        this->comparar = [indexCol](Fila* mayor, Fila* menor) -> bool
        {
            return mayor->compararMayor(menor, indexCol);
        };

        this->datosArbol = new ABB<Fila*, Fila*, nullptr>(this->comparar);

        for (auto x : *nombresCols)
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
        std::cout << "Columnas -> ";
        for (auto x : *nombresColumnas)
            std::cout << x->getNombre()<<"|"<< '\t';
        std::cout << '\n';        
        auto func = [](Fila* current)
        {
            current->imprimirFila();
            std::cout <<"|"<< '\n';
        };
        this->datosArbol->inOrder(func);
    }

    void imprimirTablaconColumnasSeleccionadas()
    {
        if (this->selectColumnas != nullptr && this->selectColumnas->size() > 0)
        {
            for (auto x : *selectColumnas)
                if (x >= 0) std::cout << this->nombresColumnas->get_pos(x)->getNombre() << '\t';
            std::cout << '\n';

            //desde aca
            Lista<int, -1>* aux = this->selectColumnas;
            auto func = [aux](Fila* current)
            {
                current->imprimirFilaporSeleccionColumnas(aux);
                std::cout << '\n';
            };
            this->datosArbol->inOrder(func);
        }
    }

    bool InsertarFila(Lista<string*, nullptr>* fila)
    {
        Fila* nuevafila = new Fila();
        //cout << "LLego hasta aqui 2\n";
        int index = 0; bool dec = true;
        for (string* s : *fila)
        {
            //cout << "LLego hasta aqui 3\n";
            //cout << s->size() << '\n';
            Columna* nuevo = this->validacion(s, this->nombresColumnas->get_pos(index++)->getTipo());
            //cout << "LLego hasta aqui\n";
            if (nuevo != nullptr) nuevafila->InsertarDato(nuevo, this->nroColumnas);
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
    
    Lista<ColumnaNombre*, nullptr>* getNombresColumnas() {
        return nombresColumnas;
    }

    void limpiarSeleccionColumnas()
    {
        delete selectColumnas;
        this->selectColumnas = new Lista<int, -1>();
    }

    void setIndexColumna(int indexCol)
    {
        //cambiamos el valor de index
        this->indexColumna = indexCol;

        //cambiamos el lambda de comparar en el arbol
        this->comparar = [indexCol](Fila* mayor, Fila* menor) -> bool
        {
            return mayor->compararMayor(menor, indexCol);
        };

        //generamos el nuevo arbol con ayuda del lambda
        ABB<Fila*, Fila*, nullptr>* nuevoArbol = new ABB<Fila*, Fila*, nullptr>(this->comparar);

        auto agregar = [&nuevoArbol](Fila* current)
        {
            nuevoArbol->addElemento(current);
        };

        this->datosArbol->inOrder(agregar);

        this->datosArbol = nuevoArbol;
    }

    void SeleccionarColumna(int index);

    void FiltrarDatosporColumna(function<Columna(Fila)> func);

    void OrdenarDatosporColumna(int indexCol)
    {
        auto lambda = [indexCol](Fila* mayor, Fila* menor) -> bool
        {
            return mayor->compararMayor(menor, indexCol);
        };

        //generamos el nuevo arbol con ayuda del lambda
        ABB<Fila*, Fila*, nullptr>* nuevoArbol = new ABB<Fila*, Fila*, nullptr>(lambda);

        auto agregar = [&nuevoArbol](Fila* current)
        {
            nuevoArbol->addElemento(current);
        };

        this->datosArbol->inOrder(agregar);

        auto func = [](Fila* current)
        {
            current->imprimirFila();
            std::cout << '\n';
        };

        //Imprime el nuevo arbol
        nuevoArbol->inOrder(func);
    }

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

    int getNroIndex() { return this->indexColumna; }

    Tipo getTipoColumnasSeleccionadas()
    {
        int indextmp = this->selectColumnas->get_inicio();
        if (indextmp == -1) return Tipo::none;

        return this->nombresColumnas->get_pos(indexColumna)->getTipo();
    }

    void ImprimirInfo()
    {
        int n = 0;
        for (auto curr : *nombresColumnas)
        {
            if (n == this->getNroIndex()) cout << "[Columna Index] -> ";
            cout << "Columna " << (n+1) << " (Nombre: " << curr->getNombre() << ", Tipo: " << this->ImprimirTipo(curr->getTipo()) << ")\n";
            ++n;
        }
    }

    void ejecutarFiltro(int opcion, Columna* datocomparar) {
        auto func = [](Fila* current)
        {
            current->imprimirFila();
            std::cout << '\n';
        };
        Lista<int, -1>* aux = this->selectColumnas;

        function<bool(Fila*)>  lambda_filtro = [&aux,opcion, &datocomparar](Fila* current) {
            if (current->compararEnFiltro(aux, datocomparar, opcion))
            {
                return true;
            }
            return false;
        };

        switch (opcion)
        {
        //mayor
        case 1:
            this->datosArbol->Mayor_que(lambda_filtro, func);
            break;
        //menor
        case 2:
            this->datosArbol->Menor_que(lambda_filtro, func);
            break;
        case 3: //igual
            this->datosArbol->Igual_que(lambda_filtro, func);
            break;
        default:
            break;
        }
    }
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
    void ejecutarFiltro() {
      //logica
    }

    string ImprimirTipo(Tipo tp)
    {
        switch (tp)
        {
        case none:
            break;
        case boolean:
            return "Booleano";
            break;
        case integer:
            return "Integer";
            break;
        case decimal:
            return "Decimal";
            break;
        case caracter:
            return "Caracter";
            break;
        case cadena:
            return "Cadena";
            break;
        default:
            break;
        }
    }

};