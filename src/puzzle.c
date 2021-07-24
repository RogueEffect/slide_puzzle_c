
/*

Slide Puzzle

    Simple sliding puzzle to practice C.

rogueeffect

*/

#include <stdio.h>
#include <string.h> 

#define WIDTH   4
#define HEIGHT  4
#define SQUARE_SIZE     2
#define BOARD_WIDTH     (SQUARE_SIZE * WIDTH + 1)
#define BOARD_HEIGHT    (SQUARE_SIZE * HEIGHT + 1)
#define INDENT  4 

char    tiles[WIDTH * HEIGHT];
// This can be the index of the space tile
int     space;

void    init();
void    draw_board();
void    swap(int, int);
int     handle_move(int, int);



int main(int argc, char** argv) {
    printf("Testing moving tiles...\n");
    init();
    draw_board();
    // Here we can test our new functions (check the definitions at the end)
    handle_move(0, -1); // move space up
    draw_board();
    handle_move(-1, 0); // move space left twice
    handle_move(-1, 0);
    draw_board();
    handle_move(0, 1); // move space down
    draw_board();
    handle_move(1, 0); // move space right
    draw_board();
    // Let's test if invalid moves do anything
    if(!handle_move(0, 1)) {
        printf("Invalid move!\n");
    }
    
    printf("done.\n");
}



void init() {
    for(int i = 0; i < WIDTH * HEIGHT - 1; i++) {
        char c = 'A' + i;
        tiles[i] = c;
    }
    
    // Set the location of the space tile (move handling will rely on this)
    space = WIDTH * HEIGHT - 1;
    tiles[space] = ' ';
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
        char indent[INDENT + 1];
        memset(indent, ' ', INDENT);
        indent[INDENT] = '\0';
        printf("%s%s\n", indent, buffer);
    }
    printf("\n");
}

// This function swaps 2 tiles given their indices
void swap(int a, int b) {
    char temp = tiles[a];
    tiles[a] = tiles[b];
    tiles[b] = temp;
}

// Here we take in 2 values representing the delta in x and y directions
// Each of the four moves provides one non-zero value and one zero value but
//   never two non-zeros, or two zeros (that wouldnt even move anything)
int handle_move(int dx, int dy) {
    // Let's assume we will always used this function properly and leave out any
    //   sanity checks about diagonal or useless moves
    int x = space % WIDTH; // Again some math because im using 1d array
    int y = space / WIDTH;
    dx += x;
    dy += y;
    // Let's check that the target x location is valid
    if(dx < 0 || dx >= WIDTH) return 0; // The move failed, warn the user
    // Now the y location
    if(dy < 0 || dy >= HEIGHT) return 0;
    // If we get here the move is valid and we can perform the swap
    swap(space, dx + dy * WIDTH);
    // Then update where the space is
    space = dx + dy * WIDTH;
    // Later we can implement move counting here
    return 1; // Move succeeded
}

// Remember handle move will always take one zero value and one non-zero (1, -1)
//   otherwise the space will make movements that could break the puzzle
// Next we'll have to map the four moves to something the user can type into
//   the console. (Probably WASD since arrow keys cannot be sent to stdin)
