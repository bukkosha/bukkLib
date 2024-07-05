# TODO For bukkLib

- MemoryAllocator

  - ~~Undarstand how to keep blocks of memory~~
  - ~~How to choose blocks for allocate memory~~
  - ~~How to allocate memory for block~~
  - ~~Get access to allocate memory~~
  - ~~If the block free, but his size more then need, what to do?~~
  - ~~Is "pthread_mutex_lock" need?~~
  
  - ~~Simple memory allocator (By using sbrk)~~
    - ~~malloc~~
      - ~~Union for header~~
      - ~~Create block for keep header and block of memry~~
    - ~~free~~
    - ~~calloc~~
    - ~~realloc~~

  - Memory allocator with mmap
    - malloc
    - free
    - calloc
    - realloc

- DynamicArray
  - Templates
  - Vector init
  - Vector free
  - Vector copy
  - Vector get item
  - Vector set item
  - Vector get size
  - Vector get capacity
  - Vector change size
  - Vector change capacity
  - Vector push back
  - Vector pop back
  - Vector shrink to fit
  - Vector resize
  - Vector reserve

- SingleLinkedList
- DoubleLinkedList
- HashTab
- HashMap
- Queue
- Stack
- Heap
