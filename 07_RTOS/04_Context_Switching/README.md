# Context Switching 

## 1. What is context switching

- In an RTOS, context switching is the process of saving the current task’s CPU context (registers, stack pointer, program counter, etc.) and restoring another task’s context so that the CPU can continue running the new task as if it had never been interrupted.
- This allows multiple tasks to share a single processor while still meeting real-time constraints.

### 1.1 PendSV (Pending Supervisor Call)

- A special exception available on ARM Cortex-M cores.
- Specifically designed to handle context switching in RTOS.
  
👉 PendSV = a software interrupt dedicated for task switching.

### 1.2. SysTick

- A hardware timer built into Cortex-M.
- In FreeRTOS, configured to generate periodic interrupts (e.g., every 1ms).
- On every SysTick interrupt:
  - FreeRTOS increments the tick count.
  - Checks whether any tasks with delay/timeout are ready to run.
  - If yes → request a context switch by triggering PendSV.

👉 SysTick = the clock/alarm that tells the RTOS when to switch.

👉 PendSV = the worker that actually performs the switch.

### 1.3. vTaskSwitchContext()

- A core function in the FreeRTOS scheduler.
- It doesn’t switch tasks directly. Instead, it:
  - Scans the ready list.
  - Picks the highest-priority task that should run.
  - Updates pxCurrentTCB to point to the new task’s TCB.

👉 The real register/stack switch is still done inside PendSV.

### 1.4. pxCurrentTCB

- A global pointer inside FreeRTOS.
- Always points to the Task Control Block (TCB) of the currently running task.

## 2. Example 

<img width="762" height="398" alt="image" src="https://github.com/user-attachments/assets/a37e46a4-e5db-4518-ab96-cf979ea362bf" />

**CPU running Task 1**

- Task 1 code at address 0xAF200
  - Local vars: a, b, c, d in STACK1 (e.g., a at 0xAC800).
- CPU registers:
  - PC = 0xAF20C → CPU is currently executing inside Task 1.
  - SP = 0xAC800 → points to Task 1’s stack frame.
- TCB1:
  - Holds Task 1’s state (PC=0xAF20C, SP=0xAC800, plus R0–R12).
- TCB2: not active yet, just waiting with initial values.

👉 CPU is executing Task 1. Task 2 is inactive.

<img width="751" height="404" alt="image" src="https://github.com/user-attachments/assets/16dcde99-6999-40b5-81a3-4fd0f020d4f8" />

**Context Switch Triggered**

- A SysTick/PendSV interrupt fires → RTOS needs to switch tasks.
- Step 1: Save Task 1’s context
  CPU pushes registers (R0–R12, LR, PC, xPSR) onto Task 1’s STACK1.
  - RTOS saves Task 1’s SP and PC into TCB1.
- Step 2: Load Task 2’s context
  - RTOS reads Task 2’s saved SP and PC from TCB2.
  - These values are loaded into CPU registers.

👉 At this moment, CPU has “paused” Task 1 and is preparing to run Task 2.

<img width="763" height="405" alt="image" src="https://github.com/user-attachments/assets/3954d235-819b-4c6e-adde-e4376e6d68eb" />

**CPU running Task 2**

- Task 2 code at address 0xAD200
  -Local vars: e, f, g, h in STACK2 (e.g., e at 0xAC700).
- CPU registers:
  - PC = 0xAD200 → CPU now executing Task 2 instructions.
  - SP = 0xAC700 → points to Task 2’s stack frame.
- TCB2: updated with Task 2’s running state.
- TCB1: still holding Task 1’s context (PC=0xAF20C, SP=0xAC800).

👉 CPU is now executing Task 2. Task 1 is fully paused but safe in TCB1.

**Example** :pointer **pxCurrentTCB** in task 2

<img width="485" height="317" alt="image" src="https://github.com/user-attachments/assets/2e5bcaab-7a77-4395-8633-462d2927cd73" />


