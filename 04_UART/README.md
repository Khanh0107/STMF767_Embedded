# 1. UART (Universal Asynchronous Receiver/Transmitter)

## 1.1 What is UART?
- UART (**Universal Asynchronous Receiver/Transmitter**) is a hardware communication protocol used for serial communication between two devices. It is widely used in embedded systems, microcontrollers, and computers to exchange data without the need for a clock signal.
- UART is **full-duplex**, is a communication mode where data can travel in both directions, but only one direction at a time

| Mode            | Direction of Data Flow            | Example                            |
| --------------- | --------------------------------- | ---------------------------------- |
| **Simplex**     | One-way only                      | Radio broadcast (you only receive) |
| **Half-duplex** | Both ways, but not simultaneously | Walkie-talkies ("push to talk")    |
| **Full-duplex** | Both ways, simultaneously         | Phone calls                        |


- UART is a **serial** protocol, meaning that data is transmitted one bit at a time in a sequential stream.
- UART is **asynchronous** (means that data is sent without a shared clock signal between the sender and the receiver), and its speed (Baud Rate) is the rate at which data is transmitted, measured in bits per second. Common baud rates are 9600, 115200, etc.
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
| **Start Bit** | transmitting UART pulls the transmission line from high to low for one (1) clock cycle |
| **Data Frame** | It can be five (5) bits up to eight (8) bits long if a parity bit is used. If no parity bit is used, the data frame can be nine (9) bits long |
| **Parity** | After the receiving UART reads the data frame, it counts the number of bits with a value of 1 and checks if the total is an even or odd number. If the parity bit is a 0 (even parity), the 1 or logic-high bit in the data frame should total to an even number. If the parity bit is a 1 (odd parity), the 1 bit or logic highs in the data frame should total to an odd number. |
| **Stop Bits** |the sending UART drives the data transmission line from a low voltage to a high voltage for one (1) to two (2) bit(s) duration. |

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

| CH340 Driver  | Function       | STM32 Pin  |
|---------|-----------------|-------------------|
| TX     | Transmit and receive data               | PA2/RX               |
| RX     | Transmit and receive data            | PA3/TX                |
| GND    | Ground        | GND |
| LED +-    | On off led        | PA4/ GND |

**Configure in STMcube**
  
<img width="688" height="592" alt="image" src="https://github.com/user-attachments/assets/19a2aae2-fa2d-4e46-b193-27c8d7daf1c5" />

<img width="692" height="43" alt="image" src="https://github.com/user-attachments/assets/49d3e36b-c3d8-4272-96d9-1308f20ca5f5" />

**Output**
- Press a then Led ON
- 
  <img width="623" height="537" alt="image" src="https://github.com/user-attachments/assets/ef8508ea-4268-406e-b1d7-67918c2b91c2" />

- eles Led off






