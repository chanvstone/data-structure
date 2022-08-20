//
// Created by sio2 on 8/20/22.
//

#ifndef CONTAINER_QUEUE_H
#define CONTAINER_QUEUE_H

#include "status.h"

#define QUEUE_INIT_SIZE 100
#define QUEUE_INCREASE_SIZE 10

struct queue;
typedef struct queue queue;

queue *queue_create(int elem_size);

status queue_clean(queue *_queue);

status queue_enqueue(queue *_queue, void *elem);

status queue_dequeue(queue *_queue, void *elem);

status queue_clear(queue *_queue);

status queue_length(queue *_queue, int *length);

#endif //CONTAINER_QUEUE_H
