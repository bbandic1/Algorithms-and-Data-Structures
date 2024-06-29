## Explanation of the Provided C++ Code

The provided C++ code implements a queue data structure using a singly linked list. The code includes a `Red` class template with various member functions to perform queue operations such as enqueue (stavi), dequeue (skini), and retrieve the front element (celo). The `main` function demonstrates the usage of this queue by enqueuing and dequeuing elements.

### `Red` Class Template
#### Private Members
- `struct Cvor`: A node structure that holds an element of the queue and a pointer to the next node.
- `Cvor* poc`: A pointer to the front node of the queue.
- `Cvor* kraj`: A pointer to the rear node of the queue.
- `int el`: A counter for the number of elements in the queue.

#### Public Members
- **Constructor**: Initializes an empty queue with `poc` and `kraj` set to `nullptr` and `el` set to 0.
- **Destructor**: Deletes all nodes in the queue to free memory.
- `int brojElemenata() const`: Returns the number of elements in the queue.
- **Copy Constructor**: Creates a deep copy of another queue.
- **Assignment Operator**: Assigns one queue to another, ensuring a deep copy.
- `void stavi(const tip &x)`: Enqueues a new element onto the queue.
- `tip skini()`: Dequeues the front element from the queue and returns it.
- `void brisi()`: Clears the queue by deleting all nodes.
- `void ispisi() const`: Prints all elements of the queue.
- `tip &celo()`: Returns the front element of the queue.

### `main` Function
- Demonstrates the usage of the `Red` class by performing the following steps:
  - Creates a queue `r` of integers.
  - Enqueues integers 1 to 5 onto the queue.
  - Tries to dequeue six elements from the queue, catching any exceptions thrown when attempting to dequeue from an empty queue and printing "Izuzetak".
