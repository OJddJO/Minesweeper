#ifndef __SSGE_ARRAY_H__
#define __SSGE_ARRAY_H__

#include <stdint.h>
#include <stdbool.h>

#include "SSGE/SSGE_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SSGE_Array {
    void **array; // Pointer to the array of pointers
    uint32_t size; // Size of the array
    uint32_t count; // Number of elements in the array
    uint32_t *indexes; // Pointer to the pile of unused indexes
    uint32_t idxSize; // The size of the pile of indexes
    uint32_t idxCount; // Number of unused indexes
} SSGE_Array;

SSGEDECL SSGE_Array *SSGE_Array_Create();
SSGEDECL uint32_t SSGE_Array_Add(SSGE_Array *array, void *element);
SSGEDECL void *SSGE_Array_Get(SSGE_Array *array, uint32_t idx);
SSGEDECL void SSGE_Array_Remove(SSGE_Array *array, uint32_t idx, void (*destroyData)(void *));
SSGEDECL void *SSGE_Array_Pop(SSGE_Array *array, uint32_t idx);
SSGEDECL void *SSGE_Array_Find(SSGE_Array *array, bool (*condition)(void *, void *), void *argument);
SSGEDECL void *SSGE_Array_FindPop(SSGE_Array *array, bool (*condition)(void *, void *), void *argument);
SSGEDECL void SSGE_Array_Destroy(SSGE_Array *array, void (*destroyData)(void *));

#ifdef __cplusplus
}
#endif

#endif // __SSGE_ARRAY_H__