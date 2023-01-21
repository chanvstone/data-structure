//
// Created by sio2 on 8/20/22.
//

#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define IS_INITIALIZED(QUEUE) if((QUEUE)==NULL){return UNINITIALIZED;}

struct queue {
    void *data;
    int front, back;
    int elem_size;
    int total_size;
};

status queue_expand_memory(queue *_queue, int target_size) {
    IS_INITIALIZED(_queue);
    if (_queue->back < _queue->total_size) {
        return OK;
    }
    int _queue_length;
    queue_length(_queue, &_queue_length);
    if (_queue_length < _queue->total_size) {
        memcpy(_queue->data, _queue->data + (_queue->front * _queue->elem_size), _queue_length * _queue->elem_size);
        _queue->front = 0;
        _queue->back = _queue_length;
    } else {
        int new_total_size = _queue->total_size;
        while (new_total_size < target_size) {
            new_total_size += QUEUE_INCREASE_SIZE;
        }
        void *new_data = malloc(new_total_size * _queue->elem_size);
        if (new_data == NULL) {
            return CAN_NOT_ALLOCATE_MEMORY;
        }
        memcpy(new_data, _queue->data + (_queue->front * _queue->elem_size), _queue_length * _queue->elem_size);
        free(_queue->data);
        _queue->data = new_data;
        _queue->front = 0;
        _queue->back = _queue_length;
        _queue->total_size = new_total_size;
    }
    return OK;
}

queue *queue_create(int elem_size) {
    assert(elem_size > 0);
    queue *_queue = malloc(sizeof(queue));
    if (_queue == NULL) {
        return NULL;
    }
    _queue->data = malloc(elem_size * QUEUE_INIT_SIZE);
    if (_queue->data == NULL) {
        free(_queue);
        return NULL;
    }
    _queue->elem_size = elem_size;
    _queue->total_size = QUEUE_INIT_SIZE;
    _queue->front = 0;
    _queue->back = 0;
    return _queue;
}

status queue_clean(queue *_queue) {
    IS_INITIALIZED(_queue);
    free(_queue->data);
    free(_queue);
    return OK;
}

status queue_enqueue(queue *_queue, void *elem) {
    IS_INITIALIZED(_queue);
    int queue_len;
    queue_length(_queue, &queue_len);
    status return_code = queue_expand_memory(_queue, queue_len + 1);
    if (return_code != OK) {
        return return_code;
    }
    memcpy(_queue->data + (_queue->back * _queue->elem_size), elem, _queue->elem_size);
    _queue->back += 1;
    return OK;
}

status queue_dequeue(queue *_queue, void *elem) {
    IS_INITIALIZED(_queue);
    if (_queue->front >= _queue->back) {
        return INDEX_OUT_OF_RANGE;
    }
    if (elem != NULL) {
        memcpy(elem, _queue->data + (_queue->front * _queue->elem_size), _queue->elem_size);
    }
    _queue->front += 1;
    return OK;
}

status queue_clear(queue *_queue) {
    IS_INITIALIZED(_queue);
    _queue->front = _queue->back = 0;
    return OK;
}

status queue_length(queue *_queue, int *length) {
    IS_INITIALIZED(_queue);
    *length = _queue->back - _queue->front;
    return OK;
}

