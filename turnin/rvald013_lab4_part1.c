/*	Author: Ryan Valdeavilla
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start, on, onWait, off, offWait} state;
unsigned char btn;
unsigned char light0;
unsigned char light1;

void Tick(){
	btn = PINA & 0x01;
	switch(state){
		case start:
			light0 = 1;
                        light1 = 0;
                        PORTB = (light1 << 1) | light0;
			state = on;
			break;
		case on:
			state = btn ? onWait : on;
			break;
		case onWait:
			state = !btn ? off : onWait;
			break;
		case off:
			state = btn ? offWait : off;
			break;
		case offWait:
			state = !btn ? on : offWait;
			break;
	//	case default:
	//		break;
	}
	switch(state){
		case start:
			break;
		case on:
			break;
		case onWait:
			light0 = 0;
			light1 = 1;
			PORTB = (light1 << 1) | light0;
			break;
		case off:
			break;
		case offWait:
			light0 = 1;
			light1 = 0;
			PORTB = (light1 << 1) | light0;
			break;
	//	case default:
	//		break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
    /* Insert your solution below */
    state = start;
    while (1) {
	Tick();
    }
    return 1;
}
