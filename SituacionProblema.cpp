// SituacionProblema.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "SituacionProblema.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

void processRecords(ShipRecord* head, const std::string& serieABuscar, std::map<std::string, std::pair<int, int>>& mesPorMes) {
    ShipRecord* current = head;

    while (current != nullptr) {
        if (current->ubi.substr(0, 3) == serieABuscar) {
            std::string fechaCompleta = current->fecha; // Utiliza la fecha completa
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

ShipRecordList sortList(ShipRecordList& list) {
    ShipRecordList result;
    result.head = mergeSort(list.head);
    // Find the new tail
    result.tail = list.head;
    while (result.tail != nullptr && result.tail->next != nullptr) {
        result.tail = result.tail->next;
    }
    return result;
}
