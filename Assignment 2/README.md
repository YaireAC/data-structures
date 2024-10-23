# Data-Structures-Assignment-2
This is a program for the course Data Structures at Oregon State. This assignment was intended to have us start working with stacks and queues and to
start building ADTs on top of other data structures. There are a couple parts to the assignment: implementing a stack, implementing a queue, implementing a basic call center using a stack and queue.


## The program completes the following requirements.

### <ins>Stack </ins>
- `stack_create()` correctly allocates and initializes a stack
- `stack_free()` correctly frees the memory allocated by a stack with no memory leaks
- `stack_push()` correctly pushes a value onto a stack with O(1) average runtime complexity
- `stack_top()` correctly returns the top value on a stack with O(1) average runtime complexity
- the stack implementation correctly uses a linked list for its underlying data storage using only the linked list implementation's interface functions (i.e. without accessing the internals of the list implementation)

### <ins>Queue </ins>
- `queue_create()` allocates and initializes a queue
- `queue_free()` frees the memory allocated by a queue with no memory leaks
- `queue_isempty()` determines whether a queue is empty
- `queue_enqueue() correctly enqueues a value into a queue with O(1) average runtime complexity
- `queue_front()` correctly returns the front value from a queue with O(1) average runtime complexity
- queue implementation correctly uses a dynamic array for its underlying data storage using only the dynamic array implementation's interface functions (i.e. without accessing the internals of the dynamic array implementation)

### <ins>Call Center </ins>
- Use queue in part 2 to keep track of incoming calls
- Use stack in part 1 to keep track of answered calls
- Each call is stored as a struct, containing ID, name, and reason
- correctly implemented 2 options described + quit
- clear and readable instructions and output

## Limitations of the program
- `stack_isempty` checks list null
- `stack_pop is not implemented
- queue is correct but no cirrcular buffer
- queue_dequeue is not imlemented with a O(1) average runtime complexity
- options 3 and 4 of the call center are not implemented:
  - Current state of the stack – answered calls
  - Current state of the queue – calls to be answered
- 2 memory leaks in call center



