/**
 *  Free Store ADT : public interface
 *    Segment:  One Memory segment in the Memory "heap"
 *    FreeStore: A sorted, singly-linked list of Memory segments
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

/*******************
 * PRIVATE TYPE DECLARATIONS
 ********************/

//----- SEGMENT -----
struct  Segment {
    void* address;
    long int size;
    struct Segment* next;
};
typedef struct Segment Segment_t;


Segment_t* segCreate(void* address, long int size);


//----- FREE STORE -----
struct FreeStore {
   Segment_t* head;
};
typedef struct FreeStore FreeStore_t;


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
 * Returns a pointer to the allocated memory segment, or NULL if !fsIsAvail(heap, size)
 */
Segment_t* fsAlloc(FreeStore_t* heap, long int size);

/**
 * Free a block of memory and return it back to the Free Store
 */
void fsFree(FreeStore_t* heap, Segment_t* segment);

// Helper:  for testing only
void fsPrint(const FreeStore_t heap);

