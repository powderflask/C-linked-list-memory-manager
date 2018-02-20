/*
 *  Basic test driver for the Dynamic Memory Free Store ADT
 *
 *  Author:  Joseph Fafs
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#include "freestore.h"

//----- TEST DRIVER -----
int main( )
{
   int v;
   Segment_t* tmp;

   FreeStore_t heap = fsCreate((void *)0xabcdef, 100000);
   assert(fsIsAvail(heap, 100));
   assert(fsIsAvail(heap, 100000));
   assert(!fsIsAvail(heap, 100001));
   printf("Fresh heap:\n");
   fsPrint(heap);

   Segment_t* s1 = fsAlloc(&heap, 20);
   assert(s1 != NULL);
   assert(s1->size == 20);
   assert(fsIsAvail(heap, 100000-20));
   assert(!fsIsAvail(heap, 100001-20));
   
   Segment_t* s2 = fsAlloc(&heap, 100);
   assert(s2 != NULL);
   assert(s2->size == 100);
   assert(fsIsAvail(heap, 100000-120));
   assert(!fsIsAvail(heap, 100001-120));

   Segment_t* s3 = fsAlloc(&heap, 30);
   assert(s3 != NULL);
   assert(s3->size == 30);
   assert(fsIsAvail(heap, 100000-150));
   assert(!fsIsAvail(heap, 100001-150));

   printf("After 3 segments allocated for 150 bytes:\n");
   fsPrint(heap);
   
   fsFree(&heap, s1);
   fsFree(&heap, s2);
   fsFree(&heap, s3);

   printf("After 3 segments freed back to heap:\n");
   fsPrint(heap);

   s1 = fsAlloc(&heap, 18);
   assert(s1 != NULL);
   assert(s1->size == 18);
   s2 = fsAlloc(&heap, 25);
   assert(s2 != NULL);
   assert(s2->size == 25);

   printf("After 2 small segments allocated:\n");
   fsPrint(heap);

   fsFree(&heap, s1);
   fsFree(&heap, s2);

   printf("After 2 small segments freed back to heap:\n");
   fsPrint(heap);

   fsDestruct(&heap);
}
