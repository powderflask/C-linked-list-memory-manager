/*
 *  A Dynamic Memory Free Store ADT
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "freestore.h"

// Helper prototypes
void fsInsertSorted(FreeStore_t* heap, Segment_t* segment); 
Segment_t* fsFindInsertionPoint(const FreeStore_t heap, const Segment_t* segment);
void fsLink(FreeStore_t* heap, Segment_t* cursor, Segment_t* newSeg);
Segment_t* fsUnlink(FreeStore_t* heap, Segment_t* cursor);
Segment_t* fsFindPriorNode(const FreeStore_t heap, const Segment_t* cursor);


//------ SEGMENT --------
Segment_t* segCreate(void* address, long int size) 
{
    Segment_t* segment = malloc(sizeof(Segment_t));
    segment->address = address;
    segment->size = size;
    segment->next = NULL;
    return segment;
}

void segPrint(Segment_t segment) 
{
    printf("[%p (%ld bytes)]%s", segment.address, segment.size, segment.next ? "-->" : "--|");
}


//----- FREE STORE -----

// Implementation Note: List of Segments maintained in descending size order -- largest to smallest.

/**
 * Construct a Free Store from the given block of memory
 * @param address : address of memory block
 * @param size : number of bytes in memory block
 */
FreeStore_t fsCreate(void* address, long int size)
{
   Segment_t* dummy = segCreate(NULL, -1); // dummy head-node
   FreeStore_t heap;
   heap.head = dummy;
   heap.head->next = segCreate(address, size); // block of memory managed by this Free Store
   return heap;
}

/**
 * Release all memory managed and used by the given Free Store
 */
void fsDestruct(FreeStore_t* heap)
{
   while (heap->head != NULL) {
      Segment_t* cur = heap->head;
      heap->head = cur->next;
      free(cur);
   }
   heap->head = NULL;
}

/**
 * Return true iff a request for a block of the given size (bytes) can be satisfied
 */
bool fsIsAvail(const FreeStore_t heap, long int size)
{
   Segment_t* cur = heap.head->next;
   // Assumes Free Store is maintained in sorted order
   return cur != NULL && cur->size >= size;  // only need to know we COULD satisfy request
}


/**
 * Allocate a block of memory of the given size (bytes) from the given Free Store
 * Returns a pointer to the allocated memory segment, or NULL if !fsIsAvail(heap, size)
 */
Segment_t* fsAlloc(FreeStore_t* heap, long int size)
{
   Segment_t* cur = heap->head->next;
   Segment_t* best_fit = NULL;
   // search portion of free store with large enough blocks to satisfy request
   while (cur != NULL && cur->size >= size) {
       best_fit = cur;
       cur = cur->next;
   }
   if (best_fit == NULL) {
       return NULL;
   }
   Segment_t* seg = fsUnlink(heap, best_fit);
   if (seg->size == size) {
       return seg;
   }
   // Return un-needed portion of segment to Free Store
   Segment_t* unused = segCreate(seg->address+size, seg->size-size);
   fsInsertSorted(heap, unused);
   seg->size = size;
   return seg;
}

/**
 * Free a block of memory and return it back to the Free Store
 */
void fsFree(FreeStore_t* heap, Segment_t* segment) {
   fsInsertSorted(heap, segment);
}


// Helper:  for testing only
void fsPrint(const FreeStore_t heap)
{
   Segment_t* cur = heap.head->next;
   printf("\nFree Store:  ");
   while (cur != NULL) {
       segPrint(*cur);
       cur = cur->next;
   }
   printf("\n\n");
}


// Helpers:  Insert / Link in freed / unused segment

// Insert the segment in sorted order into the Free Store
void fsInsertSorted(FreeStore_t* heap, Segment_t* segment) 
{
    fsLink(heap, fsFindInsertionPoint(*heap, segment), segment);
}

// Find the sorted insertion point for the given segment
// Return a pointer to the segment that precedes the insertion point
Segment_t* fsFindInsertionPoint(const FreeStore_t heap, const Segment_t* segment) 
{
   Segment_t* prior = heap.head;
   while (prior->next !=NULL && prior->next->size > segment->size) {
      prior = prior->next;
   }
   // the goal we were shooting for - insertion point between a smaller and larger value
   assert(prior->next == NULL || (prior->size > segment->size && segment->size >= prior->next->size));
   return prior;
}

// Link in the new segment following the cursor
void fsLink(FreeStore_t* list, Segment_t* cursor, Segment_t* newSeg) 
{
   newSeg->next = cursor->next;
   cursor->next = newSeg;
}

// Helpers:  Unlink allocated segment

// Unlink the cursor and return a point to the unlinked segment
Segment_t* fsUnlink(FreeStore_t* heap, Segment_t* cursor) 
{
   Segment_t* prior = fsFindPriorNode(*heap, cursor);
   prior->next = cursor->next;
   cursor->next = NULL;
   return cursor;
}

// Return a pointer to the node just prior to the cursor in the list
Segment_t* fsFindPriorNode(const FreeStore_t heap, const Segment_t* cursor) 
{
   Segment_t* prior = heap.head;
   while (prior->next != cursor) {
      prior = prior->next;
      assert(prior != NULL);  // cursor was not a node in the list - illegal call!
   }
   assert(prior->next == cursor);  // the goal we were shooting for
   return prior;
}

