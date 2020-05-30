/*
  Autores:
    Javier Córdoba Romero
    Juan José Corroto martín

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


//  CONSTANTS
#define L1 15
#define L2 25
#define L3 65

// VARIABLES
struct timeval t0, t1;
int n;
int result[4];


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
    // Check for correct argument and save it
    if (argc != 2){
        fprintf(stderr, "Uso correcto: discretizo n\n Siendo n el tamaño del vector.\n\n");
        return 1;
    }
    else{
        n = atoi(argv[1]);
    }
    printf("Vector de %d elementos\n", n);
    
    gettimeofday(&t0, NULL);

    /*
    *  INITIALIZATION
    */
    srand(time(NULL));
    printf("Hola\n");
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

  

    for (i = 0; i < n; i++){
        if (V[i] < L1){
            result[0]++;
        }
        else if (V[i] < L2)
        {
            result[1]++;
        }
        else if (V[i] < L3)
        {
            result[2]++;
        }
        else{
            result[3]++;
        }
        
        
    }

    gettimeofday(&t1, NULL);
    time_track("Tiempo secuencial", &t0, &t1);

    show_vector(result, 4);
    return 0;
}
