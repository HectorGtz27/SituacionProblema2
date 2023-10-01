//main.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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

    nodePtr mediterraneoList = nullptr;
    nodePtr marRojoList = nullptr;

    string fecha, hora, linea;

    while (getline(archivo, linea)) {
        istringstream ss(linea);
        ss >> fecha >> hora;

        char puntoEntrada;
        ss >> puntoEntrada;

        string ubi;
        ss >> ubi;

        ShipRecord record;
        record.fecha = fecha + " " + hora;
        record.punto_entrada = puntoEntrada;
        record.ubi = ubi;

        if (puntoEntrada == 'M') {
            mediterraneoList = append(mediterraneoList, record);
        }
        else if (puntoEntrada == 'R') {
            marRojoList = append(marRojoList, record);
        }
    }

    mediterraneoList = sortList(mediterraneoList);
    marRojoList = sortList(marRojoList);

    // Imprimir las listas ordenadas
    cout << "---------------------------------" << endl;
    cout << "Lista ordenada del mediterraneo:" << endl;
    cout << "---------------------------------" << endl;
    nodePtr current = mediterraneoList;
    while (current != nullptr) {
        //cout << current->data.fecha << " " << current->data.punto_entrada << " " << current->data.ubi << endl;
        cout << current->data.ubi << " " << current->data.fecha << " " << current->data.punto_entrada << " " << current->data.hora << endl;
        current = current->link;
    }
    cout << endl;

    cout << "---------------------------------" << endl;
    cout << "Lista ordenada del mar rojo:" << endl;
    cout << "---------------------------------" << endl;
    nodePtr current2 = marRojoList;
    while (current2 != nullptr) {
        cout << current2->data.ubi << " " << current2->data.fecha << " " << current2->data.punto_entrada << " " << current2->data.hora << endl;
        current2 = current2->link;
    }

    string serieABuscar;
    cout << "Ingrese la serie a buscar (primeros tres caracteres del UBI): ";
    cin >> serieABuscar;

    map<string, pair<int, int>> mesPorMes;

    processRecords(mediterraneoList, serieABuscar, mesPorMes);
    processRecords(marRojoList, serieABuscar, mesPorMes);

    for (const auto& entry : mesPorMes) {
        cout << entry.first << " " << entry.second.first << " " << entry.second.second << endl;
    }

    // Liberar la memoria de las listas
    deleteList(mediterraneoList);
    deleteList(marRojoList);

    return 0;
}
