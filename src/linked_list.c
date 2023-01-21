#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

linked_list_node *linked_list_create_node(void *data, size_t data_length)
{
    linked_list_node *new_linked_list_node = malloc(sizeof(linked_list_node));
    if (new_linked_list_node == NULL)
    {
        return NULL;
    }
    new_linked_list_node->data = malloc(data_length);
    if (new_linked_list_node->data == NULL)
    {
        free(new_linked_list_node);
        return NULL;
    }
    new_linked_list_node->next_node = NULL;
    new_linked_list_node->prev_node = NULL;
    return new_linked_list_node;
}
status linked_list_destroy(linked_list_node *ll)
{
    while (ll != NULL)
    {
        linked_list_node *temp = ll;
        ll = ll->next_node;
        free(temp);
    }
    return OK;
}
status linked_list_traverse(linked_list_node *ll, status visit(void *data))
{
    while (ll != NULL)
    {
        status r_code = visit(ll->data);
        if (r_code != OK)
        {
            return r_code;
        }
        ll = ll->next_node;
    }
    return OK;
}