## Explanation of the Provided C++ Code

The provided C++ code implements a stack data structure using a singly linked list. The code includes a `Stek` class with various member functions to perform stack operations such as push, pop, and retrieve the top element. The `main` function demonstrates the usage of this stack by pushing and popping elements.

### `Stek` Class
#### Private Members
- `struct Cvor`: A node structure that holds an element of the stack and a pointer to the next node.
- `Cvor* poc`: A pointer to the top node of the stack.
- `int el`: A counter for the number of elements in the stack.

#### Public Members
- **Constructor**: Initializes an empty stack with `poc` set to `nullptr` and `el` set to 0.
- **Destructor**: Deletes all nodes in the stack to free memory.
- **Copy Constructor**: Creates a deep copy of another stack.
- **Assignment Operator**: Assigns one stack to another, ensuring a deep copy.
- `int brojElemenata() const`: Returns the number of elements in the stack.
- `tip vrh() const`: Returns the top element of the stack (constant version).
- `tip& vrh()`: Returns the top element of the stack (modifiable version).
- `void stavi(const tip &x)`: Pushes a new element onto the stack.
- `tip skini()`: Pops the top element from the stack and returns it.
- `void brisi()`: Clears the stack by deleting all nodes.
- `void ispisi() const`: Prints all elements of the stack.

### `main` Function
- Demonstrates the usage of the `Stek` class by performing the following steps:
  - Creates a stack `s` of integers.
  - Pushes integers 1 to 5 onto the stack.
  - Tries to pop six elements from the stack, catching any exceptions thrown when attempting to pop from an empty stack and printing "Izuzetak".
