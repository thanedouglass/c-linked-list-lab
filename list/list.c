// list/list.c
// 
// Implementation for linked list.
//
// <Thane Douglass>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* Allocates a new list structure on the heap and initializes it. */
list_t *list_alloc() { 
  list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
  if (mylist != NULL) {
    mylist->head = NULL;
  }
  return mylist;
}

/* Frees all dynamically allocated nodes in the list and the list itself. */
void list_free(list_t *l) {
  if (l == NULL) {
    return;
  }
  node_t *curr = l->head;
  while (curr != NULL) {
    node_t *next = curr->next;
    free(curr);
    curr = next;
  }
  free(l);
}

/* Prints the elements of the list to standard output. */
void list_print(list_t *l) {
  if (l == NULL) {
    printf("NULL\n");
    return;
  }
  node_t *curr = l->head;
  while (curr != NULL) {
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

/* Converts the linked list into a heap-allocated string representation. */
char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  if (buf == NULL) {
    return NULL;
  }
  buf[0] = '\0';
  char tbuf[20];

  if (l != NULL) {
    node_t* curr = l->head;
    while (curr != NULL) {
      sprintf(tbuf, "%d->", curr->value);
      strcat(buf, tbuf);
      curr = curr->next;
    }
  }
  strcat(buf, "NULL");
  return buf;
}

/* Returns the number of elements in the list. */
int list_length(list_t *l) {
  if (l == NULL) {
    return 0;
  }
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
}

/* Helper function: allocates a new node on the heap with the given value. */
node_t * getNode(elem value) {
  node_t *mynode = (node_t *) malloc(sizeof(node_t));
  if (mynode == NULL) {
    return NULL;
  }
  mynode->value = value;
  mynode->next = NULL;
  return mynode;
}

/* Inserts a new element at the front of the list. */
void list_add_to_front(list_t *l, elem value) {
  if (l == NULL) {
    return;
  }
  node_t *cur_node = getNode(value);
  if (cur_node == NULL) {
    return;
  }
  cur_node->next = l->head;
  l->head = cur_node;
}

/* Inserts a new element at the end of the list. */
void list_add_to_back(list_t *l, elem value) {
  if (l == NULL) {
    return;
  }
  node_t *cur_node = getNode(value);
  if (cur_node == NULL) {
    return;
  }
  if (l->head == NULL) {
    l->head = cur_node;
    return;
  }
  node_t *curr = l->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = cur_node;
}

/* Inserts a new element at the specified 0-based index. */
void list_add_at_index(list_t *l, elem value, int index) {
  if (l == NULL || index < 0) {
    return;
  }
  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }
  node_t *curr = l->head;
  for (int i = 0; curr != NULL && i < index - 1; i++) {
    curr = curr->next;
  }
  if (curr == NULL) {
    return; // Out of bounds
  }
  node_t *new_node = getNode(value);
  if (new_node == NULL) {
    return;
  }
  new_node->next = curr->next;
  curr->next = new_node;
}

/* Removes and returns the element from the front of the list. Returns -1 if empty. */
elem list_remove_from_front(list_t *l) {
  if (l == NULL || l->head == NULL) {
    return -1;
  }
  node_t *to_remove = l->head;
  elem val = to_remove->value;
  l->head = to_remove->next;
  free(to_remove);
  return val;
}

/* Removes and returns the element from the back of the list. Returns -1 if empty. */
elem list_remove_from_back(list_t *l) {
  if (l == NULL || l->head == NULL) {
    return -1;
  }
  if (l->head->next == NULL) {
    elem val = l->head->value;
    free(l->head);
    l->head = NULL;
    return val;
  }
  node_t *curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  elem val = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return val;
}

/* Removes and returns the element at the specified 0-based index. Returns -1 if invalid. */
elem list_remove_at_index(list_t *l, int index) {
  if (l == NULL || l->head == NULL || index < 0) {
    return -1;
  }
  if (index == 0) {
    return list_remove_from_front(l);
  }
  node_t *curr = l->head;
  for (int i = 0; curr != NULL && i < index - 1; i++) {
    curr = curr->next;
  }
  if (curr == NULL || curr->next == NULL) {
    return -1; // Out of bounds
  }
  node_t *to_remove = curr->next;
  elem val = to_remove->value;
  curr->next = to_remove->next;
  free(to_remove);
  return val;
}

/* Checks if an element exists in the list. */
bool list_is_in(list_t *l, elem value) {
  if (l == NULL) {
    return false;
  }
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) {
      return true;
    }
    curr = curr->next;
  }
  return false;
}

/* Returns the element at the specified 0-based index. Returns -1 if invalid. */
elem list_get_elem_at(list_t *l, int index) {
  if (l == NULL || index < 0) {
    return -1;
  }
  node_t *curr = l->head;
  for (int i = 0; curr !=### 1. Memory Allocation: Stack vs. Heap

* **Heap Allocated (`malloc` / `free`)**:
  * **List struct (`list_t`)**: Allocated via `malloc` inside `list_alloc()`. The list container must persist across function calls and beyond the stack frame where it was instantiated.
  * **Nodes (`node_t`)**: Allocated via `malloc` inside `getNode()`. Each node must persist independently as items are inserted, traversed, or removed.
  * **String buffer (`listToString`)**: Allocated on the heap so the returned `char *` pointer remains valid after the function exits.
* **Stack Allocated**:
  * **Pointers and Primitives**: Local variables (`node_t *curr`, `list_t *mylist`, `int count`, `elem val`) and function arguments (`list_t *l`, `elem value`, `int index`) reside on the stack. They are automatically reclaimed when their respective functions return.
  * **Local Buffers**: `char tbuf[20]` in `listToString` only needs to exist during the execution of that specific call.

---

### 2. Header File (`list.h`)

```c
#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int elem;

struct node {
  elem value;
  struct node *next;
};
typedef struct node node_t;

struct list {
  node_t *head;
};
typedef struct list list_t;

list_t *list_alloc();
void list_free(list_t *l);
void list_print(list_t *l);
char *listToString(list_t *l);
int list_length(list_t *l);

node_t *getNode(elem value);
void list_add_to_front(list_t *l, elem value);
void list_add_to_back(list_t *l, elem value);
void list_add_at_index(list_t *l, elem value, int index);

elem list_remove_from_front(list_t *l);
elem list_remove_from_back(list_t *l);
elem list_remove_at_index(list_t *l, int index);

bool list_is_in(list_t *l, elem value);
elem list_get_elem_at(list_t *l, int index);
int list_get_index_of(list_t *l, elem value);

#endif // LIST_H