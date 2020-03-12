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
void delayMultiply(int times);

// is the player currently jumping, 1 is true, 0 is false
int jumping = 0;

// how many frames player can be in the air
int maxJumpFrames = 2;
// how many frames player is in the air
int currentJumpFrame = 0;

// where the obstacle is currently drawn
int obstaclePosition = 0;

// how many obstacles the player has passed
int score = 0;

// slowest possible delay for the obstacle speed increase
int slowest = 50;


// Implementation of the Chrome offline Dino game on Atmel2560
int main(void)
{
	// game board
	DDRA = 0xFF;
	// scoreboard
	DDRB = 0xFF;
	// jump button and indicator
	DDRC = 0x01;
	
	playGameOver(5);
	
    while (1) 
    {
		// increase the obstacle speed every time player score increases
		if (200 - (score * 5) > slowest) {
			delayMultiply(200 - score * 5);
		} else {
			delayMultiply(slowest);
		}
		
		PORTA = 0x00;
		PORTC = 0x00;
		inputLoop();
		drawLoop();
		gameLoop();
	}
		
		
}

// Check for all Inputs
void inputLoop() {
	// Check if the Jump Button is pressed
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

// Enable The Jumping Indicator LED
void setJumping() {
	PORTC = 0x03;
}

// Disable The Jumping Indicator LED
void unsetJumping() {
	PORTC = 0x02;
}

// Play the Game over sequence, length defines the blink count
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


// enable LED on Obstacle Position
void setObstacle(int position) {
	PORTA |= (0x80 >> position);
}


// Delay 1ms in for Loop to work arround the Constant Value needed for _delay_ms()
void delayMultiply(int times) {
	for (int i = 0; i < times; i++) {
		_delay_ms(1);
	}
}