#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    // Partition
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    // Recursion
    #pragma omp parallel sections
    {
        #pragma omp section
        if (left < j) quickSort(arr, left, j);
        #pragma omp section
        if (i < right) quickSort(arr, i, right);
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    cout << "Original array:" << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    // Parallel Quick Sort
    #pragma omp parallel
    {
        #pragma omp single
        quickSort(arr, 0, n - 1);
    }

    cout << "Sorted array:" << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
