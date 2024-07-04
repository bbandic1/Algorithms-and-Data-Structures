# Explanation of the Provided C++ Code

The provided C++ code implements three types of map classes using arrays, binary search trees, and hash maps: `NizMapa`, `BinStabloMapa`, and `HashMapaLan`. Additionally, it defines a generic graph structure using templates. The `main` function or usage examples are not provided but the code showcases the implementation of these data structures.

## Map Base Class

The `Mapa` class is a template abstract base class that defines the following virtual functions:

- `brojElemenata() const`: Returns the number of elements in the map.
- `obrisi()`: Deletes all elements in the map.
- `obrisi(const tip1 &kljuc)`: Deletes the element with the given key.
- `operator[](tip1 x)`: Accesses or inserts an element with the given key.
- `operator[](tip1 x) const`: Const version for accessing elements.

## Array-based Map

The `NizMapa` class is a template class that implements an array-based map. It provides the following functionality:

- Constructors and destructors to manage the dynamic array.
- Copy constructor and assignment operator.
- `brojElemenata() const`: Returns the number of elements in the map.
- `obrisi()`: Deletes all elements in the map.
- `obrisi(const tip1 &kljuc)`: Deletes the element with the given key.
- `operator[](tip1 kljuc)`: Accesses or inserts an element with the given key.
- `operator[](tip1 kljuc) const`: Const version for accessing elements.

## Binary Search Tree Map

The `BinStabloMapa` class is a template class that implements a binary search tree-based map. It defines a nested structure `Cvor` to represent nodes in the tree and provides the following functionality:

- `novi(tip1 k = tip1(), tip2 v = tip2())`: Creates a new node.
- `pretraga(Cvor *p, tip1 k) const`: Searches for a node with the given key.
- `dodaj(Cvor *p, tip1 k, tip2 v = tip2(), Cvor *rod = nullptr)`: Adds a new node with the given key and value.
- `nasljednik(Cvor *tren)`: Finds the in-order successor of a node.
- `konstruktor(Cvor *x, Cvor *y)`: Copies the structure of a tree.
- `obrisiC(Cvor *tren, tip1 k)`: Deletes a node with the given key.
- `obrisi_stablo(Cvor *tren)`: Deletes the entire tree.
- Various constructors, destructors, and operators to manage tree nodes.

## Hash Map with Chaining

The `HashMapaLan` class is a template class that implements a hash map with chaining. It provides the following functionality:

- Constructors and destructors to manage the hash table.
- Copy constructor and assignment operator.
- `brojElemenata() const`: Returns the number of elements in the map.
- `obrisi()`: Deletes all elements in the map.
- `obrisi(const tip1 &kljuc)`: Deletes the element with the given key.
- `operator[](tip1 kljuc)`: Accesses or inserts an element with the given key.
- `operator[](tip1 kljuc) const`: Const version for accessing elements.
- `definisiHashFunkciju(unsigned int (*func)(tip1, unsigned int))`: Defines the hash function.

## Graph Structures

The code also defines a generic graph structure using templates, including the following classes:

### `UsmjereniGraf` (Directed Graph)

An abstract base class for directed graphs, with pure virtual functions for managing graph elements:

- `dajBrojCvorova() const`: Returns the number of nodes.
- `postaviBrojCvorova(int a)`: Sets the number of nodes.
- `dodajGranu(int p, int d, float t)`: Adds an edge.
- `obrisiGranu(int p, int d)`: Deletes an edge.
- `postojiGrana(int p, int d)`: Checks if an edge exists.
- `postaviTezinuGrane(int p, int d, float t)`: Sets the weight of an edge.
- `dajOznakuGrane(int p, int d)`: Returns the label of an edge.
- `dajOznakuCvora(int b)`: Returns the label of a node.
- `dajTezinuGrane(int p, int d)`: Returns the weight of an edge.
- `postaviOznakuCvora(int b, tip a)`: Sets the label of a node.
- `postaviOznakuGrane(int p, int d, tip a)`: Sets the label of an edge.
- `dajGranu(int p, int d)`: Returns an edge object.
- `dajCvor(int b)`: Returns a node object.
- `dajGranePocetak()`: Returns an iterator to the beginning of edges.
- `dajGraneKraj()`: Returns an iterator to the end of edges.
- `dajSljedecuGranu(int p, int d)`: Returns the next edge iterator.

### `Cvor` (Node)

A class representing a node in the graph, with the following functionality:

- `dajRedniBroj() const`: Returns the node index.
- `postaviOznaku(tip a)`: Sets the node label.
- `dajOznaku() const`: Returns the node label.
- `dodajVezu(Grana<tip> g, Cvor<tip> s)`: Adds a connection.
- `obrisiVezu(Grana<tip> g, Cvor<tip> s)`: Removes a connection.
- `dajGrane() const`: Returns the edges.
- `dajSusjede() const`: Returns the neighboring nodes.

### `Grana` (Edge)

A class representing an edge in the graph, with the following functionality:

- `dajTezinu() const`: Returns the weight.
- `postaviTezinu(float a)`: Sets the weight.
- `postaviOznaku(tip a)`: Sets the label.
- `dajOznaku() const`: Returns the label.
- `dajPolazniCvor() const`: Returns the source node.
- `dajDolazniCvor() const`: Returns the destination node.

### `GranaIterator` (Edge Iterator)

A class for iterating over edges in the graph.

## Main Function

The main function is not provided in the given code. Typically, it would demonstrate the usage of these classes by performing various operations such as inserting, deleting, and accessing elements in the maps and graphs.

