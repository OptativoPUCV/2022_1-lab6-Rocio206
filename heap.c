#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo
{
   void *data;
   int priority;
} heapElem;

typedef struct Heap
{
   heapElem *heapArray;
   int size;
   int capac;
} Heap;

void *heap_top(Heap *pq)
{
   if (pq->size == 0)
      return NULL;
   return pq->heapArray->data;
}

void heap_push(Heap *pq, void *data, int priority)
{
   printf("prioridad del dato: %d\n", priority);
   if (pq->capac == pq->size)
   {
      pq->heapArray = (heapElem *)realloc(pq->heapArray, pq->capac * 2 + 1);
      pq->capac = pq->capac * 2 + 1;
   }

   pq->heapArray[pq->size].data = data;
   pq->heapArray[pq->size].priority = priority;
   pq->size += 1;

   int pos_np = (pq->size - 2) / 2;
   int pos_nh = pq->size - 1;
   while (pq->heapArray[pos_np].priority < pq->heapArray[pos_nh].priority)
   {
      heapElem aux1 = pq->heapArray[pos_np]; // padre
      heapElem aux2 = pq->heapArray[pos_nh]; // hijo
      pq->heapArray[pos_np] = aux2;          // intercanbio
      pq->heapArray[pos_nh] = aux1;

      pos_nh = pos_np;
      if (pos_nh < 1)
         break;
      pos_np = (pos_nh - 1) / 2;
   }
}

void heap_pop(Heap *pq) // elimina la raiz
{
   pq->heapArray[0] = pq->heapArray[pq->size - 1];
   pq->heapArray[pq->size - 1].data = NULL;
   pq->heapArray[pq->size - 1].priority = 0;
   pq->size -= 1;

   int pos_np = 0;
   int pos_nh = pos_np * 2;
   while (pq->heapArray[pos_np].priority < pq->heapArray[pos_nh + 1].priority || pq->heapArray[pos_np].priority < pq->heapArray[pos_nh + 2].priority)
   {
      if (pq->heapArray[pos_nh + 1].priority > pq->heapArray[pos_nh + 2].priority)
      {
         heapElem aux1 = pq->heapArray[pos_np];     // padre
         heapElem aux2 = pq->heapArray[pos_nh + 1]; // hijo
         pq->heapArray[pos_np] = aux2;              // intercanbio
         pq->heapArray[pos_nh + 1] = aux1;
         pos_np = pos_nh + 1;
         pos_nh = pos_np * 2;
      }
      else
      {
         heapElem aux1 = pq->heapArray[pos_np];     // padre
         heapElem aux2 = pq->heapArray[pos_nh + 2]; // hijo
         pq->heapArray[pos_np] = aux2;              // intercanbio
         pq->heapArray[pos_nh + 2] = aux1;
         pos_np = pos_nh + 2;
         pos_nh = pos_np * 2;
      }
   }
}

Heap *createHeap()
{
   Heap *new = (Heap *)malloc(sizeof(Heap));
   new->heapArray = (heapElem *)malloc(sizeof(heapElem) * 3);
   new->size = 0;
   new->capac = 3;

   return new;
}
