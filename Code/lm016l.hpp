/*
 * lm016l.h
 *
 * Created: 02/12/2022 16.41.47
 *  Author: fisikamodern
 */ 


#ifndef LM016L_H_
#define LM016L_H_

#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS 4 //PD4,PB4,P4
#define LCD_RW 5 //PD5,PB5,P5
#define LCD_EN 6 //PD6,PB6,P6
#define SCL_CLOCK  100000

typedef enum{lcdUsingPB,lcdUsingPD,lcdUsingI2C}LcdPort;
typedef enum{RANGE0,RANGE1,RANGE2,RANGE3,RANGE4,RANGE5,RANGE6,RANGE7,RANGE8,RANGE9}Range;

char* IntegerToString(int Value);
char* UIntegerToString(unsigned int Value);
char* LongToString(long Value);
char* DoubleToString(double Value,int Range);
char* CharToString(char c);

class lm016l{
	private:
		LcdPort port;
		unsigned char address;
		
		void i2cwaitTWDRComplete();
		void i2cInit();
		void i2cStart();
		void i2cAddress(unsigned int address);
		void i2cWrite(unsigned int port,unsigned int address);
		
		void Delay();
		void command(unsigned char cmnd);
		void data(unsigned char dataInput);
		void init(LcdPort usingPort);
		void init(LcdPort usingPort,uint8_t Address);
		
	public:
		lm016l(LcdPort usingPort);
		lm016l(LcdPort usingPort,uint8_t Address);
		
		void clear();
		void location(uint8_t x,uint8_t y);
		void print(const char* str);
		void print(uint8_t x,uint8_t y,const char* str);
		void print(int INT);
		void print(unsigned int UINT);
		void print(long LONG);
		void print(double DOUBLE,Range RANGE);
		void print(char CHAR);
		
		void shiftRight();
		void shiftLeft();
};



#endif /* LM016L_H_ */