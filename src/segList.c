/**
 *  Basic Memory Segment List ADT : implementation
 *    
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "segList.h"

// Helper prototypes
void slLink(SegList_t* list, Segment_t* cursor, Segment_t* newSeg);
Segment_t* fsUnlink(SegList_t* list, Segment_t* cursor);
Segment_t* fsFindPriorNode(const SegList_t list, const Segment_t* cursor);


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


//----- SEGMENT LIST -----
// Implementation Note: List of Segments is a singly-linked-list with a dummy-head node

/**
 * Construct an empty Segment List
 */
SegList_t slCreate()
{
   Segment_t* dummy = segCreate(NULL, -1);
   SegList_t list = {dummy};
   return list;
}

/**
 * Release all memory managed and used by the given Segment list
 * list cannot be used after destroying it.
 */
void slDestruct(SegList_t* list)
{
   while (list->head != NULL) {
      Segment_t* cur = list->head;
      list->head = cur->next;
      free(cur);
   }
   list->head = NULL;
}

/**
 * Push the given segment to the front of the Segment list
 */
void slAdd(SegList_t* list, Segment_t* segment) 
{
   segment->next = list->head->next;
   list->head->next = segment;
}

/**
 * Find a Segment by its address in the Segment list
 * return a pointer to the segment or NULL if the no such segment in the list
 */
Segment_t* slFind(const SegList_t list, const void* address)
{
   Segment_t* cur = list.head->next;
   while (cur != NULL) {
       if (cur->address == address)
         return cur;
       cur = cur->next;
   }
   return NULL;
}

/**
 * Return true iff there is at least one Segment in the list larger or equal to given size
 */
bool slHasSegment(const SegList_t list, long int size)
{
   Segment_t* cur = list.head->next;
   while (cur != NULL) {
       if (cur->size >= size)
         return true;
       cur = cur->next;
   }
   return false;
}

/**
 * Returns a pointer to the smallest sement of at least given size in list, 
 *   or NULL if !slHasSegment(list, size)
 */
Segment_t* slFindBestFit(const SegList_t list, long int size)
{
   Segment_t* cur = list.head->next;
   Segment_t* best_fit = NULL;
   while (cur != NULL) {
      if (cur->size >= size && (!best_fit || cur->size < best_fit->size))
         best_fit = cur;
      cur = cur->next;
   }
   return best_fit;
}


// HELPER: Link in the new segment following the cursor
void slLink(SegList_t* list, Segment_t* cursor, Segment_t* newSeg) 
{
   assert(newSeg != NULL);
   assert(cursor != NULL);
   newSeg->next = cursor->next;
   cursor->next = newSeg;
}

// HELPER: Unlink the given cursor node from the list and return it
Segment_t* slUnlinkNext(SegList_t* list, Segment_t* cursor) 
{
   assert(cursor != NULL);
   Segment_t* unlink = cursor->next;
   assert(unlink != NULL);
   
   cursor->next = unlink->next;
   unlink->next = NULL;

   return unlink;
}

// HELPER: Find the node prior to the cursor
// PRE: slFind(*list, segment->address) != NULL  (i.e., segment is in the list)
Segment_t* slFindPriorNode(SegList_t* list, Segment_t* cursor) 
{
   assert(cursor != NULL);
   Segment_t* prior = list->head;
   while (prior->next != cursor) {
      prior = prior->next;
      assert(prior != NULL);  // cursor was not a Node in the list - illegal call!
   }
   assert(prior->next == cursor);  // the goal we were shooting for
   return prior;
}

/**
 * Remove and return the given segment from the Segment list
 * PRE: slFind(*list, segment->address) != NULL  (i.e., segment is in the list)
 */
Segment_t* slRemove(SegList_t* list, Segment_t* segment)
{
   return slUnlinkNext(list, slFindPriorNode(list, segment));
}


// Helper:  for testing only
void slPrint(const SegList_t list)
{
   Segment_t* cur = list.head->next;
   printf("\nSegment List:  ");
   while (cur != NULL) {
       segPrint(*cur);
       cur = cur->next;
   }
   printf("\n\n");
}

