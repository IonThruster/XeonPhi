#include <cmath>

double MyFunction(int n)
{
    double A[n], B[n];
    // Language extension to C++ by Intel Compiler
    A[0:n] = B[0:n] = 1.0;

    for (int i=0; i<n; i++){
        // compiler should be able to fuse this to a FMA
        B[i] *= (double)i;
        A[i] += B[i];
    }   

    // Diverged/strided vector operation (not very efficient)
    for(int i=0; i<n/2; i++)
        A[i] += B[i*2];

    // Masked Vector operations
    for(int i=0; i<n; i++)
        if(i%3==0)
            A[i] += B[i];

    // Transcedental operation
    for(int i=0; i<n; i++)
        A[i] += exp(B[i]);
    
    // Not possible to vectorize due to dependency
    for(int i=0; i<n; i++)
        A[i] += A[i-1];

   // No dependency - should vectorize fine
   for(int i=0; i<n-1; i++)
        A[i] += A[i+1];

    return A[0];
}

/*
Compile code using : icpc -S vector_102.cc -qopt-report=5 -xMIC-AVX512

-S produces the assembly for the code (and does not require a main method
-qopt-report=5 produces a more verbose report file
-x<code> - compiles it for Xeon-Phi

Note : compiling with the -x option, make the compiler use Legacy SSE instructions which use the XMM registers.
*/
