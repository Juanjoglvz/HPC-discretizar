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
 * procedure to show vectors
 */ 
void show_vector(int *V, int len) {
    int i;
    for (i=0; i<len; i++) {
        if(i%5==0) printf("\n");
        printf("%d ",V[i]);
    }
    printf("\n");
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
        n = atol(argv[1]);
    }
    
    // Set number of threads to be the same as the mapping
    omp_set_num_threads(4);

    
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
    int bounds[5] = {0, 15, 25, 65, 96};

    /*
    *  DISCRETIZATION
    */

    int result[4];
    #pragma omp parallel for shared(V, n) private(i) reduction(+:result[:4])
    for (i = 0; i < 4; i++){
        int j;
        for (j = 0; j < n; j++){
            if (V[j] >= bounds[i] && V[j] < bounds[i+1]){
                result[i]++;
            }
        }
        
    }

    gettimeofday(&t1, NULL);
    time_track("Tiempo secuencial", &t0, &t1);
    show_vector(result, 4);
    return 0;
}
