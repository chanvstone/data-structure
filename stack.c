//
// Created by sio2 on 8/20/22.
//

#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct stack {
    void *data;
    int top;
    int elem_size;
    int total_size;
};

status stack_expand_memory(stack *_stack, int target_size) {
    if (_stack == NULL) {
        return UNINITIALIZED;
    }
    if (_stack->total_size >= target_size) {
        return OK;
    }
    int new_total_size = _stack->total_size;
    while (new_total_size < target_size) {
        new_total_size += STACK_INCREASE_SIZE;
    }
    void *new_data = realloc(_stack->data, new_total_size * _stack->elem_size);
    if (new_data == NULL) {
        return CAN_NOT_ALLOCATE_MEMORY;
    }
    _stack->data = new_data;
    _stack->total_size = new_total_size;
    return OK;
}

stack *stack_create(int elem_size) {
    assert(elem_size > 0);
    stack *_stack = malloc(sizeof(stack));
    if (_stack == NULL) {
        return NULL;
    }
    _stack->data = malloc(elem_size * STACK_INIT_SIZE);
    if (_stack->data == NULL) {
        free(_stack);
        return NULL;
    }
    _stack->top = 0;
    _stack->elem_size = elem_size;
    _stack->total_size = STACK_INIT_SIZE;
    return _stack;
}

status stack_clean(stack *_stack) {
    if (_stack == NULL) {
        return UNINITIALIZED;
    }
    free(_stack->data);
    free(_stack);
    return OK;
}

status stack_push(stack *_stack, void *elem) {
    if (_stack == NULL) {
        return UNINITIALIZED;
    }
    status return_code = stack_expand_memory(_stack, _stack->top + 1);
    if (return_code != OK) {
        return return_code;
    }
    memcpy(_stack->data + (_stack->elem_size * _stack->top), elem, _stack->elem_size);
    _stack->top += 1;
    return OK;
}

status stack_pop(stack *_stack, void *popped_elem) {
    if (_stack == NULL) {
        return UNINITIALIZED;
    }
    if (_stack->top <= 0) {
        return INDEX_OUT_OF_RANGE;
    }
    _stack->top -= 1;
    if (popped_elem != NULL) {
        memcpy(popped_elem, _stack->data + (_stack->elem_size * _stack->top), _stack->elem_size);
    }
    return OK;
}

status stack_clear(stack *_stack) {
    if (_stack == NULL) {
        return UNINITIALIZED;
    }
    _stack->top = 0;
    return OK;
}

status stack_length(stack *_stack, int *length) {
    if (_stack == NULL) {
        return UNINITIALIZED;
    }
    *length = _stack->top;
    return OK;
}
