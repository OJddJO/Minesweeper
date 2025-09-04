// Internal array struct
// Defines a dynamic array specifically made for SSGE usage
// It is not recommanded to use this array as it may
//  not be optimized for general usage.

#ifndef __SSGE_ARRAY_H__
#define __SSGE_ARRAY_H__

#include <stdint.h>
#include <stdbool.h>

#include "SSGE/SSGE_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new array
 * \param array The array to initialize
 */
SSGEAPI void SSGE_Array_Create(SSGE_Array *array);

/**
 * Add an element to an array
 * \param array The array to add the element to
 * \return The index of the element
 */
SSGEAPI uint32_t SSGE_Array_Add(SSGE_Array *array, void *element);

/**
 * Get an element from an array
 * \param array The array to get the element from
 * \param idx The index of the element to get
 * \return The pointer to the element
 */
SSGEAPI void *SSGE_Array_Get(SSGE_Array *array, uint32_t idx);

/**
 * Remove an element from an array
 * \param array The array to remove the element from
 * \param idx The index of the element to remove
 * \param destroyData The function to destroy the element to remove from the array
 */
SSGEAPI void SSGE_Array_Remove(SSGE_Array *array, uint32_t idx, void (*destroyData)(void *));

/**
 * Pop an element from an array
 * \param array The array to pop the element from
 * \param idx The index of the element to pop
 * \return The pointer to the popped element
 */
SSGEAPI void *SSGE_Array_Pop(SSGE_Array *array, uint32_t idx);

/**
 * Find an element from an array with a condition
 * \param array The array to find the element from
 * \param condition The condition to find the element. Must be `bool condition(void *element, void *argument)`
 * \param argument The argument to pass to the condition function
 * \return The pointer to the first element that matches the condition, or NULL if not found
 */
SSGEAPI void *SSGE_Array_Find(SSGE_Array *array, bool (*condition)(void *, void *), void *arg);

/**
 * Find an element from array with a condition and pops it
 * \param array The array to find and pop the element from
 * \param condition The condition to find the element. Must be `bool condition(void *element, void *argument)`
 * \param argument The argument to pass to the condition function
 * \return The pointer to the first element that matches the condition, or NULL if not found
 */
SSGEAPI void *SSGE_Array_FindPop(SSGE_Array *array, bool (*condition)(void *, void *), void *arg);

/**
 * Destroy an array
 * \param array The array to destroy
 * \param destroyData The function to destroy the elements of the array. Can be `NULL`
 */
SSGEAPI void SSGE_Array_Destroy(SSGE_Array *array, void (*destroyData)(void *));

#ifdef __cplusplus
}
#endif

#endif // __SSGE_ARRAY_H__