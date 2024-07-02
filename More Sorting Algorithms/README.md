# Description of the C++ Code

The provided C++ code defines and demonstrates various sorting algorithms, including radix sort and heap sort, along with utility functions for managing a binary heap. It includes the following components:

### Utility Functions
- **vectorMax(vector<int> v)**:
  - **Purpose**: Finds and returns the maximum value in a vector.
  - **Parameters**: A vector of integers.
  - **Returns**: The maximum value in the vector.

- **countSort(std::vector<int> &v, int exp)**:
  - **Purpose**: Performs counting sort on the vector based on the digit represented by `exp`.
  - **Parameters**: A reference to a vector of integers and an integer representing the digit's place (exponent).
  - **Returns**: Modifies the vector in place to sort it based on the current digit.

- **radixSort(vector<int>& v)**:
  - **Purpose**: Sorts a vector of integers using radix sort.
  - **Parameters**: A reference to a vector of integers.
  - **Returns**: Modifies the vector in place to sort it.

- **swapp(vector<int> &v, int i, int j)**:
  - **Purpose**: Swaps the elements at indices `i` and `j` in the vector.
  - **Parameters**: A reference to a vector of integers and two indices.
  - **Returns**: Modifies the vector in place to swap the elements.

- **roditelj(int i)**:
  - **Purpose**: Computes the parent index of a given index in a binary heap.
  - **Parameters**: An integer index.
  - **Returns**: The parent index.

- **l_dijete(int i)**:
  - **Purpose**: Computes the left child index of a given index in a binary heap.
  - **Parameters**: An integer index.
  - **Returns**: The left child index.

- **d_dijete(int i)**:
  - **Purpose**: Computes the right child index of a given index in a binary heap.
  - **Parameters**: An integer index.
  - **Returns**: The right child index.

- **popravi_dolje(vector<int> &v, int i, int vel)**:
  - **Purpose**: Fixes the binary heap property downwards from index `i`.
  - **Parameters**: A reference to a vector of integers, an integer index, and the size of the heap.
  - **Returns**: Modifies the vector in place to maintain the heap property.

- **popravi_gore(vector<int> &v, int i)**:
  - **Purpose**: Fixes the binary heap property upwards from index `i`.
  - **Parameters**: A reference to a vector of integers and an integer index.
  - **Returns**: Modifies the vector in place to maintain the heap property.

- **izbaciPrvi(vector<int> &v, int &velicina)**:
  - **Purpose**: Removes and returns the first element (root) from the heap.
  - **Parameters**: A reference to a vector of integers and a reference to the size of the heap.
  - **Returns**: The value of the removed root element and modifies the heap in place.

- **umetniUGomilu(vector<int> &v, int umetnuti, int &velicina)**:
  - **Purpose**: Inserts a new element into the heap.
  - **Parameters**: A reference to a vector of integers, the value to insert, and a reference to the size of the heap.
  - **Returns**: Modifies the heap in place to include the new element.

- **stvoriGomilu(vector<int> &v)**:
  - **Purpose**: Converts a vector into a binary heap.
  - **Parameters**: A reference to a vector of integers.
  - **Returns**: Modifies the vector in place to satisfy the heap property.

- **gomilaSort(vector<int> &v)**:
  - **Purpose**: Sorts a vector of integers using heap sort.
  - **Parameters**: A reference to a vector of integers.
  - **Returns**: Modifies the vector in place to sort it.

### Main Function
- **Purpose**: Demonstrates and tests the sorting algorithms.
- **Functionality**:
  - Creates vectors and populates them with integers.
  - Sorts the vectors using radix sort and standard sort.
  - Compares the results of both sorts to verify correctness.
  - Prints "OK" if both sorted vectors match.