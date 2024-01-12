# laplacian
How direct methods suffer from round-off errors


## Objective
Given the laplacian matrix (that comes from discretizing the laplacian operator on a 1D uniform mesh) we solve increasingly bigger linear systems $Ax = b$ with the (thomas)[] direct method.

By solving with a known solution, we measure the norm of the residuals and the errors. The analysis of the error, which also considers the working precision of the computation, will be useful for real-world applications where the exact solution is unknown.


## The Pandora's box of floating point computations
This simple computation has a major flaw: we are measuring the correctness of its result (that surely is affected with round-off errors) with another computation. This means that we have to be extra careful in every operation, to ensure that the result has only the representation error of the precision used (that may be impossible).


## State of repository
The functions in src/ directory use C++ templates to define:
 * the precision of the input array
 * the precision of the intermediate results

Such structure sacrifices efficiency in compilation for correctness of the implementations. Previoulsy multiple versions of the same algorithm had to be produced and kept maintained.


## Multiprecision
The work was naturally shaped into multiprecision algorithms. When eliminating rows in the laplacian matrix, the diagonal stores the iterates of the map f(x) = 2 - 1/x

Since the process is accumulating errors, is convenient to compute the iterates in double precisions, while storing intermediate results in single precision. This is an instance of multiprecision thinking: using fast and coarse arithmetic for converging to the solution of the problem, while computing accurate results only when necessary. The GPU architectures favours this approach because the reference floating point precision is fp32 and the fp64 arithmetic is very slow. On modern cpus there is not much cost difference in using floats over doubles, the benchmarks speak.


The reference commit where everything works, but now we are at an acceptable point
271afcaa5253ac6860edf46ddd1eb4cbd53e26a8
