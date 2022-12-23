/*
 * ADC LCD16X2(4BIT) ATMEGA8A.cpp
 *
 * Created: 23/12/2022 14.02.46
 * Author : fisikamodern
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "adc.hpp"
#include "lm016l.hpp"
#define F_CPU 8000000

int main(void)
{
	lm016l lcd = lm016l(usingPB);//lcd using in PB
	adc adc0 = adc(P0);//object adc0 uses on pin PC0
	adc adc1 = adc(P1);//object adc1 uses on pin PC1
    while (1) 
    {
		lcd.location(0,0);//set lcd location at x=0 , y=0
		lcd.print("ADC0=");//write "ADC0=" to lcd
		lcd.print(adc0.getValue());//write the result of adc0.getValue() to lcd
		lcd.print(" ");//write space
		
		lcd.location(0,1);//set lcd location at x=0 , y=0
		lcd.print("ADC1=");//write "ADC0=" to lcd
		lcd.print(adc1.getValue());//write the result of adc0.getValue() to lcd
		lcd.print(" ");//write space
		
		_delay_ms(100);//pause for 100 milliseconds
    }
}

