#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc,char *argv[])
{
 int n,i;
 double pi_est,x,y;
 int in_circle = 0;
 int local_in_circle,t;

 unsigned short xi[3];
 n = atoi(argv[1]);
 omp_set_num_threads(atoi(argv[2]));

 #pragma omp parallel private(i,xi,t,x,y,local_in_circle)
 {
 local_in_circle=0;
 xi[0]=atoi(argv[3]);
 xi[1]=atoi(argv[4]);
 xi[2]=omp_get_thread_num();
 t = omp_get_num_threads();
 for (i = xi[2]; i < n; i += t){
   x=erand48(xi);
   y=erand48(xi);
   if(x*x + y*y <= 1.0) local_in_circle++;
  }
 #pragma omp critical
   in_circle += local_in_circle;
 }
 printf("Estimate of pi: %7.5f\n",4.0*((double)in_circle/n));
 return 0;
}
