/*
 *  A Simple-minded Memory Manager for a simple-minded O/S  (Singleton)
 *
 *  Author:  Joseph Fall
 *  Date:    Feb. 19, 2018
 */
 
/**
 * Initialize the Memory manager - MUST be called EXACTLY ONCE when OS boots
 */
void mminit();

/**
 * Simulate C's stdlib malloc
 */
void* mmalloc(long int size);

/**
 * Simulate C's stdlib calloc
 */
void* mcalloc(int nitems, int item_size);

/**
 * Simulate C's stdlib free
 */
void mfree(void* ptr);

// Helper:  for testing only
void mmPrint();
