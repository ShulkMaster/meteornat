#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <algorithm>
#include <functional>
#include "LifeTimer.h"

#define timer(x) LifeTimer t = LifeTimer(x);


const int size = 100000;

int data[size] = {};

//Aux functions for formatting, printing and allocating arrays

void fillArray();

int *copyArray(const int *original);

void printArray(int *array, int scale);

void printSortArray(int *array, const std::function<void(int *)> &sort, int scale = 1);

//Sort methods

void bubbleSort(int *array, bool descendent = false);

void insertionSort(int *array, bool descendent = false);

int main() {
    fillArray();
    printSortArray(data, [](int *dataset) -> void {
                       insertionSort(dataset, false);
                   },
                   10);
    printSortArray(data, [](int *dataset) -> void {
                       bubbleSort(dataset, false);
                   },
                   10);
    return 0;
}

void printArray(int *array, int scale) {
    double step = 10 * scale;
    for (int i = 0; i < step; ++i) {
        int x = (int) std::ceil(size * (i / step));
        //std::cout << "[" << x << "] = " << array[x] << ", ";
        std::cout << array[x] << ", ";
        if (i % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void printSortArray(int *array, const std::function<void(int *)> &sort, int scale) {
    int *unsorted = copyArray(array);
    std::cout << "before:" << std::endl;
    printArray(unsorted, scale);
    sort(unsorted);
    std::cout << "After:" << std::endl;
    printArray(unsorted, scale);
    delete[] unsorted;
}

void fillArray() {
    std::mt19937 generator(std::time(nullptr));
    std::uniform_int_distribution<uint32_t> gen(0, 500);
    for (int &i : data) {
        i = gen(generator);
    }
}

int *copyArray(const int *original) {
    int *array = new int[size];
    for (int k = 0; k < size; ++k) {
        array[k] = original[k];
    }
    return array;
}

void bubbleSort(int *array, bool descendent) {
    timer("Bubble Sort")
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (array[i] < array[j]) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

void insertionSort(int *array, bool descendent) {
    timer("Insertion Sort")
    for (int i = 0; i < size; ++i) {
        int small = i;
        for (int j = i; j < size; ++j) {
            if (descendent) {
                if (array[small] < array[j]) {
                    small = j;
                }
            } else {
                if (array[small] > array[j]) {
                    small = j;
                }
            }
        }
        int temp = array[small];
        array[small] = array[i];
        array[i] = temp;
    }
}