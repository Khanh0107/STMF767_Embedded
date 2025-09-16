#  Binary Semaphore - Mutex RTOS

## 1. Difference between Binary Semaphore - Mutex RTOS

| **Aspect**               | **Binary Semaphore**                                                                                               | **Mutex**                                                                                                    |
| ------------------------ | ------------------------------------------------------------------------------------------------------------------ | ------------------------------------------------------------------------------------------------------------ |
| **Purpose**              | Used for **signaling** between tasks/ISR (e.g., "event happened").                                                 | Used for **mutual exclusion** to protect shared resources (critical section).                                |
| **Ownership**            | No ownership → any task/ISR can give or take it.                                                                   | Has ownership → only the task that *takes* the mutex can *release* it.                                       |
| **Initial State**        | Can be created as "available" or "taken".                                                                          | Always created in "available" state.                                                                         |
| **Priority Inheritance** | ❌ Not supported. If a low-priority task holds it, high-priority tasks may be blocked (priority inversion risk).    | ✅ Supported. The task holding the mutex can inherit higher priority temporarily to avoid priority inversion. |
| **Typical Use Case**     | - Synchronize task with ISR (e.g., button interrupt wakes up a task). <br> - Simple event signaling between tasks. | - Protect shared peripherals (UART, I2C, SPI). <br> - Protect global variables or data structures.           |
| **Analogy**              | "Notification flag" → task waits until another signals it.                                                         | "Key to a room" → only one person can enter at a time, must give key back.                                   |

## 2. Example 

### 2.1. Semaphore have not ownership:

 ```c
void StartTask01(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	mPrint("cnt semaphore: %d\n", osSemaphoreGetCount(myBinarySem01Handle));
  while(1)
  {
		// Gui data vao queue 
		osSemaphoreWait(myBinarySem01Handle,osWaitForever);
		mPrint("Task 1 is running\n");
		osDelay(1000);
  }
  /* USER CODE END 5 */
}

void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
	
	mPrint("cnt semaphore: %d\n", osSemaphoreGetCount(myBinarySem01Handle));
  while(1)
  {
		//Nhan data
		mPrint("Task 2 is running\n");
		osSemaphoreRelease(myBinarySem01Handle);
    	osDelay(1000);
  }
  /* USER CODE END StartTask02 */
}
```

- Output:

<img width="197" height="124" alt="image" src="https://github.com/user-attachments/assets/9dd1ded2-79f9-4ef9-a3e1-bb00cae551d0" />

- Explain:

**Task 1:**

- Prints the current semaphore count at the start.
- Inside the loop:
- Calls osSemaphoreWait() → tries to take the semaphore.
	- If the semaphore count is 0, Task1 will block until another task releases it.
	- If the count is > 0, the count is decreased and Task1 continues.
- Prints "Task 1 is running".
- Delays 1 second.
✅ This means Task1 only runs when Task2 (or someone else) signals it by releasing the semaphore.

**Task 2:**

- Prints the current semaphore count at the start.
- Inside the loop:
- Prints "Task 2 is running".
- Calls osSemaphoreRelease() → gives the semaphore.
	- This increases the semaphore count by 1.
	- If Task1 is waiting, it will be unblocked immediately.
- Delays 1 second.
✅ So Task2 is like a producer / signaler. It keeps releasing the semaphore, allowing Task1 to wake up.

### 2.2. Mutex have ownership:

```c
void StartTask01(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
	//mPrint("cnt semaphore: %d\n", osSemaphoreGetCount(myBinarySem01Handle));
  while(1)
  {
		osMutexWait(myMutex01handle,osWaitForever);
		mPrint("Task 1 is running\n");
		osDelay(1000);   
  }
  /* USER CODE END 5 */
}

void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
	
	//mPrint("cnt semaphore: %d\n", osSemaphoreGetCount(myBinarySem01Handle));
  while(1)
  {
		//Nhan data
		mPrint("Task 2 is running\n");
		osMutexRelease(myMutex01handle);
    	osDelay(1000);
  }
  /* USER CODE END StartTask02 */
}
```

- **Output:**

<img width="215" height="55" alt="image" src="https://github.com/user-attachments/assets/c11d9151-6028-447d-a406-1e32920b6eb5" />

- **Explain:**

**Task1**

- Waits (locks) the mutex.
- Once it gets the mutex, it prints "Task 1 is running".
-Then it delays for 1 second.
- ⚠️ Problem: It never releases the mutex (osMutexRelease() is missing).
- That means Task1 will hold the mutex forever, blocking any other task that tries to take it.

**Task2**

- Prints "Task 2 is running".
- Then it calls osMutexRelease() without ever calling osMutexWait() first.
- Releasing a mutex you don’t own is invalid.
	- In some RTOS implementations, this is ignored.
	- In others, it may cause an error.
- So Task2 is not really controlling the mutex at all.
