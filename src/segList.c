/**
 *  Simple Memory Segment List ADT : implementation
 *    
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "freestore.h"
#include "segList.h"


SegList_t slCreate()
{
   Segment_t* dummy = segCreate(NULL, -1);
   SegList_t list = {dummy};
   return list;
}

// Link in new segment at front of list
void slAdd(SegList_t* list, Segment_t* segment) 
{
   segment->next = list->head->next;
   list->head->next = segment;
}

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


Segment_t* slUnlinkNext(SegList_t* list, Segment_t* cursor) 
{
   Segment_t* unlink = cursor->next;
   assert(unlink != NULL);
   
   cursor->next = unlink->next;
   unlink->next = NULL;

   return unlink;
}

Segment_t* slFindPriorNode(SegList_t* list, Segment_t* cursor) 
{
   Segment_t* prior = list->head;
   while (prior->next != cursor) {
      prior = prior->next;
      assert(prior != NULL);  // cursor was not a Node in the list - illegal call!
   }
   assert(prior->next == cursor);  // the goal we were shooting for
   return prior;
}

Segment_t* slRemove(SegList_t* list, Segment_t* segment)
{
   return slUnlinkNext(list, slFindPriorNode(list, segment));
}


// Helper:  for testing only
void slPrint(const SegList_t list)
{
   Segment_t* cur = list.head->next;
   printf("\nIn-use Segments:  ");
   while (cur != NULL) {
       segPrint(*cur);
       cur = cur->next;
   }
   printf("\n\n");
}

