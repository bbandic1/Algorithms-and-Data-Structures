# Explanation of the Provided C++ Code

The provided C++ code implements two types of map classes using binary and AVL trees: `BinStabloMapa` and `AVLStabloMapa`. Both of these classes inherit from a base class `Mapa`. The `main` function demonstrates the usage of the AVL tree-based map (`AVLStabloMapa`).

## Map Base Class

The `Mapa` class is a template abstract base class that defines the following virtual functions:

- `brojElemenata() const`: Returns the number of elements in the map.
- `obrisi()`: Deletes all elements in the map.
- `obrisi(const tip1 &kljuc)`: Deletes the element with the given key.
- `operator[](tip1 i)`: Accesses or inserts an element with the given key.
- `operator[](tip1 i) const`: Const version for accessing elements.

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

## AVL Tree Map

The `AVLStabloMapa` class is a template class that implements an AVL tree-based map. It defines a nested structure `Cvor` to represent nodes in the tree and provides the following functionality:

- `balanss(Cvor *t)`: Calculates the balance factor of a node.
- `novi(tip1 i = tip1(), tip2 u = tip2())`: Creates a new node.
- `desno_rotiranje(Cvor *t)`: Performs a right rotation.
- `lijevo_rotiranje(Cvor *t)`: Performs a left rotation.
- `azurirajBalans(Cvor *t, bool b)`: Updates the balance factor of the nodes after insertion or deletion.
- `pretraga(Cvor *p, tip1 i) const`: Searches for a node with the given key.
- `dodaj(Cvor *p, tip1 i, tip2 u = tip2(), Cvor *rod = nullptr)`: Adds a new node with the given key and value.
- `nasljednik(Cvor *t)`: Finds the in-order successor of a node.
- `konstruktor(Cvor *a, Cvor *b)`: Copies the structure of a tree.
- `obrisiC(Cvor *t, tip1 i)`: Deletes a node with the given key.
- `obrisi_stablo(Cvor *t)`: Deletes the entire tree.
- Various constructors, destructors, and operators to manage tree nodes.

## Main Function

The `main` function demonstrates the usage of the `AVLStabloMapa` class by performing various operations such as inserting, deleting, and accessing elements. It includes a test to ensure that the AVL tree maintains its balance after various insertions and deletions.