# I²C Protocol (Inter-Integrated Circuit)

## 1. Introduction
- **I²C (Inter-Integrated Circuit)** is a **synchronous serial communication protocol** 
- It allows communication between **microcontrollers (MCUs)** and **peripheral devices** (sensors, EEPROM, RTC, displays, ADC/DAC...) using only **two signal lines**.
- It supports **multi-master and multi-slave** operation.
- Half-duplex Communication Protocol
- Bi-directional communication is possible but not simultaneously.

## 2. Working Principle
- It uses only 2 bi-directional open-drain lines for data communication called SDA and SCL. 
  - Serial Data (SDA) : Transfer of data takes place through this pin.
  - Serial Clock (SCL) : It carries the clock signal.

- With I2C, data is transferred in messages. Messages are broken up into frames of data. Each message has an address frame that contains the binary address of the slave, and one or more data frames that contain the data being transmitted. The message also includes start and stop conditions, read/write bits, and ACK/NACK bits between each data frame:

<img width="1024" height="258" alt="image" src="https://github.com/user-attachments/assets/4b8bfa8d-37e3-44c8-bf57-53ddc82c8446" />

- **Start Condition:** The SDA line switches from a high voltage level to a low voltage level before the SCL line switches from high to low.
- **Stop Condition:** The SDA line switches from a low voltage level to a high voltage level after the SCL line switches from low to high.
- **Address Frame:** A 7 or 10 bit sequence unique to each slave that identifies the slave when the master wants to talk to it.
- **Read/Write Bit:** A single bit specifying whether the master is sending data to the slave (low voltage level) or requesting data from it (high voltage level).
- **ACK/NACK Bit:** Each frame in a message is followed by an acknowledge/no-acknowledge bit. If an address frame or data frame was successfully received, an ACK bit is returned to the sender from the receiving device.

<img width="767" height="222" alt="image" src="https://github.com/user-attachments/assets/d1187696-31b6-4323-b95e-10246a90242f" />


## 3. Read, write steps

### 3.1 Write steps

- Step 1: Master sends a **START condition** on the I²C bus.
- Step 2: Master sends the **7-bit slave address** followed by the **Write bit (0)**.
- Step 3: Master sends the **register address** (the location inside the slave where data will be written).
- Step 4: Master sends the **data byte(s)** to be written into the register specified in Step 3.
- Step 5: Master sends a **STOP condition** to release the bus.

Example : Write data 0x00 to register 0x6B of MPU6050 have address 0x68

```c
mData = 0x00;
HAL_I2C_Mem_Write(&hi2c1, 0x68<<1, 0x6B, 1, &mData, 1, 1000);
```

<img width="997" height="249" alt="image" src="https://github.com/user-attachments/assets/54df6619-26b4-4376-a5f3-2e97120e8b4a" />

### 3.2 Read steps

Step 1: Master sends a **START condition**.
Step 2: Master sends the **7-bit slave address** followed by the **Write bit (0)**.
Step 3: Master sends the **register address** (the location inside the slave to read from).
Step 4: Master sends a **Repeated START condition**.
Step 5: Master sends the **7-bit slave address** again, but this time followed by the **Read bit (1)**.
Step 6: Slave sends back the **data byte(s)** from the register specified in Step 3, and the master reads them.
  - Master usually sends **ACK** after each byte if it wants to continue reading.
  - For the **last byte**, master sends **NACK** to tell the slave to stop sending.
Step 7: Master sends a **STOP condition**.




