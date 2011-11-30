/*	=================================================================
	Filename:			LCD.c
	Author:				Corey Davyduke
	Creation date:		2011-11-28
	Last modified date:	2011-11-29
	Description:		This file contains the source code to talk to
	the LCD display.
	=================================================================
*/


/* The LCD I/O registers are represented by a volatile array.
   Address is fixed at link time.  For this particular example,
   the _gdm_lcd_*** addresses are defined in the `memory.x' file.  */
extern volatile unsigned char _gdm_lcd_cmd;
extern volatile unsigned char _gdm_lcd_data;

int main ()
{
    LCD_Init();
    LCD_WriteMessage("Hello, world!");

	return 0;
}

void LCD_Init()
{
    LCD_DisplayFunction();
    LCD_DisplayOn_CursorAndBlinkOn();
    LCD_CursorIncrement_ShiftOff();

    LCD_Clear();
}

// Clear display, cursor to home
void LCD_Clear()
{
    LCD_Command(0x01);
}

void LCD_CursorHome()
{
    LCD_Command(0x02);
}

void LCD_CursorDecrement_ShiftOff()
{
    LCD_Command(0x04);
}

void LCD_CursorDecrement_ShiftOn()
{
    LCD_Command(0x05);
}

void LCD_CursorIncrement_ShiftOff()
{
    LCD_Command(0x06);
}

void LCD_CursorIncrement_ShiftOn()
{
    LCD_Command(0x07);
}

// Display, cursor and blink off
void LCD_DisplayOff()
{
    LCD_Command(0x08);
}

void LCD_DisplayOn_CursorAndBlinkOff()
{
    LCD_Command(0x0c);
}

void LCD_DisplayOn_CursorOnBlinkOff()
{
    LCD_Command(0x0e);
}

void LCD_DisplayOn_CursorAndBlinkOn()
{
    LCD_Command(0x0f);
}

void LCD_Cursor_ShiftLeft()
{
    LCD_Command(0x10);
}

void LCD_Cursor_ShiftRight()
{
    LCD_Command(0x14);
}

void LCD_Display_ShiftLeft()
{
    LCD_Command(0x18);
}

void LCD_Display_ShiftRight()
{
    LCD_Command(0x1c);
}

// Display Function (default 2x40 size)
void LCD_DisplayFunction()
{
    LCD_Command(0x3c);
}

// Write a string to the LCD display
void LCD_WriteMessage(char *szMessage)
{
    while(*szMessage) LCD_Write(*szMessage++);
}

// Issue a command to the LCD command register
void LCD_Command(unsigned char cval)
{
    LCD_Busy();                     // Wait for busy to clear
    _gdm_lcd_cmd = cval;            // Ouptut command
}

// Write a character to the LCD data register
void LCD_Write(char dval)
{
    LCD_Busy();                     // Wait for busy to clear
    _gdm_lcd_data = dval;           // Output character
}

// Wait for the LCD busy pin to clear
void LCD_Busy()
{
    while (_gdm_lcd_cmd & 0x80);
}
