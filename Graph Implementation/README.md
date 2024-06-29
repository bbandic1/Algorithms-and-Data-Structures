## Explanation of the Provided C++ Code

The provided C++ code defines a framework for a directed graph (`UsmjereniGraf`) and its implementation using an adjacency matrix (`MatricaGraf`). Here's a breakdown of its structure and components:

### UsmjereniGraf Class Template
- **Purpose**: Represents an abstract base class for a directed graph.
- **Methods**:
  - `postaviBrojCvorova(int)`: Sets the number of nodes in the graph.
  - `postaviTezinuGrane(int, int, double)`: Sets the weight of a specific edge.
  - `postaviOznakuCvora(int, tip)`: Sets the label of a node.
  - `postaviOznakuGrane(int, int, tip)`: Sets the label of an edge.
  - `dodajGranu(int, int, double)`: Adds a directed edge between two nodes with a specified weight.
  - `obrisiGranu(int, int)`: Removes an edge between two nodes.
  - `dajBrojCvorova() const`: Returns the number of nodes in the graph.
  - `dajTezinuGrane(int, int)`: Returns the weight of a specific edge.
  - `dajOznakuCvora(int)`: Returns the label of a node.
  - `dajOznakuGrane(int, int)`: Returns the label of an edge.
  - `dajGranu(int, int)`: Returns a reference to a specific edge.
  - `dajCvor(int)`: Returns a reference to a specific node.
  - `dajGranePocetak()`: Returns an iterator pointing to the beginning of the edge list.
  - `dajGraneKraj()`: Returns an iterator pointing to the end of the edge list.
  - `postojiGrana(int, int)`: Checks if there is an edge between two nodes.

### Grana Class Template
- **Purpose**: Represents an edge in the graph.
- **Members**:
  - `pocetak`, `kraj`: Start and end nodes of the edge.
  - `tezina`: Weight of the edge.
  - `oznaka`: Label of the edge.
  - `usmjereniGraf`: Pointer to the graph to which the edge belongs.
- **Methods**:
  - `dajOznaku() const`: Returns the label of the edge.
  - `dajTezinu() const`: Returns the weight of the edge.
  - `dajPolazniCvor()`: Returns the starting node of the edge.
  - `dajDolazniCvor()`: Returns the ending node of the edge.
  - `postaviOznaku(tip)`: Sets the label of the edge.
  - `postaviTezinu(double)`: Sets the weight of the edge.

### Cvor Class Template
- **Purpose**: Represents a node in the graph.
- **Members**:
  - `redniBroj`: Index of the node.
  - `oznaka`: Label of the node.
  - `usmjereniGraf`: Pointer to the graph to which the node belongs.
- **Methods**:
  - `dajRedniBroj() const`: Returns the index of the node.
  - `dajOznaku() const`: Returns the label of the node.
  - `postaviOznaku(tip)`: Sets the label of the node.

### GranaIterator Class Template
- **Purpose**: Provides iteration over edges in the graph.
- **Members**:
  - `dolazniCvor`, `polazniCvor`: Start and end nodes of the current edge.
  - `pozicija`: Current position in the iteration.
  - `grane`: Vector of edges in the graph.
  - `vrijednosti`: 2D vector indicating existence of edges between nodes.
- **Methods**:
  - `operator!=`, `operator++`, `operator*`: Implements comparison, prefix, and postfix increment operators for iteration.
  - `trazi(int &, int &, int &, bool)`: Helper function to find the next valid edge during iteration.

### MatricaGraf Class Template
- **Purpose**: Implements `UsmjereniGraf` using an adjacency matrix.
- **Members**:
  - `grane`: Vector storing edges in the graph.
  - `cvorovi`: Vector storing nodes in the graph.
  - `vrijednosti`: 2D vector representing the adjacency matrix.
- **Methods**:
  - Constructors, destructor, copy constructor, and assignment operator.
  - Overrides methods from `UsmjereniGraf` to manage nodes, edges, and their properties using the adjacency matrix representation.

### Main Function
- **Purpose**: Demonstrates usage of `MatricaGraf` by creating a directed graph, adding edges with weights, modifying edge weights, and printing edge information.

This code provides a framework for handling directed graphs using an adjacency matrix and supports operations such as adding, modifying, and iterating over nodes and edges in the graph.
