/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <time.h>
/*CONSTANTES PARA LA FUNCION QUE GENERA RANDOM NUMBERS*/
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
/* Function: random_num Date:                      */
/* Authors:                                        */
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
  int j; /*indice para la tabla shuffle*/
  long k; /* Variable auxiliar para el overflow*/
  static long iy=0; /*Numero previamente generado devuelto desde la tabla shuffle*/
  static long iv[NTAB];/* tabla shuffle*/
  float temp;/*Numero aleatorio que devolveremos*/

  if (*idum <= 0 || !iy)/* se inicializa si la semilla es negativa o si iy aún no se ha definido*/
  {
    if (-(*idum) < 1) *idum = 1;  /* Aseguramos que la semilla sea positiva y distinta de cero*/
    else *idum = -(*idum);

    for (j = NTAB+7; j >= 0; j--) { /* Se hace un calentamiento (8 iteraciones) y se llena la tabla*/
        k = (*idum) / IQ; /* Hacemos la semila más pequeña para que al multiplicarla por IA no nos de problemas de overflow*/
        *idum = IA * (*idum - k * IQ) - IR * k; /*Hemos conseguido aplicar LCG pero usando dos multiplicaciones para evitar overflow en vez de hacer una multiplicacion muy grande*/
        if (*idum < 0) *idum += IM; /* Hacemos que el número esté entre 0 y IM -1 si no lo está*/
        if (j < NTAB) iv[j] = *idum; /* Empezamos a llenar la tabla después de hacer el calentamiento*/
    }
    iy = iv[0]; /* Tomamos el primer valor de la tabla*/
  }
    /*Generación del numero aleatorio*/
    k = (*idum) / IQ;
    *idum = IA * (*idum - k * IQ) - IR * k; /* Hacemos LCG como antes evitando overflow*/
    if (*idum < 0) *idum += IM; /* Hacemos que el número esté entre 0 y IM -1 si no lo está*/
    j = iy / NDIV; /* Convierte el valor iy a un índice entro 0 y NTAB-1 (un índice aleatorio)*/
    iy = iv[j]; /* Obtenemos la nueva semilla para el próximo número*/
    iv[j] = *idum; /* Se actualiza la nueva semilla con la antes generada*/

    if ((temp = AM * iy) > RNMX) return RNMX; else return temp; /* Hacemos la transformación a un número en [0,1) comprobando que no sea 1*/

}


int random_num(int inf, int sup)
{
  static long seed = 0;
  int rango;
  float rand;

  if(seed == 0){
    seed = -(long)time(NULL); /*Va a ser la semilla inicial*/
  }
  rango = sup - inf + 1;
  rand = ran1(&seed);
  return inf + (int)(rand*rango);
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  /* your code */
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
/* your code */
}
