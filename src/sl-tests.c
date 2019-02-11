/*
 *  Basic test driver for the Segment List ADT
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

//----- TEST DRIVER -----
int main( )
{
   int v;
   Segment_t* tmp;

   Segment_t* s1 = segCreate((void *)0x1, 20);
   assert(s1 != NULL);
   assert(s1->size == 20);
   Segment_t* s2 = segCreate((void *)0x21, 100);
   assert(s2 != NULL);
   assert(s2->size == 100);
   Segment_t* s3 = segCreate((void *)0x121, 50);
   assert(s3 != NULL);
   assert(s3->size == 50);

   SegList_t list = slCreate();
   printf("Empty list:\n");
   slPrint(list);
   assert(!slFind(list, (void *)0x1));
   assert(!slHasSegment(list, 1));

   slAdd(&list, s1);
   slAdd(&list, s2);
   slAdd(&list, s3);
   assert(slFind(list, (void *)0x1) == s1);
   assert(slFind(list, (void *)0x21) == s2);
   assert(slFind(list, (void *)0x121) == s3);

   assert(slHasSegment(list, 5));
   assert(slHasSegment(list, 25));
   assert(slHasSegment(list, 100));
   assert(!slHasSegment(list, 101));
   
   assert(slFindBestFit(list, 5) == s1);
   assert(slFindBestFit(list, 25) == s3);
   assert(slFindBestFit(list, 55) == s2);
   assert(slFindBestFit(list, 100) == s2);
   assert(slFindBestFit(list, 101) == NULL);
   
   printf("After 3 segments added to list:\n");
   slPrint(list);
   
   slRemove(&list, s1);
   slRemove(&list, s2);
   slRemove(&list, s3);

   printf("After 3 segments removed from list:\n");
   slPrint(list);


   slAdd(&list, s3);
   slAdd(&list, s2);
   slAdd(&list, s1);
   printf("After 3 segments added again, in reverse sequence:\n");
   slPrint(list);


   printf("After middle segments removed from list:\n");
   slRemove(&list, s2);
   slPrint(list);

   slDestruct(&list);
}
