//
// Created by sio2 on 8/20/22.
//

#ifndef CONTAINER_STACK_H
#define CONTAINER_STACK_H

#include "status.h"

#define STACK_INIT_SIZE 100
#define STACK_INCREASE_SIZE 10

struct stack;
typedef struct stack stack;

stack *stack_create(int elem_size);

status stack_clean(stack *_stack);

status stack_push(stack *_stack, void *elem);

status stack_pop(stack *_stack, void *popped_elem);

status stack_clear(stack *_stack);

status stack_length(stack *_stack, int *length);

#endif //CONTAINER_STACK_H
