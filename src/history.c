#include <stdio.h>
#include <stdlib.h>
#include "history.h"

int str_len(char *str)
{
  char *sc;

  sc = str;
  while (*sc++);
  return sc - str;
}

Item *create_node(int id, char *str)
{
  char *scopy, c;
  int sindex;
  Item *node;

  node = (Item *) malloc(sizeof(Item));
  node->id = id;
  sindex = 0;
  scopy = (char *) malloc((str_len(str) + 1) * sizeof(char));
  do {
    c = *(scopy + sindex) = *(str + sindex);
    sindex++;
  } while (c);
  node->str = scopy;
  node->next = NULL;
  return node;
}

List *init_history()
{
  List *list = (List *) malloc(sizeof(List));
  list->root = NULL;
  return list;
}

void add_history(List *list, char *str)
{
  int id;

  id = 1;
  if (list->root) {
    Item *curr_node;

    id++;
    curr_node = list->root;
    while (curr_node->next) {
      curr_node = curr_node->next;
      id++;
    }
    curr_node->next = create_node(id, str);
  } else {
    list->root = create_node(id, str);
  }
}

char *get_history(List *list, int id)
{
  if (list->root) {
    Item *curr_node;

    curr_node = list->root;
    do {
      if (curr_node->id == id) {
	return curr_node->str;
      }
      curr_node = curr_node->next;
    } while (curr_node);
  }
  return NULL;
}

void print_history(List *list)
{
  if (list->root) {
    Item *curr_node;

    curr_node = list->root;
    do {
      printf("[%d]: %s", curr_node->id, curr_node->str);
      curr_node = curr_node->next;
    } while (curr_node);
  }
}

void free_history(List *list)
{
  if (list->root) {
    Item *curr_node, *temp;

    curr_node = list->root;
    do {
      temp = curr_node;
      curr_node = curr_node->next;
      free(temp->str);
      free(temp);
    } while (curr_node);
  }
  free(list);
}
