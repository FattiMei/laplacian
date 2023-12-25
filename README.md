# laplacian
How direct methods suffer from round-off errors


## Objective
Given the laplacian matrix (that comes from discretizing the laplacian operator on a 1D uniform mesh) we solve increasingly bigger linear systems $Ax = b$ with the (thomas)[] direct method.

By solving with a known solution, we measure the norm of the residuals and the errors. The analysis of the error, which also considers the working precision of the computation, will be useful for real-world applications where the exact solution is unknown.


## The Pandora's box of floating point computations
This simple computation has a major flaw: we are measuring the correctness of its result (that surely is affected with round-off errors) with another computation. This means that we have to be extra careful in every operation, to ensure that the result has only the representation error of the precision used (that may be impossible).
