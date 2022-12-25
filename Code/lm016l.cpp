/*
 * lm016l.cpp
 *
 * Created: 02/12/2022 16.41.34
 *  Author: fisikamodern
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "lm016l.hpp"


//method outside the class
char* IntegerToString(int Value)
{
	char buff[255];
	char *string;

	itoa(Value,buff,10);

	string=buff;
	return string;
}
char* UIntegerToString(unsigned int Value)
{
	char buff[255];
	char *string;

	utoa(Value,buff,10);

	string=buff;
	return string;
}
char* LongToString(long Value)
{
	char buff[255];
	char *string;

	ltoa(Value,buff,10);

	string=buff;
	return string;
}
char* DoubleToString(double Value,int Range)
{
	char buff[255];
	char *string;
	
	dtostrf(Value,0,Range,buff);
	
	string=buff;
	return string;
}
char* CharToString(char c){
	char buff[255];
	char *string;
	
	sprintf(buff,"%c",c);
	string=buff;
	return string;
}

//private method
void lm016l::i2cwaitTWDRComplete(){
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
}
void lm016l::i2cInit(){
	//scl clock = 100k hz
	TWSR = 0;                        // -->Untuk menentukan frekuensi SCL
	TWBR = ((F_CPU/SCL_CLOCK)-16)/2; // -->Untuk menentukan frekuensi SCL
}
void lm016l::i2cStart(){
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //TWCR=10100100
	while((TWCR&(1<<TWINT))==0);
}
void lm016l::i2cAddress(unsigned int address){
	TWDR=address;
	lm016l::i2cwaitTWDRComplete();
}
void lm016l::i2cWrite(unsigned int port,unsigned int address){
	lm016l::i2cStart();
	lm016l::i2cAddress(address);
	TWDR=port;
	lm016l::i2cwaitTWDRComplete();
}

void lm016l::Delay()
{
	_delay_us(500);
}
void lm016l::command(unsigned char cmnd)
{
	if(lm016l::port == lcdUsingPD){
		PORTD = (PORTD & 0xF0) | (cmnd >> 4); 
		//MENGGESER NILAI DI BIT (7-4) MENJADI DI BIT (3-0) DAN BIT (7-4) NILAINYA (0 0 0 0)
		//CONTOH : cmnd=(0 0 1 0 1 0 0 0) BERUBAH MENJADI PORTA=(0 0 0 0 0 0 1 0)
		PORTD &= ~(1<<LCD_RW);  //HANYA RW=0
		PORTD &= ~(1<<LCD_RS);  //HANYA RS=0
		PORTD |=  (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTD &= ~(1<<LCD_EN);  //HANYA EN=0
		
		lm016l::Delay();
		
		PORTD = (PORTD & 0xF0) | (cmnd & 0X0F);
		//MENGUBAH NILAI DI BIT (7-4) MENJADI (0 0 0 0) DAN NILAI DI BIT (3-0) TETAP
		//CONTOH : cmnd=(0 0 1 0 1 0 0 0) BERUBAH MENJADI (0 0 0 0 1 0 0 0)
		PORTD |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTD &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::Delay();
	}
	if(lm016l::port == lcdUsingPB){
		PORTB = (PORTB & 0xF0) | (cmnd >> 4); 
		//MENGGESER NILAI DI BIT (7-4) MENJADI DI BIT (3-0) DAN BIT (7-4) NILAINYA (0 0 0 0)
		//CONTOH : cmnd=(0 0 1 0 1 0 0 0) BERUBAH MENJADI PORTA=(0 0 0 0 0 0 1 0)
		PORTB &= ~(1<<LCD_RW);  //HANYA RW=0
		PORTB &= ~(1<<LCD_RS);  //HANYA RS=0
		PORTB |=  (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTB &= ~(1<<LCD_EN);  //HANYA EN=0
		
		lm016l::Delay();
		
		PORTB = (PORTB & 0xF0) | (cmnd & 0X0F);
		//MENGUBAH NILAI DI BIT (7-4) MENJADI (0 0 0 0) DAN NILAI DI BIT (3-0) TETAP
		//CONTOH : cmnd=(0 0 1 0 1 0 0 0) BERUBAH MENJADI (0 0 0 0 1 0 0 0)
		PORTB |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTB &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::Delay();
	}
	if(lm016l::port == lcdUsingI2C){
		TWDR = (TWDR & 0xF0) | (cmnd >> 4); 
		//MENGGESER NILAI DI BIT (7-4) MENJADI DI BIT (3-0) DAN BIT (7-4) NILAINYA (0 0 0 0)
		//CONTOH : cmnd=(0 0 1 0 1 0 0 0) BERUBAH MENJADI PORTA=(0 0 0 0 0 0 1 0)
		TWDR &= ~(1<<LCD_RW);  //HANYA RW=0
		TWDR &= ~(1<<LCD_RS);  //HANYA RS=0
		TWDR |=  (1<<LCD_EN);  //HANYA EN=1
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
		TWDR &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
		
		TWDR = (TWDR & 0xF0) | (cmnd & 0X0F);
		//MENGUBAH NILAI DI BIT (7-4) MENJADI (0 0 0 0) DAN NILAI DI BIT (3-0) TETAP
		//CONTOH : cmnd=(0 0 1 0 1 0 0 0) BERUBAH MENJADI (0 0 0 0 1 0 0 0)
		TWDR |= (1<<LCD_EN);  //HANYA EN=1
		TWDR &= ~(1<<LCD_RW);  //HANYA RW=0
		TWDR &= ~(1<<LCD_RS);  //HANYA RS=0
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
		TWDR &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
	}
}
void lm016l::data(unsigned char dataInput)
{
	if(lm016l::port == lcdUsingPD){
		PORTD = (PORTD & 0xF0) | (dataInput >> 4); 
		//MENGGESER NILAI DI BIT (7-4) MENJADI DI BIT (3-0) DAN BIT (7-4) NILAINYA (0 0 0 0)
		//CONTOH : data=(0 0 1 0 1 0 0 0) BERUBAH MENJADI PORTA=(0 0 0 0 0 0 1 0)
		PORTD &= ~(1<<LCD_RW); //HANYA RW=0
		PORTD |= (1<<LCD_RS);  //HANYA RS=1
		PORTD |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTD &= ~(1<<LCD_EN);  //HANYA EN=0
		
		lm016l::Delay();
		
		PORTD = (PORTD & 0xF0) | (dataInput & 0x0F);
		//MENGUBAH NILAI DI BIT (7-4) MENJADI (0 0 0 0) DAN NILAI DI BIT (3-0) TETAP
		//CONTOH : data=(0 0 1 0 1 0 0 0) BERUBAH MENJADI (0 0 0 0 1 0 0 0)
		PORTD |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTD &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::Delay();
	}
	if(lm016l::port == lcdUsingPB){
		PORTB = (PORTB & 0xF0) | (dataInput >> 4); 
		//MENGGESER NILAI DI BIT (7-4) MENJADI DI BIT (3-0) DAN BIT (7-4) NILAINYA (0 0 0 0)
		//CONTOH : data=(0 0 1 0 1 0 0 0) BERUBAH MENJADI PORTA=(0 0 0 0 0 0 1 0)
		PORTB &= ~(1<<LCD_RW); //HANYA RW=0
		PORTB |= (1<<LCD_RS);  //HANYA RS=1
		PORTB |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTB &= ~(1<<LCD_EN);  //HANYA EN=0
		
		lm016l::Delay();
		
		PORTB = (PORTB & 0xF0) | (dataInput & 0x0F);
		//MENGUBAH NILAI DI BIT (7-4) MENJADI (0 0 0 0) DAN NILAI DI BIT (3-0) TETAP
		//CONTOH : data=(0 0 1 0 1 0 0 0) BERUBAH MENJADI (0 0 0 0 1 0 0 0)
		PORTB |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::Delay();
		PORTB &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::Delay();
	}
	if(lm016l::port == lcdUsingI2C){
		TWDR = (TWDR & 0xF0) | (dataInput >> 4); 
		//MENGGESER NILAI DI BIT (7-4) MENJADI DI BIT (3-0) DAN BIT (7-4) NILAINYA (0 0 0 0)
		//CONTOH : data=(0 0 1 0 1 0 0 0) BERUBAH MENJADI PORTA=(0 0 0 0 0 0 1 0)
		TWDR &= ~(1<<LCD_RW); //HANYA RW=0
		TWDR |= (1<<LCD_RS);  //HANYA RS=1
		TWDR |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
		TWDR &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
		
		TWDR= (TWDR & 0xF0) | (dataInput & 0x0F);
		//MENGUBAH NILAI DI BIT (7-4) MENJADI (0 0 0 0) DAN NILAI DI BIT (3-0) TETAP
		//CONTOH : data=(0 0 1 0 1 0 0 0) BERUBAH MENJADI (0 0 0 0 1 0 0 0)
		TWDR &= ~(1<<LCD_RW); //HANYA RW=0
		TWDR |= (1<<LCD_RS);  //HANYA RS=1
		TWDR |= (1<<LCD_EN);  //HANYA EN=1
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
		TWDR &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::i2cwaitTWDRComplete();
		lm016l::Delay();
	}
}
void lm016l::init(LcdPort usingPort){
	if(usingPort == lcdUsingPB){
		DDRB = 0X7F;
		PORTB &= ~(1<<LCD_EN);  //HANYA EN=0

		lm016l::command(0x33);
		lm016l::command(0x32);
		lm016l::command(0x28);  //4-bit mode,2 line
		lm016l::command(0x0c);  //display on,cursor off
		lm016l::command(0x01);  //clear screen lcd
		lm016l::command(0x06);  //cursor geser ke kanan
	}
	if(usingPort == lcdUsingPD){
		DDRD = 0X7F;
		PORTD &= ~(1<<LCD_EN);  //HANYA EN=0

		lm016l::command(0x33);
		lm016l::command(0x32);
		lm016l::command(0x28);  //4-bit mode,2 line
		lm016l::command(0x0c);  //display on,cursor off
		lm016l::command(0x01);  //clear screen lcd
		lm016l::command(0x06);  //cursor geser ke kanan
	 }
}
void lm016l::init(LcdPort usingPort,uint8_t Address){
	if(usingPort == lcdUsingI2C){
		lm016l::i2cInit();
		lm016l::i2cWrite(0X00,Address);
		TWDR &= ~(1<<LCD_EN);  //HANYA EN=0
		lm016l::i2cwaitTWDRComplete();
		
		lm016l::command(0x33);
		lm016l::command(0x32);
		lm016l::command(0x28);  //4-bit mode,2 line
		lm016l::command(0x0c);  //display on,cursor off
		lm016l::command(0x01);  //clear screen lcd
		lm016l::command(0x06);  //cursor geser ke kanan
	}
}

//public method
lm016l::lm016l(LcdPort usingSystem){
	lm016l::port = usingSystem;
	lm016l::init(lm016l::port);	
}
lm016l::lm016l(LcdPort usingSystem,uint8_t Address){
	lm016l::port = usingSystem;
	lm016l::address = Address;
	lm016l::init(lm016l::port,lm016l::address);	
}

void lm016l::clear()
{
	lm016l::command(0x01);  //clear screen lcd
}
void lm016l::location(uint8_t x,uint8_t y)
{
	unsigned char firstCharAdr[] = { 0x80 , 0xC0 , 0x94 , 0xD4 };	
	lm016l::command(firstCharAdr[y]+x);
}
void lm016l::print(const char* str)
{
	unsigned char i=0;
	while(str[i] !=0)
	{
		lm016l::data(str[i]);
		i++;
	}
}
void lm016l::print(uint8_t x,uint8_t y,const char* str){
	lm016l::location(x,y);
	lm016l::print(str);
}
void lm016l::print(int INT){
	lm016l::print(IntegerToString(INT));
}
void lm016l::print(unsigned int UINT){
	lm016l::print(UIntegerToString(UINT));
}
void lm016l::print(long LONG){
	lm016l::print(LongToString(LONG));
}
void lm016l::print(double DOUBLE,Range RANGE){
	lm016l::print(DoubleToString(DOUBLE,RANGE));
}
void lm016l::print(char CHAR){
	lm016l::print(CharToString(CHAR));
}
void lm016l::shiftRight()
{
	lm016l::command(0x1C);      //----Perintah untuk geser kanan
}
void lm016l::shiftLeft()
{
	lm016l::command(0x18);      //----Perintah untuk geser Kiri
}
