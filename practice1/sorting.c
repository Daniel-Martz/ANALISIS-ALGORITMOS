/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include <stdio.h>

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
  if (array == NULL)
  {
    return ERR;
  }

  int i, j, num = 0, aux;

  for (i = ip; i < iu; i++)
  {
    j = i - 1;

    if (array[i] > array[i + 1])
    {
      aux = array[i];
      array[i] = array[i + 1];
      array[i + 1] = aux;
      while ((j >= ip) && (array[j + 1] < array[j]))
      {
        aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
        j--;
        num++;
      }
    }
  }
  return num;
}

/***************************************************/
/* Function: SelectSort    Date: 25/09/2025        */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
  int flag = 1;
  int i = iu;
  int j = 0;
  int aux = 0;
  int OB = 0;

  if (!array || ip < 0 || iu <= ip)
  {
    return ERR;
  }
  while ((flag == 1) && (i > ip))
  {
    flag = 0;
    for (j = ip; j < i; j++)
    {
      if (array[j] > array[j + 1])
      {
        aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
        flag = 1;
      }
      OB++;
    }
    i--;
  }
  return OB;
}
