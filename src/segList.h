/**
 *  Simple Memory Segment List ADT 
 *     - used to simply record and track memory segments currently in use.
 *     - does not allocate or free segments -- simply keeps track of exising segments
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */

typedef struct SegList {
   Segment_t* head;
} SegList_t;

SegList_t slCreate();

void slAdd(SegList_t* list, Segment_t* segment);

Segment_t* slFind(const SegList_t list, const void* address);

Segment_t* slRemove(SegList_t* list, Segment_t* segment);

// Helper:  for testing only
void slPrint(const SegList_t list);

