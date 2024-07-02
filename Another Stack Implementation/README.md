# Description of the C++ Code

The provided C++ code defines a template-based framework for managing a stack data structure and performing search operations on it. It includes the following components:

### Stek Class Template
- **Purpose**: A concrete implementation of a stack using a singly linked list.
- **Members**:
  - `Cvor`: A struct representing a node in the singly linked list.
    - **Members**:
      - `x`: The value stored in the node.
      - `sljedeci`: Pointer to the next node.
  - `top`: Pointer to the top node in the stack.
  - `el`: The number of elements in the stack.
- **Methods**:
  - Constructor: Initializes an empty stack.
  - Destructor: Deletes all nodes in the stack.
  - Copy constructor: Creates a deep copy of the stack.
  - `brojElemenata() const`: Returns the number of elements in the stack.
  - `brisi()`: Deletes all nodes in the stack.
  - `stavi(const tip &x)`: Adds a new node to the top of the stack.
  - `skini()`: Removes and returns the top node's value.
  - `Vrh() const`: Returns the value of the top node (non-modifiable).
  - `vrh()`: Returns the value of the top node (modifiable).
  - `operator=(const Stek<tip> &x)`: Assignment operator to copy the stack.
  - `ispisi() const`: Prints all elements in the stack.

### Utility Function
- **pretraga(Stek<std::vector<int>> &v, int trazeni)**:
  - **Purpose**: Searches for a specific element in a stack of vectors and prints its position.
  - **Parameters**: A reference to a stack of vectors and the element to search for.
  - **Functionality**:
    - If the stack is empty, it prints "Nema elementa".
    - If the element is found, it prints its position.
    - Otherwise, it prints "Nema elementa".

### Main Function
- **Purpose**: Demonstrates and tests the stack implementation and search functionality.
- **Functionality**:
  - Creates a stack of vectors.
  - Pushes several vectors onto the stack.
  - Searches for a specific element in the stack.
  - Prints the stack's elements after the search operation.