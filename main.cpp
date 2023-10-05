// main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "SituacionProblema.h"

using namespace std;

int main() {
    string archivoEntrada;
    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> archivoEntrada;

    ifstream archivo(archivoEntrada);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string linea2;

    // Intentar leer una línea del archivo
    if (!getline(archivo, linea2) || linea2.empty()) {
        cerr << "El archivo esta vacio." << endl;
        return 1;
    }

    

    ShipRecordList mediterraneoList;
    ShipRecordList marRojoList;

    string fecha, hora, linea;

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        ss >> fecha >> hora;

        char puntoEntrada;
        ss >> puntoEntrada;

        string ubi;
        ss >> ubi;

        string recordFecha = fecha + " " + hora;
        if (puntoEntrada == 'M') {
            mediterraneoList.append(recordFecha, puntoEntrada, ubi);
        }
        else if (puntoEntrada == 'R') {
            marRojoList.append(recordFecha, puntoEntrada, ubi);
        }
    }

    mediterraneoList = sortList(mediterraneoList);
    marRojoList = sortList(marRojoList);


    // Imprimir las listas ordenadas
    cout << "---------------------------------" << endl;
    cout << "Lista ordenada del mediterraneo:" << endl;
    cout << "---------------------------------" << endl;
    ShipRecord* current = mediterraneoList.head;
    while (current != nullptr) {
        cout << current->ubi << " " << current->fecha << " " << current->punto_entrada << endl;
        current = current->next;
    }
    cout << endl;

    cout << "---------------------------------" << endl;
    cout << "Lista ordenada del mar rojo:" << endl;
    cout << "---------------------------------" << endl;
    current = marRojoList.head;
    while (current != nullptr) {
        cout << current->ubi << " " << current->fecha << " " << current->punto_entrada << endl;
        current = current->next;
    }

    string serieABuscar;
    cout << "Ingrese la serie a buscar (primeros tres caracteres del UBI): ";
    cin >> serieABuscar;

    map<string, pair<int, int>> mesPorMes;

    // Verificar si la serie a buscar existe usando búsqueda binaria
    bool foundInMediterraneo = binarySearch(mediterraneoList.head, serieABuscar);
    bool foundInMarRojo = binarySearch(marRojoList.head, serieABuscar);

    if (foundInMediterraneo || foundInMarRojo) {
        // Si se encontró la serie, procesar los registros
        processRecords(mediterraneoList.head, serieABuscar, mesPorMes);
        processRecords(marRojoList.head, serieABuscar, mesPorMes);


        ListaEnlazada listaMesPorMes;

        // Agregar los elementos de mesPorMes a listaMesPorMes
		for (auto it = mesPorMes.begin(); it != mesPorMes.end(); it++) {
			// Obtener la fecha eliminando la hora (suponiendo que la fecha tiene un formato fijo de 10 caracteres)
			string fecha = it->first.substr(0, 10);

			listaMesPorMes.agregar(fecha, it->second.first, it->second.second);
		}

        listaMesPorMes.imprimirCantidadEntradasPorMes();

        // Liberar la memoria de listaMesPorMes
        listaMesPorMes.~ListaEnlazada();
        

    }
    else {
        cout << "La serie especificada -> " << serieABuscar << " no se encontro en los registros." << endl;
    }

    // Liberar la memoria de las listas
    deleteList(mediterraneoList.head);
    deleteList(marRojoList.head);
    

    

    return 0;
}
