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
        data[size] = idx;
        size++;
        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int smallest = weightArr[data[0]];
        data[0] = data[size - 1];
        downheap(0, weightArr);
        size--;
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0 && weightArr[data[(pos - 1) / 2]] > weightArr[data[pos]]) {
            swap(data[(pos - 1) / 2], data[pos]);
            pos = (pos - 1) / 2; // log n time complexity
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (pos ) {
            int left = data[2 * (pos + 1)];
            int right = data[2 * (pos + 2)];
            int smallest;
            if (weightArr[left] < weightArr[right]) {
                smallest = left;
            } else {
                smallest = right;
            }
            if (weightArr[smallest] < weightArr[pos]) {
                swap (data[pos], data[smallest]);
                cout << "test" << endl;
            }

        }

    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "displayed" << endl;
    }
};

#endif