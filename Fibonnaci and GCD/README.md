## Explanation of the Provided C++ Code

The provided C++ code includes implementations of various mathematical functions: Fibonacci series (both recursive and iterative approaches), an optimized recursive Fibonacci function with tail recursion, and a function to compute the greatest common divisor (GCD). The `main` function demonstrates the usage of these functions by calling them with specific arguments and printing the results.

### Functions

#### `int fib(int n)`
- A recursive function to compute the nth Fibonacci number.
- **Parameters**: `int n` - The position in the Fibonacci sequence.
- **Returns**: The nth Fibonacci number.
- **Logic**:
  - If `n` is less than or equal to 1, it returns `n`.
  - Otherwise, it recursively calls itself to compute `fib(n-1) + fib(n-2)`.

#### `int fib_petlja(int n)`
- An iterative function to compute the nth Fibonacci number.
- **Parameters**: `int n` - The position in the Fibonacci sequence.
- **Returns**: The nth Fibonacci number.
- **Logic**:
  - If `n` is less than or equal to 1, it returns `n`.
  - Otherwise, it iteratively computes the Fibonacci series up to the nth number using a loop.

#### `int fib2_0(int n, int prvi=0, int drugi=1)`
- A tail-recursive function to compute the nth Fibonacci number with default parameters.
- **Parameters**: `int n` - The position in the Fibonacci sequence, `int prvi` - The first number in the sequence (default 0), `int drugi` - The second number in the sequence (default 1).
- **Returns**: The nth Fibonacci number.
- **Logic**:
  - If `n` is 0, it returns `prvi`.
  - If `n` is 1, it returns `drugi`.
  - Otherwise, it recursively calls itself with updated parameters to achieve tail recursion.

#### `int nzd(int prvi, int drugi)`
- A recursive function to compute the greatest common divisor (GCD) using the Euclidean algorithm.
- **Parameters**: `int prvi` - The first number, `int drugi` - The second number.
- **Returns**: The GCD of the two numbers.
- **Logic**:
  - If `drugi` is 0, it returns `prvi`.
  - Otherwise, it recursively calls itself with `drugi` and the remainder of `prvi % drugi`.

### `main` Function
- Demonstrates the usage of the functions by performing the following steps:
  - Computes and prints the GCD of 101 and 12.
  - Computes and prints the 20th Fibonacci number using the tail-recursive function.
  - Computes and prints the GCD of 6 and 561.
