# Data-Structures-Assignment-2
This is a program for the course Data Structures at Oregon State. This assignment was intended to have us start working with stacks and queues and to start building ADTs on top of other data structures.

## Requirements

### Stack
- *`stack_create()`* correctly allocates and initializes a stack.
- *`stack_free()`* correctly frees the memory allocated by a stack with no memory leaks.
- *`stack_push()`* correctly pushes a value onto a stack with O(1) average runtime complexity.
- *`stack_top()`* correctly returns the top value on a stack with O(1) average runtime complexity.
- The stack implementation correctly uses a linked list for its underlying data storage using only the linked list implementation's interface functions (i.e., without accessing the internals of the list implementation).

### Queue
- *`queue_create()`* allocates and initializes a queue.
- *`queue_free()`* frees the memory allocated by a queue with no memory leaks.
- *`queue_isempty()`* determines whether a queue is empty.
- *`queue_enqueue()`* correctly enqueues a value into a queue with O(1) average runtime complexity.
- *`queue_front()`* correctly returns the front value from a queue with O(1) average runtime complexity.
- The queue implementation correctly uses a dynamic array for its underlying data storage using only the dynamic array implementation's interface functions (i.e., without accessing the internals of the dynamic array implementation).

### Call Center
- Uses queue from part 2 to keep track of incoming calls.
- Uses stack from part 1 to keep track of answered calls.
- Each call is stored as a struct, containing ID, name, and reason.
- Correctly implements 2 options described + quit.
- Clear and readable instructions and output.

## Limitations of the program
- *`stack_isempty()`* checks for list null.
- *`stack_pop()`* is not implemented.
- Queue is correct but no circular buffer.
- *`queue_dequeue()`* is not implemented with O(1) average runtime complexity.
- Options 3 and 4 of the call center are not implemented:
  - Current state of the stack – answered calls.
  - Current state of the queue – calls to be answered.
- 2 memory leaks in the call center.
