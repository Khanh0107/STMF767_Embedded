# 1. UART (Universal Asynchronous Receiver/Transmitter)

## 1.1 What is UART?
- UART (Universal Asynchronous Receiver/Transmitter) is a hardware communication protocol used for serial communication between two devices. It is widely used in embedded systems, microcontrollers, and computers to exchange data without the need for a clock signal.
- UART is half-duplex, meaning that data can only be transmitted in one direction at a time.
- UART is a serial protocol, meaning that data is transmitted one bit at a time in a sequential stream.
- UART is asynchronous, and its speed (Baud Rate) is the rate at which data is transmitted, measured in bits per second. Common baud rates are 9600, 115200, etc.
---

## 1.2. How UART Works
UART communication uses **two main lines**:
- **TX (Transmit)**: Sends data
- **RX (Receive)**: Receives data

The communication is **asynchronous**, meaning it does not require a clock line. Instead, both devices agree on:
- **Baud rate** (e.g., 9600, 115200 bps)
- **Data frame format** (data bits, parity bit, stop bits)



## 1.3. Common UART Parameters

<img width="1200" height="117" alt="image" src="https://github.com/user-attachments/assets/3d19fbb8-54b9-4b10-8bc2-022e2ed45dfb" />

| Parameter | Description |
|------------|-------------|
| **Baud Rate** | Speed of data transmission (bits per second) |
| **Data Frame** | Usually 8 bits, but can be 5–9 bits |
| **Parity** | Error detection method: None, Even, or Odd |
| **Stop Bits** | 1 or 2 bits marking the end of a frame |

**Basic data frame structure**
<img width="800" height="203" alt="image" src="https://github.com/user-attachments/assets/e1e6e1b2-940e-48c5-9bf0-a4836b3840ce" />

<img width="1296" height="128" alt="image" src="https://github.com/user-attachments/assets/4f2eb599-d40e-4000-b929-aa74b3f6c2c9" />

---

## 1.4. Advantages of UART
- Simple hardware and software
- Full-duplex communication
- Widely supported by microcontrollers and PCs

---

## 1.5. Disadvantages of UART
- Limited speed (compared to SPI or I²C)
- Only supports point-to-point communication (one transmitter and one receiver)
- Requires accurate baud rate matching

---


## 1.6. Difference Between UART and USART
| Feature | UART | USART |
|----------|-------|-------|
| **Communication** | Asynchronous only | Supports both synchronous and asynchronous |
| **Clock line** | Not required | Required for synchronous mode |
| **Flexibility** | Simpler and cheaper | More flexible, supports higher data rates |

---

# 2. UART in STM

## 2.1. Hardware connenection




