#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define F_CPU 1000000L
#define LCD_DDR DDRD

#define LCD_PORT PORTD
#define LCD_RS 0
#define LCD_EN 1

#define LCD_DATA PORTB
#define LCD_RW 4

void lcdCmd(unsigned char cmd)
{
	LCD_DATA = cmd;
	PORTD &= ~(_BV(LCD_RS));
	PORTD &= ~(_BV(LCD_RW));
	PORTD |= _BV(LCD_EN);
	_delay_ms(100);
	PORTD &= ~(_BV(LCD_EN));
	return;
}

void lcdWrite(unsigned char data)
{
	LCD_DATA = data;
	PORTD |= _BV(LCD_RS);
	PORTD &= ~(_BV(LCD_RW));
	PORTD |= _BV(LCD_EN);
	_delay_ms(100);
	PORTD &= ~(_BV(LCD_EN));
	return;
}

void lcdInit()
{
	lcdCmd(0x38);
	_delay_ms(100);
	lcdCmd(0x01);
	_delay_ms(100);
	lcdCmd(0x02);
	_delay_ms(100);
	lcdCmd(0x06);
	_delay_ms(100);
	lcdCmd(0x80);
	_delay_ms(100);
	lcdCmd(0x0E);
	_delay_ms(100);
	return;
}

void lcdSendText(unsigned char *text, int length)
{
	for(int8_t i = 0; i<length; i++)	lcdWrite(text[i]);
	return;
}


int main(void)
{
	unsigned char imie[]={'L','U','K','A','S','Z', ' ', 'O'};
	unsigned char znaczki[]={11111111, 11110101, 00110011, 11001100};
	char key;
	lcdInit();
	lcdSendText(imie, 8);
	lcdCmd(0xC0); 
	_delay_ms(100);
	lcdSendText(znaczki, 4);

	while (1)
	{
   		if(key != 'a') fgets(key, 1, stdin);
		if(key == 'a') lcdCmd(0x1C);
	}
}

