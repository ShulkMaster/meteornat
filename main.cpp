#include <iostream>
#include <cmath>
#include <ctime>
#include <random>
#include <algorithm>
#include <functional>
#include "LifeTimer.h"

#define timer(x) LifeTimer t = LifeTimer(x);


const int size = 8;

int data[size] = {2, 1, 4, 3, 6, 5, 8, 7};

//Aux functions for formatting, printing and allocating arrays

void fillArray();

int *copyArray(const int *original);

void swap(int *array, int i, int j);

void merge(int *array, int ak, int half, int bk);

void printArray(int *array);

void printArray(int *array, int scale);

void printSortArray(int *array, const std::function<void(int *)> &sort, int scale = 1);

//Sort methods

void bubbleSort(int *array, bool descendent = false);

void selectionSort(int *array, bool descendent = false);

void insertionSort(int *array, bool descendent);

void mergeSort(int *array, int start, int range, bool descendent);

int main() {
    int scale = 1;

    //fillArray();

    printSortArray(data, [](int *dataset) -> void {
                       bubbleSort(dataset, false);
                   },
                   scale);

    printSortArray(data, [](int *dataset) -> void {
                       selectionSort(dataset, false);
                   },
                   scale);
    printSortArray(data, [](int *dataset) -> void {
                       insertionSort(dataset, false);
                   },
                   scale);
    printSortArray(data, [](int *dataset) -> void {
                       timer("Merge Sort")
                       mergeSort(dataset, 0, size, false);
                   },
                   scale);


    return 0;
}

void printArray(int *array) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << ", ";
        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void printArray(int *array, int scale) {
    double step = 10 * scale;
    for (int i = 0; i < step; ++i) {
        int x = (int) std::ceil(size / step * i);
        //std::cout << "[" << x << "] = " << array[x] << ", ";
        std::cout << array[x] << ", ";
        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void printSortArray(int *array, const std::function<void(int *)> &sort, int scale) {
    int *unsorted = copyArray(array);
    std::cout << "=========================================================================" << std::endl;
    std::cout << "before:" << std::endl;
    //printArray(unsorted, scale);
    printArray(unsorted);
    sort(unsorted);
    std::cout << "After:" << std::endl;
    printArray(unsorted);
    //printArray(unsorted, scale);
    std::cout << "=========================================================================" << std::endl;
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

void swap(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void merge(int *array, int ak, int half, int bk) {
    int *temp = new int[bk];
    int stackPointer = 0;
    int divisorPointer = ak+half+1;
    while (stackPointer < bk) {
        if (ak <= half and array[ak] <= array[divisorPointer]) {
            temp[stackPointer] = array[ak];
            ak++;
        } else {
            temp[stackPointer] = array[divisorPointer];
            divisorPointer++;
        }
        stackPointer++;
    }
    for (int i = 0; i < bk; ++i) {
        array[i] = temp[i];
    }
    delete[] temp;
}

void bubbleSort(int *array, bool descendent) {
    timer("Bubble Sort")
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (descendent) {
                if (array[i] < array[j]) {
                    swap(array, i, j);
                }
            } else {
                if (array[i] > array[j]) {
                    swap(array, i, j);
                }
            }

        }
    }
}

void selectionSort(int *array, bool descendent) {
    timer("Selection Sort")
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
        swap(array, small, i);
    }
}

void insertionSort(int *array, bool descendent) {
    timer("Insertion Sort")
    for (int i = 1; i < size; ++i) {
        int j = i;
        if (descendent) {
            while (j > 0 and array[j - 1] < array[j]) {
                swap(array, j - 1, j);
                --j;
            }
        } else {
            while (j > 0 and array[j - 1] > array[j]) {
                swap(array, j - 1, j);
                --j;
            }
        }

    }
}

void mergeSort(int *array, int start, int range, bool descendent) {
    if (range <= 2) {
        if (array[start] > array[start + 1]) swap(array, start, start + 1);
        return;
    }
    int half = floor(range / 2);
    mergeSort(array, start, half, descendent);
    mergeSort(array, start + half, range - half, descendent);
    merge(array, start, half, range);
}