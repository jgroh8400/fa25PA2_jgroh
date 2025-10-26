//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = idx;
        upheap(size, data);
        size++;

    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int smallest = data[0];
        data[0] = data[size - 1];
        downheap(size - 1, data);
        size--;
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (weightArr[data[pos - 1 / 2]] > weightArr[data[pos]]) {
            swap(data[pos], data[pos - 1 / 2]);
            pos = pos - 1 / 2;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (weightArr[data[pos]] > weightArr[data[2 * pos + 1]] || weightArr[data[pos]] > weightArr[data[2 * pos + 2]]) {
            swap(data[pos], data[pos - 1 / 2]);
            pos = pos - 1 / 2;
        }
    }
};

#endif