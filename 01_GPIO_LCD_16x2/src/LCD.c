#include "LCD.h"

LCD MyLCD;

void LCD_Write_Byte(uint8_t data, uint8_t mode){
    if(mode == 0x01){
        // data
        HAL_GPIO_WritePin(MyLCD.PORT_R, MyLCD.RS, 1);   // RS = 1
    }else if(mode == 0x00){
        // cmd
        HAL_GPIO_WritePin(MyLCD.PORT_R, MyLCD.RS, 0);   // RS = 0
    }
		
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D0,  (data & 0x01) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D1,  (data & 0x02) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D2,  (data & 0x04) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D3,  (data & 0x08) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D4,  (data & 0x10) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D5,  (data & 0x20) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D6,  (data & 0x40) ? 1 : 0);
		HAL_GPIO_WritePin(MyLCD.PORT_DATA, MyLCD.D7,  (data & 0x80) ? 1 : 0);

		HAL_GPIO_WritePin(MyLCD.PORT_R, MyLCD.En, 0);
		HAL_Delay(1);
		HAL_GPIO_WritePin(MyLCD.PORT_R, MyLCD.En, 1);
		HAL_Delay(1);
		HAL_GPIO_WritePin(MyLCD.PORT_R, MyLCD.En, 0);
		HAL_Delay(1);
}

void LCD_Write_data(uint8_t data) {
    LCD_Write_Byte(data, 1);
}

void LCD_Write_cmd(uint8_t data) {
    LCD_Write_Byte(data, 0);
}

void LCD_Print(char *str){
	while(*str){
		LCD_Write_data(*str++);
	}
}

void LCD_Init() {
		HAL_GPIO_WritePin(MyLCD.PORT_R, MyLCD.RW ,0);
    HAL_Delay(50);
    LCD_Write_cmd(0x38);   // Function set (8-bit interface, 2 lines, 5x7 Pixels)
    HAL_Delay(5);
    LCD_Write_cmd(0x0C);   // Display ON, Cursor OFF, Blink OFF
    HAL_Delay(5);
    LCD_Write_cmd(0x01);   // Clear display
    HAL_Delay(5);
    LCD_Write_cmd(0x06);   // Entry mode set: auto-increment, no shift
}

