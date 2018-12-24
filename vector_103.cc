#include <cmath>
#include <omp.h>

#pragma omp declare simd
double BlackBoxFunction(const double x){
    return double(1.0/sqrt(x));
}

double ComputeIntegral(const int n, const double a, const double b){

    const double dx = (b-a)/n;
    double I = 0.0;

#pragma omp simd reduction(+: I)
    for (int i=0; i<n; i++){
        const double xipl2 = a + dx*(double(i) + 0.5);
        const double yipl2 = BlackBoxFunction(xipl2);
        const double dI = yipl2 * dx;
        I += dI;
    }
    return I;
}

/*
 * Compilation flags : icpc -S vector_103.cc  -xMIC-AVX512 -qopt-report=5 -c -qopenmp -qopenmp
 *
 * The #pragma omp declare simd - directs the compilet to create 3 different versions of the function BlackBoxFunction
 * 1. Vectorized 
 * 2. Mased Vectorized
 * 3. Non Vectorized (scalar)
 *
 * And during the funciton call, a check happens to figure out which to use.
 * We can force it to use vectorized (but run the risk of bugs/race conditions.
 *
 * NOTE : if this BlackBoxFunction has a header file - that needs to have the #pragma as well
 *
 * Also, one important thing to note is that variable I has a dependency with itself, since several simd lanes have to update the same scalar.
 * So one way to think of this is that the value across all the variables I needs to be reduced after "I += dI"
 * This can be achieved by telling the compiler that variable I needs a reduction at the end (before actually storing in I
 *
 */
