# laplacian
How direct methods suffer from round-off errors


## Objective
Given the laplacian matrix (that comes from discretizing the laplacian operator on a 1D uniform mesh) we solve increasingly bigger linear systems $Ax = b$ with the gaussian elimination method.
By solving with a known solution, we measure the norm of the residuals and the errors. The analysis of the error will be useful for real-world applications where the exact solution is unknown.


## Dependencies
 * C++ compiler (> C++11)
 * python + pandas + matplotlib for visualizing the results of the experiments
 * [google benchmark](https://github.com/google/benchmark) for comparing the performance of different methods


## Experiments

### `errors_and_residuals.cpp`
Solves the laplacian from a known solution (vector of ones), computes the norm of the residual and the norm of the error. Demonstrate how residuals norms are less useful to estimate the error when the matrix gets bigger (and more ill conditioned)

### `bad_residuals.cpp`
Solves the laplacian and computes the residual to estimate error. Compares two implementations of residual computation one of which is numerically unstable

### `solvers.cpp`
Compares the numerical error of different solvers, variations of:
 * [thomas algorithm](https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm)
 * multifrontal algorithm
the solvers can compute intermediate results using a better precision to reduce numerical errors (see section ..)

### `refinement.cpp`
Uses a tecnique called [iterative refinement](https://en.wikipedia.org/wiki/Iterative_refinement) for improving a solution from a direct method. Can potentially solve a system exactly to machine precision


## Benchmarks

### `multiprecision.cpp`
Compares the execution times of solvers computing intermediate results in higher precision

### `multifrontal.cpp`
Compares serial thomas algorithm and parallel multifrontal algorithm, the latter being twice as fast with two threads available

## Why I needed C++ features
The functions in src/ directory use C++ templates to define:
 * the precision of the input array
 * the precision of the intermediate results

such structure sacrifices efficiency in compilation for correctness of the implementations. Previoulsy multiple versions of the same algorithm had to be produced and kept up to date.


## Multiprecision
When eliminating rows in the laplacian matrix, the diagonal stores the iterates of the map f(x) = 2 - 1/x. Since the process is accumulating errors, is convenient to compute the iterates in double precisions, while storing intermediate results in single precision. This is the point of multiprecision: using fast and coarse arithmetic for converging to the solution, while computing accurate results only when necessary.


### Which architectures benefit from multiprecision
As january 2024 most gpu architecture favours lower precision computation because they provide more fp32 alus than fp64 ones. On modern cpus the difference between single and double precision is negligible at least for this specific application (see benchmarks).
