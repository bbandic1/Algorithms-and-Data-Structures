## Explanation of the Provided C++ Code

The provided C++ code implements various sorting algorithms and a utility to generate, load, and sort an array of integers stored in a file. The `main` function demonstrates the usage of these sorting algorithms by generating a large array of random integers, sorting it using quicksort, and verifying the correctness of the sort.

### Sorting Algorithms
The code defines four sorting algorithms: bubble sort, selection sort, quick sort, and merge sort.

#### Bubble Sort
The bubble sort algorithm repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.

#### Selection Sort
The selection sort algorithm divides the input list into two parts: the sublist of items already sorted and the sublist of items remaining to be sorted. It repeatedly selects the smallest (or largest) element from the unsorted sublist, swapping it with the first unsorted element.

#### Quick Sort
Quick sort is a divide-and-conquer algorithm that works by selecting a 'pivot' element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot. The sub-arrays are then sorted recursively.

#### Merge Sort
Merge sort is also a divide-and-conquer algorithm. It divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves.

### Utility Functions

#### `generisi`
This function generates a file with random characters.
- **Parameters**: `file` (filename), `vel` (number of characters).

#### `ucitaj`
This function reads integers from a file into an array.
- **Parameters**: `file` (filename), `niz` (array pointer), `vel` (array size reference).

#### `funkcija`
This function loads an array from a file, displays the array, prompts the user to choose a sorting algorithm, sorts the array using the chosen algorithm, and then saves the sorted array to an output file.
- **Parameters**: `file` (input filename), `niz` (array pointer), `vel` (array size reference), `izlaz` (output filename).

### Main Function
The `main` function demonstrates the usage of the quick sort algorithm by generating a large array of random integers, sorting it, and verifying the correctness of the sort.
