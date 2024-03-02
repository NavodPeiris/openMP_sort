#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
#include <random>
using namespace std;

vector<int> generateRandomArray(int size, int min_val, int max_val) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min_val, max_val);

    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

int partition(vector<int>& arr, int start, int end)
{
 
    int pivot = arr[start];
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (arr[i] <= pivot) {
            i++;
        }
 
        while (arr[j] > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(arr[i++], arr[j--]);
        }
    }
 
    return pivotIndex;
}
 
void quickSort(vector<int>& arr, int start, int end, int size)
{
    if (start >= end)
        return;
 
    int p = partition(arr, start, end);
    if(end - start > size/4){
        #pragma omp parallel sections num_threads(4)
        {
            #pragma omp section
            quickSort(arr, start, p - 1, size);
            #pragma omp section
            quickSort(arr, p + 1, end, size);
        }
    }
    else{
        quickSort(arr, start, p - 1, size);
        quickSort(arr, p + 1, end, size);
    }
    
}

int main() {
    int arr_size = 10000000;
    int min_val = 1;
    int max_val = 10000000; 
    vector<int> arr = generateRandomArray(arr_size, min_val, max_val);
    auto start = chrono::steady_clock::now();

    quickSort(arr, 0, arr_size - 1, arr_size);
    
    auto end = chrono::steady_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    cout << "\nTime taken: " << elapsed_seconds.count() << " seconds" << endl;
    return 0;
}
