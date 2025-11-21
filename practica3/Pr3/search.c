/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Daniel Martinez y Rodrigo Diaz-Reganon
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
    keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for (i = 0; i < n_keys; i++)
  {
    keys[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
  }

  return;
}

PDICT init_dictionary(int size, char order)
{
  int i;
  if (size <= 0)
  {
    return NULL;
  }
  PDICT dictionary = malloc(sizeof(DICT));
  if (dictionary == NULL)
  {
    fprintf(stderr, "Error en la creacion del diccionario.");
    return NULL;
  }

  dictionary->n_data = 0;
  dictionary->size = size;
  dictionary->order = order;

  dictionary->table = (int *)calloc(size, sizeof(int));
  if (dictionary->table == NULL)
  {
    fprintf(stderr, "Error en la creacion de la tabla del diccionario.");
    free(dictionary);
    return NULL;
  }

  for (i = 0; i < size; i++)
  {
    dictionary->table[i] = 0;
  }

  return dictionary;
}

void free_dictionary(PDICT pdict)
{
  if (pdict == NULL)
  {
    return;
  }
  free(pdict->table);
  free(pdict);
  return;
}

int insert_dictionary(PDICT pdict, int key)
{
  int aux;
  int j;
  int Ob = 0;

  if (!pdict || pdict->size <= 0 || pdict->n_data < 0 || pdict->n_data >= pdict->size || !pdict->table || (pdict->order != SORTED && pdict->order != NOT_SORTED))
  {
    fprintf(stderr, "Error en los parametros de entrada de insert_dictionary");
    return ERR;
  }
  pdict->table[pdict->n_data] = key;

  if (pdict->order == SORTED)
  {
    aux = pdict->table[pdict->n_data];
    j = pdict->n_data - 1;
    /* implementamos el pseudocodigo donde cada vez que se itera en el bucle se hace */
    while (j >= 0 && pdict->table[j] > aux){
      pdict->table[j + 1] = pdict->table[j];
      Ob++;
    }
    j--;
    pdict->table[j + 1] = aux;
  }
  pdict->n_data++;
  return Ob;
}

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys)
{
  int i;
  int Ob = 0;
  int aux;
  if (!pdict || pdict->size <= 0 || pdict->n_data < 0 || pdict->n_data >= pdict->size || !pdict->table || (pdict->order != SORTED && pdict->order != NOT_SORTED) || !keys || n_keys<=0 || n_keys>(pdict->size-pdict->n_data))
  {
    fprintf(stderr, "Error en los parametros de entrada de massive_insert_dictionary");
    return ERR;
  }
  /* Bucle de insercion*/
  for(i=0; i< n_keys; i++){
    if((aux=insert_dictionary(pdict, keys[i])) == ERR) return ERR;
    Ob += aux;
  }
  return Ob; 
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  if (pdict == NULL || ppos == NULL || method == NULL)
  {
    return ERR;
  }
  return method(pdict->table, 0, pdict->n_data - 1, key, ppos);
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos)
{
  if(!table)
  int OB = 0;
  int i;  
  if (table == NULL || F > L || ppos == NULL)
  {
    return NOT_FOUND; 
  }

  while (F <= L) 
  {
    /* Calculamos el punto medio en cada iteración */
    i = (F + L) / 2;
    OB++;
    /* Comparamos */
    if (table[i] == key)
    {
      *ppos = i; 
      return OB; 
    }

    /* Ajustamos los límites */
    if (key < table[i])
    {
      L = i - 1; 
    }
    else
    {
      F = i + 1;
    }
  }
  return NOT_FOUND;
}

int lin_search(int *table, int F, int L, int key, int *ppos)
{
  int OB = 0, i;
  if ((table == NULL) || (F > L) || (ppos == NULL))
  {
    return NOT_FOUND;
  }

  i = F;
  while (i <= L)
  {
    OB++;
    if (key == table[i])
    {
      *ppos = i;
      return OB;
    }
    i++;
  }
  return NOT_FOUND;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
  int i, OB = 0, aux; 
  if(table == NULL || F>L || ppos == NULL)
  {
    return NOT_FOUND; 
  }

  i = F;
  if (table[i]==key)
  {
    OB++;
    ppos = i;
    return OB;
  }
  i++; 
  while (i <= L)
  {
    OB++;
    if (key == table[i])
    {
      *ppos = i;
      tabla[i]=aux;

      return OB;
    }
    i++;
  }
  return NOT_FOUND;
  
}
