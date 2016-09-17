#include<avr/io.h>
void main(){
	DDRD = 0b00000000;    /* Setting Part D as input pin */
	PORTD = 0b11111111;	  /* Pulling up Part D */
	DDRB = 0b11111111;    /* Setting Part B as output pin */
	int c;
	while(1){			  /* Infinite Looping */
		c = PIND;
		if(c==0b11111100){       /*Both sensors LOW*/
			PORTB = 0b00001010;  /*Go Straight*/
		}
		if(c==0b11111110){       /*Left sensor is HIGH*/
			PORTB = 0b00000110;  /*Turn LEFT*/
		}
		if(c==0b11111101){       /*Right sensor is HIGH*/
			PORTB = 0b00001001;  /*Turn RIGHT*/
		}
		if(c==0b11111111){       /*Both sensors are HIGH*/
			PORTB = 0b00011010;  /*Go Straight and Beep*/
		}
	}
}