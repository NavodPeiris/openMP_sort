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

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right, int size) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        if(right - left > size/4){
            #pragma omp parallel sections num_threads(4)
            {
                #pragma omp section
                {
                    mergeSort(arr, left, mid, size);
                }
                
                #pragma omp section
                {
                    mergeSort(arr, mid + 1, right, size);
                }
            }
        }
        else{
            mergeSort(arr, left, mid, size);
            mergeSort(arr, mid + 1, right, size);
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    int arr_size = 10000000;
    int min_val = 1;
    int max_val = 10000000; 

    vector<int> arr = generateRandomArray(arr_size, min_val, max_val);

    auto start = chrono::steady_clock::now();

    // Parallel Merge Sort
    mergeSort(arr, 0, arr_size - 1, arr_size);

    auto end = chrono::steady_clock::now();

    // Calculate the elapsed time
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "\nTime taken: " << elapsed_seconds.count() << " seconds" << endl;

    return 0;
}
