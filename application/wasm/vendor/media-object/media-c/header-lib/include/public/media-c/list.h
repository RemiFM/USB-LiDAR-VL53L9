/**
 ******************************************************************************
 * @file    list.h
 * @author  IMD Software Team
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifndef MEDIA_C_LIST_H_
#define MEDIA_C_LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "value.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file list.h
 * @brief Generic dynamic array (list) container.
 *
 * Provides the @c list_t dynamic array type together with creation,
 * manipulation, iteration and validation helpers. Several higher-level
 * collection types (@c streams_t, @c controls_t, @c properties_t, etc.)
 * are defined as type aliases of @c list_t.
 */

/** @brief Generic dynamic array of fixed-size items. */
typedef struct {
    void* items;      /**< Pointer to the contiguous item storage. */
    size_t size;      /**< Current number of items in the list. */
    size_t capacity;  /**< Maximum number of items before reallocation. */
    size_t item_size; /**< Size in bytes of a single item. */
} list_t;

/**
 * @brief Allocate a new list.
 *
 * @param[in] initial_capacity  Number of items to pre-allocate.
 * @param[in] item_size         Size in bytes of a single item.
 * @return Pointer to the newly created list, or @c NULL on allocation failure.
 */
static inline list_t* list_new(size_t initial_capacity, size_t item_size) {
    list_t* list = (list_t*)malloc(sizeof(list_t));
    if (list != NULL) {
        list->items = malloc(initial_capacity * item_size);
        if (list->items == NULL) {
            free(list);
            list = NULL;
        } else {
            list->size = 0;
            list->capacity = initial_capacity;
            list->item_size = item_size;
        }
    }
    return list;
}

/**
 * @brief Remove all items from the list, optionally freeing each one.
 *
 * @param[in,out] list       Pointer to the list.
 * @param[in]     free_func  Per-item destructor (may be @c NULL).
 */
static inline void list_clear(list_t* list, void (*free_func)(void*)) {
    if ((list != NULL) && (free_func != NULL)) {
        char* base = (char*)list->items; /* cppcheck-suppress misra-c2012-11.5 ; byte-level access to void* buffer */
        for (size_t i = 0; i < list->size; ++i) {
            free_func(&base[i * list->item_size]);
        }
        list->size = 0;
    }
}

/**
 * @brief Free the list and all of its items.
 *
 * @param[in] list       Pointer to the list to free.
 * @param[in] free_func  Per-item destructor (may be @c NULL).
 */
static inline void list_free(list_t* list, void (*free_func)(void*)) {
    if (list != NULL) {
        list_clear(list, free_func);
        free(list->items);
        free(list);
    }
}

/**
 * @brief Append an item to the list, growing it if necessary.
 *
 * @param[in,out] list  Pointer to the list.
 * @param[in]     item  Pointer to the item to copy into the list.
 * @return @c true on success, @c false if reallocation failed.
 */
static inline bool list_add(list_t* list, void* item) {
    bool result = true;
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2U;
        void* new_items = realloc(list->items, new_capacity * list->item_size);
        if (new_items == NULL) {
            result = false;
        } else {
            list->items = new_items;
            list->capacity = new_capacity;
        }
    }
    if (result) {
        (void)memcpy(&((char*)list->items)[list->size * list->item_size], item, list->item_size);
        list->size++;
    }
    return result;
}

/**
 * @brief Access an item by index.
 *
 * @param[in] list   Pointer to the list.
 * @param[in] index  Zero-based index of the item.
 * @return Pointer to the item storage, or @c NULL if @p index is out of range.
 */
static inline void* list_get(const list_t* list, size_t index) {
    void* result = NULL;
    if (index < list->size) {
        result = &((char*)list->items)[index * list->item_size];
    }
    return result;
}

/**
 * @brief Overwrite an item at the given index.
 *
 * @param[in] list   Pointer to the list.
 * @param[in] index  Zero-based index of the item to overwrite.
 * @param[in] item   Pointer to the new item data.
 * @return @c true on success, @c false if @p index is out of range.
 */
static inline bool list_set(const list_t* list, size_t index, void* item) {
    bool result = false;
    if (index < list->size) {
        (void)memcpy(&((char*)list->items)[index * list->item_size], item, list->item_size);
        result = true;
    }
    return result;
}

/**
 * @brief Remove an item at the given index, shifting subsequent items.
 *
 * @param[in,out] list       Pointer to the list.
 * @param[in]     index      Zero-based index of the item to remove.
 * @param[in]     free_func  Per-item destructor (may be @c NULL).
 * @return @c true on success, @c false if @p index is out of range.
 */
static inline bool list_remove(list_t* list, size_t index, void (*free_func)(void*)) {
    bool result = false;
    if (index < list->size) {
        if (free_func != NULL) {
            free_func(&((char*)list->items)[index * list->item_size]);
        }
        for (size_t i = index; i < (list->size - 1U); ++i) {
            (void)memcpy(&((char*)list->items)[i * list->item_size], &((char*)list->items)[(i + 1U) * list->item_size],
                         list->item_size);
        }
        list->size--;
        result = true;
    }
    return result;
}

/**
 * @brief Return the current number of items.
 *
 * @param[in] list  Pointer to the list.
 * @return Current item count.
 */
static inline size_t list_size(const list_t* list) { return list->size; }

/**
 * @brief Return the allocated capacity.
 *
 * @param[in] list  Pointer to the list.
 * @return Maximum number of items before the next reallocation.
 */
static inline size_t list_capacity(const list_t* list) { return list->capacity; }

/**
 * @brief Validate a list_t instance for basic integrity.
 *
 * This function checks that the list pointer is not NULL, the items pointer is not NULL,
 * the item size matches the expected type, the capacity is not zero, and the size does not exceed the capacity.
 * If @p must_be_non_empty is true, the list must also not be empty.
 *
 * @param list Pointer to the list_t instance.
 * @param expected_item_size The expected size of each item (e.g., sizeof(stream_t)).
 * @param must_be_non_empty If true, the list must not be empty; if false, empty lists are allowed.
 * @return MEDIA_ERROR_NONE if valid, or an appropriate MEDIA_ERROR_* code.
 */
static inline int list_check_valid(const list_t* list, size_t expected_item_size, bool must_be_non_empty) {
    int ret;
    if (list == NULL) {
        ret = MEDIA_ERROR_INVALID_PARAMETER;
    } else if ((list->item_size == 0U) || (list->capacity == 0U)) {
        ret = MEDIA_ERROR_NOT_FOUND;
    } else if (list->item_size != expected_item_size) {
        ret = MEDIA_ERROR_UNIMPLEMENTED;
    } else if (list->size > list->capacity) {
        ret = MEDIA_ERROR_UNIMPLEMENTED;
    } else if ((list->items == NULL) && (list->size > 0U)) {
        ret = MEDIA_ERROR_NOT_FOUND;
    } else if (must_be_non_empty && (list->size == 0U)) {
        ret = MEDIA_ERROR_NOT_FOUND;
    } else {
        ret = MEDIA_ERROR_NONE;
    }
    return ret;
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_LIST_H_
