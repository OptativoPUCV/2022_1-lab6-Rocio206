#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct
{
  int sudo[9][9];
} Node;

Node *createNode()
{
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n)
{
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name)
{
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n)
{
  int i, j;
  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n)
{
  print_node(n);
  int i, k;
  // filas
  int *num = (int *)calloc(10, sizeof(int));
  for (i = 0; i < 9; i++)
  {
    for (k = 0; k < 9; k++)
    {
      if (num[n->sudo[i][k]] != 0)
      {
        return 0;
      }

      if (num[n->sudo[i][k]] == 0 && n->sudo[i][k] != 0)
      {
        num[n->sudo[i][k]] = 1;
      }
    }
    num = (int *)calloc(10, sizeof(int));
  }
  // columnas
  for (i = 0; i < 9; i++)
  {
    num = (int *)calloc(10, sizeof(int));
    for (k = 0; k < 9; k++)
    {
      if (num[n->sudo[k][i]] != 0)
      {
        return 0;
      }
      if (num[n->sudo[k][i]] == 0 && n->sudo[k][i] != 0)
      {
        num[n->sudo[k][i]] = 1;
      }
    }
  }

  // submatriz
  /*int s_m = 1;
  while (s_m <= 9)
  {
    num = (int *)calloc(10, sizeof(int));
    for (p = 0; p < 8; p++)
    {
      i = 3 * (s_m / 3) + (p / 3);
      k = 3 * (s_m % 3) + (p % 3);
      if (num[n->sudo[i][k]] == 0 && n->sudo[i][k] != 0)
      {
        num[n->sudo[i][k]] = 1;
      }

      else
      {
        if (n->sudo[i][k] != 0)
        {
          return 0;
        }
      }

    }
  }*/
  return 1;
}

List *get_adj_nodes(Node *n)
{
  List *list = createList();
  int i = 0;
  int k = 0;
  int flag = 0;
  while (i < 9)
  {
    while (k < 9)
    {
      if (n->sudo[i][k] == 0)
      {
        flag = 1;
        break;
      }
      k++;
    }
    if (flag == 1)
      break;
    i++;
  }

  if (flag == 1)
  {
    int cont = 1;
    while (cont <= 9)
    {
      Node *new = copy(n);
      new->sudo[i][k] = cont;
      if (is_valid(new))
      {
        pushBack(list, new);
      }
      cont++;
    }
  }
  return list;
}

int is_final(Node *n)
{
  int i = 0;
  int k = 0;
  while (i < 9)
  {
    while (k < 9)
    {
      if (n->sudo[i][k] == 0)
      {
        return 0;
      }
      k++;
    }
  }
  return 1;
}

Node *DFS(Node *initial, int *cont)
{
  Stack *pila = createStack();
  push(pila, initial);
  while (get_size(pila) != 0)
  {
    Node *n = top(pila);
    pop(pila);
    if (is_final(n))
      return n;
    List *list = get_adj_nodes(n);
    Node *aux = first(list);
    while (aux != NULL)
    {
      push(pila, aux);
      aux = next(list);
    }
    free(n);
    cont++;
  }
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/