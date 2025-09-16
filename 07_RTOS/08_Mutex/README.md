# Mutex

## 1. What is Mutex

### 1.1 Introduction

- A Mutex (Mutual Exclusion) is a synchronization object used to protect shared resources in RTOS.
- Ensures that only one task at a time can access a critical section (e.g., global variable, peripheral).
- Similar to a binary semaphore, but with additional features for ownership and priority inheritance (helps prevent priority inversion).

### 1.2 Why do we need Mutex?

- **Prevent race conditions** → Only one task accesses shared resource at a time.
- **Ownership tracking** → Mutex knows which task owns it (unlike semaphore).
- **Priority inheritance** → If a high-priority task is waiting, the low-priority task holding the mutex temporarily inherits higher priority to avoid blocking.
- **Safe resource sharing** → Useful for peripherals (UART, I2C, SPI) or shared memory.

### 1.3 How it works

- **a. Create a mutex** → allocate memory & initialize. `osMutexDef()` and `osMutexCreate()`
- **b. Lock (take) mutex**
  - If mutex is free → task acquires ownership. `osMutexWait()`
  - If mutex is taken → task will block (or return error if non-blocking).
- **c. Unlock (give) mutex** → releases resource and wakes up waiting tasks. `osMutexRelease()`
- **d. Delete mutex** → free resources if not needed anymore. `osMutexDelete()`

### 1.4 API 

| **CMSIS-RTOS**     | **FreeRTOS**                                                      | **Explanation**                                            |
| ------------------ | ----------------------------------------------------------------- | ---------------------------------------------------------- |
| `osMutexDef()`     | *(not required in FreeRTOS)*                                      | Defines a mutex object (macro, used with `osMutexCreate`). |
| `osMutexCreate()`  | `xSemaphoreCreateMutex()` <br> `xSemaphoreCreateRecursiveMutex()` | Creates a mutex (normal or recursive).                     |
| `osMutexWait()`    | `xSemaphoreTake()` <br> `xSemaphoreTakeFromISR()`                 | Task tries to take (lock) mutex. Blocks if not available.  |
| `osMutexRelease()` | `xSemaphoreGive()` <br> `xSemaphoreGiveFromISR()`                 | Releases mutex. Wakes up waiting task if any.              |
| `osMutexDelete()`  | `vSemaphoreDelete()`                                              | Deletes mutex and frees resources.                         |

## 2. Example 

[Source code](Example/main.c)

- Output:

<img width="201" height="244" alt="image" src="https://github.com/user-attachments/assets/5f7c22c0-d8f7-457f-810e-f0ab58b1d28e" />
