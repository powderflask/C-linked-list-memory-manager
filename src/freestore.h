/**
 *  Free Store ADT : public interface
 *    FreeStore: A list of Free Memory segments
 *
 *  Dependencies: segList
 * 
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

/*******************
 * PRIVATE TYPE DECLARATIONS
 ********************/
// A Free Store is just a list of segments with a different API
typedef struct SegList FreeStore_t;


/*********************
 *  PUBLIC INTERFACE
 *********************/

/**
 * Construct a Free Store from the given block of memory
 * @param address : address of memory block
 * @param size : number of bytes in memory block
 */
FreeStore_t fsCreate(void* address, long int size);

/**
 * Release all memory managed and used by the given Free Store
 */
void fsDestruct(FreeStore_t* heap);

/**
 * Return true iff a request for a block of the given size (bytes) can be satisfied
 */
bool fsIsAvail(const FreeStore_t heap, long int size);

/**
 * Allocate a block of memory of the given size (bytes) from the given Free Store
 * Returns pointer to the allocated memory segment, or NULL if !fsIsAvail(heap, size)
 */
Segment_t* fsAlloc(FreeStore_t* heap, long int size);

/**
 * Free a block of memory and return it back to the Free Store
 */
void fsFree(FreeStore_t* heap, Segment_t* address);

// Helper:  for testing only
void fsPrint(const FreeStore_t heap);

