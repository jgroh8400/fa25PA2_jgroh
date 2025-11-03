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


    // push - adds index value to minheap, increments size and upheaps last element of heap with weightArr as comparison
    void push(int idx, int weightArr[]) {
        data[size] = idx;
        size++;
        upheap(size - 1, weightArr);
    }


    // pop - removes root, calls downheap, returns root
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int smallest = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return smallest;
    }


    // upheap - swaps position of child if smaller than parent
    void upheap(int pos, int weightArr[]) {
        while (pos > 0 && weightArr[data[(pos - 1) / 2]] > weightArr[data[pos]]) {
            swap(data[(pos - 1) / 2], data[pos]);
            pos = (pos - 1) / 2; // log n time complexity
        }
    }

    // downheap - swaps parent position downward with smallest child
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (2 * pos + 1 < size) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int smallest = left;

            if (right < size && weightArr[data[left]] > weightArr[data[right]]) {
                smallest = right;
            }

            if (weightArr[data[pos]] <= weightArr[data[smallest]]) break;

            swap(data[pos], data[smallest]);
            pos = smallest;

        }

    }

    // display - used for debugging
    void display() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "displayed" << endl;
    }
};

#endif