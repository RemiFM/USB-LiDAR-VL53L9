/**
 ******************************************************************************
 * @file    capabilities.h
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

#ifndef MEDIA_C_CAPABILITIES_H_
#define MEDIA_C_CAPABILITIES_H_

#include "properties.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file capabilities.h
 * @brief Capabilities (list of property sets) for media streams.
 *
 * Provides @c capabilities_t (a @c list_t specialization holding
 * @c properties_t pointers) together with creation, access, duplication,
 * iteration and inspection helpers used during format negotiation.
 */

/** @brief List of capabilities (sets of properties). */
typedef list_t capabilities_t;

/**
 * @brief Create a new capabilities list with an initial capacity.
 *
 * @param initial_capacity The initial capacity of the list.
 * @return A pointer to the newly created capabilities list.
 */
static inline capabilities_t* capabilities_new(size_t initial_capacity) {
    return list_new(initial_capacity, sizeof(properties_t*));
}

/**
 * @brief Create a new capabilities list with a single property.
 *
 * @param properties A pointer to the properties to be added to the list.
 * @return A pointer to the newly created capabilities list.
 */
static inline capabilities_t* capabilities_new_simple(properties_t** properties) {
    capabilities_t* capabilities = list_new(1, sizeof(properties_t*));
    (void)list_add(capabilities, properties);
    return capabilities;
}

/**
 * @brief Free the memory allocated for the capabilities list.
 *
 * @param capabilities A pointer to the capabilities list to be freed.
 * @param free_func A function pointer to free the properties.
 */
static inline void capabilities_free(capabilities_t* capabilities, void (*free_func)(void*)) {
    list_free(capabilities, free_func);
}

/**
 * @brief Add a property to the capabilities list.
 *
 * @param capabilities A pointer to the capabilities list.
 * @param properties A pointer to the properties to be added.
 * @return true if the property was added successfully, false otherwise.
 */
static inline bool capabilities_add(capabilities_t* capabilities, properties_t** properties) {
    return list_add(capabilities, properties);
}

/**
 * @brief Get a property from the capabilities list by index.
 *
 * @param capabilities A pointer to the capabilities list.
 * @param index The index of the property to get.
 * @return A pointer to the property at the specified index.
 */
static inline properties_t** capabilities_get(const capabilities_t* capabilities, size_t index) {
    return (properties_t**)list_get(capabilities, index);
}

/**
 * @brief Set a property in the capabilities list by index.
 *
 * @param capabilities A pointer to the capabilities list.
 * @param index The index of the property to set.
 * @param properties A pointer to the properties to set.
 * @return true if the property was set successfully, false otherwise.
 */
static inline bool capabilities_set(const capabilities_t* capabilities, size_t index, properties_t** properties) {
    return list_set(capabilities, index, properties);
}

/**
 * @brief Get the capacity of the capabilities list.
 *
 * @param capabilities A pointer to the capabilities list.
 * @return The capacity of the capabilities list.
 */
static inline size_t capabilities_capacity(const capabilities_t* capabilities) { return capabilities->capacity; }

/**
 * @brief Get the size of the capabilities list.
 *
 * @param capabilities A pointer to the capabilities list.
 * @return The size of the capabilities list.
 */
static inline size_t capabilities_size(const capabilities_t* capabilities) { return capabilities->size; }

/**
 * @brief Check if the capabilities list is empty.
 *
 * @param capabilities A pointer to the capabilities list.
 * @return true if the capabilities list is empty, false otherwise.
 */
static inline bool capabilities_empty(const capabilities_t* capabilities) { return capabilities->size == 0U; }

/**
 * @brief Clear the capabilities list.
 *
 * @param capabilities A pointer to the capabilities list.
 * @param free_func A function pointer to free the properties.
 */
static inline void capabilities_clear(capabilities_t* capabilities, void (*free_func)(void*)) {
    list_clear(capabilities, free_func);
}

/**
 * @brief Duplicate a capabilities list.
 *
 * @param original A pointer to the original capabilities list.
 * @return A pointer to the duplicated capabilities list, or NULL if duplication failed.
 */
static inline capabilities_t* capabilities_duplicate(const capabilities_t* original) {
    capabilities_t* duplicate = NULL;
    if (original != NULL) {
        duplicate = capabilities_new(capabilities_capacity(original));
        if (duplicate != NULL) {
            bool success = true;
            for (size_t i = 0; (i < capabilities_size(original)) && success; ++i) {
                properties_t** original_properties = capabilities_get(original, i);
                if (original_properties == NULL) {
                    success = false;
                } else {
                    properties_t* new_properties = properties_duplicate(*original_properties);
                    if (new_properties == NULL) {
                        success = false;
                    } else if (!capabilities_add(duplicate, &new_properties)) {
                        properties_free(new_properties, NULL);
                        success = false;
                    } else {
                        /* item added successfully */
                    }
                }
            }
            if (!success) {
                capabilities_free(duplicate, NULL);
                duplicate = NULL;
            }
        }
    }
    return duplicate;
}

/**
 * @brief Iterate over all capability entries and invoke a callback for each.
 *
 * @param[in] capabilities  Pointer to the capabilities list.
 * @param[in] callback      Function called for each properties_t** pointer.
 */
static inline void capabilities_iterate(const capabilities_t* capabilities, void (*callback)(properties_t**)) {
    if ((capabilities != NULL) && (callback != NULL)) {
        for (size_t i = 0; i < capabilities_size(capabilities); ++i) {
            properties_t** properties = capabilities_get(capabilities, i);
            callback(properties);
        }
    }
}

/**
 * @brief Print a human-readable dump of the capabilities list.
 *
 * @param[in] caps        Pointer to the capabilities list.
 * @param[in] print_func  Printf-like callback used for output.
 * @param[in] indent      Prefix string prepended to each line.
 */
static inline void capabilities_inspect(const capabilities_t* caps, int (*print_func)(const char*, ...),
                                        const char* indent) {
    (void)print_func("%sCapabilities:\n", indent);
    char new_indent[10];
    size_t indent_len = 0U;

    if (indent == NULL) {
        indent = "";
    }

    while ((indent[indent_len] != '\0') && (indent_len < (sizeof(new_indent) - 2U))) {
        new_indent[indent_len] = indent[indent_len];
        ++indent_len;
    }

    new_indent[indent_len] = '\t';
    new_indent[indent_len + 1U] = '\0';
    for (size_t i = 0; i < capabilities_size(caps); ++i) {
        const properties_t* cap_properties = *capabilities_get(caps, i);
        properties_inspect(cap_properties, print_func, new_indent);
    }
}

#ifdef __cplusplus
}
#endif

#endif  // MEDIA_C_CAPABILITIES_H_
