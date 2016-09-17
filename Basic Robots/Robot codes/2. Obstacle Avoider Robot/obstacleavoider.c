#include<avr/io.h>
#include<util/delay.h>
void main(){
	DDRD = 0b00000000;             //setting part D as an input part
	PORTD = 0b11111111;            //Pulling up all the pins of part D
	DDRB = 0b11111111;             //setting part B as an input part
	int c;
	while(1){
		c = PIND;
		if(c==0b11111111){		   //No obstacle	
			PORTB = 0b00001010 ;  //Forward
		}
		if(c==0b11111110){       //Obstacle to the right
			PORTB = 0b00000110 ; //Turn Left
		}
		if(c==0b11111101){       //Obstacle at the centre
			PORTB = 0b00000101 ; //Go back and take right
			_delay_ms(500);
			PORTB = 0b00001001 ; 
			_delay_ms(500);
		}
		if(c==0b11111100){       //obstacle to the centre and right
			PORTB = 0b00000101 ; //Go back and take left 
			_delay_ms(500);
			PORTB = 0b00000110 ; 
			_delay_ms(500);
		}
		if(c==0b11111011){       //Obstacle to the left
			PORTB = 0b00001001 ; //Turn right
		}
		if(c==0b11111010){       //Obstacle on both sides of the robot
			PORTB = 0b00000101 ; //Go back and turn right
			_delay_ms(500);
			PORTB = 0b00001001 ; 
			_delay_ms(500);
		}
		if(c==0b11111001){      //obstacle on the centre and left
			PORTB = 0b00000101 ;//Go back and turn right
			_delay_ms(500);
			PORTB = 0b00001001 ; 
			_delay_ms(500);
		}
		if(c==0b11111000){    //Obstacles on all the sides
			PORTB = 0b00000101 ; //U turn
			_delay_ms(500);
			PORTB = 0b00001001 ; 
			_delay_ms(1035);
		}
	}
}