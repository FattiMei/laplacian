# laplacian
How direct methods suffer from round-off errors


## Objective
Given the laplacian matrix (that comes from discretizing the laplacian operator on a 1D uniform mesh) we solve increasingly bigger linear systems $Ax = b$ with the (thomas)[] direct method.

By solving with a known solution, we measure the norm of the residuals and the errors. The analysis of the error, which also considers the working precision of the computation, will be useful for real-world applications where the exact solution is unknown.


## The Pandora's box of floating point computations
This simple computation has a major flaw: we are measuring the correctness of its result (that surely is affected with round-off errors) with another computation. This means that we have to be extra careful in every operation, to ensure that the result has only the representation error of the precision used (that may be impossible).


## State of repository
I wanted to make the repository simple as possible, using the most basic language features of C. The repository now has an emergent behaviour that suggest the use of C++ templated functions, for example: the norm of a vector with given precision entries can be computed using an accumulator of another precision.

Another important instance of this concept of computing in two precisions is the thomas algorithm on the laplacian matrix, where the dynamic of the diagonal elimination can be computed in different precisions, yielding better precision with minimal additional computational cost.

From my understanding at 08/01/2024 the C++ templated functions must be declared where they are specialized. You can't declare a templated foo() in foo.cpp, compile it and link it to a main.cpp where there is specialization of foo()

The whole structure needs to accomodate this, probably having implementations declared in header files, and every user of such functions will have to include the header.

The reference commit where everything works
271afcaa5253ac6860edf46ddd1eb4cbd53e26a8
