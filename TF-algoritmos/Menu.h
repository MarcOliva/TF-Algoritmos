#pragma once
#include <iostream>
#include <stdlib.h>
#include "tabla.h"
#include <vector>

using namespace std;
class Menu
{
private:
	int opcion;
	vector<Tabla*>* mistablas;
public:
	Menu()
	{
		this->mistablas = new vector<Tabla*>();
		/*Lista<ColumnaNombre*, nullptr>* nombres = new Lista<ColumnaNombre*, nullptr>();
		nombres->agregar_final(new ColumnaNombre(Tipo::integer, "Codigo"));
		nombres->agregar_final(new ColumnaNombre(Tipo::caracter, "Sexo"));
		Tabla* mitabla = new Tabla("Alumno", 2, nombres);
		this->mistablas->push_back(mitabla);*/
		this->pantalla_menu();
	}

	~Menu()
	{
		delete mistablas;
	}

	void pantalla_menu()
	{
		do
		{
			system("cls");
			cout << "Bienvenido a MiniSGDB\n";
			cout << "1) Creacion de Tabla\n";
			cout << "2) Operaciones en la Tabla\n";
			cout << "3) Salir\n";
			cin >> opcion;

		} while (opcion < 1 || opcion > 3);
		
		switch (opcion)
		{
		case 1:
			this->pantalla_creacionTabla();
			break;
		case 2:
			this->pantalla_operaciones();
			break;
		case 3:
			system("cls");
			cout << "Gracias por usar nuestro sistema.\nVuelva pronto.";
			break;
		default:
			break;
		}

		if (opcion == 3) return;
		else this->pantalla_menu();
	}

	void pantalla_creacionTabla()
	{
		string nameTable;
		int numsColumns;
		system("cls");
		cout << "Creacion de Tabla" << endl;
		cout << "Ingrese nombre de la tabla: " << endl;
		cin >> nameTable;
		do
		{		
			system("cls");
			cout << "Tabla " + nameTable << endl;
			cout << "Ingrese numero de columnas" << endl;
			cin >> numsColumns;

		} while (numsColumns>5 || numsColumns<1);
		Lista<ColumnaNombre*, nullptr>* nombresColumnas = new Lista<ColumnaNombre*, nullptr>();
		string nameColumn;
		int tipo;
		for (int i = 0; i < numsColumns; i++)
		{
			cout << "Nombre columna " << i +1 << endl;
			cin >> nameColumn;
			cout << "Tipo columna (1:boolean, 2: interger , 3: decimal , 4: caracter , 5 : cadena) " + i << endl;
			cin >> tipo;
			//boolean, integer, decimal, caracter, cadena
			nombresColumnas->agregar_final(new ColumnaNombre((Tipo)tipo, nameColumn));

		}
		int indexColumn;
		do
		{
			cout << "Ingrese el numero de columna para indexar :" << endl;
			for (int i = 0; i < nombresColumnas->size(); i++)
			{
				cout << "( "<<i+1<<" " << nombresColumnas->get_pos(i)->getNombre() << ")" << endl;

			}
			cin >> indexColumn;
		} while (indexColumn<1 || indexColumn>nombresColumnas->size());
		Tabla* mitabla = new Tabla(nameTable, numsColumns, nombresColumnas,indexColumn-1);
		mistablas->push_back(mitabla);

	}

	void pantalla_operaciones()
	{
		if (mistablas->size() < 1) {
			cout << "Tienes que crear una tabla primero." << endl;
			return;
		}
		int index = ((int)this->mistablas->size() > 1) ? this->conquetablaTrabajar() : 0;
		Tabla* tmp = this->mistablas->at(index);

		do
		{
			system("cls");
			cout << "Trabajaremos con la tabla " + tmp->getNombre() + '\n';
			cout << "1) Ver los datos\n";
			cout << "2) Insertar Datos en la Tabla\n";
			cout << "3) Indexar Tabla\n";
			cout << "4) Seleccionar Columnas de la Tabla\n";
			cout << "5) Filtro de datos\n";
			cout << "6) Ordenamiento de datos\n";
			cout << "7) Exportacion de Tabla\n";
			cout << "8) Regresar\n";
			cin >> opcion;

		} while (opcion < 1 || opcion > 8);

		switch (opcion)
		{
		case 1: 
			this->imprimirTabla(tmp);
			break;
		case 2: 
			this->insertardatosTabla(tmp);
			break;
		case 3: 
			this->indexarNuevaColumna(tmp);
			break;
		case 4: 
			tmp->limpiarSeleccionColumnas();
			this->seleccionarcolumnasTabla(tmp);
			break;
		case 5: 
			this->pantallaFiltros(tmp);
			break;
		case 6: 
			this->pantallaOrdenartabla(tmp);
			break;
		case 7: 
			this->exportacionTabla(tmp);
			break;
		default:
			break;
		}

		if (opcion == 8) return;
		else this->pantalla_operaciones();
	}
	void pantallaFiltros(Tabla * tabla) {
		do
		{
			system("cls");
			cout << "Operaciones de filtro" << endl;
			cout << "1) Mayor" << endl;
			cout << "2) Menor" << endl;
			cout << "3) Igual a" << endl;
			cin >> opcion;
		} while (opcion<1 || opcion>3);

		string* s = new string(); Tipo tp = tabla->getTipoColumnasSeleccionadas();
		cout << "Ingrese valor con el cual se va a comparar: ";
		cin >> (*s);
		
		//provisional
		Columna* datoComparar = this->validacion(s, tp);
		if (datoComparar == nullptr) cout << "No se puede comparar, los valores, ya que no son del mismo tipo\n";

		else
		{
			tabla->ejecutarFiltro(opcion, datoComparar);
		}
		system("pause");
	}

	void pantallaOrdenartabla(Tabla* tmp)
	{
		do
		{
			system("cls");
			cout << "Ingrese el numero de la columna para ordenar:\n";
			cin >> opcion;
		} while (opcion < 1 || opcion > tmp->getNroColumnas());

		tmp->OrdenarDatosporColumna(--opcion);
		system("pause");
	}

	void imprimirTabla(Tabla* tmp)
	{
		do
		{
			system("cls");
			cout << "Tabla: " << tmp->getNombre() << '\n';
			cout << "Numero de columnas: " << tmp->getNroColumnas() << '\n';
			cout << "Numero de Filas: " << tmp->getNroFila() << '\n';
			cout << "\n\n";

			tmp->imprimirTabla();

			cout << "\n\n";
			cout << "Opciones:\n";
			cout << "1) Regresar\n";
			cin >> opcion;
		} while (opcion != 1 );

		return;
	}

	void insertardatosTabla(Tabla* tmp)
	{
		Lista<ColumnaNombre*, nullptr>* nombresColumnas = tmp->getNombresColumnas();
		do
		{
			system("cls");
			cout << "*************************************************************" << endl;
			cout << "OBS: Se permite ingresar 10 filas como maximo de golpe\n";
			cout << "Use el formato CSV (delimitar con ;) para imsertar las filas\n";
			cout << "*************************************************************" << endl;
				
			cout << "Ingrese el numero de filas a insertar: ";
			cin >> opcion;
		} while (opcion < 1 || opcion > 10);
		int j = 0;
		cout << "------------------------------------------------------------------------" << endl;
		cout << "                               Tabla                                      " << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		for (int i = 0; i < nombresColumnas->size(); i++)
		{
			cout << " - " << nombresColumnas->get_pos(i)->getNombre();
		}
		cout << endl;
		while (opcion--)
		{
			j++;
			Lista<string*, nullptr>* fila = new Lista<string*, nullptr>();

			cout << "Ingresa los datos de la fila " << j <<" : "  <<endl;
			string datos;
			//getline(cin, datos);
			cin >> datos;

			this->convertirStringToListaString(datos, fila, tmp->getNroColumnas());

			//cout << "LLego hasta aqui 1\n";
			for (auto s : *fila)
			{
				cout << (*s) << ' ';
			}
			cout << '\n';

			if (tmp->InsertarFila(fila)) cout << "Se inserto la fila correctamente\n";
			else cout << "Hubo un error al insertar la fila\n";
			delete fila;
		}
	}

	void seleccionarcolumnasTabla(Tabla* tmp)
	{
		/*do
		{*/
			system("cls");
			cout << "Tabla: " << tmp->getNombre() << '\n';
			cout << "Numero de columnas: " << tmp->getNroColumnas() << '\n';
			cout << "-----------------------------------------------------"<<endl;
			tmp->datosColumnas();
			cout << "-----------------------------------------------------"<<endl;


			do
			{
				cout << "Quieres seleccionar el index ? (y/n):";
				cin >> opcion;
			} while (opcion<0 || opcion>3);
			

		//} while (opcion < 1 || opcion > tmp->getNroColumnas());
			int numColumn;
			if (opcion == 0)return;
			
			if (opcion==1)
			{
				cout << "Ingrese numero de columna :" << endl;
				cin >> numColumn;
				//aqui registrar el numero de columna seleccionado
				do
				{
					cout << "Quieres agregar otra columna?  :" << endl;
					cin >> opcion;
				} while (opcion < 0 || opcion>3);
				if (opcion == 0)return;
			}
			
		/*while (opcion--)
		{
			int aux = 1;
			do 
			{

				cout << "Ingrese el numero de columna: "; cin >> aux;
			} while (aux < 1 || aux > tmp->getNroColumnas());
			tmp->agregarColumnaSeleccion(--aux);
		}*/
	}

	void indexarNuevaColumna(Tabla* tmp)
	{
		do
		{
			system("cls");
			cout << "Ingrese el numero de columna a indexar: ";
			cin >> opcion;
		} while (opcion < 1 || opcion > tmp->getNroColumnas());

		tmp->setIndexColumna(--opcion);
		cout << "Los resultados se veran en la opcion 1 del menu de operaciones.\n";
		system("pause");

	}

	void exportacionTabla(Tabla* tmp)
	{
		do
		{
			system("cls");
			cout << "Tabla: " << tmp->getNombre() << '\n';
			cout << "1) Ingrese nombre del archivo\n";
			cout << "2) Usar nombre de tabla para nombrar al archivo\n";
			cout << "3) Regresar\n";
			cin >> opcion;
		} while (opcion < 1 || opcion > 3);
		string nombre;
		switch (opcion)
		{
		case 1:
			cout << "Ingrese nombre de archivo: "; cin >> nombre;
			tmp->ExportacionTabla(nombre);
			break;
		case 2: 
			tmp->ExportacionTabla();
			break;
		case 3: break;
		default:
			break;
		}
		return;
	}

	int conquetablaTrabajar()
	{
		cout << "llegue a conquetablaTrabajar";
		return 0;
	}


private:
	void convertirStringToListaString(string datosCSV, Lista<string*, nullptr>*& fila, int cntcolumnas)
	{
		int cntcomas = 0;
		//primero validamos que exista la cantidad correcta de comas que es igual a ( cantidadDeColumnas - 1 )

		//el punto y coma (;) es 59 en ASCII.
		for (auto x : datosCSV)
		{
			if ((int)x == 59) ++cntcomas;
		}

		//No se cumple la codicion de la catidad de punto comas.
		if (cntcomas != (cntcolumnas - 1))
		{
			cout << "no cumple la condicion\n";
			return;
		}

		string* s = new string();
		for (auto x : datosCSV)
		{
			if ((int)x == 59)
			{
				fila->agregar_final(new string((*s)));
				s->clear();
			}
			else (*s) += x;
		}
		//imprimimos el ultimo
		fila->agregar_final(new string((*s)));
		delete s;
	}

	Columna* validacion(string* s, Tipo tp)
	{
		Columna* nuevo = nullptr;
		//cout << "LLego hasta aqui 4\n";
		//cout << (*s) << '\n';
		switch (tp)
		{
		case Tipo::none:
			break;
		case Tipo::boolean:
			if ((int)s->size() == 1)
			{
				int aux = (int)s->at(0);
				if (aux >= 48 && aux <= 57)
				{
					nuevo = new ColumnaBool((bool)aux);
				}
			}
			break;
		case Tipo::integer:
			//cout << "LLego hasta aqui, entro al integer\n";
			if (((int)(*s)[0] >= 48 && (int)(*s)[0] <= 57) || (int)(*s)[0] == 43 || (int)(*s)[0] == 45)
			{
				//cout << "LLego a entrar al if de integer\n";
				int i = 0, cntpunto = 0; bool vd = true;
				if ((int)(*s)[0] == 43 || (int)(*s)[0] == 45)
				{
					if ((int)s->size() == 1)
					{
						vd = false;
						break;
					}
					++i;
				}

				for (i; i < (int)s->size(); ++i)
				{
					int aux = (int)(*s)[i];
					if (aux == 46) ++cntpunto;
					if (!((aux >= 48 && aux <= 57) || aux == 46) ||
						(cntpunto > 1) || (aux == 46 && i == (int)s->size() - 1))
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
			if (((int)(*s)[0] >= 48 && (int)(*s)[0] <= 57) || (int)(*s)[0] == 43 || (int)(*s)[0] == 45)
			{
				int i = 0, cntpunto = 0; bool vd = true;
				if ((int)(*s)[0] == 43 || (int)(*s)[0] == 45)
				{
					if ((int)s->size() == 1)
					{
						vd = false;
						break;
					}
					++i;
				}

				for (i; i < (int)s->size(); ++i)
				{
					int aux = (int)(*s)[i];
					if (aux == 46) ++cntpunto;
					if (!((aux >= 48 && aux <= 57) || aux == 46) ||
						(cntpunto > 1) || (aux == 46 && i == (int)s->size() - 1))
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
			if ((int)s->size() == 1)
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
