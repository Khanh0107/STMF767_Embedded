# Message Queue 

## 1. What is message queue 

### 1.1 Introduction
- A Message Queue in RTOS is an inter-task communication mechanism that allows tasks (or ISRs) to exchange data in the form of messages.
  - Messages are stored in FIFO (First In – First Out) order (though priority queues can also be implemented).
  - Each message can contain data (e.g., integers, structures, commands).

## 1.2. Why do we need Message Queue?

- **Task synchronization**: A producer task sends data, a consumer task waits for it.
  - **Safe data exchange**: No need for global variables + mutex.
  - **Buffering**: Messages are stored until the receiving task is ready.
  - **Decoupling**: Sender and receiver don’t need to run at the same speed.
 
### 1.3 How it works

1. **Create a queue** → Allocate memory buffer to hold N messages `osMessageCreate`.
2. **Send (enqueue) a message**
  - Task or ISR calls `xQueueSend()` / `osMessageQueuePut()`.
  - If queue is full → block / return error.
3. **Receive (dequeue) a message**
  - Task calls `xQueueReceive()` / `osMessageQueueGet()`.
  - If queue is empty → block / return error.
4. **Delete queue** → Release memory when no longer needed.

### 1.4. API

| **CMSIS-RTOS**       | **FreeRTOS**                                                                                | **Explanation**                                                                                                                            |
| -------------------- | ------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------ |
| `osMessageCreate()`  | `xQueueCreate()` <br> `xQueueCreateStatic()`                                                | Creates a message queue. In FreeRTOS, you can use **dynamic allocation** (`xQueueCreate`) or **static allocation** (`xQueueCreateStatic`). |
| `osMessagePut()`     | `xQueueSend()` <br> `xQueueSendFromISR()`                                                   | Sends (puts) a message into the queue. The ISR version (`xQueueSendFromISR`) is used inside an interrupt.                                  |
| `osMessageGet()`     | `xQueueReceive()` <br> `xQueueReceiveFromISR()`                                             | Receives (gets) a message from the queue. The ISR version is safe to use inside interrupts.                                                |
| `osMessageDelete()`  | `vQueueDelete(queue_handler)`                                                               | Deletes a queue and frees its resources.                                                                                                   |
| `osMessageWaiting()` | `uxQueueMessagesWaiting(queue_handler)` <br> `uxQueueMessagesWaitingFromISR(queue_handler)` | Returns the number of messages currently stored in the queue. Helps check if data is pending.                                              |

## 2. Example 

- Send data from task 1 and receive data from task 2
- [Code](Example/main.c)
- Output:

<img width="306" height="174" alt="image" src="https://github.com/user-attachments/assets/7beedad1-2236-4c32-bb93-224e9bbf043b" />
