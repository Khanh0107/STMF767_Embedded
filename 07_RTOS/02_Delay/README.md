# Delay

## 1. Hal_Delay 

- From HAL library (stm32fxxx_hal.c).
- Implementation: it busy-waits using SysTick until the delay time is over.
- While waiting, the **CPU is blocked** → it does **nothing else**.
- Suitable for bare-metal (no RTOS) projects.

## 2. osdelay

- From CMSIS-RTOS API (used with FreeRTOS or RTX).
- Implementation: it tells the RTOS scheduler to **suspend the current task** for a given time.
- While the task is delayed, the **CPU is free** to run other ready tasks.
- Much more efficient in multitasking systems.

