#include <avr/io.h>
#include <util/delay.h>
void init_adc(){
	ADCSRA = ADCSRA | (0b00000001 << ADEN);
	ADCSRA = ADCSRA | (0b00000001 << ADPS2);
	ADMUX = ADMUX | (0b00000001 << REFS0);
}

unsigned int read_speed(){
	int p = 0b00000000;
	ADMUX = ADMUX | p;
	ADCSRA = ADCSRA | (0b00000001 << ADSC);
	while ((ADCSRA & (0b00000001 << ADIF)) == 0){
	}
	ADCSRA = ADCSRA | 0b00000001 << ADIF;
	return (ADC);
}

/*unsigned int read_direction(){
	int p = 0b00000101;
	ADMUX = ADMUX | p;
	ADCSRA = ADCSRA | (0b00000001 << ADSC);
	while ((ADCSRA & (0b00000001 << ADIF)) == 0){
	}
	ADCSRA = ADCSRA | 0b00000001 << ADIF;
	ADMUX &= 0b11111000;
	return (ADC);
}*/

void delay(int n){
	for (int i=0; i<n; i++){
		_delay_ms(i);
	}
}

void main(){
	DDRB = 0b11111111;
	DDRD = 0b00000000;
	PORTD = 0b11111111;
	init_adc();
	_delay_ms(500);
	unsigned int a;
	unsigned int speed;
	unsigned int direction;
	unsigned int T;
	unsigned int TON_speed;
	unsigned int TOFF_speed;
	int c;
	while(1){
		c = PIND;
		speed = read_speed();
		//direction = read_direction();
		a = (speed/40);
		T = 25.6;
		TON_speed = a;
		TOFF_speed = T - TON_speed;
		
		if( c == 0b11110100){
			if(speed > 256 || speed < 500){
				PORTB = 0b00001010;
				delay(TON_speed);
				PORTB = 0b00000000;
				delay(TOFF_speed);
			}
		}
		else {
				PORTB = 0b00001010;
		}
		
	}
}