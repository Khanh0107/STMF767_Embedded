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

- Semaphore have not ownership:

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


- Mutex have ownership:

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

- Output:

<img width="215" height="55" alt="image" src="https://github.com/user-attachments/assets/c11d9151-6028-447d-a406-1e32920b6eb5" />
