#include "linear_list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct list {
    void *data;
    int elem_size;
    int total_size;
    int used_size;
};

list *list_create(int size_of_element) {
    assert(size_of_element > 0);
    list *_list = malloc(sizeof(list));
    if (_list == NULL) {
        return NULL;
    }
    _list->data = malloc(size_of_element * LIST_INIT_SIZE);
    if (_list->data == NULL) {
        free(_list);
        return NULL;
    }
    _list->elem_size = size_of_element;
    _list->total_size = LIST_INIT_SIZE;
    _list->used_size = 0;
    return _list;
}

status list_clean(list *_list) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    free(_list->data);
    free(_list);
    return OK;
}

status list_expand_memory(list *_list, int size) {
    if (size <= _list->total_size) {
        return OK;
    }
    int new_size = _list->total_size;
    while (new_size < size) {
        new_size += LIST_INCREASE_SIZE;
    }
    void *new_data = realloc(_list->data, new_size * _list->elem_size);
    if (new_data == NULL) {
        return CAN_NOT_ALLOCATE_MEMORY;
    }
    _list->data = new_data;
    _list->total_size = new_size;
    return OK;
}

status list_insert_elem(list *_list, int pos, void *elem) {
    return list_insert_elems(_list, pos, elem, 1);
}

status list_insert_elems(list *_list, int pos, void *elems, int count) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    if (pos < 0 || pos > _list->used_size) {
        return INDEX_OUT_OF_RANGE;
    }
    const int new_used_size = _list->used_size + count;
    status return_code = list_expand_memory(_list, new_used_size);
    if (return_code != OK) {
        return return_code;
    }
    const int elem_size = _list->elem_size;
    for (int right_index = new_used_size - 1, left_index = _list->used_size - 1;
         left_index >= pos; right_index--, left_index--) {
        void *dest_ptr = _list->data + (right_index * elem_size);
        void *src_ptr = _list->data + (left_index * elem_size);
        memcpy(dest_ptr, src_ptr, elem_size);
    }
    memcpy(_list->data + (pos * elem_size), elems, count * elem_size);
    _list->used_size = new_used_size;
    return OK;
}

status list_insert_list(list *dest_list, int pos, list *src_list) {
    return list_insert_elems(dest_list, pos, src_list->data, src_list->used_size);
}

status list_insert_elem_back(list *_list, void *elem) {
    return list_insert_elem(_list, _list->used_size, elem);
}

status list_insert_elem_front(list *_list, void *elem) {
    return list_insert_elem(_list, 0, elem);
}

status list_delete_elem(list *_list, int pos, void *deleted_elem) {
    if (deleted_elem != NULL) {
        memcpy(deleted_elem, _list->data + (pos * _list->elem_size), _list->elem_size);
    }
    return list_delete_elems(_list, pos, 1, NULL);
}

status list_delete_elems(list *_list, int pos, int count, void *deleted_elems) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    if (pos < 0 || (pos + count) >= _list->used_size || count <= 0) {
        return INDEX_OUT_OF_RANGE;
    }
    const int elem_size = _list->elem_size;
    if (deleted_elems != NULL) {
        memcpy(deleted_elems, _list->data + (pos * elem_size), count * elem_size);
    }
    for (int left_index = pos, right_index = pos + count; right_index < _list->used_size; left_index++, right_index++) {
        void *dest_ptr = _list->data + (left_index * elem_size);
        void *src_ptr = _list->data + (right_index * elem_size);
        memcpy(dest_ptr, src_ptr, elem_size);
    }
    _list->used_size -= count;
    return OK;
}

status list_change_elem(list *_list, int pos, void *elem) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    if (pos < 0 || pos >= _list->used_size) {
        return INDEX_OUT_OF_RANGE;
    }
    memcpy(_list->data + (pos * _list->elem_size), elem, _list->elem_size);
    return OK;
}

status list_get_elem(const list *_list, int pos, void *elem) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    if (pos < 0 || pos >= _list->used_size) {
        return INDEX_OUT_OF_RANGE;
    }
    memcpy(elem, _list->data + (pos * _list->elem_size), _list->elem_size);
    return OK;
}

status list_length(const list *_list, int *length) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    *length = _list->used_size;
    return OK;
}

status list_clear(list *_list) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    _list->used_size = 0;
    return OK;
}

status list_traverse(list *_list, status (*visit)(void *)) {
    if (_list == NULL) {
        return UNINITIALIZED;
    }
    for (int i = 0; i < _list->used_size; i++) {
        status return_code = visit(_list->data + (i * _list->elem_size));
        if (return_code != OK) {
            return return_code;
        }
    }
    return OK;
}
