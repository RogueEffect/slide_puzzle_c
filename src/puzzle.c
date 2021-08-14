
/*

Slide Puzzle

    Simple sliding puzzle to practice C.

rogueeffect

*/

#include <stdio.h>
#include <stdlib.h> // For rand and srand
#include <string.h>
#include <time.h> // For time function

#define WIDTH   4
#define HEIGHT  4
#define SQUARE_SIZE     2
#define BOARD_WIDTH     (SQUARE_SIZE * WIDTH + 1)
#define BOARD_HEIGHT    (SQUARE_SIZE * HEIGHT + 1)
// I originally wanted to make the indent change depending on the board size
#define INDENT  "    " // but I'm changing this to a static string instead
// Macro to generate a random number from 0 to max - 1
#define randint(max)    (rand() % max)

char    tiles[WIDTH * HEIGHT];

int     space;
int     moves;

void    init();
void    draw_board();
void    swap(int, int);
int     handle_move(int, int);
void    shuffle_board();
int     game_loop();
void    clear_input();



int main(int argc, char** argv) {
    // Seed random number generator
    srand(time(0));
    
    printf("Testing user input...\n");
    init();
    // Run the game loop until it returns false
    while(game_loop());
    
    printf("done.\n");
}



void init() {
    for(int i = 0; i < WIDTH * HEIGHT - 1; i++) {
        char c = 'A' + i;
        tiles[i] = c;
    }
    
    space = WIDTH * HEIGHT - 1;
    tiles[space] = ' ';
    shuffle_board();
    // Make sure to do this after we shuffle since that will increment the
    moves = 0; // move counter when we shuffle
}

void draw_board() {
    printf("\n");
    for(int y = 0; y < BOARD_HEIGHT; y++) {
        char buffer[BOARD_WIDTH + 1];
        for(int x = 0; x < BOARD_WIDTH; x++) {
            char c = ' ';
            if(y % SQUARE_SIZE == 0) c = '-';
            else if(x % SQUARE_SIZE == 0) c = '|';
            if(x % SQUARE_SIZE == 1 && y % SQUARE_SIZE == 1) {
                int tx = x / SQUARE_SIZE;
                int ty = y / SQUARE_SIZE;
                c = tiles[tx + ty * WIDTH];
            }
            buffer[x] = c;
        }
        buffer[BOARD_WIDTH] = '\0';
        // changed the indent here
        printf("%s%s\n", INDENT, buffer);
    }
    printf("\n");
}

void swap(int a, int b) {
    char temp = tiles[a];
    tiles[a] = tiles[b];
    tiles[b] = temp;
}

int handle_move(int dx, int dy) {
    int x = space % WIDTH;
    int y = space / WIDTH;
    dx += x;
    dy += y;
   
    if(dx < 0 || dx >= WIDTH) return 0;
    if(dy < 0 || dy >= HEIGHT) return 0;
   
    swap(space, dx + dy * WIDTH);
    space = dx + dy * WIDTH;
    moves++; // Only increment move counter on a valid move
    return 1;
}

// Shuffle the board by doing random moves
void shuffle_board() {
    // We'll base the amount of moves on the size of the board
    int target = WIDTH * HEIGHT * 20;
    int dx, dy;
    while(target > 0) {
        // Pick a random number from 0 - 3. We'll set up dx and dy to handle
        //   one of the four directions
        switch(randint(4)) {
            case 0: // Up
                dx = 0;
                dy = -1;
                break;
            case 1: // Down
                dx = 0;
                dy = 1;
                break;
            case 2: // Left
                dx = -1;
                dy = 0;
                break;
            case 3: // Right
                dx = 1;
                dy = 0;
                break;
        }
        // Only count down if the move is valid
        if(handle_move(dx, dy)) target--;
    }
    // Next time we should make sure the shuffle didnt solve itself here
}

// Draw the board and ask for user input
int game_loop() {
    draw_board();
    // We should check here for the win condition
    // Print an indent then the amount of moves then a prompt for input
    //   the %-4d specifier will print a number left justified with a width
    //   of 4. This means if the number is less than 4 digits wide it will
    //   add spaces to make it 4 wide
    printf("%s%-4d > ", INDENT, moves);
    char c = fgetc(stdin);
    clear_input();
    int valid = 0;
    switch(c) {
        // In a switch statement we can use multiple cases to do the same
        //   thing if we place them one after another like this
        case 'w':
        case 'W':
            valid = handle_move(0, -1);
            break;
        case 's':
        case 'S':
            valid = handle_move(0, 1);
            break;
        case 'a':
        case 'A':
            valid = handle_move(-1, 0);
            break;
        case 'd':
        case 'D':
            valid = handle_move(1, 0);
            break;
        case 'q':
        case 'Q':
            // End the game
            return 0;
        default:
            // if we get here the user entered an invalid char
            printf("%sInvalid input!\n", INDENT);
            // return early since we didnt specify a move;
            return 1;
    }
    if(!valid) printf("%sInvalid move!\n", INDENT);
    return 1;
}

// We need this to clear out the input buffer if the user enters more characters
//   than we need. Otherwise further reading from stdin will use the excess
//   characters instead of asking for input again
void clear_input() {
    char c;
    while(( c = fgetc(stdin)) != '\n' && c != EOF);
}

// Now the player can actually move pieces around the board and quit the game
// Next time we'll add a way to check the win condition and test out a larger
//   square size
