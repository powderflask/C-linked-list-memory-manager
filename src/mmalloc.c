/*
 *  A Simple-minded Memory Manager for a simple-minded O/S   (Singleton)
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "segList.h"
#include "freestore.h"
#include "mmalloc.h"

struct memManager {
   FreeStore_t freestore;
   SegList_t allocated;
};

// Singleton memory manager.  Module scope "global"
// An O/S memory manager might create an independent memory manager for each process.
struct memManager memoryManager;

// Hard-code the size of the free-store.  
// An O/S memory manager would be working with the available memory in hardware.
#define MEM_SIZE 100000

void mminit() {
   // Allocate a big block of memory for this memory manager to manage
   // An O/S memory manager would be working with hardware memory - here we are simulating...
   void* base_addr = malloc(MEM_SIZE);
   memoryManager.freestore = fsCreate(base_addr, MEM_SIZE);
   memoryManager.allocated = slCreate();
}

void* mmalloc(long int size) {
   // This assert causes memory manager to crash program if sufficient memory unavailable -- not ideal!
   assert(fsIsAvail(memoryManager.freestore, size));
   Segment_t* seg = fsAlloc(&memoryManager.freestore, size);
   slAdd(&memoryManager.allocated, seg);
   return seg->address;
}

void* mcalloc(int nitems, int item_size) {
   void* address = mmalloc(nitems * item_size);
   // here we should reset all memory bytes in the segment to zero
   return address;
}

void mfree(void* ptr)
{
   Segment_t* seg = slFind(memoryManager.allocated, ptr);
   assert(seg != NULL);  // Crash program if trying to free a ptr that is not allocated
   slRemove(&memoryManager.allocated, seg);
   fsFree(&memoryManager.freestore, seg);
   // notice there is no way for us to set the caller's pointer to NULL for them!
}

// Helper:  for testing only
void mmPrint()
{
   slPrint(memoryManager.allocated);
   fsPrint(memoryManager.freestore);
}
