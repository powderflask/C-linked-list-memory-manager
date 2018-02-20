/*
 *  Basic test driver for the Simple Memory Manager ADT
 *
 *  Author:  Joseph Fafs
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "mmalloc.h"

struct foo {
   int bar;
   char baz;
   double buz;
};

//----- TEST DRIVER -----
int main( )
{
   mminit();
   
   void *ptr1, *ptr2, *ptr3;
   
   printf("Allocating 3 pointers... \n");

   ptr1 = mmalloc(100 * sizeof(int));
   
   ptr2 = mcalloc(42, sizeof(char));
   
   ptr3 = mmalloc(sizeof(struct foo));
   
   printf("Allocated 3 pointers:  %p, %p, %p \n", ptr1, ptr2, ptr3);
   mmPrint();
   
   mfree(ptr1);
   ptr1 = NULL;
   mfree(ptr3);
   ptr3 = NULL;
   mfree(ptr2);
   ptr2 = NULL;
   
   printf("\n\nFreed 3 pointers back to the heap.\n");
   mmPrint();
}
