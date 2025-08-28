# 1. Overview 

- Controlling a 16x2 character LCD (based on the popular HD44780 controller) using the STM32F767 microcontroller through GPIO pins is a fundamental project in embedded systems development.
- This setup allows displaying text, numbers, and basic symbols on the LCD without the need for additional communication modules like I²C or SPI.
- Data sheet of LCD : [Data sheet](https://cdn-shop.adafruit.com/datasheets/TC1602A-01T.pdf)


# 2. Hardware connection
| LCD Pin | Chức năng       | STM32 Pin (ví dụ) |
|---------|-----------------|-------------------|
| VSS     | GND             | GND               |
| VDD     | +5V             | 5V                |
| V0      | Contrast        | Biến trở 10k → GND/5V |
| RS      | Register Select | PD0               |
| RW      | Read/Write      | GND (chỉ ghi)     |
| E       | Enable          | PD1               |
| D4      | Data Bit 4      | PD4               |
| D5      | Data Bit 5      | PD5               |
| D6      | Data Bit 6      | PD6               |
| D7      | Data Bit 7      | PD7               |
| A/K     | LED Backlight   | +5V / GND         |

- **Create mapping in Altium STM32F7 vs TC1602A-01T**

# Step to init LCD 

- The initial procedure

![alt text](image-3.png)

- Write timing diagram

![alt text](image-2.png)

- The commands for HD44780 chip in this [HD44780](http://www.dinceraydin.com/lcd/commands.htm)
