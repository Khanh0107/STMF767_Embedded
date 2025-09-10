# Task

## 1. Introduction

- A task is a unit of execution (a piece of code or function) that performs a specific job.
- Only 1 task executes at a time, because a single core can fetch, decode, and execute only one instruction stream at once.

## 2. Task States

- 1. Running 
  - The task is currently being executed on the CPU.
  - Only one task per core can be in this state at any moment.
- 2. Ready 
  - The task is ready to run (has all resources) but the CPU is busy with another task.
  - Tasks in this state are waiting for the scheduler to give them CPU time.
  - If a higher priority task becomes ready, it can preempt (take over) the running task.
- 3. Blocked 
  - The task is waiting for something to happen before it can continue:
  - Example: waiting for a delay (vTaskDelay()), waiting for a queue, semaphore, or event.
  - Once the resource/event becomes available → the task goes back to Ready state.
- 4. Suspended 
  - The task is manually suspended by calling vTaskSuspend().
  - It will not run until explicitly resumed with vTaskResume().
  - Difference from Blocked:
    - Blocked: waiting automatically for a resource/event.
    - Suspended: paused manually by the programmer.
   
<img width="638" height="480" alt="image" src="https://github.com/user-attachments/assets/b7825de5-5f23-4b8d-89dd-47a70354b1d0" />

## 3. Scheduling

- Each task is assigned a priority level. The RTOS always selects the highest priority task that is ready to run.
- If a new task with a higher priority becomes ready while a lower priority task is running, the RTOS will pause (preempt) the running task and switch execution to the higher priority task.
- The RTOS uses a priority queue for tasks that are ready to run. Whenever the scheduler makes a decision, it picks the task with the highest priority from the ready queue and executes it

## 4. API 

**Task Management API: CMSIS-RTOS vs FreeRTOS**

| **Feature**                | **CMSIS-RTOS API**     | **FreeRTOS API**          |
|-----------------------------|------------------------|----------------------------|
| Define task attribute       | `osThreadDef`          | `osThreadDef_t`            |
| Create task                 | `osThreadCreate`       | `xTaskCreate`              |
| Terminate task              | `osThreadTerminate`    | `vTaskDelete`              |
| Yield task                  | `osThreadYield`        | `taskYield`                |
| Delay task                  | `osDelay`              | `vTaskDelay`               |
| Get task ID                 | `osThreadGetId`        | `xTaskGetCurrentTaskHandle`|
| Set task priority           | `osThreadSetPriority`  | `vTaskPrioritySet`         |
| Get task priority           | `osThreadGetPriority`  | `uxTaskPriorityGet`        |
| Suspend task                | `osThreadSuspend`      | `vTaskSuspend`             |
| Suspend all tasks           | `osThreadSuspendAll`   | `vTaskSuspendAll`          |
| Resume task                 | `osThreadResume`       | `vTaskResume`              |
| Resume all tasks            | `osThreadResumeAll`    | `xTaskResumeAll`           |
| Get state of task           | `osThreadState`        | `eTaskGetState`            |
| List current tasks info     | `osThreadList`         | `vTaskList`                |
| Delay task until time       | `osDelayUntil`         | `vTaskDelayUntil`          |

## 5. Demo 

### 5.1 Example 1: The task with higher priority runs first.

- Task 1: priority 3 OsDelay(1000)
- Task 2: priority 2 OsDelay(1000)
- [Source code](Example_1/main.c) 
- Output: Task 1 always run before Task 2

<img width="499" height="185" alt="image" src="https://github.com/user-attachments/assets/77ff4639-b851-4cc2-9970-c975260b3b48" />

### 5.2. Example 2: If the one with higher priority is not blocked or stopped by some mechanism → it will always run → kernel

- Task 1: priority 3 
- Task 2: priority 2 OsDelay(1000)
- [Source code](Example_2/main.c) 
- Output: Run Task 1 only

<img width="385" height="233" alt="image" src="https://github.com/user-attachments/assets/6ffaa1bb-6ed1-4a02-b706-14cc707874c7" />

### 5.3 See the states of the task

- Task 1: priority 3 OsDelay(5000)
- Task 2: priority 2 OsDelay(1000)
- [Source code](Example_3/main.c) 
- Output: See states of 2 task

<img width="1036" height="147" alt="image" src="https://github.com/user-attachments/assets/317fd17d-bf04-413a-858c-1f4d5c67be23" />

<img width="328" height="195" alt="image" src="https://github.com/user-attachments/assets/d3ef184a-36e8-4b1e-bad7-653ea830c8bc" />



