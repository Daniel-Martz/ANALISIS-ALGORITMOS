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
#include <stdio.h>
#include <stdlib.h> 
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


int random_num(int inf, int sup)
{
  static long seed = 0;
  int rango;
  float rand;

  if(inf>sup){
    fprintf(stderr, "El índice inferior no puede ser mayor que el superior.");
    return ERR;
  }
  if(seed == 0){
    seed = -(long)time(NULL); /*Va a ser la semilla inicial*/
  }
  rango = sup - inf + 1;
  rand = ran1(&seed);
  return inf + (int)(rand*rango);
}

/***************************************************/
/* Function: generate_perm Date: 22/09/2025        */
/* Authors: Daniel Martínez                        */
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
  int i, *perm,e_aux,i_aux;

  if(N <= 0){
    fprintf(stderr, "El tamaño de la permutacion no es valido");
    return NULL;
  }
  if(!(perm =(int*)calloc(N, sizeof(int)))){
    fprintf(stderr, "Problema reservando la memoria para la permutacion");
    return NULL;
  }
  for(i=1;i<=N;i++){
    perm[i-1] = i;
  }
  for(i=0;i<N;i++){
    e_aux = perm[i];
    i_aux = random_num(0,N-1); 
    perm[i] = perm[i_aux];
    perm[i_aux] = e_aux;
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors: Rodrigo Diaz                           */
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
  int **array_perm = NULL, i, j;

  if (n_perms <=0 || N<= 0)
  {
    fprintf(stderr, "Las variables introducidas no son válidas.");
    return NULL;
  }

  array_perm = (int**)calloc(n_perms,sizeof(int*)); 
  if (array_perm == NULL)
  {
    fprintf(stderr, "Error reservando la memoria para el array de permutaciones.");
    return NULL;
  }

  for (i=0; i<n_perms; i++)
  {
    array_perm[i]= generate_perm(N);

    if (array_perm[i]==NULL) 
    {
      for (j = 0; j < i; j++) 
      {
        free(array_perm[j]);
      }
    free(array_perm);
    return NULL;
    }
  }
  return array_perm;
}
