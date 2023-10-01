//SituacionProblema.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "SituacionProblema.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;


bool compareRecords(const ShipRecord& a, const ShipRecord& b) {
    // Utiliza sscanf para descomponer las fechas en año, mes y día
    int yearA, monthA, dayA;
    int yearB, monthB, dayB;

    sscanf(a.fecha.c_str(), "%d/%d/%d", &dayA, &monthA, &yearA);
    sscanf(b.fecha.c_str(), "%d/%d/%d", &dayB, &monthB, &yearB);

    if (a.ubi == b.ubi) {
        if (yearA != yearB) {
            return yearA < yearB; // Compara los años
        }
        else if (monthA != monthB) {
            return monthA < monthB; // Si los años son iguales, compara los meses
        }
        else {
            return dayA < dayB; // Si los años y meses son iguales, compara los días
        }
	}
    else {
		return a.ubi < b.ubi; // Si las ubicaciones son diferentes, compara las ubicaciones
	}
    
}







nodePtr append(nodePtr head, const ShipRecord& data) {
    nodePtr newNode = new Node;
    newNode->data = data;
    newNode->link = nullptr;

    if (head == nullptr) {
        head = newNode;
        return head;
    }

    nodePtr current = head;
    while (current->link != nullptr) {
        current = current->link;
    }

    current->link = newNode;

    return head;
}

nodePtr merge(nodePtr left, nodePtr right) {
    nodePtr result = nullptr;

    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }

    if (compareRecords(left->data, right->data)) {
        result = left;
        result->link = merge(left->link, right);
    }
    else {
        result = right;
        result->link = merge(left, right->link);
    }

    return result;
}

nodePtr getMiddle(nodePtr head) {
    if (head == nullptr) {
        return head;
    }

    nodePtr slow = head;
    nodePtr fast = head;

    while (fast->link != nullptr && fast->link->link != nullptr) {
        slow = slow->link;
        fast = fast->link->link;
    }

    return slow;
}

nodePtr mergeSort(nodePtr head) {
    if (head == nullptr || head->link == nullptr) {
        return head;
    }

    nodePtr middle = getMiddle(head);
    nodePtr left = head;
    nodePtr right = middle->link;
    middle->link = nullptr;

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

void processRecords(nodePtr head, const std::string& serieABuscar, std::map<std::string, std::pair<int, int>>& mesPorMes) {
    nodePtr current = head;

    while (current != nullptr) {
        if (current->data.ubi.substr(0, 3) == serieABuscar) {
			std::string mes = current->data.fecha.substr(0, 7);
            if (mesPorMes.find(mes) == mesPorMes.end()) {
				mesPorMes[mes] = std::make_pair(0, 0);
			}
            if (current->data.punto_entrada == 'M') {
				mesPorMes[mes].first++;
			}
            else if (current->data.punto_entrada == 'R') {
				mesPorMes[mes].second++;
			}
		}
		current = current->link;
	}
}

void deleteList(nodePtr& head) {
    while (head != nullptr) {
        nodePtr temp = head;
        head = head->link;
        delete temp;
    }
}


nodePtr sortList(nodePtr head) {
    return mergeSort(head); // Llama a mergeSort para ordenar la lista
}
