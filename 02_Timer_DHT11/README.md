# 1. Timer

- Timer is a hardware peripheral inside the microcontroller (MCU) used to measure time or count events based on a clock signal. 
- Timers are essential because many embedded applications require precise timing without overloading the CPU.

- A typical MCU timer includes:
  - Counter register (CNT): Holds the current count value.
  - Prescaler (PSC): Divides the input clock to slow down counting.
  - Auto-reload register (ARR): Defines the maximum value before the counter resets.

- A timer is a counter that operates independently of the CPU. After every time interval t (this interval can be configured), the value of the timer’s **CNT register** increases by one. When the counter value equals the value in the **ARR register**, the counter rolls back to zero, and at the same time, the program generates an update interrupt.

**System Clock (SYSCLK)**

- The system clock is the main clock source driving the entire microcontroller, including CPU, peripherals, and timers. (ex: HSI is an internal RC oscillator built into the microcontroller, HSE is an external crystal or oscillator connected to the microcontroller pins)

**Timer Clock**

- The timer clock is the clock source that feeds a specific timer peripheral.

**Prescaler (PSC)**

- The prescaler slows down the timer clock to achieve the desired timing resolution.
- Formula:

    $f_\text{timer counter} = \frac{f_\text{timer clock}}{PSC + 1}$

**Auto-Reload Register (ARR)**

- The auto-reload register (ARR) defines the maximum value the timer counter will count up to before it resets.
  
	​
**Counter Register (CNT)**

- The counter register (CNT) stores the current count value of the timer.
- It increments (or decrements in down-count mode) based on the timer counter frequency (after prescaler).
- When CNT reaches ARR, it resets to 0.
- Reading CNT lets you measure elapsed time or detect when an event occurs.

# 2. Read data from DHT11 sensor.

## 2.1. What is DHT sensor
- DHT11 Temperature & Humidity Sensor features a temperature & humidity sensor
- Datasheet: [link](https://www.alldatasheet.com/datasheet-pdf/download/2193416/OSEPP/DHT11.html)

## 2.2 Hardware connection

<img width="622" height="427" alt="image" src="https://github.com/user-attachments/assets/780cb42d-1aaf-4bb5-b1b5-dfa74af54700" />

| DHT11 Pin | Chức năng       | STM32 Pin  |
|---------|-----------------|-------------------|
| VSS     | GND             | GND               |
| VDD     | +3.3V           | 3.3V                |
| Data    | Transmit and received data        | PA4 |

- Data consists of decimal and integral parts. A complete data transmission is 40bit, and the
sensor sends higher data bit first.

- Data format: 8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T
data + 8bit check sum. If the data transmission is right, the check-sum should be the last 8bit of
"8bit integral RH data + 8bit decimal RH data + 8bit integral T data + 8bit decimal T data".

## 2.2 Communication Process

**Overall communication**

<img width="832" height="280" alt="image" src="https://github.com/user-attachments/assets/d00794b4-458e-47e7-8367-7384ce179b84" />

**MCU Sends out Start Signal to DHT**

<img width="760" height="265" alt="image" src="https://github.com/user-attachments/assets/a8d3479b-81f9-4741-92f0-8040b58dc461" />

**DHT Responses to MCU**

- If bit data = 0

<img width="750" height="410" alt="image" src="https://github.com/user-attachments/assets/28a581b1-941c-4f25-ad6f-33836c078c00" />

- If bit data = 1

<img width="755" height="363" alt="image" src="https://github.com/user-attachments/assets/e3913b7f-cb0b-4dd9-a0f0-612ff7feba1f" />

