# Memory Management

## 1. Task memory allocation

<img width="710" height="370" alt="image" src="https://github.com/user-attachments/assets/8955c939-433e-49ee-84cd-a207a4112e7b" />

- FreeRTOS uses this **heap memory** to allocate memory task for:
  - **Task Control Blocks (TCB)**
    - Used by the task when it is running.
    - Stores local variables, function return addresses, saved registers during context switching.
    - Each task has a separate stack, so they don’t overwrite each other.
  - **Task Stacks**
    - Task priority
    - Task state (Running, Ready, Blocked, Suspended)
    - Pointer to the stack
    - Task name
    - Linked list info for the scheduler

<img width="773" height="392" alt="image" src="https://github.com/user-attachments/assets/3bfc4444-60ea-4cfd-badf-c7f30cc2ffb1" />

- **Task Control Blocks (TCB)**
    - Local variables (e.g., a, b, c, d in Task1()).
    - Function call info.
    - Return addresses.
- **Task Stacks**
    - PC (Program Counter) → where the task will resume. FreeRTOS remembers exactly which line (instruction) the task was at. Later, the task continues exactly where it left off.
    - SP (Stack Pointer) → current top of the task’s stack.
    - CPU registers (R0, R1, …) → so the task can be paused and resumed later.
    - Task state (Ready, Blocked, Suspended, etc.).
    - Priority and other metadata.
 
## 2. Heap memory management options

### 2.1. Heap_1

- Does not allow freeing memory.
- Very simple, just allocates memory sequentially.
- Best when tasks are created once and never deleted.

### 2.2. Heap_2

- Allows freeing memory.
- But it does not place freed memory blocks next to each other (no coalescing).
- May cause fragmentation.

### 2.3. Heap_3

- Uses standard C malloc() and free().
- Can allocate and free memory normally.
- ⚠️ Warning: After a task is deleted, its memory becomes free space.
→ Over time, this may lead to heap fragmentation (scattered free memory blocks that cannot be reused efficiently).

### 2.4. Heap_4

- Can allocate and free memory.
- Includes a better algorithm to reduce fragmentation compared to heap_2 and heap_3.
- More flexible and efficient.

### 2.5. Heap_5

- Similar to heap_4 but even more advanced.
- Supports managing multiple separate memory regions.
- Best for complex systems where memory comes from different sources.
