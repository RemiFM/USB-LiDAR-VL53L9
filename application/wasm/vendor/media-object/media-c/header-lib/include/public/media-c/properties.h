/**
 ******************************************************************************
 * @file    properties.h
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

#ifndef MEDIA_C_PROPERTIES_H_
#define MEDIA_C_PROPERTIES_H_

#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "property.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file properties.h
 * @brief Typed list of property_t key-value pairs.
 *
 * Provides @c properties_t (a @c list_t specialization) together with
 * creation, lookup, duplication and inspection helpers.
 */

/** @brief List of property_t key-value pairs. */
typedef list_t properties_t;

/**
 * @brief Allocate a new properties list.
 * @param[in] size  Initial capacity.
 * @return Pointer to the new list, or @c NULL on failure.
 */
static inline properties_t* properties_new(size_t size) { return list_new(size, sizeof(property_t)); }

/**
 * @brief Free a properties list and optionally each property.
 * @param[in] properties  Pointer to the list.
 * @param[in] free_func   Per-item destructor (may be @c NULL).
 */
static inline void properties_free(properties_t* properties, void (*free_func)(void*)) {
    if (properties != NULL) {
        list_free(properties, free_func);
    }
}

/**
 * @brief Append a property to the list.
 * @param[in,out] properties  Pointer to the list.
 * @param[in]     property    Pointer to the property to copy in.
 * @return @c true on success.
 */
static inline bool properties_add(properties_t* properties, property_t* property) {
    return list_add(properties, property);
}

/**
 * @brief Retrieve a property by index.
 * @param[in] properties  Pointer to the list.
 * @param[in] index       Zero-based index.
 * @return Pointer to the property, or @c NULL if out of range.
 */
static inline property_t* properties_get(const properties_t* properties, size_t index) {
    return (property_t*)list_get(properties, index);
}

/**
 * @brief Return the current number of properties.
 * @param[in] properties  Pointer to the list.
 * @return Item count.
 */
static inline size_t properties_size(const properties_t* properties) { return properties->size; }

/**
 * @brief Return the allocated capacity.
 * @param[in] properties  Pointer to the list.
 * @return Capacity.
 */
static inline size_t properties_capacity(const properties_t* properties) { return properties->capacity; }

/**
 * @brief Check whether the list is empty.
 * @param[in] properties  Pointer to the list.
 * @return @c true if the list contains no items.
 */
static inline bool properties_empty(const properties_t* properties) { return properties->size == 0U; }

/**
 * @brief Find a property by name.
 * @param[in] properties  Pointer to the list.
 * @param[in] name        Null-terminated name to search for.
 * @return Pointer to the matching property, or @c NULL if not found.
 */
static inline property_t* properties_find(const properties_t* properties, const char* name) {
    property_t* result = NULL;
    for (size_t i = 0; i < properties->size; ++i) {
        property_t* property = (property_t*)list_get(properties, i);
        if (strcmp(property->name, name) == 0) {
            result = property;
            break;
        }
    }
    return result;
}

/**
 * @brief Remove all properties from the list, optionally freeing each one.
 * @param[in,out] properties  Pointer to the list.
 * @param[in]     free_func   Per-item destructor (may be @c NULL).
 */
static inline void properties_clear(properties_t* properties, void (*free_func)(void*)) {
    list_clear(properties, free_func);
}

/**
 * @brief Create a deep copy of a properties list.
 *
 * Each property is copied by value; string pointers are shared.
 *
 * @param[in] original  Pointer to the source properties list.
 * @return Pointer to the duplicated list, or @c NULL on failure.
 */
static inline properties_t* properties_duplicate(const properties_t* original) {
    properties_t* duplicate = NULL;
    if (original != NULL) {
        duplicate = properties_new(properties_capacity(original));
        if (duplicate != NULL) {
            bool success = true;
            for (size_t i = 0; i < properties_size(original); ++i) {
                property_t* original_property = properties_get(original, i);
                if (original_property == NULL) {
                    success = false;
                    break;
                }

                if (!properties_add(duplicate, original_property)) {
                    success = false;
                    break;
                }
            }
            if (!success) {
                properties_free(duplicate, NULL);
                duplicate = NULL;
            }
        }
    }
    return duplicate;
}

/**
 * @brief Iterate over all properties and invoke a callback for each.
 * @param[in] properties  Pointer to the list.
 * @param[in] callback    Function called for each property_t pointer.
 */
static inline void properties_iterate(const properties_t* properties, void (*callback)(property_t*)) {
    if ((properties != NULL) && (callback != NULL)) {
        for (size_t i = 0; i < properties->size; ++i) {
            property_t* property = (property_t*)list_get(properties, i);
            callback(property);
        }
    }
}

/**
 * @brief Print a human-readable dump of the properties list.
 *
 * @param[in] properties  Pointer to the list.
 * @param[in] print_func  Printf-like callback used for output.
 * @param[in] indent      Prefix string prepended to each line.
 */
static inline void properties_inspect(const properties_t* properties, int (*print_func)(const char*, ...),
                                      const char* indent) {
    (void)print_func("%sProperties:\n", indent);
    char new_indent[10];
    size_t indent_len = strlen(indent);
    if (indent_len > (sizeof(new_indent) - 2U)) {
        indent_len = sizeof(new_indent) - 2U;
    }
    (void)memcpy(new_indent, indent, indent_len);
    new_indent[indent_len] = '\t';
    new_indent[indent_len + 1U] = '\0';
    for (size_t i = 0; i < properties->size; ++i) {
        const property_t* property = properties_get(properties, i);
        property_print(property, print_func, new_indent);
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_PROPERTIES_H_
