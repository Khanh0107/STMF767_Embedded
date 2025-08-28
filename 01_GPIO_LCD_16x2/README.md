# 1. Overview 

- Controlling a 16x2 character LCD (based on the popular HD44780 controller) using the STM32F767 microcontroller through GPIO pins is a fundamental project in embedded systems development.
- This setup allows displaying text, numbers, and basic symbols on the LCD without the need for additional communication modules like I²C or SPI.
- Data sheet of LCD : [Data sheet](https://cdn-shop.adafruit.com/datasheets/TC1602A-01T.pdf)
- Create LCD  library 

# 2. Hardware connection
| LCD Pin | Chức năng       | STM32 Pin (ví dụ) |
|---------|-----------------|-------------------|
| VSS     | GND             | GND               |
| VDD     | +5V             | 5V                |
| V0      | Contrast        | Biến trở 10k → GND/5V |
| RS      | Register Select | PB0               |
| RW      | Read/Write      | PB1               |  
| E       | Enable          | PB10              |
| D4      | Data Bit 0      | PA0               |
| D5      | Data Bit 1      | PA1               |
| D6      | Data Bit 2      | PA2               |
| D7      | Data Bit 3      | PA3               |
| D4      | Data Bit 4      | PA4               |
| D5      | Data Bit 5      | PA5               |
| D6      | Data Bit 6      | PA6               |
| D7      | Data Bit 7      | PA7               |
| A/K     | LED Backlight   | +5V / GND         |

- **Create mapping in Altium STM32F7 vs TC1602A-01T**

## Step to init LCD 

- The initial procedure

<img width="632" height="616" alt="image" src="https://github.com/user-attachments/assets/b62e3bc9-d5f0-4ce8-9be6-c6dcb9acba9e" />


- Write timing diagram

<img width="632" height="616" alt="image" src="https://github.com/user-attachments/assets/0e40c226-f272-447a-92ed-021ff4e6122d" />


- The commands for HD44780 chip in this [HD44780](http://www.dinceraydin.com/lcd/commands.htm)
