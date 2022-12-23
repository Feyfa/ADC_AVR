/*
 * adc.h
 *
 * Created: 02/12/2022 17.11.01
 *  Author: fisikamodern
 */ 


#ifndef ADC_H_
#define ADC_H_

typedef enum{P0,P1,P2,P3,P4,P5,P6,P7}Pin;

class adc{
	private:
		Pin PIN;
		void init(Pin pin);
		
	public:
		adc(Pin pin);
		int getValue();	
};



#endif /* ADC_H_ */