#pragma once

#include <string>
#include <map>

class ShipRecord {
public:
    std::string fecha;
    char punto_entrada;
    std::string ubi;
    ShipRecord* next;

    ShipRecord(const std::string& _fecha, char _punto_entrada, const std::string& _ubi)
        : fecha(_fecha), punto_entrada(_punto_entrada), ubi(_ubi), next(nullptr) {}
};

class ShipRecordList {
public:
    ShipRecord* head;
    ShipRecord* tail;

    ShipRecordList() : head(nullptr), tail(nullptr) {}

    void append(const std::string& fecha, char punto_entrada, const std::string& ubi) {
        ShipRecord* newNode = new ShipRecord(fecha, punto_entrada, ubi);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
};


bool compareRecords(const ShipRecord& a, const ShipRecord& b);

void processRecords(ShipRecord* head, const std::string& serieABuscar, std::map<std::string, std::pair<int, int>>& mesPorMes);

void deleteList(ShipRecord*& head);

ShipRecord* mergeSort(ShipRecord* head);

ShipRecordList sortList(ShipRecordList& list);

bool binarySearch(ShipRecord* head, const std::string& targetSerie);
