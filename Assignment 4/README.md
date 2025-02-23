# Data-Structures-Assignment-4
This is a program for the course Data Structures at Oregon State. In this assignment, we implemented a binary heap-based priority queue (PQ).

## Requirements

### Correctly implements a priority queue based on a minimizing binary heap
- *`struct pq`* defines a heap-based priority queue.
- *`pq_create()`* correctly allocates and initializes a heap-based priority queue.
- *`pq_free()`* correctly frees all memory associated with a priority queue with no leaks.
- *`pq_isempty()`* correctly determines whether a priority queue contains any elements.
- *`pq_first()`* correctly returns the first value in a priority queue in O(1) runtime complexity.
- *`pq_first_priority()`* correctly returns the priority value associated with the first element in a priority queue in O(1) runtime complexity.
- *`pq_insert()`* correctly inserts a value into a priority queue with the specified priority and restores the heap property as needed in O(log n) runtime complexity.
- *`pq_remove_first()`* correctly removes the first element from a priority queue and returns its value, restoring the heap property as needed in O(log n) runtime complexity.
