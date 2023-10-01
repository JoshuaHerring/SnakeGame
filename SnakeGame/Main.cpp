/*
Imports in this order 
1. Raylib for drawing
2. raylib math for doing math with vector2d
3. a deque struct which the snake is made out of
*/
#include"raylib.h"
#include"raymath.h"
#include<deque>

// sets up the stl library to use stl structs like deque
using namespace std;

// int used to determine the sizes of the grid cells
int cellSize = 30;
// int used to determine the number of grid cells width and height to have in the grid
int cellCount = 30;

// A bool when set to true will end the game.
bool gameOver = false;
// An int to determine how many times to play the death sound when the game ends. (Leave at one)
int deathSounds = 1;
// An int that is displayed at the top of the screen to keep track of how many apples have been eaten
int Score = 0;










/*The Snake class that that has the methods
draw() to draw the snake to the screen
addSegment() that will extend the length of the snake every time it is called
hitself() that when called checks if the snakes head is hitting it's body and if it is sets the gameOver bool to true
move() which controls the movemnet based on user input
edgeCollision() which checks if the snake has moved off the screen and if it has moves it to the other side
getDirection() which returns the current direction the snake is moving as a Vector2
getSnakeHead() returns the Vector2 coords of the snake head
*/
class Snake {
private:
	// the vector change necesary to go up
	Vector2 up = { 0, -1 };
	// the vector change necesary to go down
	Vector2 down = { 0, 1 };
	// the vector change necesary to go left
	Vector2 left = { -1, 0 };
	// the vector change necesary to go right
	Vector2 right = { 1, 0 };

	// A deque Struct that holds the snake body, starts with 3 body parts at cells 6,7  6,8   6,9
	deque<Vector2> body = { Vector2{6,7}, Vector2{6,8}, Vector2{6,9} };

	// The current direction of the snake
	Vector2 direction = { 1, 0 };

public:

	//Returns the Vector2 of the head of the snake
	Vector2 getSnakeHead() {
		return body[0];
	}

	//Returns the current direction of the snake as a Vector2
	Vector2 getDirection() {
		return direction;
	}

	/* Draws the Snake to the screen*/
	void draw() {

		//lopps through the body and draws a rect at each location
		for (unsigned int i = 0; i < body.size(); i++) {

			float x = body[i].x;
			float y = body[i].y;

			DrawRectangle((int)x * cellSize, (int)y * cellSize, cellSize, cellSize, GREEN);
		}
	}
	// Adds an additional segment to the snake (It originally draws it off the screen to be added by the snakes movement)
	void addSegment() {
		body.push_back(Vector2{100, 100});
	}

	// Checks if the snake has hit itself and if it has sets gameOver to true
	void hitSelf() {
		// Loops through the body and checks if the head is in the same spot as any body part
		for (int i = 1; i <= body.size() - 1; i++) {
			if (Vector2Equals(body[0], body[i])) {
				gameOver = true;
			}
		}
	}

	// Moves the snake according to user input and prevents snake from turning 180 degress and coliding with itself. Keys checked: wasd
	void move() {
		//The first part checks if the key is pressed and the second part checks if it is flipping directions then it changes the direction
		if (IsKeyPressed(KEY_W) && !Vector2Equals(direction, down)) {
			direction = up;
		}
		if (IsKeyPressed(KEY_A) && !Vector2Equals(direction, right)) {
			direction = left;
		}
		if (IsKeyPressed(KEY_D) && !Vector2Equals(direction, left)) {
			direction = right;
		}
		if (IsKeyPressed(KEY_S) && !Vector2Equals(direction, up)) {
			direction = down;
		}
		
		//removes the tail part of the snake
		body.pop_back();
		//adds a new part to the front of the snake. This removal and addition visually mimics the snakes movement acroos the screen.
		body.push_front(Vector2Add(body[0], direction));
	}

	//Checks if the snake has hit the edge of the screen and of it has it moves it to the opposite side.
	void edgeCollision() {

		//Checks if it hit the right side
		if (body[0].x >= cellCount) {
			body[0].x = 0;
		}
		//Checks if it hit the left side
		 if (body[0].x <= -1) {
			body[0].x = (float)cellCount - 1;
		}
		 //Checks if it hit the bottom
		if (body[0].y >= cellCount) {
			body[0].y = 0;
		}
		//Checks if it hit the top
		if (body[0].y <= -1) {
			body[0].y = (float)cellCount - 1;
		}
		
	}
};












/*The Food class that has the methods
setRandCoords() which moves the food to a random spot on the grid
draw() which draws the food to the screen
getCoords() which returns the coords of the food
*/
class Food {
private:
	// The current coords of the food
	Vector2 coords;

public:
	// Initializes the food at a rondom spot
	Food() {
		setRandCoords();
	}

	//Returns the coords of the food as a Vector2
	Vector2 getCoords() {
		return coords;
	}

	// Changes the coords of the food to a random location on the grid
	void setRandCoords() {
		int num1 = rand() % cellCount;
		int num2 = rand() % cellCount;
		coords = { (float)num1, (float)num2 };
	}

	//Draws the food to the grid as a red rectangle
	void draw() {
		DrawRectangle((int)coords.x * cellSize, (int)coords.y * cellSize, cellSize, cellSize, RED);
	}
};












/*Initializes the game (window, audio device) and it loads all the assets (sounds, snake, food)
then it runs the main game loop)
*/
int main() {

	//Sets the spped of the game
	SetTargetFPS(10);
	// initializes the window for the game as a grid that is cellcount wide and tall and each gridcell is equal to cellsize, Names the window "My Snake Game"
	InitWindow(cellSize * cellCount, cellSize * cellCount, "My Snake Game");

	//creates a new instance of Snake
	Snake snake = Snake();
	//Creates a new instance of Food
	Food food = Food();

	//Initializes the audio device to allow playing of sounds and then loads the sound files for eat and death
	InitAudioDevice();
	Sound eat = LoadSound("sounds/eat.mp3");
	Sound death = LoadSound("sounds/death.mp3");
	
	//The main game loop that repeats at a rate of targetFPS and runs until the window is exited by the esc key or clixking the close window buttton in the top right
	while (!WindowShouldClose()) {
		//Starts the drawing process
		BeginDrawing();
		//Clears all previous drawings and turns the background to darkgreen
		ClearBackground(DARKGREEN);

		// Draws the Score keeper at the top of the screen with a dynamic score
		DrawText(TextFormat("Score: %i", Score), 0, 0, 50, WHITE);

		//draws the snake
		snake.draw();
		//Draws the food
		food.draw();
		//moves the snake
		snake.move();

		// Checks if the snake head has hit the food and the game is not over
		if (Vector2Equals(snake.getSnakeHead(), food.getCoords()) && gameOver == false) {
			//Randomizes the location of the food
			food.setRandCoords();
			//adds a segment onto the snake
			snake.addSegment();
			//increments the score
			Score++;
			//Plays the eat soundfile that we loaded previously
			PlaySound(eat);
		}

		//checks if the game is over
		if (gameOver) {
			//Draws "Game Over" onto the screen
			DrawText("Game Over", (cellSize * cellCount) / 5, (cellSize * cellCount) / 3, 100, DARKPURPLE);
			// Checks if the death sound has already played
			if (deathSounds > 0) {
				// Plays the death sound
				PlaySound(death);
				// Tells the game that we just played the death sound
				deathSounds--;
			}
		}

		// Checkls if the snake hit hitself
		snake.hitSelf();
		//Chekcs of the snake has hit the edge of the sceen and moves it tpo the opposite side if it has
		snake.edgeCollision();

		//Ends the current drawing process so we can start a new one in the next iteration of our game loop
		EndDrawing();
	}

	//Closes the window and the audio device and unloads the sound files
	CloseWindow();
	CloseAudioDevice();
	UnloadSound(eat);
	UnloadSound(death);

	//The End
	return 0;
}