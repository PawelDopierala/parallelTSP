    /*
     gcc genkomb2.c -o genkomb2 -fopenmp
    */
    #include <stdio.h>
    #include <stdlib.h>
    #include <malloc.h>
    #include <omp.h>
     
    typedef struct REC {
        char v;
        struct REC * next0;
        struct REC * next1;
    } rec;
     
    // void drukuj (rec * x, int n) {
    //  char * buf = malloc(sizeof(char)*(n+1));
    //  buf[n]=0; while (x) {buf[--n]=x->v; x = x -> prev;}
    //  printf("%d: %s\n",omp_get_thread_num(),buf);
    //  free(buf);
    // }
     
    void genkomb(rec * x, int level, int n, int k) {
     rec X1,X2;
     if (level==n) {} 
     else 
      {
        #pragma omp task
        {
            x->next0 = &X1;
            X1.v = '0';
          if (n-level>k) genkomb(&X1,level+1,n,k);
        }
        #pragma omp task  
        {
            x->next1 = &X2;
            X2.v = '1';
         if (k>0) genkomb(&X2,level+1,n,k-1);
        }
        #pragma omp taskwait  
      }
    }
     
    int main(int argc, char * argv[]) {
     int n = 1;
     int k = 1;
     rec x;
     x.v = -1;
     if (argc > 1)  n = atoi(argv[1]);
     if (argc > 2)  k = atoi(argv[2]);
     #pragma omp parallel
     #pragma omp single
     genkomb(&x,0,n,k);

     return EXIT_SUCCESS;
    }
