# C-linked-list-memory-manager
## COMP220 Linked List application example
A simple memory manager - to demonstrate linked-list application. \
This example is NOT intended to show how real memory managers actually work, but does demonstrate some of the basic principles involved.

### C modules:
 * `freestore` : a linked-list of memory segments representing the memory free-store (heap).
 * `seglist` : a linked-list of memory segments representing in-use (allocated) memory blocks.
 * `mmalloc` : an C-programmers API to the memory manager - provides mmalloc(), mcalloc(), and mfree() operation similar to those provided by <stdlib>
  
### Test drivers:
 * fs-tests : comprehensive unit tests for freestore ADT
 * mm-tests : a simple test driver to illustrate use of mmalloc API
 
### Build Drivers
`> make`
