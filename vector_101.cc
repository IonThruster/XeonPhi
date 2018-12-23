#include <cstdio>

int main(){
    const int n=1024;
    int A[n] __attribute__((aligned(64)));
    int B[n] __attribute__((aligned(64)));

    for (int i = 0; i < n; i++)
    A[i] = B[i] = i;

    // This loop will be auto-vectorized
    for (int i = 0; i < n; i++)
    A[i] = A[i] + B[i];

    for (int i = 0; i < n; i++)
    printf("%2d %2d %2d\n",i,A[i],B[i]);

    return 0;
}

/*
Compile instructions : 
> icpc -o vector_101 vector_101.cc -qopt-report

For running instruction :
See hello.cc file (need to use qsub)

Sample output from auto-vectorization report : Found in <filename>.optrpt
===================================
Begin optimization report for: main()

    Report from: Interprocedural optimizations [ipo]

INLINE REPORT: (main()) [1] vector_101.cc(3,11)


    Report from: Loop nest, Vector & Auto-parallelization optimizations [loop, vec, par]


LOOP BEGIN at vector_101.cc(8,5)
   remark #15300: LOOP WAS VECTORIZED
LOOP END

LOOP BEGIN at vector_101.cc(12,5)
   remark #15300: LOOP WAS VECTORIZED
LOOP END

LOOP BEGIN at vector_101.cc(15,5)
   remark #15344: loop was not vectorized: vector dependence prevents vectorization. First dependence is shown below. Use level 5 report for details
LOOP END
===================================

*/
