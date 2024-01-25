# laplacian
How direct methods suffer from round-off errors


## Objective
Given the laplacian matrix (that comes from discretizing the laplacian operator on a 1D uniform mesh) we solve increasingly bigger linear systems $Ax = b$ with the gaussian elimination method.
By solving with a known solution, we measure the norm of the residuals and the errors. The analysis of the error will be useful for real-world applications where the exact solution is unknown.


## Dependencies
 * C++ compiler (> C++11)
 * python + pandas + matplotlib for visualizing the results of the experiments
 * (google benchmark)[https://github.com/google/benchmark] for comparing the performance of different methods


## Experiments

### errors_and_residuals
Solves the laplacian from a known solution (vector of ones), computes the norm of the residual and the norm of the error. Demonstrate how residuals norms are less useful to estimate the error when the matrix gets bigger (and more ill conditioned)


## Why I needed C++ features
The functions in src/ directory use C++ templates to define:
 * the precision of the input array
 * the precision of the intermediate results

such structure sacrifices efficiency in compilation for correctness of the implementations. Previoulsy multiple versions of the same algorithm had to be produced and kept up to date.


## Multiprecision
The work was naturally shaped into multiprecision algorithms. When eliminating rows in the laplacian matrix, the diagonal stores the iterates of the map f(x) = 2 - 1/x

Since the process is accumulating errors, is convenient to compute the iterates in double precisions, while storing intermediate results in single precision. This is an instance of multiprecision thinking: using fast and coarse arithmetic for converging to the solution of the problem, while computing accurate results only when necessary. The GPU architectures favours this approach because the reference floating point precision is fp32 and the fp64 arithmetic is very slow. On modern cpus there is not much cost difference in using floats over doubles, the benchmarks speak.
