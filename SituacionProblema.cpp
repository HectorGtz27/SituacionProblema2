//SituacionProblema.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "SituacionProblema.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//compareEecords se utiliza para comparar dos registros de buques y ordenarlos por fecha y ubicacion en orden ascendente
// 
bool compareRecords(const ShipRecord& a, const ShipRecord& b) {
    int yearA, monthA, dayA;
    int yearB, monthB, dayB;

    sscanf(a.fecha.c_str(), "%d/%d/%d", &dayA, &monthA, &yearA);
    sscanf(b.fecha.c_str(), "%d/%d/%d", &dayB, &monthB, &yearB);

    if (a.ubi == b.ubi) {
        if (yearA != yearB) {
            return yearA < yearB;
        }
        else if (monthA != monthB) {
            return monthA < monthB;
        }
        else {
            return dayA < dayB;
        }
    }
    else {
        return a.ubi < b.ubi;
    }
}

//map es para realizar un seguimiento de la cantidad de entradas de buques por mes en funcion de una fecha dada
// La clave del mapa es la fecha en formato "MM / AAAA" y el valor es un par de enteros que representan la cantidad de entradas de buques en el mediterraneo y el mar rojo respectivamente

//La funcion processRecors es para procesar los registros de buques y actualizar el mapa con la cantidad de entradas de buques por mes
// tambien sirve para verificar si la serie a buscar existe en la lista de registros de buques
void processRecords(ShipRecord* head, const std::string& serieABuscar, std::map<std::string, std::pair<int, int>>& mesPorMes) {
    ShipRecord* current = head;

    while (current != nullptr) {
        if (current->ubi.substr(0, 3) == serieABuscar) {
            std::string fechaCompleta = current->fecha;
            if (mesPorMes.find(fechaCompleta) == mesPorMes.end()) {
                mesPorMes[fechaCompleta] = std::make_pair(0, 0);
            }
            if (current->punto_entrada == 'M') {
                mesPorMes[fechaCompleta].first++;
            }
            else if (current->punto_entrada == 'R') {
                mesPorMes[fechaCompleta].second++;
            }
        }
        current = current->next;
    }
}

void deleteList(ShipRecord*& head) {
    while (head != nullptr) {
        ShipRecord* temp = head;
        head = head->next;
        delete temp;
    }
}

ShipRecord* merge(ShipRecord* left, ShipRecord* right) {
    ShipRecord* result = nullptr;

    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    if (compareRecords(*left, *right)) {
        result = left;
        result->next = merge(left->next, right);
    }
    else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

ShipRecord* getMiddle(ShipRecord* head) {
    if (head == nullptr) {
        return head;
    }

    ShipRecord* slow = head;
    ShipRecord* fast = head;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

ShipRecord* mergeSort(ShipRecord* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    ShipRecord* middle = getMiddle(head);
    ShipRecord* left = head;
    ShipRecord* right = middle->next;
    middle->next = nullptr;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

//La funcion sortList tiene una complejidad computacional de O (n log n) ya que utiliza el algoritmo de ordenacion de mezcla para ordenar la lista.
ShipRecordList sortList(ShipRecordList& list) {
    ShipRecordList result;
    result.head = mergeSort(list.head);
    result.tail = list.head;
    while (result.tail != nullptr && result.tail->next != nullptr) {
        result.tail = result.tail->next;
    }
    return result;
}

//La funcion binarySearch tiene una complejidad computacional de O (log n) ya que la lista esta ordenada y se divide a la mitad en cada iteracion de la funcion. 
bool binarySearch(ShipRecord* head, const std::string& targetSerie) {
    ShipRecord* left = head;
    ShipRecord* right = nullptr;

    while (left != right) {
        ShipRecord* middle = left;
        int count = 0;

        // Avanzar 'middle' a la mitad de la lista
        while (middle != right) {
            middle = middle->next;
            count++;
        }

        // Avanzar 'middle' a la mitad de la lista nuevamente
        middle = left;
        for (int i = 0; i < count / 2; i++) {
            middle = middle->next;
        }

        // Verificar si 'middle' es el elemento deseado
        if (middle->ubi.substr(0, 3) == targetSerie) {
            return true;
        }

        // Actualizar 'left' y 'right' según la comparación
        if (middle->ubi.substr(0, 3) < targetSerie) {
            left = middle->next;
        }
        else {
            right = middle;
        }
    }

    // Verificar el último elemento (cuando la lista tiene un solo elemento)
    if (left && left->ubi.substr(0, 3) == targetSerie) {
        return true;
    }

    return false;
}

// La funcion imprimirCantidadEntradasPorMes tiene una complejidad computacional de O (n) ya que recorre la lista una vez para extraer el mes y el año de cada fecha y luego recorre el mapa una vez para imprimir la cantidad de entradas de buques por mes.
void ListaEnlazada::imprimirCantidadEntradasPorMes() {
    // Implementación de la función imprimirCantidadEntradasPorMes
    std::map<std::string, std::pair<int, int>> cantidadPorMes;
    Nodo* actual = cabeza;
    while (actual) {
        // Extraer mes y año de la fecha
        std::string fecha = actual->fecha;
        std::string mes = fecha.substr(3, 2);
        std::string anio = fecha.substr(6, 4);

        // Incrementar la cantidad de entrada de buques de esa serie en ese mes
        cantidadPorMes[mes + " " + anio].first += actual->valor1;
        cantidadPorMes[mes + " " + anio].second += actual->valor2;

        actual = actual->siguiente;
    }

    // Imprimir la cantidad de entrada de buques por mes
    std::cout << "Cantidad de Entradas de Buques por Mes:" << std::endl;
    std::cout << "M   A  CM CR" << std::endl;
    for (const auto& entry : cantidadPorMes) {
        std::istringstream ss(entry.first);

        std::string month, year;
        ss >> month >> year;

        if (month == "01") {
            std::cout << "Jan ";
        }
        else if (month == "02") {
            std::cout << "Feb ";
        }
        else if (month == "03") {
            std::cout << "Mar ";
        }
        else if (month == "04") {
            std::cout << "Apr ";
        }
        else if (month == "05") {
            std::cout << "May ";
        }
        else if (month == "06") {
            std::cout << "Jun ";
        }
        else if (month == "07") {
            std::cout << "Jul ";
        }
        else if (month == "08") {
            std::cout << "Aug ";
        }
        else if (month == "09") {
            std::cout << "Sep ";
        }
        else if (month == "10") {
            std::cout << "Oct ";
        }
        else if (month == "11") {
            std::cout << "Nov ";
        }
        else {
			std::cout << "Dec ";
		}


        //std::cout << entry.first << " "  << std::endl;
        std::cout << year << " " << entry.second.first << " " << entry.second.second << std::endl;
    }
}
