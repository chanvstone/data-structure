#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "status.h"

struct linked_list_node
{
    void *data;
    struct linked_list_node *next_node, *prev_node;
};

typedef struct linked_list_node linked_list_node;

linked_list_node *linked_list_create_node(void *data, size_t data_length);
status linked_list_destroy(linked_list_node *ll);
status linked_list_traverse(linked_list_node *ll, status visit(void *data));

#endif // LINKED_LIST_H