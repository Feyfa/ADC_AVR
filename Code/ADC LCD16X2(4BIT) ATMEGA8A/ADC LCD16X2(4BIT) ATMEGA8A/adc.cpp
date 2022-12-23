/*
 * adc.cpp
 *
 * Created: 02/12/2022 17.11.12
 *  Author: fisikamodern
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "adc.hpp"

//private method
void adc::init(Pin pin)
{
	DDRC &= ~(pin);//to determine the adc pin used
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);//adc is enabled, using the clock/64 prescaller
}

//public method
adc::adc(Pin pin){
	adc::PIN=pin;
	init(adc::PIN);
}
int adc::getValue()
{
	int adcValue;
	
	ADMUX=(1<<REFS0)|((adc::PIN) & 0X0F);//AVCC as reference voltage, and pin selection for adc reading
	ADCSRA|=(1<<ADSC);//adc reading starts
	while( !(ADCSRA&(1<<ADIF)) );//waiting for the adc reading to finish
	
	adcValue=(int)ADC;
	return adcValue;
}
