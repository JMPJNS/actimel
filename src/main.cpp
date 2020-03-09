/*
 * Lauflicht.cpp
 *
 * Created: 3/6/2020 8:48:22 AM
 * Author : Jonas
 */ 

#define F_CPU 1600000
#include <avr/io.h>
#include <util/delay.h>

void inputLoop();
void drawLoop();
void gameLoop();

void setJumping();
void unsetJumping();

void playGameOver(int length);
void setObstacle(int position);

int jumping = 0;

int maxJumpFrames = 3;
int currentJumpFrame = 0;
int obstaclePosition = 0;
int score = 0;

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0x01;
	
	playGameOver(5);
	
    while (1) 
    {
		_delay_ms(200);
		PORTA = 0x00;
		PORTC = 0x00;
		inputLoop();
		drawLoop();
		gameLoop();
	}
		
		
}

void inputLoop() {
	jumping = ((~PINC) & 0x02) >> 1;
}

void drawLoop() {
	
	// draw Player
	if(jumping && currentJumpFrame < maxJumpFrames) {
		currentJumpFrame++;
		setJumping();
	} else {
		currentJumpFrame = 0;
		unsetJumping();
		PORTA |= 0x01;
	}
	
	// draw Obstacle
	setObstacle(obstaclePosition);
	
	// draw Score
	
	PORTB = score;
}

void gameLoop() {
	if (obstaclePosition < 8) {
		obstaclePosition++;
	} else {
		score++;
		
		// check if player and obstacle collide
		if(PORTC == 0x02) {
			playGameOver(10);
			score = 0;
		}
		obstaclePosition = 0;
	}
}

void setJumping() {
	PORTC = 0x03;
}

void unsetJumping() {
	PORTC = 0x02;
}

void playGameOver(int length) {
	for(int i = 0; i < length; i++) {
		if (i%2) {
			PORTA = 0xFF;
		} else {
			PORTA = 0x00;
		}
		_delay_ms(100);
	}
}

void setObstacle(int position) {
	PORTA |= 0x80 >> position;
}