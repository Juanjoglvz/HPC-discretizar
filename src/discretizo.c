/*
  Autores:
    Javier Córdoba Romero
    Juan José Corroto martín

*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


//  CONSTANTS
#define L1 15
#define L2 25
#define L3 65



/*
* Procedure that displays the time (in milliseconds): pt1-pt0 together with the parameterized string: pText
*/
void time_track(char * pText, struct timeval *pt0, struct timeval *pt1){
    double tej;
    tej = (pt1->tv_sec - pt0->tv_sec) + (pt1->tv_usec - pt0->tv_usec) / 1e6;
    printf("%s = %10.3f\n",pText, tej*1000);
}

/*
*  Procedure that generates a random integer number in the range (bounds included)
*/
int random_int(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

/*
 * Procedure to show vectors
 */ 
void show_vector(int *V, long len) {
    int i;
    for (i=0; i<len; i++) {
        if(i%5==0) printf("\n");
        printf("%d ",V[i]);
    }
    printf("\n");
}

/*
 * Procedure to compare 2 vectors
 */ 

void compare_vectors(int *V, int *W, long len){
    int i;
    int res = 1;

    for (i = 0; i < len; i++){
        if (V[i] != W[i]){
            res = 0;
        }
    }

    printf("Los vectores son %s\n", res == 1 ? "iguales" : "diferentes");
}

/*
* MAIN PROGRAM
*/

int main (int argc, char* argv[]){
    long n;
    // Check for correct argument and save it
    if (argc != 2){
        fprintf(stderr, "Uso correcto: discretizo n\n Siendo n el tamaño del vector.\n\n");
        return 1;
    }
    else{
        n = atoi(argv[1]);
    }
    printf("Vector de %ld elementos\n", n);
    

    struct timeval t0, t1;
    gettimeofday(&t0, NULL);

    /*
    *  INITIALIZATION
    */
    srand(time(NULL));
    int* V = 0;
    V = malloc(n * sizeof(int));

    if (!V)
    {
        printf("Error reservando memoria para el vector\n");
        return 1;
    }
      
    int i;
    for(i = 0; i < n; i++){
        V[i] = random_int(0, 95);
    }

    /*
    *  DISCRETIZATION
    */

  
    int *result = 0;
    result = calloc(n, sizeof(int));

    #pragma omp parallel for shared(n, V, result) private(i) schedule(guided)
    for (i = 0; i < n; i++){
        if (V[i] >= L1 && V[i] < L2){
            result[i] = 1;
        }
        else if (V[i] >= L2 && V[i] < L3){
            result[i] = 2;
        }
        else if (V[i] >= L3){
            result[i] = 3;
        }
        
    }

    gettimeofday(&t1, NULL);
    time_track("Tiempo paralelo", &t0, &t1);

    show_vector(V, 10);
    show_vector(result, 10);


    /*
    *  SEQUENTIAL ALGORITHM
    *  Checking for correctness
    */

    int *result2 = 0;
    result2 = calloc(n, sizeof(int));
    for (i = 0; i < n; i++){
        if (V[i] >= L1 && V[i] < L2){
            result2[i] = 1;
        }
        else if (V[i] >= L2 && V[i] < L3){
            result2[i] = 2;
        }
        else if (V[i] >= L3){
            result2[i] = 3;
        }
        
    }

    compare_vectors(result, result2, n);

    return 0;
}
