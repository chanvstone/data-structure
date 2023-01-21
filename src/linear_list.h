#ifndef CONTAINER_LINEAR_LIST_H
#define CONTAINER_LINEAR_LIST_H

#include "status.h"

#define LIST_INIT_SIZE 100
#define LIST_INCREASE_SIZE 10

struct list;
typedef struct list list;

// create list
list *list_create(int size_of_element);

// clean list
status list_clean(list *_list);

// insert an element
status list_insert_elem(list *_list, int pos, void *elem);

// insert elements
status list_insert_elems(list *_list, int pos, void *elem, int count);

// insert a list
status list_insert_list(list *dest_list, int pos, list *src_list);

// insert an element to the back of the list
status list_insert_elem_back(list *_list, void *elem);

// insert an element to the front of the list
status list_insert_elem_front(list *_list, void *elem);

// delete an element of the list
status list_delete_elem(list *_list, int pos, void *deleted_elem);

// delete "count" elements begin at "pos" of the list
status list_delete_elems(list *_list, int pos, int count, void *deleted_elems);

status list_change_elem(list *_list, int pos, void *elem);

status list_get_elem(const list *_list, int pos, void *elem);

status list_length(const list *_list, int *length);

status list_clear(list *_list);

status list_traverse(list *_list, status (*visit)(void *elem));

#endif //CONTAINER_LINEAR_LIST_H
