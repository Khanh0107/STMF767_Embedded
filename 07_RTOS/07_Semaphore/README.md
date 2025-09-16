# Semaphore

## 1. What is Semaphore

### 1.1 Introduction

- A Semaphore in RTOS is a synchronization mechanism used to control access to shared resources among multiple tasks or between ISRs and tasks.
- It acts like a token or signal.
  - If a task takes (waits) a semaphore, the token is consumed.
  - If another task or ISR gives (releases) it, the token is returned.

### 1.2 Why do we need Semaphore?

- **Mutual Exclusion** (Mutex style): Prevents multiple tasks from accessing the same resource at the same time (e.g., UART, SPI, shared variable).
- **Task synchronization**: One task can signal another (e.g., ISR gives semaphore to unblock a task).
- **Resource management**: Limits access to a resource pool (like N buffers).

### 1.3 How it works

- **a. Create semaphore** → `osSemaphoreDef()` Initialize with count = 1 (binary) or count = N (counting).
- **b. Take (wait) semaphore**
  - Task calls `osSemaphoreWait()` 
  - If token available → task continues.
  - If not available → task blocks until timeout or semaphore released.

- **c. Give (release) semaphore**
  - Task or ISR calls `osSemaphoreRelease()`
  - Returns token → wakes up waiting task.
- **d. Delete semaphore** → Release memory if no longer used.

### 1.4 Types of Semaphore

- **Binary Semaphore** → Value = 0 or 1, used mainly for signaling between ISR and task.
- **Counting Semaphore** → Value = 0…N, used to manage multiple identical resources.
- **Mutex (special semaphore)** → Ensures only one task at a time uses a resource, supports priority inheritance.

### 1.5 API

| **CMSIS-RTOS (v1)**    | **FreeRTOS**                                                 | **Explanation**                                                      |
| ---------------------- | ------------------------------------------------------------ | -------------------------------------------------------------------- |
| `osSemaphoreDef()`     | *(no direct equivalent — FreeRTOS does not need macros)*     | Defines a semaphore object (used together with `osSemaphoreCreate`). |
| `osSemaphoreCreate()`  | `xSemaphoreCreateBinary()` <br> `xSemaphoreCreateCounting()` | Creates a semaphore (binary or counting).                            |
| `osSemaphoreWait()`    | `xSemaphoreTake()` <br> `xSemaphoreTakeFromISR()`            | Task/ISR tries to take (lock) semaphore. Blocks if not available.    |
| `osSemaphoreRelease()` | `xSemaphoreGive()` <br> `xSemaphoreGiveFromISR()`            | Releases semaphore. Wakes up waiting task if any.                    |
| `osSemaphoreDelete()`  | `vSemaphoreDelete()`                                         | Deletes semaphore and frees resources.                               |

## 2. Example 

[Source](Example/main.c)

