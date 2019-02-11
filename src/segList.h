/**
 *  Simple Memory Segment List ADT 
 *    Segment:  One Memory segment in the Memory "heap"
 *    SegList:  A list of Segments
 *     - used to simply record and track memory segments.
 *     - does not allocate or free segments -- simply keeps track of a list of segments
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

// Helper:  for testing only
void segPrint(const Segment_t segment);


//----- SEGMENT LIST -----
// A singly-linked-list of Segments.
typedef struct SegList {
   Segment_t* head;
} SegList_t;


/*********************
 *  PUBLIC INTERFACE
 *********************/

/**
 * Construct an empty Segment List
 */
SegList_t slCreate();

/**
 * Release all memory managed and used by the given Segment list
 */
void slDestruct(SegList_t* list);

/**
 * Push the given segment to the front of the Segment list
 */
void slAdd(SegList_t* list, Segment_t* segment);

/**
 * Remove the given segment from the Segment list
 * PRE: slFind(*list, segment->address) != NULL  (i.e., segment is in the list)
 */
Segment_t* slRemove(SegList_t* list, Segment_t* segment);

/**
 * Find a Segment by its address in the Segment list
 * return a pointer to the segment or NULL if the no such segment in the list
 */
Segment_t* slFind(const SegList_t list, const void* address);

/**
 * Return true iff there is at least one Segment in the list larger or equal to given size
 */
bool slHasSegment(const SegList_t list, long int size);

/**
 * Returns a pointer to the smallest sement of at least given size in list, 
 *   or NULL if !slHasSegment(list, size)
 */
Segment_t* slFindBestFit(const SegList_t list, long int size);


// Helper:  for testing only
void slPrint(const SegList_t list);

