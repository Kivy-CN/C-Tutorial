#include <ncurses.h> // Include the ncurses library for terminal-based user interfaces
#include <stdlib.h> // Include the standard library for general purpose functions

typedef enum { UP, DOWN, LEFT, RIGHT } Direction; // Define an enumeration for the four possible directions

// Define a struct for the snake
typedef struct Snake {
    int x, y; // The x and y coordinates of the snake
    int speed; // The speed of the snake
    Direction direction; // The direction the snake is moving in
    struct Snake *next; // A pointer to the next segment of the snake
} Snake;

Snake *snake_head; // A pointer to the head of the snake
int score; // The player's score
struct { int x, y; } food; // The x and y coordinates of the food

/**
 * Initializes the game.
 * Sets up the screen, snake, score, and food.
 */
void initialize() {
    initscr(); // Initialize the screen
    cbreak(); // Disable line buffering
    noecho(); // Don't echo user input
    curs_set(0); // Hide the cursor
    keypad(stdscr, TRUE); // Enable special keys
    timeout(300); // Set a timeout for user input

    // Initialize the snake
    snake_head = malloc(sizeof(Snake)); // Allocate memory for the snake
    snake_head->x = COLS / 2; // Set the initial x coordinate of the snake
    snake_head->y = LINES / 2; // Set the initial y coordinate of the snake
    snake_head->speed = 1; // Set the initial speed of the snake
    snake_head->direction = RIGHT; // Set the initial direction of the snake
    snake_head->next = NULL; // The snake has no other segments yet

    score = 0; // Initialize the score
    food.x = rand() % COLS; // Set the initial x coordinate of the food
    food.y = rand() % LINES; // Set the initial y coordinate of the food
}

/**
 * Draws the game screen.
 * Clears the screen, prints the score, snake, and food.
 */
void draw() {
    clear(); // Clear the screen
    mvprintw(0, 0, "Score: %d", score); // Print the score at the top left corner of the screen

    // Print the snake
    Snake *temp = snake_head; // Start with the head of the snake
    while (temp) { // While there are more segments of the snake
        mvprintw(temp->y, temp->x, "O"); // Print the current segment of the snake
        temp = temp->next; // Move on to the next segment of the snake
    }

    mvprintw(food.y, food.x, "X"); // Print the food
    refresh(); // Refresh the screen to show the new state
}

/**
 * Updates the game state.
 * Handles user input, moves the snake, checks for collisions, and updates the score.
 */
void update() {
    int ch = getch(); // Get the user's input
    Snake *new_head = malloc(sizeof(Snake)); // Allocate memory for a new head of the snake
    new_head->next = snake_head; // The new head's next segment is the old head
    new_head->speed = snake_head->speed; // The new head has the same speed as the old head
    new_head->direction = snake_head->direction; // The new head starts off with the same direction as the old head

    // Change the direction of the new head based on the user's input
    if (ch == KEY_LEFT) new_head->direction = LEFT;
    else if (ch == KEY_RIGHT) new_head->direction = RIGHT;
    else if (ch == KEY_UP) new_head->direction = UP;
    else if (ch == KEY_DOWN) new_head->direction = DOWN;

    // Move the new head in the correct direction
    if (new_head->direction == LEFT) new_head->x = snake_head->x - new_head->speed, new_head->y = snake_head->y;
    else if (new_head->direction == RIGHT) new_head->x = snake_head->x + new_head->speed, new_head->y = snake_head->y;
    else if (new_head->direction == UP) new_head->x = snake_head->x, new_head->y = snake_head->y - new_head->speed;
    else if (new_head->direction == DOWN) new_head->x = snake_head->x, new_head->y = snake_head->y + new_head->speed;

    // Check if the new head has collided with the food
    if (new_head->x == food.x && new_head->y == food.y) {
        score++; // Increase the score
        food.x = rand() % COLS; // Move the food to a new random location
        food.y = rand() % LINES; // Move the food to a new random location
        timeout(300 / snake_head->speed); // Decrease the timeout based on the speed of the snake

        // Add a new segment to the tail of the snake
        Snake *temp = snake_head; // Start with the head of the snake
        while (temp->next) temp = temp->next; // Find the tail of the snake
        Snake *new_tail = malloc(sizeof(Snake)); // Allocate memory for a new tail
        new_tail->x = temp->x; // The new tail has the same x coordinate as the old tail
        new_tail->y = temp->y; // The new tail has the same y coordinate as the old tail
        new_tail->next = NULL; // The new tail has no next segment
        temp->next = new_tail; // The old tail's next segment is the new tail
    } else {
        // Remove the tail of the snake
        Snake *temp = snake_head; // Start with the head of the snake
        while (temp->next && temp->next->next) temp = temp->next; // Find the second to last segment of the snake
        if (temp->next) { // If there is a last segment
            free(temp->next); // Free the memory of the last segment
            temp->next = NULL; // The second to last segment is now the last segment
        }
    }

    snake_head = new_head; // The new head is now the head of the snake
}

/**
 * The main function of the game.
 * Initializes the game and runs the game loop.
 */
int main() {
    initialize(); // Initialize the game

    while (1) { // Game loop
        draw(); // Draw the game state
        update(); // Update the game state
    }

    endwin(); // End the window
    return 0; // Exit the program
}