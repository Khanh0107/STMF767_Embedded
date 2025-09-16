# Mail Queue

## 1. What is Mail Queue

### 1.1 Introduction

- A Mail Queue in RTOS is an inter-task communication mechanism that allows tasks (or ISRs) to exchange data in the form of mail objects (structures).
- Unlike Message Queue (which usually sends raw values), Mail Queue sends predefined data structures (e.g., sensor data, command packets).
- Each mail object has fixed size, allocated from a memory pool.
- Data is stored in FIFO order (or priority if supported).

### 1.2. Why do we need Mail Queue?

- Structured data exchange: Allows sending complex data (struct) instead of single variables.
- Task synchronization: A producer task allocates and sends mail, while a consumer task waits to receive it.
- Memory management: The RTOS handles allocation and deallocation of mail blocks.
- Decoupling: Sender and receiver do not need to run at the same speed.

### 1.3 How it works

- **a. Create a mail queue** → Allocate a memory pool for N mail objects (osMailCreate).
- **b. Allocate mail**
  - Task calls osMailAlloc() or osMailCAlloc() to get a free mail block.
  - Fill the mail object with data.
- **c. Send (put) mail**
  - Task calls osMailPut() to send mail into the queue.
  - If queue is full → block or return error.
- **d. Receive (get) mail**
  - Task calls osMailGet() to receive a mail.
  - Process the data, then free the mail block with osMailFree().
- **e. Delete mail queue** → Release memory when no longer needed.

### 1.4. API

| **CMSIS-RTOS**   | **FreeRTOS (equivalent)** | **Explanation**                                                                                  |
| ---------------- | ------------------------- | ------------------------------------------------------------------------------------------------ |
| `osMailCreate()` | No direct equivalent      | Creates a mail queue with memory pool. FreeRTOS does not have built-in mail queues (use queues). |
| `osMailAlloc()`  | `pvPortMalloc()`          | Allocates a mail block (uninitialized).                                                          |
| `osMailCAlloc()` | `pvPortCalloc()`          | Allocates a mail block (zero-initialized).                                                       |
| `osMailPut()`    | `xQueueSend()`            | Sends a mail block pointer into the queue.                                                       |
| `osMailGet()`    | `xQueueReceive()`         | Receives a mail block pointer from the queue.                                                    |
| `osMailFree()`   | `vPortFree()`             | Frees the memory block after processing.                                                         |
| `osMailDelete()` | —                         | Deletes a mail queue and its memory pool.                                                        |

## 2. Example 

- [Source](Example1/main.c)
  
