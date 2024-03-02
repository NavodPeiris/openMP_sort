how to compile sequential programs:

- g++ -std=c++11 mergesort.cpp -o mergesort
- g++ -std=c++11 quicksort.cpp -o quicksort

how to compile parallel programs:

- g++ -std=c++11 -fopenmp mergesort_parallel.cpp -o mergesort_parallel
- g++ -std=c++11 -fopenmp quicksort_parallel.cpp -o quicksort_parallel


