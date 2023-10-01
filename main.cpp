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
    while(current != nullptr) {
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

    processRecords(mediterraneoList.head, serieABuscar, mesPorMes);
    processRecords(marRojoList.head, serieABuscar, mesPorMes);

    // Imprimir el mapa con la fecha que se encontró y la cantidad de entradas por cada punto de entrada
    cout << "---------------------------------" << endl;
    cout << "Mapa con la fecha que se encontro y la cantidad de entradas por cada punto de entrada:" << endl;
    cout << "---------------------------------" << endl;
    for (const auto& entry : mesPorMes) {
        cout << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
    }

    // Liberar la memoria de las listas
    deleteList(mediterraneoList.head);
    deleteList(marRojoList.head);

    return 0;
}
