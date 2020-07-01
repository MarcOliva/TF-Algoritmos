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
		Lista<ColumnaNombre*, nullptr>* nombres = new Lista<ColumnaNombre*, nullptr>();
		nombres->agregar_final(new ColumnaNombre(Tipo::integer, "Codigo"));
		nombres->agregar_final(new ColumnaNombre(Tipo::caracter, "Sexo"));
		Tabla* mitabla = new Tabla("Alumno", 2, nombres);

		this->mistablas->push_back(mitabla);
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
		cout << "llegue a pantalla_creacionTabla";
	}

	void pantalla_operaciones()
	{
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
		case 3: break;
		case 4: 
			tmp->limpiarSeleccionColumnas();
			this->seleccionarcolumnasTabla(tmp);
			break;
		case 5: break;
		case 6: break;
		case 7: 
			this->exportacionTabla(tmp);
			break;
		default:
			break;
		}

		if (opcion == 8) return;
		else this->pantalla_operaciones();
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
		do
		{
			system("cls");
			
			cout << "OBS: Se permite ingresar 10 filas como maximo de golpe\n";
			cout << "Use el formato CSV para imsertar las filas\n";
			cout << "Ingrese el numero de filas a insertar: ";
			cin >> opcion;
		} while (opcion < 1 || opcion > 10);

		while (opcion--)
		{
			Lista<string*, nullptr>* fila = new Lista<string*, nullptr>();
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
		do
		{
			system("cls");
			cout << "Tabla: " << tmp->getNombre() << '\n';
			cout << "Numero de columnas: " << tmp->getNroColumnas() << '\n';

			cout << "Ingrese el numero de columnas a seleccionar: ";
			cin >> opcion;
		} while (opcion < 1 || opcion > tmp->getNroColumnas());

		while (opcion--)
		{
			int aux = 1;
			do 
			{

				cout << "Ingrese el numero de columna: "; cin >> aux;
			} while (aux < 1 || aux > tmp->getNroColumnas());
			tmp->agregarColumnaSeleccion(--aux);
		}
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
};