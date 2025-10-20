#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ERR -1

/* --- Declaración de ran1 --- */

#define IA 16807 /*Multiplicador de Park and Miller*/
#define IM 2147483647/* Primo 2^31 - 1 muy grande que será nuestro módulo y nos dará una secuencia de 2^31-2 números*/
#define AM (1.0/IM)/* Convierte el número generado a un flotante en [0,1)*/
#define IQ 127773 /* IM/IA lo utilizaremos para evitar overflow */
#define IR 2836 /* IM%IA utilizado para evitar overflow*/
#define NTAB 32 /* Tamaño de la tabla de shuffle Bays-Durham*/
#define NDIV (1+(IM-1)/NTAB)/* Factor para indexar la tabla de shuffle*/
#define EPS 1.2e-7 /* epsilon lo suficientemente pequeño*/
#define RNMX (1.0-EPS)/* evita que el generador devuelva exactamente 1*/


/***************************************************/
/* Function: random_num Date: 20/09/2025           */
/* Authors: Daniel Martínez                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/

/**
 * @brief Función privada que nos dará el número random entre 0 y 1
 * 
 * @param idum puntero a la seed
 * @return un decimal entr 0 y 1 sin incluir este ultimo
 */
float ran1(long *idum){
  int j; 
  long k; 
  static long iy=0;
  static long iv[NTAB];
  float temp;

  if (*idum <= 0 || !iy)
  {
    if (-(*idum) < 1) *idum = 1;
    else *idum = -(*idum);

    for (j = NTAB+7; j >= 0; j--) { 
        k = (*idum) / IQ; 
        *idum = IA * (*idum - k * IQ) - IR * k; 
        if (*idum < 0) *idum += IM; 
        if (j < NTAB) iv[j] = *idum; 
    }
    iy = iv[0]; 
  }
    /*Generación del numero aleatorio*/
    k = (*idum) / IQ;
    *idum = IA * (*idum - k * IQ) - IR * k;
    if (*idum < 0) *idum += IM; 
    j = iy / NDIV;
    iy = iv[j]; 
    iv[j] = *idum;

    if ((temp = AM * iy) > RNMX) return RNMX; else return temp; 
}
/* ran1 es la función generadora uniforme de -1.0 a 1.0 o 0 a 1.0 según la versión */
/* Si usas la de Numerical Recipes, debe estar implementada aparte, aquí la simulamos con rand(). */

/* --- Función random_num (la tuya) --- */
int random_num(int inf, int sup) {
    static long seed = 0;
    int rango;
    float randv;

    if (inf > sup) {
        fprintf(stderr, "El índice inferior no puede ser mayor que el superior.\n");
        return ERR;
    }
    if (seed == 0) {
        seed = -(long)time(NULL); /* Semilla inicial */
    }

    rango = sup - inf + 1;
    randv = ran1(&seed);

    return inf + (int)(randv * rango);
}

/* --- Programa principal para generar datos --- */
int main(void) {
    int i, n = 10000000;      /* número de muestras */
    int inf = -1, sup = -2;   /* intervalo del generador */
    FILE *fout = fopen("random_data.dat", "w");
    if (!fout) {
        perror("Error al abrir fichero");
        return 1;
    }

    for (i = 0; i < n; i++) {
        int x = random_num(inf, sup);
        fprintf(fout, "%d\n", x);
    }

    fclose(fout);
    printf("Datos generados en random_data.dat (%d muestras)\n", n);
    return 0;
}
