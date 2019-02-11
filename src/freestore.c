/*
 *  A Free Store ADT
 *    reprents the available memory heap 
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "segList.h"
#include "freestore.h"


/**
 * Construct a Free Store from the given block of memory
 * @param address : address of memory block
 * @param size : number of bytes in memory block
 */
FreeStore_t fsCreate(void* address, long int size)
{
   FreeStore_t heap = slCreate();
   slAdd(&heap, segCreate(address, size));
   return heap;
}

/**
 * Release all memory managed and used by the given Free Store
 */
void fsDestruct(FreeStore_t* heap)
{
   slDestruct(heap);
}

/**
 * Return true iff a request for a block of the given size (bytes) can be satisfied
 */
bool fsIsAvail(const FreeStore_t heap, long int size)
{
   return slHasSegment(heap, size);
}


/**
 * Allocate a block of memory of the given size (bytes) from the given Free Store
 * Returns a pointer to the allocated memory segment, or NULL if !fsIsAvail(heap, size)
 */
Segment_t* fsAlloc(FreeStore_t* heap, long int size)
{
   Segment_t* best_fit = slFindBestFit(*heap, size);
   if (best_fit == NULL) {
       return NULL;
   }
   Segment_t* seg = slRemove(heap, best_fit);
   // short-cut if the segment just happens to be the right size.
   if (seg->size == size) {
       return seg;
   }
   // Return un-needed portion of segment to Free Store
   Segment_t* unused = segCreate(seg->address+size, seg->size-size);
   slAdd(heap, unused);
   seg->size = size;
   return seg;
}

/**
 * Free a block of memory and return it back to the Free Store
 */
void fsFree(FreeStore_t* heap, Segment_t* segment) {
   slAdd(heap, segment);
}


// Helper:  for testing only
void fsPrint(const FreeStore_t heap)
{
   printf("\nFree Store:  ");
   slPrint(heap);
}
