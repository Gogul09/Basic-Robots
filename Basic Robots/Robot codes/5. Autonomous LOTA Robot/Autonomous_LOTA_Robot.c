#include <avr/io.h>
#include <util/delay.h>

void main(){
	DDRD = 0b00000000;       // Part D is the input part that receives the sensor inputs
	DDRB = 0b11111111;		 // Part B is the output part that is used to drive the motors
	PORTD = 0b11111111; 	 // Pulling up all the pins of Part D
	
	init_adc();
	_delay_ms(1000);
	int sensor;				 // Variable to check input values
	
	////////////////////////////////////////////
	// PD0 - Right Bottom Sensor - Line follower
	// PD1 - Left Bottom Sensor - Line follower
	// PD2 - Center Sensor - Obstacle avoider
	// PD3 - Right Sensor - ADC speed control
	///////////////////////////////////////////
	
	while (1) {
		
		sensor = PIND;
		
		// Obstacle has been detected. So, STOP the robot! <----Beep---->
		
		if(sensor == 0b11110000) {         
			PORTB = 0b000100000;            
		}
		if(sensor == 0b11110001) {         
			PORTB = 0b00010000;            
		}
		if(sensor == 0b11110010) {		   
			PORTB = 0b00010000;			   
		}
		if(sensor == 0b11110011) {        
			PORTB = 0b00010000;			  
		}
		
		// Entered into the Cave. So, SLOW DOWN the robot!
		
		if(sensor == 0b11110100) {          
			speed_control();
		}
		if(sensor == 0b11110101) {        
			speed_control_Right();
		}
		if(sensor == 0b11110110) {		   
			speed_control_Left();
		}
		if(sensor == 0b11110111) {    // Marker detected. <----Beep---->
			speed_control_beep();			  
		}
		
		// Obstacle has been detected. So, STOP the robot! <----Beep---->
		
		if(sensor == 0b11111000) {         
			PORTB = 0b00010000;            
		}
		if(sensor == 0b11111001) {         
			PORTB = 0b00010000;            
		}
		if(sensor == 0b11111010) {		   
			PORTB = 0b00010000;			   
		}
		if(sensor == 0b11111011) {        
			PORTB = 0b00010000;			  
		}
		
		// No Obstacle and Cave. Robot should follow the line!
		
		if(sensor == 0b11111100) {         
			PORTB = 0b00001010;            
		}
		if(sensor == 0b11111101) {         
			PORTB = 0b00001001;            
		}
		if(sensor == 0b11111110) {		   
			PORTB = 0b00000110;			   
		}
		if(sensor == 0b11111111) {    // Marker detected. <----Beep---->
			PORTB = 0b00011010;			  
		}
	}
}

////////////////////////////////////////
// ADC based Speed Control functions
////////////////////////////////////////

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

void delay(int n){
	for (int i=0; i<n; i++){
		_delay_ms(i);
	}
}

void speed_control(){
		unsigned int a;
		unsigned int speed;
		unsigned int T;
		unsigned int TON_speed;
		unsigned int TOFF_speed;
		
		speed = read_speed();
		a = (speed/40);
		T = 25.6;
		TON_speed = a;
		TOFF_speed = T - TON_speed;
		
		PORTB = 0b00001010;
		delay(TON_speed);
		PORTB = 0b00000000;
		delay(TOFF_speed);
	
}

void speed_control_Right(){
		unsigned int a;
		unsigned int speed;
		unsigned int T;
		unsigned int TON_speed;
		unsigned int TOFF_speed;
		
		speed = read_speed();
		a = (speed/40);
		T = 25.6;
		TON_speed = a;
		TOFF_speed = T - TON_speed;
		
		PORTB = 0b00001001;
		delay(TON_speed);
		PORTB = 0b00000000;
		delay(TOFF_speed);
	
}
void speed_control_Left(){
		unsigned int a;
		unsigned int speed;
		unsigned int T;
		unsigned int TON_speed;
		unsigned int TOFF_speed;
		
		speed = read_speed();
		a = (speed/40);
		T = 25.6;
		TON_speed = a;
		TOFF_speed = T - TON_speed;
		
		PORTB = 0b00000110;
		delay(TON_speed);
		PORTB = 0b00000000;
		delay(TOFF_speed);
		
	
}
void speed_control_beep(){
		unsigned int a;
		unsigned int speed;
		unsigned int T;
		unsigned int TON_speed;
		unsigned int TOFF_speed;
		
		speed = read_speed();
		a = (speed/40);
		T = 25.6;
		TON_speed = a;
		TOFF_speed = T - TON_speed;
		
		PORTB = 0b00011010;
		delay(TON_speed);
		PORTB = 0b00000000;
		delay(TOFF_speed);
		
	
}
