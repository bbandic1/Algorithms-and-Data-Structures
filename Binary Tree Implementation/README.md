## Explanation of the Provided C++ Code

The provided C++ code implements two map classes (`Mapa` and its derived classes `NizMapa` and `BinStabloMapa`) and a demonstration in the `main` function. 

### Mapa Class
The `Mapa` class is a template abstract base class with the following methods:
- `brojElemenata() const`: returns the number of elements.
- `obrisi()`: removes all elements.
- `obrisi(const tip1 &kljuc)`: removes the element with the given key.
- `operator[](tip1 i)`: returns a reference to the value associated with the given key.
- `operator[](tip1 i) const`: returns the value associated with the given key.

### NizMapa Class
The `NizMapa` class is a template class derived from `Mapa`, using an array of pointers to store key-value pairs.
- **Constructors**: Initializes the map with a default size of 100,000.
- **Destructor**: Deletes all allocated memory.
- **Copy Constructor**: Creates a deep copy of the given map.
- **Methods**:
  - `brojElemenata() const`: returns the number of elements.
  - `obrisi()`: removes all elements and throws an exception if the map is empty.
  - `obrisi(const tip1 &kljuc)`: removes the element with the given key and throws an exception if the key is not found.
  - `operator[](tip1 kljuc)`: returns a reference to the value associated with the given key, adding a new element if the key is not found.
  - `operator[](tip1 kljuc) const`: returns the value associated with the given key, or a default value if the key is not found.

### BinStabloMapa Class
The `BinStabloMapa` class is a template class derived from `Mapa`, using a binary search tree to store key-value pairs.
- **Cvor Structure**: Represents a node in the binary search tree.
- **Constructors**: Initializes an empty tree.
- **Destructor**: Deletes all nodes in the tree.
- **Copy Constructor**: Creates a deep copy of the given tree.
- **Methods**:
  - `brojElemenata() const`: returns the number of elements.
  - `obrisi()`: removes all elements.
  - `obrisi(const tip1 &k)`: removes the element with the given key.
  - `operator=(const BinStabloMapa<tip1, tip2> &x)`: assigns the given tree to the current tree.
  - `operator[](tip1 k)`: returns a reference to the value associated with the given key, adding a new element if the key is not found.
  - `operator[](tip1 k) const`: returns the value associated with the given key, or a default value if the key is not found.

### Main Function
The `main` function demonstrates the usage of the `BinStabloMapa` class by performing the following operations:
1. Creates an instance of `BinStabloMapa` with `float` keys and values.
2. Adds several key-value pairs to the map.
3. Outputs the value associated with key `4.5`.
4. Deletes the element with key `8` and outputs the values associated with keys `7` and `8`.
5. Adds the key-value pair `(8, 8)` again and deletes the element with key `7`, then outputs the values associated with keys `5`, `8`, and `7`.
6. Deletes the element with key `3` and outputs the values associated with keys `2`, `1.5`, `1`, and `0.5`.
7. Deletes the root element with key `5`, adds the key-value pair `(3, 3)`, and outputs the values associated with keys `8`, `1.5`, and `3`.
8. Deletes the element with key `7` and outputs the values associated with keys `8` and `7`.
