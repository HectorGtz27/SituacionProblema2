// SituacionProblema.h
#pragma once

#include <string>
#include <map>

class ShipRecord {
public:
    // dejalo asi, no lo cambies
    std::string fecha;
    std::string hora;
    char punto_entrada;
    std::string ubi;
};

class Node {
public:
    ShipRecord data;
    Node* link;
};

typedef Node* nodePtr;

bool compareRecords(const ShipRecord& a, const ShipRecord& b);

nodePtr append(nodePtr head, const ShipRecord& data);

nodePtr merge(nodePtr left, nodePtr right);

nodePtr mergeSort(nodePtr head);

nodePtr sortList(nodePtr head);

void processRecords(nodePtr head, const std::string& serieABuscar, std::map<std::string, std::pair<int, int>>& mesPorMes);

void deleteList(nodePtr& head);
