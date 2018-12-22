#include <cstdio>
#include <unistd.h>

int main()
{
    char hostname[100];
    int ncpus;

    gethostname(hostname, 100);
    ncpus = sysconf(_SC_NPROCESSORS_ONLN);

    printf("Hello World ! I am running on host %s with %d logical CPUs.\n", hostname, ncpus);

    return 0;
}

/*
Instructions for running on qsub : 
Put the file inside a folder called myproj, compile using : icpc -o hello.o hello.cc

Jobfile contents : 
#PBS -l walltime=0:01:00
#PBS -N hello
#PBS -l nodes=1
cd /home/<username>/myproj

cat $PBS_NODEFILE

./hello

# Remember to leave one line at the end

Then run : qsub jobfile
*/
